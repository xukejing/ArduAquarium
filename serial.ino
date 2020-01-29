void comRead(void)
{
	ssRead();
	if (mark == true)
	{
		if (comdata[0] == 't')
		{
			ssAnalysis(2, 4);
			comReadControltest();
		}
		else if (comdata[0] == 's')
			comReadControl();
		else if (comdata[0] == 'S')
			setTime();
	
		mark = false;
		comdata = "";
	}
}
void setTime()
{
	if (comdata[1] == 'T')
	{
		ssAnalysis(2, 3);
		ds3231put2();
	}
	else if (comdata[1] == 'D')
	{
		ssAnalysis(2, 4);
		ds3231put1();
	}
}
void  comReadControl()
{
	int ii;
	
	if (comdata[1] == 't')
	{
		ssAnalysis(2, 2);
		setTempMax = dataByte[0];
		setTempMin = dataByte[1];
		if (setTempMax > 32)
			setTempMax = 32;
		else if (setTempMax < 12)
			setTempMax = 12;
		else if (setTempMin > 32)
			setTempMax = 32;
		else if (setTempMin < 12)
			setTempMax = 12;
		eepromputT();
	}
	else if (comdata[1] == 'B')
	{
		if(comdata[2] == 'n')
		{ 
			ssAnalysis(3, 1);
			bump_counts = dataByte[0];
			Serial.print("bump_c=");
			Serial.println(bump_counts);
		}
		else
		{
			ssAnalysis(2, 2);
			if (dataByte[0] == 0)
			{
				autoBUMP = false;
				Serial.println("bump_auto off");
				if (dataByte[1] == 0)
				{
					BUMP = false;
					Serial.println("bump off");//sB0,0,
         eepromputB();
				}
				else if (dataByte[1] == 1)
				{
					BUMP = true;
					Serial.println("bump on");//sB0,1,
          eepromputB();
				}
			}
			else if (dataByte[0] == 1)
			{
				autoBUMP = true;
				Serial.println("bump_auto on");//sB1,
       eepromputB();
			}
		}	
	}
	else if (comdata[1] == 'b')
	{
		if (comdata[2] == 'b')
		{
			eepromputB();
		}
		else if (comdata[2] == 'p')
		{
			Serial.print("There are ");
			Serial.print(bump_counts);
			Serial.println("bump control");
			for (ii = 0; ii < bump_counts; ii++)
			{
				Serial.print(ii);
				Serial.print(" open at T = ");
				Serial.print( bump_T_min[ii]);
				Serial.print(" and close at T = ");
				Serial.println(bump_T_max[ii]);
			}
		}
		else
		{
			ssAnalysis(2, 5);
			bump_T_min[dataByte[0]] = dataByte[1] + dataByte[2] / 100.0;
			bump_T_max[dataByte[0]] = dataByte[3] + dataByte[4] / 100.0;
			Serial.print(dataByte[0]);
			Serial.print(" open at T = ");
			Serial.print(bump_T_min[dataByte[0]]);
			Serial.print(" and close at T = ");
			Serial.println(bump_T_max[dataByte[0]]);
		}
	}
 else if (comdata[1] == 'o')
 {
  ssAnalysis(2, 2);
  o3_on=dataByte[0];
 }
}

void comWriteTime()
{
	Serial.print("20");
	Serial.print(myclock.year);
	Serial.print("/");
	Serial.print(myclock.month);
	Serial.print("/");
	Serial.print(myclock.date);
	Serial.print("/W");
	Serial.print(myclock.DoW);
	Serial.print(" ");
	Serial.print(myclock.hour);
	Serial.print(":");
	Serial.print(myclock.minute);
	Serial.print(":");
	Serial.println(myclock.second);
}
void comWriteTempur()
{
	Serial.print("Tmax=");
	Serial.print(setTempMax);
	Serial.print(" Tmin=");
	Serial.print(setTempMin);
	Serial.print(" SetT=");
	Serial.print(set_Temp);
	Serial.print(" T_real=");
	Serial.println(temp);
}
