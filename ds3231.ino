
void ds3231get()
{
	myclock.second = Clock.getSecond();
	myclock.minute = Clock.getMinute();
	myclock.hour = Clock.getHour(h12, PM);
	myclock.date = Clock.getDate();
	myclock.month = Clock.getMonth(Century);
	myclock.year = Clock.getYear();
	myclock.DoW = Clock.getDoW();
	myclock.temperature = Clock.getTemperature();
	time = myclock.hour + myclock.minute / 100.0;
}
void ds3231put1()
{
	Clock.setDoW(dataByte[3]);    //Set the day of the week
	Clock.setDate(dataByte[2]);  //Set the date of the month
	Clock.setMonth(dataByte[1]);  //Set the month of the year
	Clock.setYear(dataByte[0]);  //Set the year (Last two digits of the year)
 Serial.println(dataByte[0]);
}
void ds3231put2()
{
	Clock.setHour(dataByte[0]);    //Set the day of the H
	Clock.setMinute(dataByte[1]);  //Set the date of the M
	Clock.setSecond(dataByte[2]);  //Set the month of the S
}

