//Define base address for peripherals
#define PERIPH_BASE							(0x40000000UL)
//Offset for APB2 peripheral bus
#define APB2PERIPH_OFFSET 					(0x00010000UL)
//Base address for APB2 peripherals
#define APB2PERIPH_BASE						(PERIPH_BASE + APB2PERIPH_OFFSET)
//Offset for GPIOC
#define GPIOC_OFFSET						0x00011000UL
//Base address for GPIOC
#define GPIOC_BASE							(PERIPH_BASE + GPIOC_OFFSET)
//Offset for RCC
#define RCC_OFFSET							(0x00021000UL)
//Base address for RCC
#define RCC_BASE							(PERIPH_BASE + RCC_OFFSET)
//Offset for APB2EN register
#define APB2EN_R_OFFSET						0x18UL
//Address of APB2EN register
#define RCC_APB2EN_R						(*(volatile unsigned int *)(RCC_BASE + APB2EN_R_OFFSET))
//Offset for CRH register
#define CRH_OFFSET							0x04UL
//Address of GPIO_CRH
#define GPIOC_CRH							(*(volatile unsigned int *)(GPIOC_BASE + CRH_OFFSET))
//Offset for ODR
#define ODR_OFFSET							0x0CUL
//Address of GPIO_ODR
#define GPIOC_ODR							(*(volatile unsigned int *)(GPIOC_BASE + ODR_OFFSET))
//Enable GPIOC
#define GPIOCEN								(1U << 4)
//Alias for PIN 13 representing LED pin
#define LED_PIN								(1U << 13)

int main(void)
{
    //Enable clock access to GPIOC
	RCC_APB2EN_R |= GPIOCEN;
	//Configure PC13 to output push pull 2 MHz
	//MODE13 =10, CNF13 = 00
	GPIOC_CRH &= ~(0xF << 20);
	GPIOC_CRH |= (0x2 << 20);

	while(1) {
		GPIOC_ODR &= ~LED_PIN;
	}

}
