#include "../../include/hui/button_irq.hpp"

namespace qymos
{
    namespace hui
    {
        volatile uint32_t ButtonIrq::_irqInputMs = 0;
        Button *ButtonIrq::_first = nullptr;

        void ButtonIrq::Process()
        {
            Button *button = _first;
            while (button != nullptr)
            {
                if (button->_isIrq && HAL_GPIO_ReadPin(button->port, button->pin) == button->edge)
                {
                    if (HAL_GetTick() - button->_elapsedIrq < button->longClickMs)
                        button->OnClick(button->port, button->pin, (bool)HAL_GPIO_ReadPin(button->port, button->pin));
                    else
                        button->OnLongClick(button->port, button->pin, (bool)HAL_GPIO_ReadPin(button->port, button->pin));

                    button->_elapsedIrq = 0;
                    button->_isIrq = false;
                }
                button = button->_next;
            }
        }

        void ButtonIrq::Add(Button *button)
        {
            if (_first == nullptr)
            {
                _first = button;
                return;
            }
            Button *next = _first;
            while (next->_next != nullptr)
                next = next->_next;
            next->_next = button;
        }

        void ButtonIrq::Irq(uint16_t gpio)
        {
            Button *button = _first;
            while (button != nullptr)
            {
                if (button->pin == gpio)
                {
                    button->_elapsedIrq = HAL_GetTick();
                    button->_isIrq = true;
                }
                button = button->_next;
            }
        }
    } // namespace hui

} // namespace qymos
