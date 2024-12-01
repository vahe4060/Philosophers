/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyepremy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:09:27 by vyepremy          #+#    #+#             */
/*   Updated: 2024/07/27 16:56:09 by vyepremy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_dinner(t_philo *philos)
{
	
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init_args(argc, argv, &data) == EXIT_SUCCESS)
	{
		if (init_philos(&data) == EXIT_SUCCESS)
			start_dinner(data.philos);
		else
			message(MALLOC_ERROR);
	}
	else
		message(USAGE);
	return (0);
}
