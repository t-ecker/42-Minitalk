/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:29:02 by tomecker          #+#    #+#             */
/*   Updated: 2024/04/26 18:07:16 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <unistd.h>

void converter_int(int c, int pid)
{
	int res;
	int i;
	i = 31;
	while (i >= 0)
	{
		res = (c >> i) & 1;
		if (res == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(42);
		i--;
	}
}

void	handler_function(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "\nMessage sent successfully\n\n", 28);
		exit(1);
	}
	if (sig == SIGUSR2)
		usleep(42);
}

void	converter(char c, int pid)
{
	int					i;
	int					res;
	struct sigaction	sa;

	sa.sa_handler = handler_function;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR2, &sa, NULL);
	i = 7;
	while (i >= 0)
	{
		res = (c >> i) & 1;
		if (res == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
		i--;
	}
}

int	main(int argc, char *argv[])
{
	int					i;
	int					pid;
	struct sigaction	b;
	int len;

	i = 0;
	b.sa_handler = handler_function;
	sigemptyset(&b.sa_mask);
	b.sa_flags = 0;
	sigaction(SIGUSR1, &b, NULL);
	if (argc != 3 || (ft_strlen(argv[1]) > 5 && ft_strlen(argv[1]) < 4))
		return (write(1, "Error\n", 6), 1);
	pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	printf("%i\n", len);
	converter(len, pid);
	while (argv[2][i])
		converter(argv[2][i++], pid);
	converter('\0', pid);
	pause();
	return (0);
}

