### Link do vídeo explicativo
https://youtu.be/...

# PWM
Embarcatech - Tarefa 2 - Aula Síncrona 06/02

### Requisitos cumpridos pelo projeto
1. Considerando a GPIO 22, defina a sua frequência de PWM para, aproximadamente, 50Hz – período de 20ms. 
2. Defina o ciclo ativo do módulo PWM para 2.400µs (microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,12%. Isto ajustará a flange (braço) do servomotor para a posição de, aproximadamente, 180 graus. Aguarde 05 segundos nesta posição. 
3. Defina o ciclo ativo do módulo PWM para 1.470µs (microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,0735%. Isto ajustará a flange do servomotor para a posição de, aproximadamente, 90 graus. Aguarde 05 segundos nesta posição. 
4. Defina o ciclo ativo do módulo PWM para 500µs (microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,025%. Isto ajustará a flange do servomotor para a posição de, aproximadamente, 0 graus. Aguarde 05 segundos nesta posição. 
5. Após a realização das proposições anteriores, crie uma rotina para movimentação periódica do braço do servomotor entre os ângulos de 0 e 180 graus. Obs.: a movimentação da flange deve ser suave, recomenda-se o incremento de ciclo ativo de ±5µs, com um atraso de ajuste de 10ms. 
6. Com o emprego da Ferramenta Educacional BitDogLab, faça um experimento com o código deste exercício utilizando o LED RGB – GPIO 12. O que o discente observou no comportamento da iluminação do referido LED?

### Funcionamento 📋
1. Utilizando o ambiente de simulação WOKWI, foram incluídos uma placa Raspberry Pico W e 1 servo motor padrão.
2. O servo motor foi contectado à GPIO 22.
3. A frequência do módulo PWM foi alterada para, aproximadamente, 50Hz – período de 20ms. 
4. O ciclo ativo do módulo PWM foi alterado para 2.400µs (microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,12%. O braço do servo motor foi deslocado, aproximadamente, para 180 graus. 
5. Foi inserida uma pausa de 5 segundos nesta posição.
6. O ciclo ativo do módulo PWM foi alterado para 1.470µs (microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,0735%. O braço do servo motor foi deslocado, aproximadamente, para 90 graus.
7. Foi inserida uma pausa de 5 segundos nesta posição.
8. O ciclo ativo do módulo PWM foi alterado para 500µs (microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,025%. O braço do servo motor foi deslocado, aproximadamente, para 0 graus. 
9. Foi inserida uma pausa de 5 segundos nesta posição.
10. Foi criada uma rotina para movimentação periódica do braço do servomotor entre os ângulos de 0 e 180 graus. 
11. Utilizando a placa BitDogLab, foi feito um experimento com o código anterior utilizando o LED RGB – GPIO 12.
