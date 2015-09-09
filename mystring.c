#include <stdlib.h>
#include "mystring.h"

int mystrlen(char * s)
{
	int count = 0;
	while (*s != '\0')
	{
		count ++;
		s ++;
	}
	return count;
}

char * mystrcpy(char * dest, char * src)
{
	char * in = src;
	char * cpy = dest;
	while (*in != '\0')
	{
		*cpy = *in;
		in ++;
		cpy ++;
	}
	*cpy = '\0';
	return dest;
}

char * mystrcat(char * dest, char * src)
{
	char * cpy = src;
	char * in = dest;
	while (*in != '\0')
	{
		in ++;
	}
	while (*cpy != '\0')
	{
		*in = *cpy;
		cpy ++;
		in ++;
	}
	*in = '\0';
	return dest;
}

int mystrcmp(char * s1, char * s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1 ++;
		s2 ++;
	}
	if (*s1 > *s2)
	{
		return 1;
	}
	else if (*s1 < *s2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

char * mystrstr(char * hay, char * needle)
{
	char * cpyHay = hay;
	char * cpyNeedle = needle;
	while (*cpyHay != '\0')
	{
		if (*cpyHay == *cpyNeedle)
		{
			char * foundN = cpyNeedle;
			char * foundH = cpyHay;
			while (*foundN != '\0' && *foundH != '\0' && *foundN == *foundH)
			{
				foundN ++;
				foundH ++;
			}
			if (*foundN == '\0')
			{
				return cpyHay;
			}
		}
		cpyHay ++;
	}
	return NULL;
}

char * mystrdup(char * s)
{
	char * cpy = malloc(mystrlen(s)*sizeof(char));
	mystrcpy(cpy, s);
	return cpy;
}

char * mymemcpy(char * dest, char * src, int n)
{
	char * cpyD = dest;
	char * cpyS = src;
	int count = 1;
	while (*cpyS != '\0' && count < n)
	{
		*cpyD = *cpyS;
		cpyD ++;
		cpyS ++;
		count ++;
	}
	return dest;
}
