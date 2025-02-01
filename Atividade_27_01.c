#include "Atividade_27_01.h"
#include "numeros.h"
#include "pico/bootrom.h"
#include "pico/time.h"  // Para usar timestamps


#define DEBOUNCE_TIME 200 // Tempo de debounce em milissegundos
#define LED_RED 13 
#define LED_BLUE 12
#define LED_GREEN 11
#define BUTTON_A 5
#define BUTTON_B 6
#define brilho_padrao 100

volatile uint32_t ultimo_tempoA = 0;
volatile uint32_t ultimo_tempoB = 0;
repeating_timer_t timer;
volatile bool ligado = false;
int numero = 0; 
PIO pio;
int sm;

void gpio_irq_handler(uint gpio, uint32_t events);


void iniciar_led() {
    gpio_init(LED_RED); 
    gpio_init(LED_BLUE);
    gpio_init(LED_GREEN);    
    gpio_set_dir(LED_RED, GPIO_OUT); 
    gpio_set_dir(LED_BLUE, GPIO_OUT); 
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_A); // Ativa resistor pull-up interno
    gpio_pull_up(BUTTON_B);

    
    // Configura interrupção no botão (borda de descida)
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, gpio_irq_handler);
}

// Função de callback para alternar o estado do LED
bool piscar_led_red_callback(repeating_timer_t *t) {
    ligado = !ligado;  // Alterna o estado do LED
    gpio_put(LED_RED, ligado);  // Atualiza o estado do LED
    return true;  // Retorna true para continuar o temporizador
}

int main()
{
    // Iniciando variaveis e sistema
    pio = pio0; //Cria uma variável que armazena o bloco PIO usado
    bool clock_setado; //Armazena estado do clock
    clock_setado = set_sys_clock_khz(133000, false); //Seta o clock do sitema
    stdio_init_all(); //Inicia a library stdio (UART)

    if(clock_setado) 
    printf("Clock  setado %ld\n", clock_get_hz(clk_sys)); //Printa a velocidade do CLOCK
    int offset = pio_add_program(pio, &Matriz_5x5_program);
    sm = pio_claim_unused_sm(pio, true);
    Matriz_5x5_program_init(pio, sm, offset, matriz_pin);

    iniciar_led();
 
    add_repeating_timer_ms(100, piscar_led_red_callback, NULL, &timer);


    while (true) {

    }

}

// Função de interrupção do botão
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

    if (gpio == BUTTON_A && (events & GPIO_IRQ_EDGE_FALL)) { 
        if (tempo_atual - ultimo_tempoA > DEBOUNCE_TIME) { 
            if (numero < 9) numero++;  // Incrementa o número
            exibir_numero();  // Chama a função para exibir o número
            ultimo_tempoA = tempo_atual;
        }
    } else if (gpio == BUTTON_B && (events & GPIO_IRQ_EDGE_FALL)) {
        if (tempo_atual - ultimo_tempoB > DEBOUNCE_TIME) {
            if (numero > 0) numero--;  // Decrementa o número
            exibir_numero();  // Chama a função para exibir o número
            ultimo_tempoB = tempo_atual;
        }
    }
}



void exibir_numero() {
    switch (numero) {
        case 0: 
            desenha_fig(numero_0, brilho_padrao, pio, sm); 
            break;
        case 1: 
            desenha_fig(numero_1, brilho_padrao, pio, sm);
            break;
        case 2: 
            desenha_fig(numero_2, brilho_padrao, pio, sm); 
            break;
        case 3: 
            desenha_fig(numero_3, brilho_padrao, pio, sm); 
            break;
        case 4: 
            desenha_fig(numero_4, brilho_padrao, pio, sm); 
            break;
        case 5: 
            desenha_fig(numero_5, brilho_padrao, pio, sm); 
            break;
        case 6: 
            desenha_fig(numero_6, brilho_padrao, pio, sm); 
            break;
        case 7: 
            desenha_fig(numero_7, brilho_padrao, pio, sm); 
            break;
        case 8: 
            desenha_fig(numero_8, brilho_padrao, pio, sm);; 
            break;
        case 9: 
            desenha_fig(numero_9, brilho_padrao, pio, sm); 
            break;
        default: 
            break;
    }
}


void desenha_fig(uint32_t *_matriz, uint8_t _intensidade, PIO pio, uint sm){
    uint32_t pixel = 0; uint8_t r, g, b;

    for(int i = 24; i>19; i--) //Linha 1
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF)*(_intensidade/100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF)*(_intensidade/100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF)*(_intensidade/100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel<<8u);
    }

    for(int i = 15; i<20; i++) //Linha 2
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF)*(_intensidade/100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF)*(_intensidade/100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF)*(_intensidade/100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (b << 16) | (r << 8) | g;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel<<8u);

    }

    for(int i = 14; i>9; i--) //Linha 3
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF)*(_intensidade/100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF)*(_intensidade/100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF)*(_intensidade/100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel<<8u);
    }

    for(int i = 5; i<10; i++) //Linha 4
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF)*(_intensidade/100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF)*(_intensidade/100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF)*(_intensidade/100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel<<8u);
    }

    for(int i = 4; i > -1 ; i--) //Linha 5
    {
        pixel = _matriz[i];
        b = ((pixel >> 16) & 0xFF)*(_intensidade/100.00); // Isola os 8 bits mais significativos (azul)
        g = ((pixel >> 8) & 0xFF)*(_intensidade/100.00);  // Isola os 8 bits intermediários (verde)
        r = (pixel & 0xFF)*(_intensidade/100.00);         // Isola os 8 bits menos significativos (vermelho)
        pixel = 0;
        pixel = (g << 16) | (r << 8) | b;
        pio_sm_put_blocking(pio, sm, pixel<<8u);
    }
}





