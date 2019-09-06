/*
* "Melody" library
* Created by: Matan Bright
*
*/


#if !defined(MELODY_DEFINITIONS)																			// If 'MELODY_DEFINITIONS' is not defined. It means that this file is included at the first time
#define MELODY_DEFINITIONS																					// Define 'MELODY_DEFINITIONS' for preventing multiple inclusions of this file

// Including the Arduino library according to the Arduino's version
#if defined(ARDUINO) && ARDUINO >= 100																		// If the Arduino's built-in version constant exists and the version is 1.0 or above
#include <Arduino.h>																						// Include the library for Arduino version 1.0 or above
#else																										// If the Arduino's version is unknown or bellow 1.0
#include <WProgram.h>																						// Include the old Arduino library
#endif

// Defining a constant for determining how much tone generation timers can be used (according to each micro-controller's capabilities)
#if defined(__AVR_ATtiny84__) || defined(__AVR_ATmega328P__)												// If you are using ATtiny84 or ATmega328P (Arduino UNO)
#define TONE_GENERATION_TIMERS_COUNT 1																		// Define a constant for determining how much timers can be used for tone generation
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)											// If you are using ATmega1280 (Arduino MEGA 1280) or ATmega2560 (Arduino MEGA 2560)
#define TONE_GENERATION_TIMERS_COUNT 4																		// Define a constant for determining how much timers can be used for tone generation
#endif

// Defining a constant for the system's clock frequency
#if defined(F_CPU)																							// If the built-in constant for the system clock frequency exists
#define SYSTEM_CLOCK_FREQUENCY F_CPU																		// Set the constant's value to the value of the built-in constant
#else																										// If the built-in variable for the system clock frequency does not exist
#define SYSTEM_CLOCK_FREQUENCY 16000000																		// Set the constant's value to the common system clock frequency (16MHz)
#endif

// Defining constants for the default melody settings
#define DEFAULT_MELODY_TEMPO 120																			// Define a constant for the default melody tempo (beats-per-minute)
#define DEFAULT_MELODY_SNAP 4																				// Define a constant for the default melody snap (bars-per-beat)

// Defining a constant for the interrupt service routine of the notes timing timer and defining functions for the notes timing timer (timer 0)
#if defined(__AVR_ATtiny84__)																				// If you are using ATtiny84
#define NOTES_TIMING_TIMER_INTERRUPT_SERVICE_ROUTINE TIM0_COMPA_vect										// Define a constant for the selected notes timing timer's interrupt service routine (for ATtiny84)
#else																										// If you are not using ATtiny84
#define NOTES_TIMING_TIMER_INTERRUPT_SERVICE_ROUTINE TIMER0_COMPA_vect										// Define a constant for the selected notes timing timer's interrupt service routine
#endif
#define ENABLE_NOTES_TIMING_TIMER_INTERRUPTS() ({															/* Define a function for enabling the selected notes timing timer interrupts */ \
	cli(); 																										/* Disable all interrupts */ \
	TIMSK0 |= (1 << OCIE0A); 																					/* Enable timer compare interrupt */ \
	sei(); 																										/* Enable all interrupts */ \
})
#define DISABLE_NOTES_TIMING_TIMER_INTERRUPTS() ({															/* Define a function for disabling the selected notes timing timer interrupts */ \
	cli(); 																										/* Disable all interrupts */ \
	TIMSK0 &= ~(1 << OCIE0A); 																					/* Disable timer compare interrupt */ \
	sei(); 																										/* Enable all interrupts */ \
})

