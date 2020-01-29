void tempget()
{
  float gettemp[2];
  sensors.requestTemperatures();//获得传感器温度
  for(i=0;i<2;i++)
  {
    sensor_temp[i]=sensors.getTempCByIndex(i);
    if(sensor_temp[i]>0&&sensor_temp[i]<50)
        gettemp[i]=sensor_temp[i];//有可能读错 所以只保留正确的温度值
    else
    {
      Serial.print("sensor ");
      Serial.print(i); 
      Serial.println(" error");
    }
  }
  temp[0]=gettemp[1];
  temp[1]=gettemp[0];
  tempCurv[0]=-cos(((hour*60+minute)-120)/229.2994)*(tmax[0]-tmin[0])/2+(tmax[0]+tmin[0])/2;
  tempCurv[1]=-cos(((hour*60+minute)-120)/229.2994)*(tmax[1]-tmin[1])/2+(tmax[1]+tmin[1])/2;
   for(i=0;i<2;i++)//目标温度设置
  {
  if(automode[i]==true)
  tempNow[i]=tempCurv[i];
  else
  tempNow[i]=tempSet[i];
  }
  
}

