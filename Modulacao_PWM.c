#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// O clock PWM foi definido arbitrariamente em 1 MHz para facilitar os cálculos
#define GPIO_PWM_SERVO  22      // GPIO do servo motor
#define PWM_FREQUENCY   50      // Frequência definida em 50Hz para que o servo motor funcione
#define GPIO_PWM_LED    12      // GPIO do LED RGB AZUL
#define WRAP_PERIOD     20000   // Valor máximo do contador - WRAP (considerando clock PWM em 1 MHz)
#define PWM_DIVISER     125.0   // Clock do divisor em 125 
#define STEP_SERVO      5       // Passo do duty cycle do servo motor em 5 milissegundos
#define CICLO_0         500     // Ciclo ativo para mover o braço do servo motor a 0º
#define CICLO_90        1470    // Ciclo ativo para mover o braço do servo motor a 180º
#define CICLO_180       2400    // Ciclo ativo para mover o braço do servo motor a 180º

// Duty cycle inicial
uint16_t dutyCycle = 200; 

void init_pwm() {
    // Habilita o pino GPIO como PWM do servo motor 
    gpio_set_function(GPIO_PWM_SERVO, GPIO_FUNC_PWM);
    gpio_set_function(GPIO_PWM_LED, GPIO_FUNC_PWM);
    
    // Captura o canal (slice) PWM do servo motor 
    uint slicePWM = pwm_gpio_to_slice_num(GPIO_PWM_SERVO);
    uint slicePWMLed = pwm_gpio_to_slice_num(GPIO_PWM_LED);

    // Define o dividor de clock do PWM do servo motor em 2.0
    pwm_set_clkdiv(slicePWM, PWM_DIVISER);
    pwm_set_clkdiv(slicePWMLed, PWM_DIVISER);

    // Define o valor WRAP em 2000
    pwm_set_wrap(slicePWM, WRAP_PERIOD);
    pwm_set_wrap(slicePWMLed, WRAP_PERIOD);

    // Habilita o PWM no slice correspondente
    pwm_set_enabled(slicePWM, 1);
    pwm_set_enabled(slicePWMLed, 1);
}

// Movimenta suavemente o servo entre dois pulsos, com incremento de 5us
void move_servo(uint16_t pulso_inicial, uint16_t pulso_final) {
    uint16_t step = STEP_SERVO;
    if (pulso_inicial < pulso_final) {
        while (pulso_inicial <= pulso_final) {
            pwm_set_gpio_level(GPIO_PWM_SERVO, pulso_inicial); 
            pwm_set_gpio_level(GPIO_PWM_LED, pulso_inicial); 
            pulso_inicial += step;
            sleep_ms(10);  // Delay de 10ms para suavizar a movimentação
        }
    } else {
        while (pulso_inicial >= pulso_final) {
            pwm_set_gpio_level(GPIO_PWM_SERVO, pulso_inicial); 
            pwm_set_gpio_level(GPIO_PWM_LED, pulso_inicial); 
            pulso_inicial -= step;
            sleep_ms(10);  // Delay de 10ms para suavizar a movimentação
        }
    }
}

int main() {
    stdio_init_all();

    // Inicializa PWM
    init_pwm();

    // Calcula a quantidade de ciclos em nível alto que o sinal PWM deve permanecer para a posição 180° (2400us)
    pwm_set_gpio_level(GPIO_PWM_SERVO, CICLO_180);
    pwm_set_gpio_level(GPIO_PWM_LED, CICLO_180);
    sleep_ms(5000);

    // Calcula a quantidade de ciclos em nível alto que o sinal PWM deve permanecer para a posição 90° (1470us)
    pwm_set_gpio_level(GPIO_PWM_SERVO, CICLO_90);
    pwm_set_gpio_level(GPIO_PWM_LED, CICLO_90);
    sleep_ms(5000);

    // Calcula a quantidade de ciclos em nível alto que o sinal PWM deve permanecer para a posição 0° (500us)
    pwm_set_gpio_level(GPIO_PWM_SERVO, CICLO_0);
    pwm_set_gpio_level(GPIO_PWM_LED, CICLO_0);
    sleep_ms(5000);

    // Movimentação periódica suave entre 0° e 180°
    while (true) {
        move_servo(CICLO_0, CICLO_180);   // Movimenta de 0° para 180°
        move_servo(CICLO_180, CICLO_0);   // Movimenta de 180° para 0°
    }

    return 0;
}
