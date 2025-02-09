#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// O clock PWM foi definido arbitrariamente em 1 MHz para facilitar os cálculos
#define GPIO_PWM_SERVO  22          // GPIO do servo motor
#define PWM_FREQUENCY   50          // Frequência definida em 50Hz para que o servo motor funcione
#define GPIO_PWM_LED    12          // GPIO do LED RGB AZUL
#define CLOCK_BASE      125000000   // 125 MHz
#define PWM_DIVISER     125.0       // Divisor inteiro de 125.0. Poderia ser de até 
#define PERIOD          20000       // Período total em milissegundos para um período de 20ms a 50Hz
#define STEP_SERVO      5           // Passo do duty cycle do servo motor em 5 milissegundos
#define CICLO_0         500         // Ciclo ativo para mover o braço do servo motor a 0º
#define CICLO_90        1470        // Ciclo ativo para mover o braço do servo motor a 180º
#define CICLO_180       2400        // Ciclo ativo para mover o braço do servo motor a 180º

// Variável  para calcular o PWM WRAP (número de ciclos do clock do PWM)
// O PWM WRAP é calculado pela fórmula da FREQUÊNCIA PWM = FREQUÊNCIA DE CLOCK DO RP2040 / (DIVISOR  * WRAP)
uint16_t wrapValue = CLOCK_BASE / (PWM_FREQUENCY * PWM_DIVISER);

void init_pwm() {
    // Habilita o pino GPIO como PWM do servo motor 
    gpio_set_function(GPIO_PWM_SERVO, GPIO_FUNC_PWM);
    gpio_set_function(GPIO_PWM_LED, GPIO_FUNC_PWM);
    
    // Captura o canal (slice) PWM do servo motor 
    uint16_t slicePWM = pwm_gpio_to_slice_num(GPIO_PWM_SERVO);
    uint16_t slicePWMLed = pwm_gpio_to_slice_num(GPIO_PWM_LED);

    // Define o dividor de clock do PWM do servo motor em 2.0
    pwm_set_clkdiv(slicePWM, PWM_DIVISER);
    pwm_set_clkdiv(slicePWMLed, PWM_DIVISER);

    // Define o valor WRAP PWM
    pwm_set_wrap(slicePWM, wrapValue);
    pwm_set_wrap(slicePWMLed, wrapValue);

    // Habilita o PWM no slice correspondente
    pwm_set_enabled(slicePWM, 1);
    pwm_set_enabled(slicePWMLed, 1);
}

// Movimenta suavemente o servo entre dois pulsos, com incremento de 5us
void move_servo(uint16_t pulso_inicial, uint16_t pulso_final) {
    uint16_t step = STEP_SERVO;
    // Variável para calcular o nível do sinal PWM
    uint16_t level;
    if (pulso_inicial < pulso_final) {
        while (pulso_inicial <= pulso_final) {
            level = (pulso_inicial * wrapValue) / PERIOD;
            pwm_set_gpio_level(GPIO_PWM_SERVO, pulso_inicial); 
            pwm_set_gpio_level(GPIO_PWM_LED, pulso_inicial); 
            pulso_inicial += step;
            sleep_ms(10);  // Delay de 10ms para suavizar a movimentação
        }
    } else {
        while (pulso_inicial >= pulso_final) {
            level = (pulso_inicial * wrapValue) / PERIOD;
            pwm_set_gpio_level(GPIO_PWM_SERVO, pulso_inicial); 
            pwm_set_gpio_level(GPIO_PWM_LED, pulso_inicial); 
            pulso_inicial -= step;
            sleep_ms(10);  // Delay de 10ms para suavizar a movimentação
        }
    }
}

// Laço principal do programa
int main() {
    stdio_init_all();

    // Inicializa PWM
    init_pwm();

    // Variáveis para calcular os níveis do sinal PWM
    uint16_t level0, level90, level180;
    level0 = (CICLO_0 * wrapValue) / PERIOD;
    level90 = (CICLO_90 * wrapValue) / PERIOD;
    level180 = (CICLO_180 * wrapValue) / PERIOD;

    // Movimenta braço do servo motor para a posição 180° (2.400µs)
    pwm_set_gpio_level(GPIO_PWM_SERVO, level180);
    pwm_set_gpio_level(GPIO_PWM_LED, level180);
    // Pausa de 5s
    sleep_ms(5000);

    // Movimenta braço do servo motor para a posição 90° (1.470µs)
    pwm_set_gpio_level(GPIO_PWM_SERVO, level90);
    pwm_set_gpio_level(GPIO_PWM_LED, level90);
    // Pausa de 5s
    sleep_ms(5000);

    // Movimenta braço do servo motor para a posição 0° (500µs)
    pwm_set_gpio_level(GPIO_PWM_SERVO, level0);
    pwm_set_gpio_level(GPIO_PWM_LED, level0);
    // Pausa de 5s
    sleep_ms(5000);

    // Movimentação periódica suave entre 0° e 180°
    while (true) {
        move_servo(CICLO_0, level180);   // Movimenta de 0° para 180°
        move_servo(CICLO_180, level0);   // Movimenta de 180° para 0°
    }

    return 0;
}
