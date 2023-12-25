#include <avr/io.h>

#define F_CPU   (16000000UL)

#include <util/delay.h>

#define DRV8835_MODE    (PD2)
#define MOTOR_PHASE     (PD4)
#define MOTOR_ENABLE    (PD5)

void DRV8835_init(void) {
    DDRD |= ((1 << DRV8835_MODE) | (1 << MOTOR_PHASE));     // set PD2 and PD4 as an output
    PORTD |= (1 << DRV8835_MODE);    // set HIGH on PD2 to set DRV8835 in PHASE/ENABLE mode
}

void init_PWM(void) {
    TCCR0A |= ((1 << WGM00) | (1 << WGM01) | (1 << COM0B1));
    TCCR0B |= (1 << CS02);  // 62.5 kHz
    
    DDRD |= (1 << MOTOR_ENABLE);
}

void set_PWM_duty_cycle(uint8_t percentage) {
    if (percentage >= 100) {
        percentage = 100;
    }

    uint16_t PWM_value = (percentage * 255) / 100;

    OCR0B = (uint8_t)PWM_value;
}

void move_forward(void) {
    PORTD &= ~(1 << MOTOR_PHASE);
}

void move_backward(void) {
    PORTD |= (1 << MOTOR_PHASE);
}

int main(void) {
    DRV8835_init();
    init_PWM();
    set_PWM_duty_cycle(75);

    while(1) {
        move_forward();
        _delay_ms(2000);
        move_backward();
        _delay_ms(2000);
    }
    return 0;
}

