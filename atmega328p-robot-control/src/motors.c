#include "../inc/motors.h"
#include "../inc/adc.h"


#define MOTOR_SIDE_RIGHT        (RIGHT_MOTOR_ENABLE)
#define MOTOR_SIDE_LEFT         (LEFT_MOTOR_ENABLE)

#define DIRECTION_FORWARD       (1U)
#define DIRECTION_BACKWARD      (0U)


/* Static helper functions */

static void motor_stop(const uint8_t motor_side) {
    // if the motor PWM pin is connected to the timer - disconnect it and set it to LOW
    if (motor_side == MOTOR_SIDE_RIGHT) {
        if (TCCR0A & (1 << COM0A1)) {
            TCCR0A &= ~(1 << COM0A1);
        }

    } else if (motor_side == MOTOR_SIDE_LEFT) {
        if (TCCR0A & (1 << COM0B1)) {
            TCCR0A &= ~(1 << COM0B1);
        }
    }

    PORTD &= ~(1 << motor_side);
}

static void motor_spin(const uint8_t motor_side, const uint8_t direction) {
    uint8_t phase = 0;

    // assign the given (right/left) motor phase pin to the temp variable 'phase' 
    if (motor_side == MOTOR_SIDE_RIGHT) {
        phase = (uint8_t)RIGHT_MOTOR_PHASE;    
    } else if (motor_side == MOTOR_SIDE_LEFT) {
        phase = (uint8_t)LEFT_MOTOR_PHASE;
    }
    
    // set or reset the given (right/left) motor phase pin to change the spinning direction
    if (direction == DIRECTION_FORWARD) {
        PORTD |= (1 << phase);
    } else if (direction == DIRECTION_BACKWARD) {
        PORTD &= ~(1 << phase);
    }
    
    // if motor PWM pin is not connected to the timer - connect it 
    if (motor_side == MOTOR_SIDE_RIGHT) {
        if (!(TCCR0A & (1 << COM0A1))) {
            TCCR0A |= (1 << COM0A1);
        }
    } else if (motor_side == MOTOR_SIDE_LEFT) {
        if (!(TCCR0A & (1 << COM0B1))) {
            TCCR0A |= (1 << COM0B1);
        }
    } 
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

void PWM_set_duty_cycle(const uint16_t adc_value) {
    uint16_t PWM_value = (adc_value * 100) / 1024;
    OCR0A = (uint8_t)PWM_value;
    OCR0B = (uint8_t)PWM_value;
}

void robot_move_forward(void) {
    motor_spin(MOTOR_SIDE_RIGHT, DIRECTION_FORWARD);
    motor_spin(MOTOR_SIDE_LEFT, DIRECTION_FORWARD);
}

void robot_move_backward(void) {
    motor_spin(MOTOR_SIDE_RIGHT, DIRECTION_BACKWARD);
    motor_spin(MOTOR_SIDE_LEFT, DIRECTION_BACKWARD);
}

void robot_turn_left(void) {
    motor_stop(MOTOR_SIDE_RIGHT);
    motor_spin(MOTOR_SIDE_LEFT, DIRECTION_FORWARD);
}

void robot_turn_right(void) {
    motor_stop(MOTOR_SIDE_LEFT);
    motor_spin(MOTOR_SIDE_RIGHT, DIRECTION_FORWARD);
}

void robot_stop(void) {
    motor_stop(MOTOR_SIDE_RIGHT);
    motor_stop(MOTOR_SIDE_LEFT);
}
