#ifndef F_CPU  
#define F_CPU   (16000000UL)
#endif


#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "inc/motors.h"
#include "inc/lcd.h"
#include "inc/adc.h"
#include "inc/usart.h"
#include "inc/HC-SR04.h"


#define LCD_FUNCTIONS_CNT       (3)  // Number of LCD functions
#define MOTORS_FUNCTIONS_CNT     (5)  // Number of motor functions


// This function initialises Timer2
static void timer2_init(void); 


// This function reads ADC value from potentiometer
static void read_potentiometer(void);

// This function reads ADC value from LM35DZ temperature sensor
static void read_lm35(void);

// This function calculates distance in cm based on pulse duration
static uint8_t calc_distance(uint16_t pulse_duration);


// This function shows the temperature on the LCD
static void show_temp(void);  

// This function shows the current PWM duty cycle on the LCD                          
static void show_pwm_duty_cycle(void);  

// This function shows the distance to the obstacle on the LCD               
static void show_distance(void);       


// Array of function pointers to each lcd function
static void (*lcd_functions[LCD_FUNCTIONS_CNT])(void) = {
    show_temp,
    show_pwm_duty_cycle,
    show_distance
};

// Array of function pointers to each motors function
static void (*motors_functions[MOTORS_FUNCTIONS_CNT])(void) = {
    robot_stop,
    robot_move_forward,
    robot_move_backward,
    robot_turn_left,
    robot_turn_right
};


// Enumeration type to index functions in the lcd functions array
typedef enum {
    SHOW_TEMP,
    SHOW_PWM_DUTY_CYCLE,
    SHOW_DISTANCE
}LCD_FUNCTION_t;

// Enumeration type to index functions in the motor functions array
typedef enum {
    STOP,
    GO_FORWARD,
    GO_LEFT,
    GO_RIGHT,
    GO_BACK,
}MOTOR_FUNCTION_t;


static volatile uint16_t adc_channel0_value = 0;
static volatile uint16_t adc_channel1_value = 0;

static volatile uint8_t duty_cycle_percent = 0;
static volatile uint8_t distance = 0;

static volatile LCD_FUNCTION_t current_lcd_function = SHOW_TEMP;
static volatile MOTOR_FUNCTION_t current_motors_function = STOP;


int main(void) {
    lcd_init();
    ADC_init();
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
    ADMUX &= ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);

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
    lcd_go_to(0, 0);
    lcd_print_text("Temperature:");
    lcd_go_to(0, 1);
    lcd_printf("%u *C", adc_channel1_value * 5 * 100 / 1024);
}

static void show_pwm_duty_cycle(void) {
    lcd_go_to(0, 0);
    lcd_print_text("PWM duty cycle:");
    lcd_go_to(0, 1);
    lcd_printf("%d %%", (uint32_t)adc_channel0_value * 100 / 1024);
}

static void show_distance(void) {
    lcd_go_to(0, 0);
    lcd_print_text("Distance:");
    lcd_go_to(0, 1);
    lcd_printf("%u cm", distance);
}

ISR(TIMER2_COMPA_vect) {
    read_potentiometer();
    lcd_clear();
    show_pwm_duty_cycle();
}

ISR(ADC_vect) {
    // check which channel is read
    if (ADMUX & (1 << MUX0)) {
        adc_channel1_value = ADC;
    } else {
        adc_channel0_value = ADC;
    }
}

ISR(USART_RX_vect) {
    if (UDR0 != 0xFF) {
        uint8_t received_command = UDR0;
    }
}
