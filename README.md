# Atividade - Interrupções

Este projeto foi desenvolvido para aprimorar o conhecimento sobre interrupções utilizando o **Raspberry Pi Pico W**. Foi realizado com o auxílio do simulador de eletrônica **Wokwi** e da placa **BitDogLab**.

## Componentes Utilizados

1. **LED RGB** (Vermelho, Verde e Azul)
2. **Matriz de LED 5x5 WS2812** (Vermelho, Verde e Azul)
3. **Microcontrolador Raspberry Pi Pico W**
4. **Dois botões Pushbutton**

## Funcionalidade

Ao iniciar o programa, o LED RGB piscará na cor vermelha com uma frequência de **5 vezes por segundo** até a finalização do programa.

### Funcionalidades dos Botões

- **Botão A**: Incrementa o valor exibido na matriz de LED WS2812.
- **Botão B**: Decrementa o valor exibido na matriz de LED WS2812.

### Como Usar

#### Usando o Simulador Wokwi

- Clone este repositório: git clone https://github.com/rober1o/10.37M2---U4C4O12T----Atividade_interrupcao.git;
- Usando a extensão Raspberry Pi Pico importar o projeto;
- Compilar o código e clicar no arquivo diagram.json.

#### Usando a BitDogLab

- Clone este repositório: git clone https://github.com/rober1o/10.37M2---U4C4O12T----Atividade_interrupcao.git;
- Usando a extensão Raspberry Pi Pico importar o projeto;
- Compilar o projeto;
- Plugar a BitDogLab usando um cabo apropriado e gravar o código.

## Atenção

O brilho dos LEDs é muito intenso, para evitar danos aos olhos recomendamos que o brilho_padrao seja ajustado para 10% quando estiver usando o kit BitDogLab.

## Demonstração

<!-- TODO: adicionar link do vídeo -->
Vídeo demonstrando as funcionalidades da solução implementada: [Demonstração](https://youtu.be/pDz5KutL2i4)