// Defining constants for the interrupt service routines of the supported tone generation timers and defining functions for the supported tone generation timers
#if TONE_GENERATION_TIMERS_COUNT >= 1																		// If there is at least 1 tone generation timer, timer1 is used (16bit timer [maximum 65535 increments until counter reset])
#if defined(__AVR_ATtiny84__)																				// If you are using ATtiny84
#define TIMER1_TONE_GENERATION_TIMER_INTERRUPT_SERVICE_ROUTINE TIM1_COMPA_vect								// Define a constant for the selected notes timing timer's interrupt service routine (for ATtiny84)
#else																										// If you are not using ATtiny84
#define TIMER1_TONE_GENERATION_TIMER_INTERRUPT_SERVICE_ROUTINE TIMER1_COMPA_vect							// Define a constant for the selected notes timing timer's interrupt service routine
#endif
#define INITIALIZE_TONE_GENERATION_TIMER1(frequency) ({														/* Define a function for initializing the selected tone generation timer with the selected frequency */ \
	cli();																										/* Disable all interrupts */ \
	TCCR1A = 0;																									/* Set entire TCCRxA register to 0 */ \
	TCCR1B = 0;																									/* Set entire TCCRxB register to 0 */ \
	TCNT1  = 0;																									/* Initialize counter value to 0 */ \
	unsigned int timerPrescaler = 0;																			/* Set a variable for the timer prescaler */ \
	byte timerPrescalerRegisterBits = 0;																		/* Set a variable for the timer prescaler register bits */ \
	unsigned long compareMatchValue = 0;																		/* Set a variable for the compare-match register value */ \
	if (frequency == 0) {																						/* If the selected frequency is 0Hz (no sound) */ \
		timerPrescalerRegisterBits = (0 << CS12) | (0 << CS11) | (0 << CS10);										/* Set the timer prescaler register bits variable value for prescaler 0 (turning off the timer) */ \
		compareMatchValue = 0;																						/* Change the compare-match register variable value to 0 */ \
	} else {																									/* If the selected frequency is above 0Hz */ \
		timerPrescaler = 1;																							/* Set the timer prescaler variable value to 1 */ \
		timerPrescalerRegisterBits = (0 << CS12) | (0 << CS11) | (1 << CS10);										/* Set the timer prescaler register bits variable value for prescaler 1 */ \
		compareMatchValue = SYSTEM_CLOCK_FREQUENCY / (timerPrescaler * frequency * 4) - 1;							/* Change the compare-match register variable value to the value with the new prescaler */ \
		while (compareMatchValue > 65535) {																			/* Loop until the compare-match variable value is less than 65535 or equal to it */ \
			switch (timerPrescaler) {																					/* Check the value of the timer prescaler variable */ \
				case 1:																										/* If the timer prescaler variable value is 1 */ \
					timerPrescaler = 8;																							/* Set the timer prescaler variable value to 8 */ \
					timerPrescalerRegisterBits = (0 << CS12) | (1 << CS11) | (0 << CS10);										/* Set the timer prescaler register bits variable value for prescaler 8 */ \
					break;																										\
				case 8:																										/* If the timer prescaler variable value is 8 */ \
					timerPrescaler = 64;																						/* Set the timer prescaler variable value to 64 */ \
					timerPrescalerRegisterBits = (0 << CS12) | (1 << CS11) | (1 << CS10);										/* Set the timer prescaler register bits variable value for prescaler 64 */ \
					break;																										\
				case 64:																									/* If the timer prescaler variable value is 64 */ \
					timerPrescaler = 256;																						/* Set the timer prescaler variable value to 256 */ \
					timerPrescalerRegisterBits = (1 << CS12) | (0 << CS11) | (0 << CS10);										/* Set the timer prescaler register bits variable value for prescaler 256 */ \
					break;																										\
				case 256:																									/* If the timer prescaler variable value is 256 */ \
					timerPrescaler = 1024;																						/* Set the timer prescaler variable value to 1024 */ \
					timerPrescalerRegisterBits = (1 << CS12) | (0 << CS11) | (1 << CS10);										/* Set the timer prescaler register bits variable value for prescaler 1024 */ \
					break;																										\
				case 1024:																									/* If the timer prescaler variable value is 1024 (it means that the timer is not suitable for the desired frequency) */ \
					timerPrescaler = 0;																							/* Set the timer prescaler variable value to 0 */ \
					timerPrescalerRegisterBits = (0 << CS12) | (0 << CS11) | (0 << CS10);										/* Set the timer prescaler register bits variable value for prescaler 0 (turning off the timer) */ \
					break;																										\
			}																											\
			if (timerPrescaler > 0)																						/* If the timer prescaler variable value is greater than 0 (if the timer is working) */ \
				compareMatchValue = SYSTEM_CLOCK_FREQUENCY / (timerPrescaler * frequency * 4) - 1;							/* Change the compare-match register variable value to the value with the new prescaler */ \
		}																											\
	}																											\
	OCR1A = compareMatchValue;																					/* Set compare-match register increments for the desired frequency with the selected prescaler */ \
	TCCR1B |= (1 << WGM12);																						/* Set WGMx2 bit in the TCCRxB register for CTC mode */ \
	TCCR1B |= timerPrescalerRegisterBits;																		/* Set CSx2, CSx1 and CSx0 bits in the TCCRxB register for the selected prescaler */ \
	TIMSK1 &= ~(1 << OCIE1A);																					/* Disable timer compare interrupt */ \
	sei();																										/* Enable all interrupts */ \
})
#define ENABLE_TONE_GENERATION_TIMER1_INTERRUPTS() ({														/* Define a function for enabling the selected tone generation timer interrupts */ \
	cli(); 																										/* Disable all interrupts */ \
	if (TCCR1B & ((1 << CS12) | (1 << CS11) | (1 << CS10)) > 0)													/* If the timer is working (the timer prescaler is above 0) */ \
		TIMSK1 |= (1 << OCIE1A); 																					/* Enable timer compare interrupt */ \
	sei(); 																										/* Enable all interrupts */ \
})
#define DISABLE_TONE_GENERATION_TIMER1_INTERRUPTS() ({														/* Define a function for disabling the selected tone generation timer interrupts */ \
	cli(); 																										/* Disable all interrupts */ \
	TIMSK1 &= ~(1 << OCIE1A); 																					/* Disable timer compare interrupt */ \
	sei(); 																										/* Enable all interrupts */ \
})
#endif
#if TONE_GENERATION_TIMERS_COUNT >= 2																		// If there are at least 2 tone generation timers, timer3 is used (16bit timer [maximum 65535 increments until counter reset])
#define TIMER3_TONE_GENERATION_TIMER_INTERRUPT_SERVICE_ROUTINE TIMER3_COMPA_vect							// Define a constant for the selected tone generation timer's interrupt service routine
#define INITIALIZE_TONE_GENERATION_TIMER3(frequency) ({														/* Define a function for initializing the selected tone generation timer with the selected frequency */ \
	cli();																										/* Disable all interrupts */ \
	TCCR3A = 0;																									/* Set entire TCCRxA register to 0 */ \
	TCCR3B = 0;																									/* Set entire TCCRxB register to 0 */ \
	TCNT3  = 0;																									/* Initialize counter value to 0 */ \
	unsigned int timerPrescaler = 0;																			/* Set a variable for the timer prescaler */ \
	byte timerPrescalerRegisterBits = 0;																		/* Set a variable for the timer prescaler register bits */ \
	unsigned long compareMatchValue = 0;																		/* Set a variable for the compare-match register value */ \
	if (frequency == 0) {																						/* If the selected frequency is 0Hz (no sound) */ \
		timerPrescalerRegisterBits = (0 << CS32) | (0 << CS31) | (0 << CS30);										/* Set the timer prescaler register bits variable value for prescaler 0 (turning off the timer) */ \
		compareMatchValue = 0;																						/* Change the compare-match register variable value to 0 */ \
	} else {																									/* If the selected frequency is above 0Hz */ \
		timerPrescaler = 1;																							/* Set the timer prescaler variable value to 1 */ \
		timerPrescalerRegisterBits = (0 << CS32) | (0 << CS31) | (1 << CS30);										/* Set the timer prescaler register bits variable value for prescaler 1 */ \
		compareMatchValue = SYSTEM_CLOCK_FREQUENCY / (timerPrescaler * frequency * 4) - 1;							/* Change the compare-match register variable value to the value with the new prescaler */ \
		while (compareMatchValue > 65535) {																			/* Loop until the compare-match variable value is less than 65535 or equal to it */ \
			switch (timerPrescaler) {																					/* Check the value of the timer prescaler variable */ \
				case 1:																										/* If the timer prescaler variable value is 1 */ \
					timerPrescaler = 8;																							/* Set the timer prescaler variable value to 8 */ \
					timerPrescalerRegisterBits = (0 << CS32) | (1 << CS31) | (0 << CS30);										/* Set the timer prescaler register bits variable value for prescaler 8 */ \
					break;																										\
				case 8:																										/* If the timer prescaler variable value is 8 */ \
					timerPrescaler = 64;																						/* Set the timer prescaler variable value to 64 */ \
					timerPrescalerRegisterBits = (0 << CS32) | (1 << CS31) | (1 << CS30);										/* Set the timer prescaler register bits variable value for prescaler 64 */ \
					break;																										\
				case 64:																									/* If the timer prescaler variable value is 64 */ \
					timerPrescaler = 256;																						/* Set the timer prescaler variable value to 256 */ \
					timerPrescalerRegisterBits = (1 << CS32) | (0 << CS31) | (0 << CS30);										/* Set the timer prescaler register bits variable value for prescaler 256 */ \
					break;																										\
				case 256:																									/* If the timer prescaler variable value is 256 */ \
					timerPrescaler = 1024;																						/* Set the timer prescaler variable value to 1024 */ \
					timerPrescalerRegisterBits = (1 << CS32) | (0 << CS31) | (1 << CS30);										/* Set the timer prescaler register bits variable value for prescaler 1024 */ \
					break;																										\
				case 1024:																									/* If the timer prescaler variable value is 1024 (it means that the timer is not suitable for the desired frequency) */ \
					timerPrescaler = 0;																							/* Set the timer prescaler variable value to 0 */ \
					timerPrescalerRegisterBits = (0 << CS32) | (0 << CS31) | (0 << CS30);										/* Set the timer prescaler register bits variable value for prescaler 0 (turning off the timer) */ \
					break;																										\
			}																											\
			if (timerPrescaler > 0)																						/* If the timer prescaler variable value is greater than 0 (if the timer is working) */ \
				compareMatchValue = SYSTEM_CLOCK_FREQUENCY / (timerPrescaler * frequency * 4) - 1;							/* Change the compare-match register variable value to the value with the new prescaler */ \
		}																											\
	}																											\
	OCR3A = compareMatchValue;																					/* Set compare-match register increments for the desired frequency with the selected prescaler */ \
	TCCR3B |= (1 << WGM32);																						/* Set WGMx2 bit in the TCCRxB register for CTC mode */ \
	TCCR3B |= timerPrescalerRegisterBits;																		/* Set CSx2, CSx1 and CSx0 bits in the TCCRxB register for the selected prescaler */ \
	TIMSK3 &= ~(1 << OCIE3A);																					/* Disable timer compare interrupt */ \
	sei();																										/* Enable all interrupts */ \
})
#define ENABLE_TONE_GENERATION_TIMER3_INTERRUPTS() ({														/* Define a function for enabling the selected tone generation timer interrupts */ \
	cli(); 																										/* Disable all interrupts */ \
	if (TCCR3B & ((1 << CS32) | (1 << CS31) | (1 << CS30)) > 0)													/* If the timer is working (the timer prescaler is above 0) */ \
		TIMSK3 |= (1 << OCIE3A); 																					/* Enable timer compare interrupt */ \
	sei(); 																										/* Enable all interrupts */ \
})
#define DISABLE_TONE_GENERATION_TIMER3_INTERRUPTS() ({														/* Define a function for disabling the selected tone generation timer interrupts */ \
	cli(); 																										/* Disable all interrupts */ \
	TIMSK3 &= ~(1 << OCIE3A); 																					/* Disable timer compare interrupt */ \
	sei(); 																										/* Enable all interrupts */ \
})
#endif
#if TONE_GENERATION_TIMERS_COUNT >= 3																		// If there are at least 3 tone generation timers, timer4 is used (16bit timer [maximum 65535 increments until counter reset])
#define TIMER4_TONE_GENERATION_TIMER_INTERRUPT_SERVICE_ROUTINE TIMER4_COMPA_vect							// Define a constant for the selected tone generation timer's interrupt service routine
#define INITIALIZE_TONE_GENERATION_TIMER4(frequency) ({														/* Define a function for initializing the selected tone generation timer with the selected frequency */ \
	cli();																										/* Disable all interrupts */ \
	TCCR4A = 0;																									/* Set entire TCCRxA register to 0 */ \
	TCCR4B = 0;																									/* Set entire TCCRxB register to 0 */ \
	TCNT4  = 0;																									/* Initialize counter value to 0 */ \
	unsigned int timerPrescaler = 0;																			/* Set a variable for the timer prescaler */ \
	byte timerPrescalerRegisterBits = 0;																		/* Set a variable for the timer prescaler register bits */ \
	unsigned long compareMatchValue = 0;																		/* Set a variable for the compare-match register value */ \
	if (frequency == 0) {																						/* If the selected frequency is 0Hz (no sound) */ \
		timerPrescalerRegisterBits = (0 << CS42) | (0 << CS41) | (0 << CS40);										/* Set the timer prescaler register bits variable value for prescaler 0 (turning off the timer) */ \
		compareMatchValue = 0;																						/* Change the compare-match register variable value to 0 */ \
	} else {																									/* If the selected frequency is above 0Hz */ \
		timerPrescaler = 1;																							/* Set the timer prescaler variable value to 1 */ \
		timerPrescalerRegisterBits = (0 << CS42) | (0 << CS41) | (1 << CS40);										/* Set the timer prescaler register bits variable value for prescaler 1 */ \
		compareMatchValue = SYSTEM_CLOCK_FREQUENCY / (timerPrescaler * frequency * 4) - 1;							/* Change the compare-match register variable value to the value with the new prescaler */ \
		while (compareMatchValue > 65535) {																			/* Loop until the compare-match variable value is less than 65535 or equal to it */ \
			switch (timerPrescaler) {																					/* Check the value of the timer prescaler variable */ \
				case 1:																										/* If the timer prescaler variable value is 1 */ \
					timerPrescaler = 8;																							/* Set the timer prescaler variable value to 8 */ \
					timerPrescalerRegisterBits = (0 << CS42) | (1 << CS41) | (0 << CS40);										/* Set the timer prescaler register bits variable value for prescaler 8 */ \
					break;																										\
				case 8:																										/* If the timer prescaler variable value is 8 */ \
					timerPrescaler = 64;																						/* Set the timer prescaler variable value to 64 */ \
					timerPrescalerRegisterBits = (0 << CS42) | (1 << CS41) | (1 << CS40);										/* Set the timer prescaler register bits variable value for prescaler 64 */ \
					break;																										\
				case 64:																									/* If the timer prescaler variable value is 64 */ \
					timerPrescaler = 256;																						/* Set the timer prescaler variable value to 256 */ \
					timerPrescalerRegisterBits = (1 << CS42) | (0 << CS41) | (0 << CS40);										/* Set the timer prescaler register bits variable value for prescaler 256 */ \
					break;																										\
				case 256:																									/* If the timer prescaler variable value is 256 */ \
					timerPrescaler = 1024;																						/* Set the timer prescaler variable value to 1024 */ \
					timerPrescalerRegisterBits = (1 << CS42) | (0 << CS41) | (1 << CS40);										/* Set the timer prescaler register bits variable value for prescaler 1024 */ \
					break;																										\
				case 1024:																									/* If the timer prescaler variable value is 1024 (it means that the timer is not suitable for the desired frequency) */ \
					timerPrescaler = 0;																							/* Set the timer prescaler variable value to 0 */ \
					timerPrescalerRegisterBits = (0 << CS42) | (0 << CS41) | (0 << CS40);										/* Set the timer prescaler register bits variable value for prescaler 0 (turning off the timer) */ \
					break;																										\
			}																											\
			if (timerPrescaler > 0)																						/* If the timer prescaler variable value is greater than 0 (if the timer is working) */ \
				compareMatchValue = SYSTEM_CLOCK_FREQUENCY / (timerPrescaler * frequency * 4) - 1;							/* Change the compare-match register variable value to the value with the new prescaler */ \
		}																											\
	}																											\
	OCR4A = compareMatchValue;																					/* Set compare-match register increments for the desired frequency with the selected prescaler */ \
	TCCR4B |= (1 << WGM42);																						/* Set WGMx2 bit in the TCCRxB register for CTC mode */ \
	TCCR4B |= timerPrescalerRegisterBits;																		/* Set CSx2, CSx1 and CSx0 bits in the TCCRxB register for the selected prescaler */ \
	TIMSK4 &= ~(1 << OCIE4A);																					/* Disable timer compare interrupt */ \
	sei();																										/* Enable all interrupts */ \
})
#define ENABLE_TONE_GENERATION_TIMER4_INTERRUPTS() ({														/* Define a function for enabling the selected tone generation timer interrupts */ \
	cli(); 																										/* Disable all interrupts */ \
	if (TCCR4B & ((1 << CS42) | (1 << CS41) | (1 << CS40)) > 0)													/* If the timer is working (the timer prescaler is above 0) */ \
		TIMSK4 |= (1 << OCIE4A); 																					/* Enable timer compare interrupt */ \
	sei(); 																										/* Enable all interrupts */ \
})
#define DISABLE_TONE_GENERATION_TIMER4_INTERRUPTS() ({														/* Define a function for disabling the selected tone generation timer interrupts */ \
	cli(); 																										/* Disable all interrupts */ \
	TIMSK4 &= ~(1 << OCIE4A); 																					/* Disable timer compare interrupt */ \
	sei(); 																										/* Enable all interrupts */ \
})
#endif
#if TONE_GENERATION_TIMERS_COUNT >= 4																		// If there are at least 4 tone generation timers, timer5 is used (16bit timer [maximum 65535 increments until counter reset])
#define TIMER5_TONE_GENERATION_TIMER_INTERRUPT_SERVICE_ROUTINE TIMER5_COMPA_vect							// Define a constant for the selected tone generation timer's interrupt service routine
#define INITIALIZE_TONE_GENERATION_TIMER5(frequency) ({														/* Define a function for initializing the selected tone generation timer with the selected frequency */ \
	cli();																										/* Disable all interrupts */ \
	TCCR5A = 0;																									/* Set entire TCCRxA register to 0 */ \
	TCCR5B = 0;																									/* Set entire TCCRxB register to 0 */ \
	TCNT5  = 0;																									/* Initialize counter value to 0 */ \
	unsigned int timerPrescaler = 0;																			/* Set a variable for the timer prescaler */ \
	byte timerPrescalerRegisterBits = 0;																		/* Set a variable for the timer prescaler register bits */ \
	unsigned long compareMatchValue = 0;																		/* Set a variable for the compare-match register value */ \
	if (frequency == 0) {																						/* If the selected frequency is 0Hz (no sound) */ \
		timerPrescalerRegisterBits = (0 << CS52) | (0 << CS51) | (0 << CS50);										/* Set the timer prescaler register bits variable value for prescaler 0 (turning off the timer) */ \
		compareMatchValue = 0;																						/* Change the compare-match register variable value to 0 */ \
	} else {																									/* If the selected frequency is above 0Hz */ \
		timerPrescaler = 1;																							/* Set the timer prescaler variable value to 1 */ \
		timerPrescalerRegisterBits = (0 << CS52) | (0 << CS51) | (1 << CS50);										/* Set the timer prescaler register bits variable value for prescaler 1 */ \
		compareMatchValue = SYSTEM_CLOCK_FREQUENCY / (timerPrescaler * frequency * 4) - 1;							/* Change the compare-match register variable value to the value with the new prescaler */ \
		while (compareMatchValue > 65535) {																			/* Loop until the compare-match variable value is less than 65535 or equal to it */ \
			switch (timerPrescaler) {																					/* Check the value of the timer prescaler variable */ \
				case 1:																										/* If the timer prescaler variable value is 1 */ \
					timerPrescaler = 8;																							/* Set the timer prescaler variable value to 8 */ \
					timerPrescalerRegisterBits = (0 << CS52) | (1 << CS51) | (0 << CS50);										/* Set the timer prescaler register bits variable value for prescaler 8 */ \
					break;																										\
				case 8:																										/* If the timer prescaler variable value is 8 */ \
					timerPrescaler = 64;																						/* Set the timer prescaler variable value to 64 */ \
					timerPrescalerRegisterBits = (0 << CS52) | (1 << CS51) | (1 << CS50);										/* Set the timer prescaler register bits variable value for prescaler 64 */ \
					break;																										\
				case 64:																									/* If the timer prescaler variable value is 64 */ \
					timerPrescaler = 256;																						/* Set the timer prescaler variable value to 256 */ \
					timerPrescalerRegisterBits = (1 << CS52) | (0 << CS51) | (0 << CS50);										/* Set the timer prescaler register bits variable value for prescaler 256 */ \
					break;																										\
				case 256:																									/* If the timer prescaler variable value is 256 */ \
					timerPrescaler = 1024;																						/* Set the timer prescaler variable value to 1024 */ \
					timerPrescalerRegisterBits = (1 << CS52) | (0 << CS51) | (1 << CS50);										/* Set the timer prescaler register bits variable value for prescaler 1024 */ \
					break;																										\
				case 1024:																									/* If the timer prescaler variable value is 1024 (it means that the timer is not suitable for the desired frequency) */ \
					timerPrescaler = 0;																							/* Set the timer prescaler variable value to 0 */ \
					timerPrescalerRegisterBits = (0 << CS52) | (0 << CS51) | (0 << CS50);										/* Set the timer prescaler register bits variable value for prescaler 0 (turning off the timer) */ \
					break;																										\
			}																											\
			if (timerPrescaler > 0)																						/* If the timer prescaler variable value is greater than 0 (if the timer is working) */ \
				compareMatchValue = SYSTEM_CLOCK_FREQUENCY / (timerPrescaler * frequency * 4) - 1;							/* Change the compare-match register variable value to the value with the new prescaler */ \
		}																											\
	}																											\
	OCR5A = compareMatchValue;																					/* Set compare-match register increments for the desired frequency with the selected prescaler */ \
	TCCR5B |= (1 << WGM52);																						/* Set WGMx2 bit in the TCCRxB register for CTC mode */ \
	TCCR5B |= timerPrescalerRegisterBits;																		/* Set CSx2, CSx1 and CSx0 bits in the TCCRxB register for the selected prescaler */ \
	TIMSK5 &= ~(1 << OCIE5A);																					/* Disable timer compare interrupt */ \
	sei();																										/* Enable all interrupts */ \
})
#define ENABLE_TONE_GENERATION_TIMER5_INTERRUPTS() ({														/* Define a function for enabling the selected tone generation timer interrupts */ \
	cli(); 																										/* Disable all interrupts */ \
	if (TCCR5B & ((1 << CS52) | (1 << CS51) | (1 << CS50)) > 0)													/* If the timer is working (the timer prescaler is above 0) */ \
		TIMSK5 |= (1 << OCIE5A); 																					/* Enable timer compare interrupt */ \
	sei(); 																										/* Enable all interrupts */ \
})
#define DISABLE_TONE_GENERATION_TIMER5_INTERRUPTS() ({														/* Define a function for disabling the selected tone generation timer interrupts */ \
	cli(); 																										/* Disable all interrupts */ \
	TIMSK5 &= ~(1 << OCIE5A); 																					/* Disable timer compare interrupt */ \
	sei(); 																										/* Enable all interrupts */ \
})
#endif

