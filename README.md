Projeto de Controle de Servomotor e LED RGB
Este projeto utiliza um servomotor controlado por PWM e um LED RGB com controle de on/off. O código é executado em um Raspberry Pi Pico, utilizando a biblioteca pico/stdlib e hardware/pwm para configurar o PWM (Pulse Width Modulation), que permite o controle de dispositivos como o servomotor. O LED RGB é usado para feedback visual durante o movimento do servo.

Vídeo Demonstrativo
https://youtu.be/HTnWL8LU0Ds

Descrição
Este código implementa um controle simples de um servomotor e LED RGB. O servomotor pode ser movido para diferentes posições, e o LED acende e apaga para fornecer feedback visual do estado atual do sistema.

Funcionalidades:
Controle do Servomotor:

O servomotor é controlado através do pino GPIO 22 utilizando um sinal PWM. A posição do servo é ajustada com base na largura do pulso, variando entre 0° (500µs) e 180° (2400µs).
O código faz o servo mover-se de forma gradual entre as posições 0° e 180° e vice-versa.
LED RGB:

Um LED RGB é controlado pelo pino GPIO 12. O LED alterna entre ligado e desligado a cada 1 segundo, fornecendo feedback visual sobre o status do sistema.
