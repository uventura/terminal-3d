int approach(float n)
{
	int int_n = n;
	if(abs(int_n - n) >= 0.5)
	{
		if(n - int_n > 0)
			return int_n + 1;
		else
			return int_n - 1;
	}

	return int_n;
}

float rad(float degrees)
{
	return (degrees * 3.14) / 180;
}