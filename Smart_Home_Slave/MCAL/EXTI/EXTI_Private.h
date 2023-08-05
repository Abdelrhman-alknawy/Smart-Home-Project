#ifndef EXTI_PRIVATE_C
#define EXTI_PRIVATE_C

#define MCUCR_REG            *((volatile u8 *)0x55)
#define MCUCSR_REG           *((volatile u8 *)0x54)
#define GICR_REG             *((volatile u8 *)0x5B)
#define GIFR_REG             *((volatile u8 *)0x5A)

#define  MCUCR_ISC00	0
#define  MCUCR_ISC01	1
#define  MCUCR_ISC10	2
#define  MCUCR_ISC11	3

#define  GICR_ISC00		0
#define  GICR_ISC01		1
#define  GICR_ISC10		2
#define  GICR_ISC11		3

#endif
