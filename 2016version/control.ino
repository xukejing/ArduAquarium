void init_control()
{
 for(i=0;i<2;i++)//参数初始化
 {
 temp[i]=21;
 sensor_temp[i]=21;
 tempNow[i]=21;
 tempSet[i]=21;
 tmax[i]=23;
 tmin[i]=20;
 }
 hmin=8;
 hmax=21;

 ctrlPin[0]=A2;//控制引脚定义
 ctrlPin[1]=A3;
 ctrlPin[2]=A1;
 ctrlPin[3]=A0;
 
 for(i=0;i<4;i++)//控制引脚初始化
 {
  pinMode(ctrlPin[i], OUTPUT); 
  digitalWrite(ctrlPin[i], HIGH); 
  automode[i]=true;
 }
}
void myCtrl()
{
  for(i=0;i<2;i++)//温控
  {
    if(temp[i]<tempNow[i]-0.2)
      digitalWrite(ctrlPin[i], LOW);
    if(temp[i]>tempNow[i]+0.1)
      digitalWrite(ctrlPin[i], HIGH); 
  }
  if(automode[2]==true)//水泵
  {
    if(hour>=hmin&&hour<=hmax)
      digitalWrite(ctrlPin[2], LOW);
    else
      digitalWrite(ctrlPin[2], HIGH); 
  }
  else
  {
     if(bensec>0)
      {
       digitalWrite(ctrlPin[2], LOW);
       Serial.print("Ben=");
       Serial.print(bensec); 
       Serial.print('\n');
       bensec--;
      }
    else
      digitalWrite(ctrlPin[2], HIGH); 
    
  }
    
    if(automode[3]==true)//臭氧
  {
    if((hour>=12&&hour<=16)&&(minute>=0&&minute<=2))
      digitalWrite(ctrlPin[3], LOW);
    else
      digitalWrite(ctrlPin[3], HIGH); 
  }
  else
    {
     if(o3sec>0)
      {
       digitalWrite(ctrlPin[3], LOW);
       Serial.print("O3=");
       Serial.print(o3sec); 
       Serial.print('\n');
       o3sec--;
      }
    else
      digitalWrite(ctrlPin[3], HIGH); 
    }
  
    

    
}

