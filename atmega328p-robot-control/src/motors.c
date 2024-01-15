#include "../inc/motors.h"
#include "../inc/adc.h"

#include <avr/interrupt.h>


#define MOTOR_SIDE_RIGHT        (RIGHT_MOTOR_ENABLE)
#define MOTOR_SIDE_LEFT         (LEFT_MOTOR_ENABLE)

#define DIRECTION_BACKWARD      (1U)
#define DIRECTION_FORWARD       (0U)




/* Static helper functions */

static void right_motor_spin(uint8_t direction) {
    TCCR0A |= (1 << COM0A1);

    if (direction == DIRECTION_FORWARD) {
        PORTD &= ~(1 << RIGHT_MOTOR_PHASE);
    } else {
        PORTD |= (1 << RIGHT_MOTOR_PHASE);
    }
}

static void left_motor_spin(uint8_t direction) {
    TCCR0A |= (1 << COM0B1);

    if (direction == DIRECTION_FORWARD) {
        PORTD &= ~(1 << LEFT_MOTOR_PHASE);
    } else {
        PORTD |= (1 << LEFT_MOTOR_PHASE);
    }
}

static void right_motor_stop(void) {
    TCCR0A &= ~(1 << COM0A1);
}

static void left_motor_stop(void) {
    TCCR0A &= ~(1 << COM0B1);
}


/* Function definitions from motors.h */

void DRV8835_init(void) {
    // set the mode pin, right and left motor phase/enable pins as an output
    DDRD |= ((1 << DRV8835_MODE) | (1 << RIGHT_MOTOR_PHASE) | (1 << LEFT_MOTOR_PHASE) | (1 << RIGHT_MOTOR_ENABLE) | (1 << LEFT_MOTOR_ENABLE));

    // set PD2 pin HIGH to set drv8835 mode to PHASE/ENABLE MODE
    PORTD |= (1 << DRV8835_MODE);
}

void PWM_init(void) {
    TCCR0A |= ((1 << WGM00) | (1 << WGM01));    // Fast PWM mode
    TCCR0B |= (1 << CS02);      // prescaler set to 256; PWM freq ~62,5kHz
}

void PWM_set_duty_cycle(uint16_t adc_value) {
    uint8_t PWM_value = (uint32_t)(adc_value) * 255 / 1024;
    OCR0A = PWM_value;
    OCR0B = PWM_value;
}

void robot_move_forward(void) {
    right_motor_spin(DIRECTION_FORWARD);
    left_motor_spin(DIRECTION_FORWARD);
}

void robot_move_backward(void) {
    right_motor_spin(DIRECTION_BACKWARD);
    left_motor_spin(DIRECTION_BACKWARD);
}

void robot_turn_left(void) {
    robot_move_forward();
    left_motor_stop();
}

void robot_turn_right(void) {
    robot_move_forward();
    right_motor_stop();
}

void robot_stop(void) {
    right_motor_stop();
    left_motor_stop();
}
