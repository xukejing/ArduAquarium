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
byte clockByte[5];
byte dateByte[5];
byte tempByte[4];
byte ledByte[4];
byte o3Byte[4];
int o3sec=0;

byte year, month, date, DoW, hour, minute, second,temperature;
float temp=0;
float temp1=0;
float tempNow=26;
int ctrlPin1=A2;
int ctrlPin2=A3;
int ctrlPin4=A1;
int ctrlPin3=A0;

byte i=0,j=0;//0~255
bool mark=false;
String comdata = "";
float tmax=28;
float tmin=22;

void setup()
{
	
  Wire.begin();
  
  pinMode(ctrlPin1, OUTPUT); 
  digitalWrite(ctrlPin1, HIGH); 
    pinMode(ctrlPin2, OUTPUT); 
  digitalWrite(ctrlPin2, HIGH); 
    pinMode(ctrlPin2, OUTPUT); 
  digitalWrite(ctrlPin2, HIGH); 
    pinMode(ctrlPin3, OUTPUT); 
  digitalWrite(ctrlPin3, HIGH); 
      pinMode(ctrlPin4, OUTPUT); 
  digitalWrite(ctrlPin4, HIGH); 
  sensors.begin();
  Serial.begin(9600);
}
void loop()
{
  comRead();
  sensors.requestTemperatures();
	temp1=sensors.getTempCByIndex(0);
        if(temp1>0&&temp<50)
        temp=temp1;
        else Serial.println("error is resolved");
	second=Clock.getSecond();
	minute=Clock.getMinute();
	hour=Clock.getHour(h12, PM);
	date=Clock.getDate();
	month=Clock.getMonth(Century);
	year=Clock.getYear();
	DoW=Clock.getDoW();
	temperature=Clock.getTemperature();
        tempNow=-cos(((hour*60+minute)-120)/229.2994)*(tmax-tmin)/2+(tmax+tmin)/2;
       
        
myDisplay();
myCtrl();
myCtrlLed();
myCtrlO3();
delay(1000);
}
void myDisplay(void)
{ 
     Serial.print("20");
  Serial.print(year,DEC);
  Serial.print('-');
  Serial.print(month,DEC);
  Serial.print('-');
  Serial.print(date,DEC);
  Serial.print(' ');
  Serial.print(hour,DEC);
  Serial.print(':');
  Serial.print(minute,DEC);
  Serial.print(':');
  Serial.print(second,DEC);
  Serial.print(' ');
  Serial.print("Temperature Air=");
  Serial.print(temperature); 
  Serial.print('\n');
  Serial.print("Temperature Water=");
  Serial.print(temp); 
    Serial.print(' ');
   Serial.print("Temperature Now=");
  Serial.print(tempNow); 
  Serial.print('\n');
}
void myCtrl()
{
  	if(temp<tempNow-0.2)
      digitalWrite(ctrlPin1, LOW);
    if(temp>tempNow+0.1)
      digitalWrite(ctrlPin1, HIGH);

    if(o3sec==0)  
   {
      
      if(hour>=14&&hour<=18)
      {
        if((minute==10||minute==20)||(minute==30||(minute==40||minute==50)))
          {
            if(second<=30)
            digitalWrite(ctrlPin2, LOW);
            else
            digitalWrite(ctrlPin2, HIGH);
          }
        else
          digitalWrite(ctrlPin2, HIGH);
      }
       else
          digitalWrite(ctrlPin2, HIGH);
}
      
  
  
}
void myCtrlLed()
{
  if(ledByte[0]==1)
      digitalWrite(ctrlPin3, LOW);
  else
      digitalWrite(ctrlPin3, HIGH);
   if(ledByte[1]==1)
      digitalWrite(ctrlPin4, LOW);
  else
      digitalWrite(ctrlPin4, HIGH);
      
}
void myCtrlO3()
{
  
  if(o3sec>0)
  {
      digitalWrite(ctrlPin2, LOW);
       Serial.print("O3 countdown=");
       Serial.print(o3sec); 
      Serial.print('\n');
      o3sec--;
  }
  else
      digitalWrite(ctrlPin2, HIGH);
}
void comRead(void)
{
  while (Serial.available() > 0)  
     {
         comdata += char(Serial.read());
         delay(2);
         mark=true;
         j=0;
     }
      if (mark==true)
     {
       
       if(comdata[0] == 'd')
          {
             for(i = 0; i < 4 ; i++)
             dateByte[i]=0;
             for(i = 1; i < comdata.length() ; i++)
               {
                  if(comdata[i] == ',')
                  j++;
                  else
                   {
                    dateByte[j]=dateByte[j]*10+(comdata[i]-'0');
                   }
                }
             Clock.setDoW(dateByte[3]);    //Set the day of the week
             Clock.setDate(dateByte[2]);  //Set the date of the month
             Clock.setMonth(dateByte[1]);  //Set the month of the year
             Clock.setYear(dateByte[0]);  //Set the year (Last two digits of the year)
          }
         else  if(comdata[0] == 't')
          {
             for(i = 0; i < 4 ; i++)
             clockByte[i]=0;
             for(i = 1; i < comdata.length() ; i++)
               {
                  if(comdata[i] == ',')
                  j++;
                  else
                   {
                    clockByte[j]=clockByte[j]*10+(comdata[i]-'0');
                   }
                }
             Clock.setHour(clockByte[0]);    //Set the day of the H
             Clock.setMinute(clockByte[1]);  //Set the date of the M
             Clock.setSecond(clockByte[2]);  //Set the month of the S
          } 
          else  if(comdata[0] == 'l')
          {
            for(i = 0; i < 4 ; i++)
             ledByte[i]=0;
             for(i = 1; i < comdata.length() ; i++)
               {
                  if(comdata[i] == ',')
                  j++;
                  else
                   {
                    ledByte[j]=ledByte[j]*10+(comdata[i]-'0');
                   }
                } 
          }
          else  if(comdata[0] == 'o')
          {
            for(i = 0; i < 4 ; i++)
             o3Byte[i]=0;
             for(i = 1; i < comdata.length() ; i++)
               {
                  if(comdata[i] == ',')
                  j++;
                  else
                   {
                    o3Byte[j]=o3Byte[j]*10+(comdata[i]-'0');
                   }
                } 
                o3sec=o3Byte[0]+o3Byte[1]*60;
                if(o3sec>=600)
                 o3sec=600;
          }
           mark=false;
           comdata = "";
     }
}

