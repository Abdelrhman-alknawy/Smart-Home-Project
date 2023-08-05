#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include "EXTI_Config.h"
#include "EXTI_Interface.h"
#include "EXTI_Private.h"

void (*GPF_1)(void) =NULL ;
void (*GPF_2)(void) =NULL ;
void (*GPF_3)(void) =NULL ;



void EXTI_VoidInit()
{

#if INT_ID == INT0
	/*ENABLE INT0*/
	SET_BIT(GICR_REG,6);
#if INT_SENSE_CONTROL == FALLING_EDGE

	/*Falling Edge */
	SET_BIT(MCUCR_REG,1);
	CLR_BIT(MCUCR_REG,0);
#elif INT_SENSE_CONTROL == RISING_EDGE
	/*RISING EDGE*/
	SET_BIT(MCUCR_REG,1);
	SET_BIT(MCUCR_REG,0);
#elif INT_SENSE_CONTROL == ON_CHANGE
		/*ANYCHANGE */
	CLR_BIT(MCUCR_REG,1);
	SET_BIT(MCUCR_REG,0);
#else
	/*LOW LEVEL */
	CLR_BIT(MCUCR_REG,1);
	CLR_BIT(MCUCR_REG,0);
#endif

#elif	INT_ID == INT1
	SET_BIT(GICR_REG,7);
	/*ENABLE INT1*/
		SET_BIT(GICR_REG,7);
	#if INT_SENSE_CONTROL == FALLING_EDGE

		/*Falling Edge */
		SET_BIT(MCUCR_REG,3);
		CLR_BIT(MCUCR_REG,2);
	#elif INT_SENSE_CONTROL == RISING_EDGE
		/*RISING EDGE*/
		SET_BIT(MCUCR_REG,3);
		SET_BIT(MCUCR_REG,2);
	#elif INT_SENSE_CONTROL == ON_CHANGE
			/*ANYCHANGE */
		CLR_BIT(MCUCR_REG,3);
		SET_BIT(MCUCR_REG,2);
	#else
		/*LOW LEVEL */
		CLR_BIT(MCUCR_REG,3);
		CLR_BIT(MCUCR_REG,2);
	#endif
#elif 		INT_ID == INT2
		/*ENABLE INT2 */
		SET_BIT(GICR_REG,5);
#if INT_SENSE_CONTROL == FALLING_EDGE

	/*Falling Edge */
	CLR_BIT(MCUCSR_REG,6);
#elif INT_SENSE_CONTROL == RISING_EDGE
	/*RISING EDGE*/
	SET_BIT(MCUCSR_REG,6);


#endif

#endif

}
void EXTI_VoidEnable(u8 Copy_u8InterruptNumber, u8 Copy_u8SenseControll)
{
	switch(Copy_u8InterruptNumber)
	{
			case INT0 : SET_BIT(GICR_REG,6);

				switch(Copy_u8SenseControll)
				{
					case FALLING_EDGE :
						/*Falling Edge */
						SET_BIT(MCUCR_REG,1);
						CLR_BIT(MCUCR_REG,0);
						break ;

					case RISING_EDGE :
						SET_BIT(MCUCR_REG,1);
						SET_BIT(MCUCR_REG,0);
						break;

					case ON_CHANGE :
					/*ANYCHANGE */
						CLR_BIT(MCUCR_REG,1);
						SET_BIT(MCUCR_REG,0);
						break;
					case LOW_LEVEL :
						CLR_BIT(MCUCR_REG,1);
						CLR_BIT(MCUCR_REG,0);
						 break ;
					default : break ;

				}

			break ;
				case INT1 : SET_BIT(GICR_REG,7);

				switch(Copy_u8SenseControll)
				{
					case FALLING_EDGE :
						/*Falling Edge */
						SET_BIT(MCUCR_REG,3);
						CLR_BIT(MCUCR_REG,2);
						break ;

					case RISING_EDGE :
						SET_BIT(MCUCR_REG,3);
						SET_BIT(MCUCR_REG,2);
						break;

					case ON_CHANGE :
					/*ANYCHANGE */
						CLR_BIT(MCUCR_REG,3);
						SET_BIT(MCUCR_REG,2);
						break;
					case LOW_LEVEL :
						CLR_BIT(MCUCR_REG,3);
						CLR_BIT(MCUCR_REG,2);
						 break ;
					default : break ;

				}
			break;
				case INT2 : SET_BIT(GICR_REG,5);

					switch(Copy_u8SenseControll)
					{
						case FALLING_EDGE :
							/*Falling Edge */
							CLR_BIT(MCUCSR_REG,6);
							break ;

						case RISING_EDGE :
							SET_BIT(MCUCSR_REG,6);

							break;
						default : break ;

					}
							break;



	}
}
void EXTI_VoidDisable(u8 Copy_u8InterruptNumber)
{
	switch (Copy_u8InterruptNumber )
	{
			case	INT0 :	CLR_BIT(GICR_REG,6);
								break ;
			case	INT1 :	CLR_BIT(GICR_REG,7);
											break ;
			case	INT2 :	CLR_BIT(GICR_REG,5);
											break ;
	}
}


void EXTI_SetCallBack_INT0(void(*LPF)(void))
{
	GPF_1  = LPF ;
}
void EXTI_SetCallBack_INT1(void(*LPF)(void))
{
	GPF_2  = LPF ;
}
void EXTI_SetCallBack_INT2(void(*LPF)(void))
{
	GPF_3  = LPF ;
}

void __vector_1 (void)	__attribute__((signal));

void __vector_1(void)
{
	if(GPF_1!=NULL)
		{
			GPF_1();
		}

}
void __vector_2(void)	__attribute__((signal));

void __vector_2(void)
{
	if(GPF_2!=NULL)
		{
			GPF_2();
		}
	GPF_2 =NULL;
}
void __vector_3(void)	__attribute__((signal));

void __vector_3(void)
{
	if(GPF_3!=NULL )
		{
			GPF_3();
		}
	GPF_3 = NULL ;
}

