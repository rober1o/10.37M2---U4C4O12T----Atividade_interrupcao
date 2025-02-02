#ifndef Atividade_27_01
#define Atividade_27_01

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_wave.pio.h"
#include "numeros.h"
#include "pico/bootrom.h"
#include "pico/time.h" 


//Definição dos pinos dos LED e botões, e definição do tempo de debouce e intencidade do brilho.
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13 
#define BUTTON_A 5
#define BUTTON_B 6
#define brilho_padrao 100
#define DEBOUNCE_TIME 200 
#define matriz_pin 7
#define NUM_PIXELS 25

//Declaração das variáveis globais usadas no arquivo C
volatile uint32_t ultimo_tempoA = 0;
volatile uint32_t ultimo_tempoB = 0;
repeating_timer_t timer;
volatile bool ligado = false;
int numero = 0; 
PIO pio;
int sm;



// Declaração das funções a serem implementadas no arquivo C
bool piscar_led_red_callback(repeating_timer_t *t);
bool debounce_ok(uint gpio);
void gpio_irq_handler(uint gpio, uint32_t events);
void exibir_numero(void);
void iniciar_pinos(void);
void desenha_fig(uint32_t *_matriz, uint8_t _intensidade, PIO pio, uint sm);

#endif // Atividade_27_01