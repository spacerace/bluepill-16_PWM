#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/timer.h>
#include "pwm.h"

void init_pwm_TIM1(void) {
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_TIM1);
	
    //TIM1 CH1-CH4
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO8);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO9);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO10);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO11);
    
	timer_reset(TIM1);
	
    // timer mode: no divider (72MHz), edge aligned, upcounting
	timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	
    // timer speed before prescaler = 72MHz
    timer_set_prescaler(TIM1, 0);
    timer_set_period(TIM1, 0xFFFF-1);
    
    // PWM mode 1 (output high if CNT > CCR1)
	timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM1, TIM_OC2, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM1, TIM_OC4, TIM_OCM_PWM1);
    
    timer_enable_oc_preload(TIM1, TIM_OC1);
    timer_enable_oc_preload(TIM1, TIM_OC2);
    timer_enable_oc_preload(TIM1, TIM_OC3);
    timer_enable_oc_preload(TIM1, TIM_OC4);
    timer_enable_preload(TIM1);  

    timer_enable_break_main_output(TIM1);

    timer_enable_oc_output(TIM1, TIM_OC1);
    timer_enable_oc_output(TIM1, TIM_OC2);
    timer_enable_oc_output(TIM1, TIM_OC3);
    timer_enable_oc_output(TIM1, TIM_OC4);
    
    timer_enable_counter(TIM1);
	
    return;	    
}

void init_pwm_TIM2(void) {
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_TIM2);

    //TIM2 CH1-CH4
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO0);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO1);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO2);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO3);

	timer_reset(TIM2);

    // timer mode: no divider (72MHz), edge aligned, upcounting
	timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    // timer speed before prescaler = 72MHz
    // after prescaler = 1MHz
    timer_set_prescaler(TIM2, 72-1);

    
    // 1khz PWM
    timer_set_period(TIM2, 1000-1);

    // PWM mode 1 (output high if CNT > CCR1)
	timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM2, TIM_OC2, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM2, TIM_OC3, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM2, TIM_OC4, TIM_OCM_PWM1);

    timer_enable_oc_preload(TIM2, TIM_OC1);
    timer_enable_oc_preload(TIM2, TIM_OC2);
    timer_enable_oc_preload(TIM2, TIM_OC3);
    timer_enable_oc_preload(TIM2, TIM_OC4);
    timer_enable_preload(TIM2);  

    timer_enable_oc_output(TIM2, TIM_OC1);
    timer_enable_oc_output(TIM2, TIM_OC2);
    timer_enable_oc_output(TIM2, TIM_OC3);
    timer_enable_oc_output(TIM2, TIM_OC4);

	timer_enable_counter(TIM2);

    return;	    
}

void init_pwm_TIM3(void) {
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_TIM3);

	//TIM3 CH1-CH4
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO6);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO7);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO0);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO1);

	timer_reset(TIM3);

    // timer mode: no divider (72MHz), edge aligned, upcounting
    timer_set_mode(TIM3, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    // timer speed before prescaler = 72MHz

    timer_set_prescaler(TIM3, 0);

    timer_set_period(TIM3, 71-1);

    // PWM mode 1 (output high if CNT > CCR1)
	timer_set_oc_mode(TIM3, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM3, TIM_OC2, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM3, TIM_OC3, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM3, TIM_OC4, TIM_OCM_PWM1); 

    timer_enable_oc_preload(TIM3, TIM_OC1);
    timer_enable_oc_preload(TIM3, TIM_OC2);
    timer_enable_oc_preload(TIM3, TIM_OC3);
    timer_enable_oc_preload(TIM3, TIM_OC4);
    timer_enable_preload(TIM3);  
    
    timer_enable_oc_output(TIM3, TIM_OC1);
    timer_enable_oc_output(TIM3, TIM_OC2);
    timer_enable_oc_output(TIM3, TIM_OC3);
    timer_enable_oc_output(TIM3, TIM_OC4);
    
	timer_enable_counter(TIM3);
    return;	
}

void init_pwm_TIM4(void) {
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_TIM4);

	//TIM4 CH1-CH4
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO6);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO7);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO8);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO9);

	timer_reset(TIM4);

    // timer mode: no divider (72MHz), edge aligned, upcounting
    timer_set_mode(TIM4, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    timer_set_prescaler(TIM4, 16);
    timer_set_period(TIM4, 1023-1);

    // PWM mode 1 (output high if CNT > CCR1)
	timer_set_oc_mode(TIM4, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM4, TIM_OC2, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM4, TIM_OC3, TIM_OCM_PWM1);
    timer_set_oc_mode(TIM4, TIM_OC4, TIM_OCM_PWM1);

	timer_enable_oc_preload(TIM4, TIM_OC1);
    timer_enable_oc_preload(TIM4, TIM_OC2);
    timer_enable_oc_preload(TIM4, TIM_OC3);
    timer_enable_oc_preload(TIM4, TIM_OC4);
    timer_enable_preload(TIM4);  

    timer_enable_oc_output(TIM4, TIM_OC1);
    timer_enable_oc_output(TIM4, TIM_OC2);
    timer_enable_oc_output(TIM4, TIM_OC3);
    timer_enable_oc_output(TIM4, TIM_OC4);

	timer_enable_counter(TIM4);
    return;	    
}
