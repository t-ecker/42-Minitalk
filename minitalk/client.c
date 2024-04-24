/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:09:34 by tecker            #+#    #+#             */
/*   Updated: 2024/04/24 15:58:59 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int	ft_atoi(char *str)
{
	int	i;
	int	number;

	number = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += (str[i] - 48);
		i++;
	}
	return (number);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	converter(char *str, int pid)
{
	int	i;
	int	j;
	int	res;

	j = 0;
	while (j < ft_strlen(str))
	{
		i = 7;
		while (i >= 0)
		{
			res = (str[j] >> i) & 1;
			if (res == 1)
				kill (pid, SIGUSR1);
			else
				kill (pid, SIGUSR2);
			i--;
			usleep(300);
		}
		j++;
	}
	i = 7;
    while (i >= 0)
	{
        kill(pid, SIGUSR2);
        i--;
        usleep(300);
    }
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
		return (write(1, "Error\n", 6), 1);
	pid = ft_atoi(argv[1]);
	converter(argv[2], pid);
	return (0);
}
