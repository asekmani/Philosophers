/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:03:28 by asekmani          #+#    #+#             */
/*   Updated: 2023/05/24 12:11:28 by asekmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int arc, char **arv)
{
    t_table *table;

    table = NULL;
    if(arc < 5 || arc > 6)
    {
        printf("Eroor: Wrong number of arguments !!");
        exit(EXIT_FAILURE);
    }
    if (check_error(arc, arv) == 1)
        exit(EXIT_FAILURE);
    table_init(&table, arc, arv);
    if (!table)
		return (EXIT_FAILURE);
    if (start_simulation(table) == 0)
		return (EXIT_FAILURE);
    return(0);
}