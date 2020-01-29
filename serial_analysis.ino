
void ssRead()
{
	while (Serial.available() > 0)
	{
		comdata += char(Serial.read());
		delay(2);
		mark = true;
		j = 0;
	}
}
void ssAnalysis(byte datastart, byte datalong)
{
	for (i = 0; i < datalong; i++)
		dataByte[i] = 0;
	for (i = datastart; i < comdata.length(); i++)
	{
		if (comdata[i] == ',')
			j++;
		else
		{
			dataByte[j] = dataByte[j] * 10 + (comdata[i] - '0');
		}
	}
}

