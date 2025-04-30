#include "stm32f10x.h"    

int main(void)
{
    // Enable the Alternate Function for PINs and enable GPIOA
    RCC->APB2ENR |= 5;

    // Enable UART2 clock
    RCC->APB1ENR |= 0x20000;

    // Clear bits for PA0 - PA7
    GPIOA->CRL &= ~(0xFFFFFFFF);

    // Set mode and configuration for PA0 - PA7
    GPIOA->CRL |= 0x33330033;

    // Set GPIOA pin 2 as TX and pin 3 as RX
    GPIOA->CRL |= 0xB00;
    GPIOA->CRL |= 0x8000;

    // Setup the baud rate for 9600 bps
    uint32_t system_clock = 36000000; 
    uint32_t baud_rate = 9600;
    USART2->BRR = (system_clock + (baud_rate / 2)) / baud_rate;

    // Enable UART Transmit
    USART2->CR1 |= 8;

    // Enable UART Receive
    USART2->CR1 |= 4;

    // Enable UART
    USART2->CR1 |= 0x2000;

    // Set word length
    USART2->CR1 |= 0x1000;

    while (1)
    {
        char chat = 'D';

        // Wait until data transmission is complete
        while (!(USART2->SR & (1 << 6))) {};

        // Send data to data register
        USART2->DR = chat;
    }
}
