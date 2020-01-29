#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <DS3231.h>



#define ONE_WIRE_BUS  2//8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DS3231 Clock;
struct MyStruct
{
	byte year, month, date, DoW, hour, minute, second, temperature;
};
MyStruct myclock;

bool Century = false;
bool h12;
bool PM;
bool autoBUMP = true;
bool BUMP = false;
String comdata = "";
bool mark = false;
unsigned int dataByte[10] = { 0 };

byte i,j;


float temp = 0;
float temp10 = 0;
float set_Temp=0;
float set_Temp10 = 0;
float setTempMax=0;
float setTempMin=0;

float time = 0;
byte bump_i = 0;
byte bump_counts = 1;
float bump_T_max[20] = { 0 };

float bump_T_min[20] = { 0 };

int o3_on=0;


void setup()
{

	Wire.begin();
	sensors.begin();
	Serial.begin(9600);
	init_control();
	//delay(5000);
Serial.println("hello xkj");
}

void loop()
{
	comRead();
	ds3231get();
	sensors.requestTemperatures();
	temp = sensors.getTempCByIndex(0);
	comWriteTime();
	comWriteTempur();
	tempur_control();
	bump_control();
	o3_control();
 delay(1000);
}

