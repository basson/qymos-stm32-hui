#pragma once

#include "stdint.h"
#include "stdio.h"
#include "stm32f1xx_hal.h"

namespace qymos
{
    namespace hui
    {
        struct Button
        {
            GPIO_TypeDef *port;
            uint16_t pin;
            volatile uint16_t longClickMs;
            bool edge = false;
            void (*OnClick)(GPIO_TypeDef *port, uint16_t pin, bool state);
            void (*OnLongClick)(GPIO_TypeDef *port, uint16_t pin, bool state);

            /*This is private variable, do not use*/
            volatile bool _isIrq = false;
            volatile uint32_t _elapsedIrq = 0;
            Button *_next = nullptr;
        };


    } // namespace hui

} // namespace qymos
