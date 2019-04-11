# 16 PWM channels on a STM32F103C8 ("Blue Pill")
  
Timers 1 to 4 are configured to generate 4 PWM channels each. No soft-PWM.  

## Pins
These are the pins used by this setup:
```
TIM1_CH1-TIM1_CH4 = PA8, PA9, PA10, PA11         (5V tolerant)  
TIM2_CH1-TIM2_CH4 = PA0, PA1, PA2, PA3     (*not* 5V tolerant)
TIM3_CH1-TIM3_CH4 = PA6, PA7, PB0, PB1     (*not* 5V tolerant)
TIM4_CH1-TIM4_CH4 = PB6, PB7, PB8, PB9           (5V tolerant)
```
Be careful with those NOT 5V tolerant pins. If you connect a 5V operated buffer/driver, that has pullups
on it's inputs you could ruin your microcontroller. In case you're looking for a easy-to-use buffer,
I suggest `ULN2803`. Two of these will buffer all PWM channels with a darlington-transistor per channel.
  

## Requirements
You will need a suitable arm-gcc for building and texane's st-link utility for flashing.  
If you're using ARM's official gcc distribution everything will be fine.
  
libopencm3 is included in this archive.  

## Compiling
```
$ make
```
This will build libopencm3 and the PWM-code. It will generate an ELF, a BIN and a HEX binary.

## libopencm3
There is a "static" copy of libopencm3 in `src/` unlike other examples and tutorials on the internet,
which use a git submodule to allow automatic updating of libopencm3.  
I prefer *not* to update a project's library once it is working, as it could break things.  
Once you're done and your device is running the working firmware you really should keep a exact copy
of your sourcecode.  
Updating is a good thing, but only if you know what you're doing and in this case, only if needed.  
  
I have removed a lot of stuff from libopencm3's source directory which targets other MCUs.

## Licensing
libopencm3 is GNU LGPL v3.  
Makefile and demo-code written by me is 'public domain'.  

