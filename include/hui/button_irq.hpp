#pragma once

#include "stdint.h"

#include "stm32f1xx_hal.h"

#include "button.hpp"

namespace qymos
{
    namespace hui
    {
        class ButtonIrq
        {
        private:
            static volatile uint32_t _noizeFilterMs;
            static Button *_first;
        public:
            void Process();
            
            void Add(Button *button);

            static void Irq(uint16_t gpio);
        };

    } // namespace hui

} // namespace qymos
