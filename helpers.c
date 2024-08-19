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

/**
 * is_valid_number - checks if exit code is a valid number.
 * @str: string to be tested
 * Return: 1 if valid
 *			0 if not valid
 */
int is_valid_number(const char *str)
{
	int i = 0;

	if (str[0] == '+')
		i++;

	for (; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}

	return (1);
}

