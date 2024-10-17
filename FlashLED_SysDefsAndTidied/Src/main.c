// Header Files
#include "stm32f429xx.h"

// Local Definitions

// Pin Definitions
#define PIN13		(1<<13)

// GPIO Pins in use
#define LED_PIN		PIN13

// Enumerations

// Structure Types

// Global Variable References

// Local Variable Declarations

// Local Only Function Prototypes
void Initialise_GPIO(void);

/****************************
* @brief Main entry point
* @param None
* @retval None
*/
int main(void)
{
	Initialise_GPIO();

	while(1)
	{
		GPIOG->ODR ^= LED_PIN;
		// Delay to make the flash rate human visible.
		for(int i = 0;i < 300000;i++);
	}

	return 0;
}

/****************************
* @brief Initialise GPIO etc.
* Handles all USART1 Interrupts
* @param None
* @retval None
*/
void Initialise_GPIO(void)
{
	//RCC_TypeDef *pRCC = (RCC_TypeDef *)RCC_BASE;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;

	//GPIO_TypeDef *pGPIOG = (GPIO_TypeDef *)GPIOG_BASE;
	GPIOG->MODER |= (1<<26);
	GPIOG->MODER &= ~(1<<27);
}
