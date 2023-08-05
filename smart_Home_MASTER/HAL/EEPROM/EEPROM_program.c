
#include "../../LIB/STD_TYPES.h"
#define F_CPU	8000000UL
#include <util/delay.h>

#include "../../MCAL/TWI/TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_config.h"
#include "EEPROM_private.h"

void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte)
{
	u8 Local_add ;
	Local_add = EEPROM_FIXED_ADDRESS |(A2_CONNECTION<<2) | ((u8)(Copy_u16LocationAddress>>8)) ;

	/*Send start condition*/
	TWI_ErrorStatusSendStartConditionWithACK();

	/*Send the address packet*/
	TWI_ErrorStatusSendSlaveAddressWithWriteACK(Local_add);

	/*Send the rest 8bits of the location address*/
	TWI_ErrorStatusMasterWriteDataByteWithACK((u8)(Copy_u16LocationAddress));

	/*Send the data byte to the memory location*/
	TWI_ErrorStatusMasterWriteDataByteWithACK(Copy_u8DataByte);

	/*Send stop condition*/
	TWI_voidSendStopCondition();

	/*Delay until the write cycle is finished*/
	_delay_ms(10);

}

u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress)
{
	u8 Data ;
	u8 Local_add ;
	Local_add = EEPROM_FIXED_ADDRESS |(A2_CONNECTION<<2) | ((u8)(Copy_u16LocationAddress>>8)) ;
	/*Send start condition*/
	TWI_ErrorStatusSendStartConditionWithACK();
	/*Send the address packet with write request*/
	TWI_ErrorStatusSendSlaveAddressWithWriteACK(Local_add);
	/*Send the rest 8bits of the location address*/
	TWI_ErrorStatusMasterWriteDataByteWithACK((u8)(Copy_u16LocationAddress));
	/*Send repeated start to change write request into read request*/
	TWI_ErrorStatusSendRepeatedStartConditionWithACK();
	/*Send the address packet with read request*/
	TWI_ErrorStatusSendSlaveAddressWithReadACK(Local_add);
	/*Get the data from memory*/
	TWI_ErrorStatusMasterReadDataByteWithNACK(&Data);
	/*send the stop condition*/
	TWI_voidSendStopCondition();
	/*Delay until the write cycle is finished*/
	_delay_ms(10);
	//return data
	return Data ;
}

void EEPROM_voidSendWord(u16 Copy_u16LocationAddress , u16 Copy_u16DataByte )
{
	EEPROM_voidSendDataByte(Copy_u16LocationAddress ,  (u8)Copy_u16DataByte  );
	EEPROM_voidSendDataByte(Copy_u16LocationAddress+1 ,  (Copy_u16DataByte>>8)  );
}
u16 EEPROM_u16ReadWord(u16 Copy_u16LocationAddress )
{
	u8 DATA_LOW ;
	u8 DATA_HIGH ;
	u16 DATA ;
	DATA_LOW= 	EEPROM_u8ReadDataByte(Copy_u16LocationAddress );
	DATA_HIGH = EEPROM_u8ReadDataByte(Copy_u16LocationAddress+1);
	DATA = DATA_LOW +(DATA_HIGH<<8) ;
	return DATA ;
}
