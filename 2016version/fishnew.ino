#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <DS3231.h>
#define ONE_WIRE_BUS 8 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DS3231 Clock;
bool Century=false;
bool h12;
bool PM;
float dateByte[10];
bool automode[4];

byte year, month, date, DoW, hour, minute, second,temperature;
float temp[4];
float sensor_temp[4];
float tempNow[4];
float tempSet[4];
float tempCurv[2];
int ctrlPin[5];
byte hmin,hmax;

byte i=0,j=0;//0~255
bool mark=false;
String comdata = "";
float tmax[2];
float tmin[2];
unsigned long o3sec;
unsigned long bensec;
void setup()
{
	init_control();
  Wire.begin();
  sensors.begin();
  Serial.begin(9600);
}
void loop()
{
  comRead();

ds3231get();
tempget();
       
        
myDisplay();
myCtrl();

delay(1000);
}


