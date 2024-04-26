/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:29:02 by tomecker          #+#    #+#             */
/*   Updated: 2024/04/26 15:55:23 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_function2(int sig)
{
	if (sig == SIGUSR2)
		usleep(20);
}

void	handler_function(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "\nMessage sent successfully\n\n", 28);
		exit(1);
	}
}

void	converter(char c, int pid)
{
	int					i;
	int					res;
	struct sigaction	sa;

	sa.sa_handler = handler_function2;
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
		i--;
	}
		pause();
}

int	main(int argc, char *argv[])
{
	int					i;
	int					pid;
	struct sigaction	b;

	i = 0;
	b.sa_handler = handler_function;
	sigemptyset(&b.sa_mask);
	b.sa_flags = 0;
	sigaction(SIGUSR1, &b, NULL);
	if (argc != 3 || (ft_strlen(argv[1]) > 5 && ft_strlen(argv[1]) < 4))
		return (write(1, "Error\n", 6), 1);
	pid = ft_atoi(argv[1]);
	while (argv[2][i])
		converter(argv[2][i++], pid);
	converter('\0', pid);
	pause();
	return (0);
}
