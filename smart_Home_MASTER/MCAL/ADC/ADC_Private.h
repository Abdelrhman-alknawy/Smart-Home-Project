#ifndef _ADC_PRIVATE_H_
#define _ADC_PRIVATE_H_

/*=========================================================================================
 * ADC Registers
 *=========================================================================================*/


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ACSR_REG       	*((volatile u8*)0x28)
#define ADMUX_REG       *((volatile u8*)0x27)//ADC multiplixer selection register
#define ADC_CHANNEL_MASK	0b11100000 // mask to make the msb bits as configured in intit
/*ADMUX Reg*/
#define ADMUX_MUX0      0
#define ADMUX_MUX1      1
#define ADMUX_MUX2		2
#define ADMUX_MUX3		3
#define ADMUX_MUX4		4
#define ADMUX_ADLAR		5
#define ADMUX_REFS0		6 //
#define ADMUX_REFS1		7


#define ADCSRA_REG      *((volatile u8*)0x26)//ADC CONTROL AND STATUS REG
/*ADCSRA Reg*/
#define ADCSRA_ADPS0    0//ADC Prescaler Select Bitss
#define ADCSRA_ADPS1    1//ADC Prescaler Select Bits
#define ADCSRA_ADPS2	2// ADC Prescaler Select Bits
#define ADCSRA_ADIE 	3// ADC Interrupt Enable
#define ADCSRA_ADIF		4// ADC Interrupt Flag
#define ADCSRA_ADATE	5//ADC Auto Trigger Enable
#define ADCSRA_ADSC		6//adc start conversion
#define ADCSRA_ADEN		7//adc enable

#define ADCH_REG        *((volatile u8*)0x25)// ADC HIGH REG (LEFT)

#define ADCL_REG        *((volatile u8*)0x24)// ADC LOW REG (RIGHT)
#define ADC_REG			*((volatile u16 *)0x24)//TO GET THE WHOLE PORTWHEN USING RIGHT

#endif


/*ADCSRA Reg*/
#define ADC_ADPS0       0
#define ADC_ADPS1       1
#define ADC_ADPS2		2
#define ADC_ADIE		3
#define ADC_ADIF		4
#define ADC_ADATE		5
#define ADC_ADSC		6
#define ADC_ADEN		7

/*SFIOR Reg*/
#define ADC_ADTS0	    5
#define ADC_ADTS1		6
#define ADC_ADTS2 		7

/*=========================================================================================
 * Config parameters
 *=========================================================================================*/

/*VREF Select*/
#define ADC_AREF		            0
#define ADC_AVCC					1
#define ADC_INTERNAL_VREF			3

/*ADC Adjustment*/
#define	ADC_RIGHT_ADJUSTMENT		0
#define ADC_LEFT_ADJUSTMENT			1

/*ADC Interrupt State*/
#define ADC_INT_DISABLED			0
#define ADC_INT_ENABLED				1

/*ADC Input CLK Prescaler*/
#define ADC_PRESCALER_2				1
#define ADC_PRESCALER_4				2
#define ADC_PRESCALER_8				3
#define ADC_PRESCALER_16			4
#define ADC_PRESCALER_32			5
#define ADC_PRESCALER_64			6
#define ADC_PRESCALER_128			7
#define ADC_PRE_PRESCALER			0b11111000
/*ADC Trigger Sources */
#define ADC_FREE_RUNNING           0
#define ADC_ANALOG_COMPARATOR      1
#define ADC_EXTERNAL_INT           2
#define ADC_TIMER0_COMPARE_MATCH   3
#define ADC_TIMER0_OVER_FLOW       4
#define ADC_TIMERB_COMPARE_MATCH   5
#define ADC_TIMER1_OVER_FLOW       6
#define ADC_TIMER1_CAPTURE_EVENT   7

/*ADC AAuto Trigger State*/
#define ADC_AUTO_TRIGGER_DISABLED  0
#define ADC_AUTO_TRIGGER_ENABLED   1
/*-----------------------------------------------------------------*/
// PRESCALER OF THE ADC




#endif
