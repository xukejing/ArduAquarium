void ds3231get()
{
  second=Clock.getSecond();
  minute=Clock.getMinute();
  hour=Clock.getHour(h12, PM);
  date=Clock.getDate();
  month=Clock.getMonth(Century);
  year=Clock.getYear();
  DoW=Clock.getDoW();
  temperature=Clock.getTemperature();
}
void ds3231put1()
{
  Clock.setDoW(dateByte[3]);    //Set the day of the week
  Clock.setDate(dateByte[2]);  //Set the date of the month
  Clock.setMonth(dateByte[1]);  //Set the month of the year
  Clock.setYear(dateByte[0]);  //Set the year (Last two digits of the year)
}
void ds3231put2()
{
   Clock.setHour(dateByte[0]);    //Set the day of the H
   Clock.setMinute(dateByte[1]);  //Set the date of the M
   Clock.setSecond(dateByte[2]);  //Set the month of the S
}


