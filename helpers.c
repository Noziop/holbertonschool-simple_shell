#include "StarHeader.h"
/**
 * _atoi - from a char string, extract numbers, and convert into int
 *@s: string to be tested
*
* Return: 0 if success
*/
int _atoi(char *s)
{
		int a, sign, numb;

		a = 0, sign = 1, numb = 0;

		while (s[a] != '\0')
		{
			if (s[a] == '-')
				sign *= -1;
			if (s[a] >= '0' && s[a] <= '9')
			{
				while (s[a] >= '0' && s[a] <= '9')
				{
					numb = (s[a] - '0') * sign + numb * 10;
					a++;
				}
				break;
			}
			a++;
		}
		return (numb);
}
