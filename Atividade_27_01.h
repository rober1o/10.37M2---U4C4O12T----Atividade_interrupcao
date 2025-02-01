#ifndef Atividade_27_01
#define Atividade_27_01

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_wave.pio.h"



//número de LEDs
#define NUM_PIXELS 25

//Pino de Dados para a Matriz
#define matriz_pin 7



//Criação de Pio
PIO pio = pio0;
extern int sm;



void imprimir_binario(int num);
uint32_t matrix_rgb(double b, double r, double g);
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b);
void desenha_fig(uint32_t *_matriz, uint8_t _intensidade, PIO pio, uint sm);

#endif // Atividade_27_01