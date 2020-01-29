void init_control()
{
	pinMode(pin_j1, OUTPUT);
	pinMode(pin_j2, OUTPUT);
  pinMode(pin_j3, OUTPUT);
	digitalWrite(pin_j1, HIGH);
	digitalWrite(pin_j2, HIGH);
 digitalWrite(pin_j3, HIGH);
	eepromgetT();
	eepromgetB();
}
void realtemp()
{
	set_Temp = -cos(((myclock.hour * 60 + myclock.minute) - 120) / 229.2994)*(setTempMax - setTempMin) / 2 + (setTempMax + setTempMin) / 2;
}
void tempur_control()
{
	realtemp();
	if (temp < set_Temp - 0.2)
		digitalWrite(pin_j1, LOW);
	else if (temp > set_Temp + 0.1)
		digitalWrite(pin_j1, HIGH);
}
void bump_control()
{
	byte ii = 0;
	if (autoBUMP)
	{
		for (bump_i = 0; bump_i < bump_counts; bump_i++)
		{
			if (time <= bump_T_max[bump_i] && time >= bump_T_min[bump_i])
				ii=ii+1;
		}
		if(ii>0)
			digitalWrite(pin_j2, LOW);
		else
			digitalWrite(pin_j2, HIGH);
	}
	else
	{
		if(BUMP)
			digitalWrite(pin_j2, LOW);
		else
			digitalWrite(pin_j2, HIGH);
	}
}
void o3_control()
{
  if(o3_on>0)
  {
    o3_on=o3_on-1;
    digitalWrite(pin_j3, LOW);
    Serial.print("O3--delay-- ");
    Serial.print(o3_on);
    Serial.println(" s");
  }
  else
  {
    if (time >= 8.0&&time <= 8.01)
    digitalWrite(pin_j3, LOW);
  else if (time >= 17.0&&time <= 17.01)
  digitalWrite(pin_j3, LOW);
  else
    digitalWrite(pin_j3, HIGH);
  }
	
}
