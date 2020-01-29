#include <EEPROM.h>
void eepromputT()
{
	//Serial.print("epprom put ");
	int eeAddress = 0;
	EEPROM.put(eeAddress, setTempMax);
	eeAddress += 4;
	EEPROM.put(eeAddress, setTempMin);
	//Serial.println("done");
}
void eepromgetT()
{
	//Serial.print("epprom get ");
	int eeAddress = 0;
	EEPROM.get(eeAddress, setTempMax);
	eeAddress += 4;
	EEPROM.get(eeAddress, setTempMin);
	//Serial.println("done");
}
void eepromputB()
{
	int ii;
	//Serial.print("epprom put ");
	int eeAddress = 8;
	EEPROM.put(eeAddress, autoBUMP);
	eeAddress += 1;
	EEPROM.put(eeAddress, bump_counts);
	eeAddress += 1;
	for (ii = 0; ii < bump_counts; ii++)
	{
		EEPROM.put(eeAddress, bump_T_max[ii]);
		eeAddress += 4;
		EEPROM.put(eeAddress, bump_T_min[ii]);
		eeAddress += 4;
	}
	//Serial.println("done");
}
void eepromgetB()
{
	int ii;
	//Serial.print("epprom put ");
	int eeAddress = 8;
	EEPROM.get(eeAddress, autoBUMP);
	eeAddress += 1;
	EEPROM.get(eeAddress, bump_counts);
	eeAddress += 1;
	for (ii = 0; ii < bump_counts; ii++)
	{
		EEPROM.get(eeAddress, bump_T_max[ii]);
		eeAddress += 4;
		EEPROM.get(eeAddress, bump_T_min[ii]);
		eeAddress += 4;
	}
	//Serial.println("done");
}