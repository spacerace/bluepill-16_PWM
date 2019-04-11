#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/timer.h>
#include "random.h"

static volatile uint32_t _ticks_ms = 0;

int _systick_delay(unsigned int ms) {
    uint32_t end = _ticks_ms + ms;
    while(_ticks_ms < end) {
        __asm__("nop");
    }
    
    return 0;
}

void sys_tick_handler(void) {
    _ticks_ms++;
}
void init_systick(void) {
   /*
    * SysTick timer calculation:
    *   We have configured system clock to 72MHz in main. This sets AHB to
    *   clock to 72MHz.
    *   We use a prescaler of 8 for the systick interrupt.
    * 
    *    clocksource = AHB 72MHz / prescaler 8 = 9MHz
    *    => 9000 ticks per seconds
    * 
    *    we set a reload value of 9000. This gives a 1mS SysTick interrupt.
    *    1s / 1000 = 1mS
    *    => 9000000 / 10 = 9000 ticks for 1mS 
    */

    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
    systick_set_reload(9000);
    systick_counter_enable();
    nvic_set_priority(NVIC_SYSTICK_IRQ, 0);
    systick_interrupt_enable();
    
    return;
}
