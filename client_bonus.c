/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:29:02 by tomecker          #+#    #+#             */
/*   Updated: 2024/04/24 18:17:15 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

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

void	converter(char c, int pid)
{
	int	i;
	int	res;

	i = 7;
	while (i >= 0)
	{
		res = (c >> i) & 1;
		if (res == 1)
			kill (pid, SIGUSR1);
		else
			kill (pid, SIGUSR2);
		i--;
		usleep(420);
	}
}

void	handler_function(int sigum)
{
	if (sigum == SIGUSR1)
		write(1, "Message Received\n", 17);
}

int	main(int argc, char *argv[])
{
	int	i;
	int	pid;

	i = 0;
	signal(SIGUSR1, handler_function);
	if (argc != 3 || ft_strlen(argv[1]) != 5)
		return (write(1, "Error\n", 6), 1);
	pid = ft_atoi(argv[1]);
	while (argv[2][i])
		converter(argv[2][i++], pid);
	converter('\0', pid);
	return (0);
}
