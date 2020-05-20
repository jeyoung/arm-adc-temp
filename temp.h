#define RCC             0x40023800
#define RCC_AHB1ENR     (*((volatile unsigned long *)((RCC) + 0x30)))
#define RCC_APB2ENR     (*((volatile unsigned long *)((RCC) + 0x44)))

#define GPIOA           0x40020000
#define GPIOA_MODER     (*((volatile unsigned long *)((GPIOA) + 0x00)))
#define GPIOA_OTYPER    (*((volatile unsigned long *)((GPIOA) + 0x04)))
#define GPIOA_SPEEDER   (*((volatile unsigned long *)((GPIOA) + 0x08)))
#define GPIOA_ODR       (*((volatile unsigned long *)((GPIOA) + 0x14)))
#define GPIOA_AFRH      (*((volatile unsigned long *)((GPIOA) + 0x24)))

#define USART1          0x40011000
#define USART1_SR       (*((volatile unsigned long *)((USART1) + 0x00)))
#define USART1_DR       (*((volatile unsigned long *)((USART1) + 0x04)))
#define USART1_BRR      (*((volatile unsigned long *)((USART1) + 0x08)))
#define USART1_CR1      (*((volatile unsigned long *)((USART1) + 0x0C)))
#define USART1_CR2      (*((volatile unsigned long *)((USART1) + 0x10)))
#define USART1_CR3      (*((volatile unsigned long *)((USART1) + 0x14)))

#define ADC1            0x40012000
#define ADC1_SR         (*((volatile unsigned long *)((ADC1) + 0x00)))
#define ADC1_CR1        (*((volatile unsigned long *)((ADC1) + 0x04)))
#define ADC1_CR2        (*((volatile unsigned long *)((ADC1) + 0x08)))
#define ADC1_SMPR1      (*((volatile unsigned long *)((ADC1) + 0x0C)))
#define ADC1_SMPR2      (*((volatile unsigned long *)((ADC1) + 0x10)))
#define ADC1_SQR1       (*((volatile unsigned long *)((ADC1) + 0x2C)))
#define ADC1_SQR2       (*((volatile unsigned long *)((ADC1) + 0x30)))
#define ADC1_SQR3       (*((volatile unsigned long *)((ADC1) + 0x34)))
#define ADC1_DR         (*((volatile unsigned long *)((ADC1) + 0x4C)))
#define ADC1_CCR        (*((volatile unsigned long *)((ADC1+0x300) + 0x04)))

#define VREFINT         1.21
#define V25             0.78
#define AVG_SLOPE       2.50
#define RESOLUTION      4096    // 12 bits
#define TEMP_OFFSET     25.0

#define OUTPUT_LENGTH   15

int main(void);
