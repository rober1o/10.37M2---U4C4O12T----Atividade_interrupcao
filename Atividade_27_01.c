#include "Atividade_27_01.h"

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

    iniciar_pinos();
    desenha_fig(numero_0, brilho_padrao, pio, sm);
    while (true) {
        piscar_led_red();
        sleep_ms(100);
    }

}

// Rotina para iniciar e configurar os LEDs e botões

void iniciar_pinos() {
    gpio_init(LED_RED); 
    gpio_init(LED_BLUE);
    gpio_init(LED_GREEN);    
    gpio_set_dir(LED_RED, GPIO_OUT); 
    gpio_set_dir(LED_BLUE, GPIO_OUT); 
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_A); 
    gpio_pull_up(BUTTON_B);

    // Configura interrupção no botão
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, gpio_irq_handler);
}


// Rotina de para alternar o estado do LED
void piscar_led_red() {
    ligado = !ligado;  // Alterna o estado do LED
    gpio_put(LED_RED, ligado);  // Atualiza o estado do LED
}

// Função de interrupção do botão
void gpio_irq_handler(uint gpio, uint32_t events) {

    if ((events & GPIO_IRQ_EDGE_FALL) && debounce_ok(gpio)) { // Verifica se passou 200ms desde a última chamada do botão

        if (gpio == BUTTON_A && numero < 9) { // Verifica se a interrupçãoveio do botão A e se já não atingiu o valor máximo da matriz
            numero++;  // Incrementa o número
        } else if (gpio == BUTTON_B && numero > 0) { // Verifica se a interrupção veio do botão B e se já não atingiu o valor mínimo da matriz
            numero--;  // Decrementa o número
        }

        exibir_numero();  // Atualiza a exibição do número
    }
}

// Função para verificar debounce
bool debounce_ok(uint gpio) {
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time()); 
    
    if (gpio == BUTTON_A) {
        if (tempo_atual - ultimo_tempoA > DEBOUNCE_TIME) {
            ultimo_tempoA = tempo_atual;
            return true;
        }
    } else if (gpio == BUTTON_B) {
        if (tempo_atual - ultimo_tempoB > DEBOUNCE_TIME) {
            ultimo_tempoB = tempo_atual;
            return true;
        }
    }
    return false;
}



// Rotina para exibir os números na matriz de LED
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





