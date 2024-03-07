/*
 * g4_doorbell_module.c
 *
 * Created: 21/11/2022 19:43:24
 * Author : felix
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define transmitter_out		PB0
#define g4_power_out		PB1
#define sens_input			PB2

int main(void)
{
    DDRB |= (1 << transmitter_out) | (1 << g4_power_out);	// Outputs
	PORTB |= (1 << g4_power_out);							// G4 on
	
    while (1) 
    {
		// While there is power do nothing
		if (PINB & (1 << sens_input))
		{
			_delay_ms(100);									// Wait a little bit
		}
		
		// When G4 shorts input
		else
		{
			PORTB &= ~(1 << g4_power_out);					// Deactivate power for G4
			PORTB |= (1 << transmitter_out);				// Power for transmitter
			_delay_ms(2000);								// Wait 1s
			PORTB |= (1 << g4_power_out);					// Activate power for G4
			_delay_ms(3000);								// Wait more until transmitter is active
			PORTB &= ~(1 << transmitter_out);				// Power off transmitter
			_delay_ms(1000);								// Wait 1s until everything is stabilized
		}
    }
}

