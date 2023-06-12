/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:40:33 by asekmani          #+#    #+#             */
/*   Updated: 2023/05/26 17:40:54 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int i;
	long long nb;

	i = 0;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	if (nb > INT_MAX)
    {
        printf("Error: inputs are not integer !!");
        exit(EXIT_FAILURE);
    }
	return (nb);
}

int     check_error(int arc, char **arv)
{
    int i;

    i = 1;
    while(i < arc)
    {
        if(is_digit(arv[i]) == 0)
        {
            printf("Error: Invalid inputs (not digits/unsigned int) !!");
            return(1);
        }
        ft_atoi(arv[i]);
        i++;
    }
    return(0);
}