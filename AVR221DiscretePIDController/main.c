#include "atmel_start.h"
#include "stdint.h"
#include "pid.h"

/*! \brief P, I and D parameter values
 *
 * The K_P, K_I and K_D values (P, I and D gains)
 * need to be modified to adapt to the application at hand
 */
//! \xref item todo "Todo" "Todo list"
#define K_P 1.00
//! \xref item todo "Todo" "Todo list"
#define K_I 0.00
//! \xref item todo "Todo" "Todo list"
#define K_D 0.00

/*! \brief Flags for status information
 */
struct GLOBAL_FLAGS {
	//! True when PID control loop should run one time
	uint8_t pidTimer : 1;
	uint8_t dummy : 7;
} gFlags = {0, 0};

//! Parameters for regulator
struct PID_DATA pidData;

/*! \brief Sampling Time Interval
 *
 * Specify the desired PID sample time interval
 * With a 8-bit counter (255 cylces to overflow), the time interval value is calculated as follows:
 * TIME_INTERVAL = ( desired interval [sec] ) * ( frequency [Hz] ) / 255
 */
//! \xref item todo "Todo" "Todo list"
#define TIME_INTERVAL 157

ISR(TIMER0_OVF_vect)
{
	static uint16_t i = 0;

	if (i < TIME_INTERVAL) {
		i++;
	} else {
		gFlags.pidTimer = 1;
		i               = 0;
	}
}

/*! \brief Init of PID controller demo
 */
void Init(void)
{
	pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR, K_D * SCALING_FACTOR, &pidData);

	// Set up timer, enable timer/counter 0 overflow interrupt
	TCCR0B = (1 << CS00); // clock source to be used by the Timer/Counter clkI/O
	TIMSK0 = (1 << TOIE0);
	TCNT0  = 0;
}

/*! \brief Read reference value.
 *
 * This function must return the reference value.
 * May be constant or varying
 */
int16_t Get_Reference(void)
{
	return 8;
}

/*! \brief Read system process value
 *
 * This function must return the measured data
 */
int16_t Get_Measurement(void)
{
	return 4;
}

/*! \brief Set control input to system
 *
 * Set the output from the controller as input
 * to system.
 */
void Set_Input(int16_t inputValue)
{
	;
}

/*! \brief Demo of PID controller
 */
void main(void)
{
	int16_t referenceValue, measurementValue, inputValue;
	system_init();
	// Configure Power reduction register to enable the Timer0 module
	// Atmel START code by default configures PRR to reduce the power consumption.
	PRR &= ~(1 << PRTIM0);
	Init();
	sei();

	while (1) {
		// Run PID calculations once every PID timer timeout
		if (gFlags.pidTimer == 1) {
			referenceValue   = Get_Reference();
			measurementValue = Get_Measurement();

			inputValue = pid_Controller(referenceValue, measurementValue, &pidData);

			Set_Input(inputValue);

			gFlags.pidTimer = FALSE;
		}
	}
}

/*! \mainpage
 * \section Intro Introduction
 * This documents data structures, functions, variables, defines, enums, and
 * typedefs in the software for application note AVR221.
 *
 *
 * \section DI Device Info
 *
 *
 * \section TDL ToDo List
 * \todo Write own code in:
 * \ref Get_Reference(void), \ref Get_Measurement(void) and \ref Set_Input(int16_t inputValue)
 *
 * \todo Modify the \ref K_P (P), \ref K_I (I) and \ref K_D (D) gain to adapt to your application
 * \todo Specify the sampling interval time \ref TIME_INTERVAL
 */
