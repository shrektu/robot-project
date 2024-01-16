#ifndef F_CPU  
#define F_CPU   (16000000UL)
#endif


#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "inc/motors.h"
#include "inc/lcd.h"
#include "inc/adc.h"
#include "inc/usart.h"
#include "inc/HC-SR04.h"


/* Macro definitions for commands received by USART */

#define STOP                (48)
#define FORWARD             (49)
#define LEFT                (51)
#define RIGHT               (52)
#define BACK                (50)
#define VIEW_TEMP           (53)
#define VIEW_PWM            (54)
#define VIEW_DISTANCE       (55)


/* Static functions for main */

// This function initialises Timer2
static void timer2_init(void); 


// This function reads ADC value from potentiometer
static void read_potentiometer(void);

// This function reads ADC value from LM35DZ temperature sensor
static void read_lm35(void);


// This function shows the temperature on the LCD
static void show_temp(void);  

// This function shows the current PWM duty cycle on the LCD                          
static void show_pwm_duty_cycle(void);  

// This function shows the distance to the obstacle on the LCD               
static void show_distance(void);

// This function refreshes the current LCD view
static void refresh_view(uint8_t current_view);  

// This function handles command received from USART 
static void handle_command(uint8_t cmd);


/* Static variables global to main */

static volatile uint16_t echo_width = 0;
static volatile uint8_t echo_flag = 0;

static volatile uint16_t adc_channel0_value = 0;
static volatile uint16_t adc_channel1_value = 0;

static volatile uint16_t distance = 0;

static volatile uint8_t timer = 1;

static volatile uint8_t rx_usart_data = STOP;
static volatile uint8_t current_view = VIEW_PWM;


int main(void) {

    lcd_init();
    DRV8835_init();
    PWM_init();
    HCSR04_init();
    ADC_init();
    USART_init();
    timer2_init();

    sei();

    while(1) { 
    }

    return EXIT_SUCCESS;
}


static void timer2_init(void) {
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;  

    OCR2A = 255;

    TCCR2B |= ((1 << CS20) | (1 << CS21) | (1 << CS22));  // set prescaler to 1024
    TIMSK2 |= (1 << OCIE2A);
}

static void read_potentiometer(void) {
    // set ADMUX to read channel 0
    ADMUX &= ~(1 << MUX0);

    ADC_start_conversion();
}

static void read_lm35(void) {
    // set ADMUX to read channel 1
    ADMUX |= (1 << MUX0);

    ADC_start_conversion();
}

static uint8_t calc_distance(uint16_t pulse_duration) {
    return pulse_duration / 58;
}

static void show_temp(void) {
    lcd_clear();
    lcd_go_to(0, 0);
    lcd_print_text("Temperature:");
    lcd_go_to(0, 1);
    lcd_printf("%u *C", (uint32_t)adc_channel1_value * 5 * 100 / 1024);
}

static void show_pwm_duty_cycle(void) {
    lcd_clear();
    lcd_go_to(0, 0);
    lcd_print_text("PWM duty cycle:");
    lcd_go_to(0, 1);
    lcd_printf("%u %%", (uint32_t)adc_channel0_value * 100 / 1024);
}

static void show_distance(void) {
    lcd_clear();
    lcd_go_to(0, 0);
    lcd_print_text("Distance:");
    lcd_go_to(0, 1);
    distance = (echo_width + 29) / 58;
    if (distance > 100) {
        lcd_print_text("100+ cm");
    } else {
        lcd_printf("%d cm", distance);
    }
}

static void refresh_view(uint8_t current_view) {
    if (current_view == VIEW_TEMP) {
        show_temp();
    } else if (current_view == VIEW_PWM) {
        show_pwm_duty_cycle();
    } else if (current_view == VIEW_DISTANCE) {
        show_distance();
    }
}

static void handle_command(uint8_t cmd) {
    switch (cmd) {
        case FORWARD:
        robot_move_forward();
        break;
    case BACK:
        robot_move_backward();
        break;
    case LEFT:
        robot_turn_left();
        break;
    case RIGHT:
        robot_turn_right();
        break;
    case VIEW_TEMP:
        show_temp();
        current_view = VIEW_TEMP;
        break;
    case VIEW_PWM:
        show_pwm_duty_cycle();
        current_view = VIEW_PWM;
        break;
    case VIEW_DISTANCE:
        show_distance();
        current_view = VIEW_DISTANCE;
        break;
    case STOP:
        robot_stop();
        break;
    default:
        robot_stop();
        break;
    }
}

ISR(TIMER2_COMPA_vect) {
    if (timer == 4) {
        read_potentiometer();
    } else if (timer == 5) {
        HCSR04_start_measurement();
    } else if (timer == 6) {
        refresh_view(current_view);
    } else if (timer == 10) {
        read_lm35();
    }

    timer++;
    if (timer > 10) {
        timer = 1;
    }  
}

ISR(ADC_vect) {
    // check which channel is read
    if (ADMUX & (1 << MUX0)) {
        adc_channel1_value = ADC;
    } else {
        adc_channel0_value = ADC;
        PWM_set_duty_cycle(adc_channel0_value);
    }
}

ISR(USART_RX_vect) {
    rx_usart_data = UDR0;
    handle_command(rx_usart_data);
}

ISR(TIMER1_CAPT_vect) {
    static uint16_t last_capture;

    if (!(TCCR1B & (1 << ICES1))) {
        echo_width = ICR1 / 2 - last_capture;     // Timer1 prescaler is 8, F_CPU is 16M so timer1 frequency is 2MHz. 
                                                    // Division by 2 makes it 1 MHz - 1us
        echo_flag = 1;
    }
    
    last_capture = ICR1 / 2;
    // change interrupt trigger to the other edge
    TCCR1B ^= (1 << ICES1);
}
