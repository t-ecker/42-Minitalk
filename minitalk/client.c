/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:09:34 by tecker            #+#    #+#             */
/*   Updated: 2024/04/23 14:36:53 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int ft_atoi(char *str)
{
	int i;
	int number;
	
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
int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
void converter(char *str, int pid)
{
	int i;
	int j;
	int res;

	j = 0;
	while (j < ft_strlen(str))
	{
		i = 7;
		while(i >= 0)
		{
			res = (str[j] >> i) & 1;
			if (res == 1)
				kill (pid, SIGUSR1);
				// write(1, "1", 1);
			else
				kill (pid, SIGUSR2);
				// write(1, "0", 1);
			i--;
			usleep(300);
		}
		write(1, "\n", 1);
		j++;
	}
}

int	main(int argc, char *argv[])
{
	int pid;
	if (argc != 3)
		write(1, "Error\n", 6);
	pid = ft_atoi(argv[1]);
	converter(argv[2], pid);
	return (0);
}
