#pragma once

#ifndef F_CPU
#define F_CPU   (16000000UL)
#endif

#include <avr/io.h>


/* Helper macros */

#define DRV8835_MODE            (PD2)

#define RIGHT_MOTOR_PHASE       (PD4)
#define RIGHT_MOTOR_ENABLE      (PD5)   // OC0B (output compare channel B) pin

#define LEFT_MOTOR_PHASE        (PD7)
#define LEFT_MOTOR_ENABLE       (PD6)   // OC0A (output compare channel A) pin


/* Function prototypes */

/* This function initialises DRV8835 motor driver */
void DRV8835_init(void);

/* This function setups Timer/Counter 0 as a PWM to control DRV8835 driver */
void PWM_init(void);

/* This function sets PWM duty cycle according to the potentiometer setting */
void PWM_set_duty_cycle(const uint16_t adc_value);

/* This function moves the robot forward */
void robot_move_forward(void); 

/* This function moves the robot backward */
void robot_move_backward(void);

/* This function turns the robot left */
void robot_turn_left(void);

/* This function turns the robot right */
void robot_turn_right(void);

/* This function stops the robot */
void robot_stop(void);
