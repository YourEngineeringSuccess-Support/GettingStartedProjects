
// Define peripheral addresses from the reference manual
#define PERIPH_BASE								(0x40000000UL)
#define AHB1PERIPH_OFFSET						(0x00020000UL)
#define AHB1PERIPH_BASE							(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOG_OFFSET							(0x00021800UL)
#define GPIOG_BASE								(PERIPH_BASE + GPIOG_OFFSET)

#define RCC_OFFSET								(0x00023800UL)
#define RCC_BASE								(PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET							(0x00000030UL)
#define AHB1EN_R								(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET							(0x00000000UL)
#define GPIOG_MODE_R							(*(volatile unsigned int *)(GPIOG_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET								(0x00000014UL)
#define GPIOG_OD_R								(*(volatile unsigned int *)(GPIOG_BASE + OD_R_OFFSET))
#define GPIOG_EN								(0x00000040UL)

#define PIN13									(1<<13)
#define LED_PIN									PIN13

// Note: To also work with the red LED, you would need to also create definitions for PIN14 and LED_RED_PIN

// Main entry point
int main(void)
{
	// Enable clock access to GPIOG
	AHB1EN_R |= GPIOG_EN;

	// Set PG13 as output - Set mode register bits for PG13
	GPIOG_MODE_R |= (1<<26); // Set bit 26 to 1. - See Ref Doc for why
	GPIOG_MODE_R &= ~(1<<27); // Set bit 27 to 0.

	// Note: For the red LED, here you would also need to set the same pattern as above in bits 28 and 29 of GPIOG_MODE_R.
	// Note2: If you want the red and green LED to flash out of sync rather than together, insert one line here...
	// GPIOG_OD_R ^= LED_PIN;

    /* Loop forever */
	while (1)
	{
		GPIOG_OD_R ^= LED_PIN; // note: This inverts the specific bit we want using the XOR operator with whatever's in the register already.

		// To also flash the red LED use "GPIOG_OD_R ^= LED_PIN | LED_RED_PIN;" instead of the above.

		// Delay for a while to make the flashing human visible.
		for (int i = 0; i < 100000; i++);
	}
}

