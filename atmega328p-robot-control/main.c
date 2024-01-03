#ifndef F_CPU  
#define F_CPU   (16000000UL)
#endif


#include <avr/io.h>
#include <util/delay.h>

#include "inc/motors.h"
#include "inc/wire.h"
#include "inc/lcd.h"
#include "inc/ds18b20.h"


int main(void) {
   DRV8835_init();
   PWM_init();
   PWM_set_duty_cycle(60);

    while(1) {
        robot_move_forward();
        _delay_ms(500);
        robot_move_backward();
        _delay_ms(500);
        robot_turn_right();
        _delay_ms(500);
        robot_turn_left();
        _delay_ms(500);
        robot_stop();
        _delay_ms(500);
    }
    return 0;
}

