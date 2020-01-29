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
  Serial.print("TA=");
  Serial.print(temperature); 
  Serial.print('\n');
  Serial.print("T1=");
  Serial.print(temp[0]); 
  Serial.print(' ');
  Serial.print("T2=");
  Serial.print(temp[1]); 
  Serial.print(' ');
  Serial.print("T1N=");
  Serial.print(tempNow[0]); 
  Serial.print(' ');
   Serial.print("T2N=");
  Serial.print(tempNow[1]); 
  Serial.print('\n');
}
void myDisplay2(void)
{ 
  byte dispbyte[4];

   for(i = 0; i < 4 ; i++)
   {
    if(automode[i]==true)
    dispbyte[i]=1;
    else
    dispbyte[i]=0;
   }
  Serial.print("automode: ");
  for(i = 0; i < 4 ; i++)
   { 
    Serial.print(dispbyte[i]); 
    Serial.print(' ');
    }
  Serial.print('\n');
  
  Serial.print("TminTmax: ");
    Serial.print(tmin[0]); 
    Serial.print(' ');
    Serial.print(tmax[0]); 
    Serial.print(' ');
    Serial.print(tmin[1]); 
    Serial.print(' ');
    Serial.print(tmax[1]); 
    Serial.print(' ');
  Serial.print('\n');
    Serial.print("tSet: ");
    Serial.print(tempSet[0]); 
    Serial.print(' ');
    Serial.print(tempSet[1]); 
    Serial.print(' ');
  Serial.print('\n');
      Serial.print("HminHmax: ");
    Serial.print(hmin); 
    Serial.print(' ');
    Serial.print(hmax); 
    Serial.print(' ');
  Serial.print('\n');

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
         if(comdata[0] == 'd')
         ds3231put1();
         if(comdata[0] == 't')
         ds3231put2();
         if(comdata[0] == 'o')
         {
          if(automode[3]==false)
          o3sec=dateByte[0];
         }
         if(comdata[0] == 'b')
         {
          if(automode[2]==false)
          bensec=dateByte[0];
         }
         if(comdata[0] == 'a')
         {
          for(i = 0; i < 4 ; i++)
            { 
            if(dateByte[i]==0)
            automode[i]=true;
            else
            automode[i]=false;
            }
         }
          if(comdata[0] == 'T')
         {
          for(i=0;i<2;i++)
            {  if(dateByte[i]>=18&&dateByte[i]<=28)
                tempSet[i]=dateByte[i];
            }
          
         }
            if(comdata[0] == 'h')
         {
          hmin=dateByte[0];
          hmax=dateByte[1];
          
         }
           if(comdata[0] == 'm')
         {
          
            if(dateByte[0]>=18&&dateByte[0]<=28)
                tmin[0]=dateByte[0];
            if(dateByte[1]>=18&&dateByte[1]<=28)
                tmax[0]=dateByte[1];
            if(dateByte[2]>=18&&dateByte[2]<=28)
                tmin[1]=dateByte[2];
            if(dateByte[3]>=18&&dateByte[3]<=28)
                tmax[1]=dateByte[3];
            for(i=0;i<2;i++)
            {
              if(tmin[i]>tmax[i])
              tmax[i]=tmin[i]+1;
            }
          
         }
         if(comdata[0] == 'p')
         myDisplay2();
                
          mark=false;
          comdata = "";
     }
}

