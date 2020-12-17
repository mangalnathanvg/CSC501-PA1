#include <stdio.h>
#include <math.h>
#include <kernel.h>

/* Calculate Power of x with y as exponent */
double pow(double x, int y)
{
	double result = 1;

	if (y==0)
	{
		return result;
	}
	
	if (y==1)
	{
		return x;
	}
	
	int exp = y;

	while ( exp > 0 )
	{
		result = result * x;
		exp--;
	}

	return result;
}

/* Log function using the Taylor Series Expansion Formula in Wikipedia */
double log(double x)
{
	if(x < 0)
	{
		return SYSERR;	
	}
	
	double logResult = 0;
	
	int i;
	
	for(i = 1; i<=20; i++)
	{
		logResult = logResult + (pow(-1, i-1) * (pow(x-1, i)/i));
	}

	return logResult;
	
}

/* Function to generate random number based on exponential distribution */
double expdev(double lambda)
{
	
	double dummy;
	do
		dummy = (double) rand()/RAND_MAX;
	while (dummy == 0.0);
	
	return -log(dummy) / lambda;
}
