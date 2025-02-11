#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22    // Pino do servomotor com saída PWM
#define LED_PIN 12      // Pino do LED RGB
#define PWM_WRAP 20000  // Valor máximo do contador PWM para 50Hz (20ms)

// Configuração do PWM para o servomotor
void setup_pwm() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);  // Define a GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o slice correspondente ao pino

    pwm_set_clkdiv(slice, 125.0);  // Ajusta o divisor de clock para gerar 50Hz
    pwm_set_wrap(slice, PWM_WRAP); // Configura o valor máximo do contador
    pwm_set_enabled(slice, true);  // Ativa o PWM
}

// Define a posição do servomotor
void set_servo_position(uint slice, uint16_t pulse_width_us) {
    uint duty_cycle = (pulse_width_us * PWM_WRAP) / 20000;  // Calcula o ciclo de trabalho baseado no tempo do pulso
    pwm_set_gpio_level(SERVO_PIN, duty_cycle);  // Aplica o valor calculado ao PWM
}

// Inicializa o LED RGB
void setup_led() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int main() {
    stdio_init_all();   // Configura a comunicação padrão
    setup_pwm();        // Inicializa o PWM do servo
    setup_led();        // Configura a GPIO do LED

    uint slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o slice do PWM

    // Define a posição do servo em 180° (pulso de 2400µs)
    set_servo_position(slice, 2400);
    sleep_ms(5000);  // Aguarda 5 segundos

    // Ajusta a posição para 90° (pulso de 1470µs)
    set_servo_position(slice, 1470);
    sleep_ms(5000);  // Aguarda 5 segundos

    // Define a posição em 0° (pulso de 500µs)
    set_servo_position(slice, 500);
    sleep_ms(5000);  // Aguarda 5 segundos

    // Movimento gradual do servo entre 0° e 180°
    for (int i = 500; i <= 2400; i += 5) {
        set_servo_position(slice, i);  // Move o servo de forma progressiva
        sleep_ms(10);   // Pequeno atraso para suavizar o movimento
    }
    for (int i = 2400; i >= 500; i -= 5) {
        set_servo_position(slice, i);  // Retorna suavemente à posição inicial
        sleep_ms(10);   // Pequeno atraso
    }

    // Alterna o LED RGB ligado e desligado
    gpio_put(LED_PIN, 1); // Liga o LED
    sleep_ms(1000);  // Mantém o LED aceso
    gpio_put(LED_PIN, 0); // Desliga o LED
    sleep_ms(1000);  // Mantém o LED apagado

    // Movimento contínuo do servo entre 0° e 180°
    while (true) {
        for (int i = 500; i <= 2400; i += 5) {
            set_servo_position(slice, i);
            sleep_ms(10);
        }
        for (int i = 2400; i >= 500; i -= 5) {
            set_servo_position(slice, i);
            sleep_ms(10);
        }
    }

    return 0;
}
