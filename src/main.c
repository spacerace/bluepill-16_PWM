/* 16 PWM channels on a blue pill (STM32F103C8)
 * 
 * Licenseing: This is public domain code.
 * (2019 Nils Stec)
 * 
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/timer.h>
#include "random.h"
#include "systick.h"
#include "pwm.h"

const uint16_t pwmtable_10[64] =
{
    0, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 10,
    11, 12, 13, 15, 17, 19, 21, 23, 26, 29, 32, 36, 40, 44, 49, 55,
    61, 68, 76, 85, 94, 105, 117, 131, 146, 162, 181, 202, 225, 250,
    279, 311, 346, 386, 430, 479, 534, 595, 663, 739, 824, 918, 1023
};
 
const uint16_t pwmtable_16[256] =
{
    0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3,
    3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7,
    7, 7, 8, 8, 8, 9, 9, 10, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15,
    15, 16, 17, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    31, 32, 33, 35, 36, 38, 40, 41, 43, 45, 47, 49, 52, 54, 56, 59,
    61, 64, 67, 70, 73, 76, 79, 83, 87, 91, 95, 99, 103, 108, 112,
    117, 123, 128, 134, 140, 146, 152, 159, 166, 173, 181, 189, 197,
    206, 215, 225, 235, 245, 256, 267, 279, 292, 304, 318, 332, 347,
    362, 378, 395, 412, 431, 450, 470, 490, 512, 535, 558, 583, 609,
    636, 664, 693, 724, 756, 790, 825, 861, 899, 939, 981, 1024, 1069,
    1117, 1166, 1218, 1272, 1328, 1387, 1448, 1512, 1579, 1649, 1722,
    1798, 1878, 1961, 2048, 2139, 2233, 2332, 2435, 2543, 2656, 2773,
    2896, 3025, 3158, 3298, 3444, 3597, 3756, 3922, 4096, 4277, 4467,
    4664, 4871, 5087, 5312, 5547, 5793, 6049, 6317, 6596, 6889, 7194,
    7512, 7845, 8192, 8555, 8933, 9329, 9742, 10173, 10624, 11094,
    11585, 12098, 12634, 13193, 13777, 14387, 15024, 15689, 16384,
    17109, 17867, 18658, 19484, 20346, 21247, 22188, 23170, 24196,
    25267, 26386, 27554, 28774, 30048, 31378, 32768, 34218, 35733,
    37315, 38967, 40693, 42494, 44376, 46340, 48392, 50534, 52772,
    55108, 57548, 60096, 62757, 65535
};

int main(void) {
	uint32_t rndval;

    rcc_clock_setup_in_hse_8mhz_out_72mhz();

    init_systick();

    init_pwm_TIM1();
    init_pwm_TIM2();
    init_pwm_TIM3();
    init_pwm_TIM4();
    
    rndval = 0;
    int i;
    for(;;) {
		/* available channels: TIM_CCR1(TIM1...TIM4)
		 *                     TIM_CCR2(..
		 */
		
		
		/* this one is configured to take a 16bit value for duty cycle.
		 * (0-0xFFFF)
		 * this takes a LOT of timer ticks. Max. PWM frequency on a 72MHz
		 * device is 1.01kHz
		 */
		TIM_CCR1(TIM1) = 0x2FFF;	// PA8
		TIM_CCR2(TIM1) = 0xFFFE;	// PA9
		
		
		
		/* generates a 50:50 clock signal of 1MHz for some peripherials */
		TIM_CCR1(TIM3) = 35;	// PA6
		
		/* this one is configured to take 10bit value for duty cycle (0-1023).
		 * 
		 * PWM frequency is good for LED dimming, ~4.14kHz
		 */
		TIM_CCR1(TIM4) = 128;
        TIM_CCR2(TIM4) = 256;
        TIM_CCR3(TIM4) = 384;
        TIM_CCR4(TIM4) = 512;
		
		_systick_delay(75);
	}
    


    return 0;
}



