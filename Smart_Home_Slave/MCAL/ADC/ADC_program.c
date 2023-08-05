
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <util/delay.h>
#include"../../LIB/STATE.H"
#include "../../MCAL/DIO/DIO_Interface.h"
#include"ADC_config.h"
#include"ADC_private.h"
#include"ADC_interface.h"

ADC_STATE = IDLE;
 static u16 *GPu16Copy = NULL;
 static	void(*GPF)(void) =NULL;
void ADC_voidInit 	(void)
{


#if ReferenceSelection ==	AVCC
	//select ref voltage = AVCC
	//DIO_voidSetPortDirection(PORTA , INPUT);

	SET_BIT(ADMUX_REG , ADMUX_REFS0);
	CLR_BIT(ADMUX_REG , ADMUX_REFS1);
#elif	ReferenceSelection==	AREF
	CLR_BIT(ADMUX_REG , ADMUX_REFS0);
	CLR_BIT(ADMUX_REG , ADMUX_REFS1);
#elif ReferenceSelection==	INTREF
	SET_BIT(ADMUX_REG , ADMUX_REFS0);
	SET_BIT(ADMUX_REG , ADMUX_REFS1);

#endif
	#if ADC_RETURN == ADC_RIGHT
	//right adjust
	CLR_BIT(ADMUX_REG , ADMUX_ADLAR);
	#elif  ADC_RETURN == ADC_LEFT
	// LEFT ADJUST
	SET_BIT(ADMUX_REG , ADMUX_ADLAR);
	#endif
#if PRESCALER == PRE64
	SET_BIT(ADCSRA_REG , ADCSRA_ADPS2);
	SET_BIT(ADCSRA_REG , ADCSRA_ADPS1);
	CLR_BIT(ADCSRA_REG , ADCSRA_ADPS0);

#elif PRESCALER == PRE2
	CLR_BIT(ADCSRA_REG , ADCSRA_ADPS2);
	CLR_BIT(ADCSRA_REG , ADCSRA_ADPS1);
	CLR_BIT(ADCSRA_REG , ADCSRA_ADPS0);
#elif	PRESCALER == PRE4
	CLR_BIT(ADCSRA_REG , ADCSRA_ADPS2);
	SET_BIT(ADCSRA_REG , ADCSRA_ADPS1);
	CLR_BIT(ADCSRA_REG , ADCSRA_ADPS0);
#elif	PRESCALER == PRE4
	CLR_BIT(ADCSRA_REG , ADCSRA_ADPS2);
	SET_BIT(ADCSRA_REG , ADCSRA_ADPS1);
	SET_BIT(ADCSRA_REG , ADCSRA_ADPS0);
#elif	PRESCALER == PRE8
#endif
	//ADC Enable
	SET_BIT(ADCSRA_REG , ADCSRA_ADEN);
	//Disable Auto Trigger
	//#if	ADC_MODE == POLLING
	//CLR_BIT(ADCSRA_REG , ADCSRA_ADATE);

	//#elif ADC_MODE == INTERRUPT
		//enable Auto Trigger
	//SET_BIT(ADCSRA_REG , ADCSRA_ADATE);
		//enable PIE for ADC
	//SET_BIT(ADCSRA_REG , ADCSRA_ADIF);
	//#endif
	//prescaler 64


}
//..........................//
//.SWC:ASYNCHRONUS ADC 	   .//
//.I/O Arguments .//
//..........................//
//..........................//
//..........................//


//..........................//
//SWC : ADC_voidGetAnalogRead
//I/P ARGUMENTS : 0 -31
//Return : u32
//Func Descreption : Function that starting the conversion and return
// it to a u32
//..........................//
u16 ADC_u16GetAnalogReadSYNC(u8 Copy_Channel)
{

	//u32 Local_u32Counter ;
	//clear Mux from 0 to 4 (reg&0b11100000)
	ADMUX_REG &= ADC_CHANNEL_MASK ;
	//reg or with copy_channel
	ADMUX_REG |= Copy_Channel ;
	//start conversion
	SET_BIT(ADCSRA_REG , ADCSRA_ADSC);
	//polling flag
	while((GET_BIT(ADCSRA_REG,ADCSRA_ADIF))==0);
	//clear flag
	SET_BIT(ADCSRA_REG,ADCSRA_ADIF);
	//get reading right adjust
	//Local_u32ADCDigitalValue = ADCL_REG + (ADCH_REG << 8) ;
//
//	Local_u32ADCAnalogValue = (Local_u32ADCDigitalValue * 500) / 1024 ;

#if ADC_RETURN == BITS_10
	return ADC_REG ;
#elif  ADC_RETURN == BITS_8
	return ADCH_REG ;
#endif
}
//.................................................//
//................................................//
//.SWC:ADC_u16GetAnalogReadASYNC.................//
//.I/O:1-Copy_Channel(0-7)2-u8 *Pu8Reading......//
//.(*PF_NotificationFun).......................//
//.Function Desc:Asynchronus ADC using ISR ...//
//.NOTE!!!:Enable Global Interrupt in main...//
//..........................................//
u8 	ADC_u16GetAnalogReadASYNC(u8 Copy_Channel,u16 *Pu8Reading,void (*PF_NotificationFun)(void))
{
	u8	Local_uErrorState = OK;
	if(ADC_STATE == IDLE)
	{


		if((Pu8Reading==NULL)||(PF_NotificationFun==NULL))
		{
			Local_uErrorState = NOK;
		}
		else
		{
			//assign the value to gp
			GPu16Copy=Pu8Reading;
			GPF=PF_NotificationFun;
			//u32 Local_u32Counter ;
			//clear Mux from 0 to 4 (reg&0b11100000)
			ADMUX_REG &= ADC_CHANNEL_MASK ;
			//reg or with copy_channel
			ADMUX_REG |= Copy_Channel ;
			//start conversion
			SET_BIT(ADCSRA_REG , ADCSRA_ADSC);
			//enable Interrupt
			SET_BIT(ADCSRA_REG,ADC_ADIE);
		}
	}
	else {
		 Local_uErrorState = BUSY_FUNC;
	}
		return Local_uErrorState ;
}

void __vector_16(void) __attribute__((signal));

void __vector_16(void)
{

	//Read ADC Result
	*GPu16Copy=ADC_REG;
	//Change the state of ADC TO IDLE
	ADC_STATE = IDLE ;
	//Invoke Notification func
	GPF();
	//Disable Interrupt
	CLR_BIT(ADCSRA_REG,ADC_ADIE);
}
