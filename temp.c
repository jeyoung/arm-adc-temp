#include <math.h>
#include "temp.h"

/*
 * This program reads the temperature from the onboard sensor and sends the
 * output to USART1.
 *
 * The program waits for a key press from the console before sending the
 * measured temperature value.
 *
 * The program is tested for an STM32 Nucleo F446RE.
 */
int main(void)
{
    /* Enable GPIOA */
    RCC_AHB1ENR |= (0x01 << 0x00);
    /* Alternate function (AF) mode for PA9 and PA10 */
    GPIOA_MODER |= (0x02 << 0x12) | (0x02 << 0x14);
    /* AF7 (USART TX and RX) for PA9 and PA10 */
    GPIOA_AFRH  |= (0x07 << 0x04) | (0x07 << 0x08); 

    /* Configure PA5 and PA6 for debugging output */
    GPIOA_MODER |= (0x01 << 0x0A) | (0x01 << 0x0C);

    /* Enable USART1 */
    RCC_APB2ENR |= (0x01 << 0x04);
    /* Configure baud rate based on APB2 clock (equals to HSI 16MHz by default) */
    USART1_BRR   = 0x683;
    /* Enable TX and RX, and USART overall */
    USART1_CR1  |= (0x01 << 0x03) | (0x01 << 0x02) | (0x01 << 0x0D);

    /* Enable ADC1 */
    RCC_APB2ENR |= (0x01 << 0x08);
    /* Set channel 18 for temperature sensor */
    ADC1_SQR3   |= (0x12 << 0x00);
    /* Set the number of conversion (which is same as default) */
    ADC1_SQR1   &= ~(0x0F << 0x14);
    /* Set sampling rate for channel 18 (must be > 10 for STM32 F446) */
    ADC1_SMPR1  |= (0x01 << 0x18);
    /* Choose the temperature sensor for channel 18 (instead of battery) */
    ADC1_CCR    |= (0x01 << 0x17);

    while (1)
    {
        /* Turn ADC1 on */
        ADC1_CR2    |= (0x01 << 0x00);

        /* Start conversion */
        ADC1_CR2    |= (0x01 << 0x1E);

        /* Wait for conversion to complete */
        while (!(ADC1_SR & (0x01 << 0x01)))
            ;

        unsigned int adc_reading = ADC1_DR;
        float vsense = adc_reading * (VREFINT/RESOLUTION);
        float temp = ((vsense - V25)/AVG_SLOPE)+TEMP_OFFSET;
        if (temp > 0)
        {
            /* Light up PA5 */
            GPIOA_ODR ^= (0x01 << 0x05);
        }

        /* Look for an RX (wait for a keypress) */
        if (USART1_SR & (0x01 << 0x05))
        {
            volatile char char_in = USART1_DR;

            /* Toggle PA6 */
            GPIOA_ODR ^= (0x01 << 0x06);

            char output[OUTPUT_LENGTH];
            for (int i = 0; i < OUTPUT_LENGTH; i++)
                output[i] = ' ';

            int whole = (int) temp;
            int fraction = trunc((temp - whole)*10);

            int digit_counter = 0;
            while (fraction > 0 && digit_counter < OUTPUT_LENGTH)
            {
                ++digit_counter;
                int rem = fraction % 10;
                output[OUTPUT_LENGTH - digit_counter] = '0'+(char)(rem);
                fraction = trunc(fraction/10);
            }
            output[OUTPUT_LENGTH - (++digit_counter)] = '.';
            while (whole > 0 && digit_counter < OUTPUT_LENGTH)
            {
                ++digit_counter;
                int rem = whole % 10;
                output[OUTPUT_LENGTH - digit_counter] = '0'+(char)(rem);
                whole = trunc(whole/10);
            }

            USART1_DR = '\t';

            /* Check for TC before continuing */
            while (!(USART1_SR & (0x01 << 0x06)))
                ;

            for (int i = 0; i < OUTPUT_LENGTH; i++)
            {
                USART1_DR = output[i];

                /* Check for TC before continuing */
                while (!(USART1_SR & (0x01 << 0x06)))
                    ;
            }

        }

        /* Turn ADC1 off */
        ADC1_CR2    &= ~(0x01 << 0x00);
    }

    return 0;
}