// Defining functions for manipulating the associated tone generation timer of each melody instance and determining the assigning order of the timers (according to the tone generation timers count)
#if TONE_GENERATION_TIMERS_COUNT == 1																		// If there is 1 tone generation timer
#define INITIALIZE_TONE_GENERATION_TIMER(melodyInstanceIndex, frequency) ({									/* Define a function for initializing the associated tone generation timer of the selected melody instance with the selected frequency */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			INITIALIZE_TONE_GENERATION_TIMER1(frequency);																/* Call the initialization function of timer1 with the selected frequency */ \
			break;																										\
	}																											\
})
#define ENABLE_TONE_GENERATION_TIMER(melodyInstanceIndex) ({												/* Define a function for enabling the associated tone generation timer of the selected melody instance */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			ENABLE_TONE_GENERATION_TIMER1_INTERRUPTS();																	/* Call the enabling function of timer1 */ \
			break;																										\
	}																											\
})
#define DISABLE_TONE_GENERATION_TIMER(melodyInstanceIndex) ({												/* Define a function for disabling the associated tone generation timer of the selected melody instance */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			DISABLE_TONE_GENERATION_TIMER1_INTERRUPTS();																/* Call the disabling function of timer1 */ \
			break;																										\
	}																											\
})
#elif TONE_GENERATION_TIMERS_COUNT == 2																		// If there are 2 tone generation timers
#define INITIALIZE_TONE_GENERATION_TIMER(melodyInstanceIndex, frequency) ({									/* Define a function for initializing the associated tone generation timer of the selected melody instance with the selected frequency */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			INITIALIZE_TONE_GENERATION_TIMER1(frequency);																/* Call the initialization function of timer1 with the selected frequency */ \
			break;																										\
		case 1:																										/* If the melody instance index variable value is 1 */ \
			INITIALIZE_TONE_GENERATION_TIMER3(frequency);																/* Call the initialization function of timer3 with the selected frequency */ \
			break;																										\
	}																											\
})
#define ENABLE_TONE_GENERATION_TIMER(melodyInstanceIndex) ({												/* Define a function for enabling the associated tone generation timer of the selected melody instance */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			ENABLE_TONE_GENERATION_TIMER1_INTERRUPTS();																	/* Call the enabling function of timer1 */ \
			break;																										\
		case 1:																										/* If the melody instance index variable value is 1 */ \
			ENABLE_TONE_GENERATION_TIMER3_INTERRUPTS();																	/* Call the enabling function of timer3 */ \
			break;																										\
	}																											\
})
#define DISABLE_TONE_GENERATION_TIMER(melodyInstanceIndex) ({												/* Define a function for disabling the associated tone generation timer of the selected melody instance */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			DISABLE_TONE_GENERATION_TIMER1_INTERRUPTS();																/* Call the disabling function of timer1 */ \
			break;																										\
		case 1:																										/* If the melody instance index variable value is 1 */ \
			DISABLE_TONE_GENERATION_TIMER3_INTERRUPTS();																/* Call the disabling function of timer3 */ \
			break;																										\
	}																											\
})
#elif TONE_GENERATION_TIMERS_COUNT == 3																		// If there are 3 tone generation timers
#define INITIALIZE_TONE_GENERATION_TIMER(melodyInstanceIndex, frequency) ({									/* Define a function for initializing the associated tone generation timer of the selected melody instance with the selected frequency */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			INITIALIZE_TONE_GENERATION_TIMER1(frequency);																/* Call the initialization function of timer1 with the selected frequency */ \
			break;																										\
		case 1:																										/* If the melody instance index variable value is 1 */ \
			INITIALIZE_TONE_GENERATION_TIMER3(frequency);																/* Call the initialization function of timer3 with the selected frequency */ \
			break;																										\
		case 2:																										/* If the melody instance index variable value is 2 */ \
			INITIALIZE_TONE_GENERATION_TIMER4(frequency);																/* Call the initialization function of timer4 with the selected frequency */ \
			break;																										\
	}																											\
})
#define ENABLE_TONE_GENERATION_TIMER(melodyInstanceIndex) ({												/* Define a function for enabling the associated tone generation timer of the selected melody instance */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			ENABLE_TONE_GENERATION_TIMER1_INTERRUPTS();																	/* Call the enabling function of timer1 */ \
			break;																										\
		case 1:																										/* If the melody instance index variable value is 1 */ \
			ENABLE_TONE_GENERATION_TIMER3_INTERRUPTS();																	/* Call the enabling function of timer3 */ \
			break;																										\
		case 2:																										/* If the melody instance index variable value is 2 */ \
			ENABLE_TONE_GENERATION_TIMER4_INTERRUPTS();																	/* Call the enabling function of timer4 */ \
			break;																										\
	}																											\
})
#define DISABLE_TONE_GENERATION_TIMER(melodyInstanceIndex) ({												/* Define a function for disabling the associated tone generation timer of the selected melody instance */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			DISABLE_TONE_GENERATION_TIMER1_INTERRUPTS();																/* Call the disabling function of timer1 */ \
			break;																										\
		case 1:																										/* If the melody instance index variable value is 1 */ \
			DISABLE_TONE_GENERATION_TIMER3_INTERRUPTS();																/* Call the disabling function of timer3 */ \
			break;																										\
		case 2:																										/* If the melody instance index variable value is 2 */ \
			DISABLE_TONE_GENERATION_TIMER4_INTERRUPTS();																/* Call the disabling function of timer4 */ \
			break;																										\
	}																											\
})
#elif TONE_GENERATION_TIMERS_COUNT == 4																		// If there are 4 tone generation timers
#define INITIALIZE_TONE_GENERATION_TIMER(melodyInstanceIndex, frequency) ({									/* Define a function for initializing the associated tone generation timer of the selected melody instance with the selected frequency */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			INITIALIZE_TONE_GENERATION_TIMER1(frequency);																/* Call the initialization function of timer1 with the selected frequency */ \
			break;																										\
		case 1:																										/* If the melody instance index variable value is 1 */ \
			INITIALIZE_TONE_GENERATION_TIMER3(frequency);																/* Call the initialization function of timer3 with the selected frequency */ \
			break;																										\
		case 2:																										/* If the melody instance index variable value is 2 */ \
			INITIALIZE_TONE_GENERATION_TIMER4(frequency);																/* Call the initialization function of timer4 with the selected frequency */ \
			break;																										\
		case 3:																										/* If the melody instance index variable value is 3 */ \
			INITIALIZE_TONE_GENERATION_TIMER5(frequency);																/* Call the initialization function of timer5 with the selected frequency */ \
			break;																										\
	}																											\
})
#define ENABLE_TONE_GENERATION_TIMER(melodyInstanceIndex) ({												/* Define a function for enabling the associated tone generation timer of the selected melody instance */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			ENABLE_TONE_GENERATION_TIMER1_INTERRUPTS();																	/* Call the enabling function of timer1 */ \
			break;																										\
		case 1:																										/* If the melody instance index variable value is 1 */ \
			ENABLE_TONE_GENERATION_TIMER3_INTERRUPTS();																	/* Call the enabling function of timer3 */ \
			break;																										\
		case 2:																										/* If the melody instance index variable value is 2 */ \
			ENABLE_TONE_GENERATION_TIMER4_INTERRUPTS();																	/* Call the enabling function of timer4 */ \
			break;																										\
		case 3:																										/* If the melody instance index variable value is 3 */ \
			ENABLE_TONE_GENERATION_TIMER5_INTERRUPTS();																	/* Call the enabling function of timer5 */ \
			break;																										\
	}																											\
})
#define DISABLE_TONE_GENERATION_TIMER(melodyInstanceIndex) ({												/* Define a function for disabling the associated tone generation timer of the selected melody instance */ \
	switch (melodyInstanceIndex) {																				/* Check the value of the melody instance index variable */ \
		case 0:																										/* If the melody instance index variable value is 0 */ \
			DISABLE_TONE_GENERATION_TIMER1_INTERRUPTS();																/* Call the disabling function of timer1 */ \
			break;																										\
		case 1:																										/* If the melody instance index variable value is 1 */ \
			DISABLE_TONE_GENERATION_TIMER3_INTERRUPTS();																/* Call the disabling function of timer3 */ \
			break;																										\
		case 2:																										/* If the melody instance index variable value is 2 */ \
			DISABLE_TONE_GENERATION_TIMER4_INTERRUPTS();																/* Call the disabling function of timer4 */ \
			break;																										\
		case 3:																										/* If the melody instance index variable value is 3 */ \
			DISABLE_TONE_GENERATION_TIMER5_INTERRUPTS();																/* Call the disabling function of timer5 */ \
			break;																										\
	}																											\
})
#endif
#endif
