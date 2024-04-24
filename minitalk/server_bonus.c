/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:32:10 by tomecker          #+#    #+#             */
/*   Updated: 2024/04/24 16:11:59 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void	ft_putnbr(int n)
{
	char	c;

	if (n > 9)
	{
		ft_putnbr(n / 10);
	}
	c = (n % 10) + '0';
	write(1, &c, 1);
}

void converter(int signum, siginfo_t *info, void *context)
{
	static int	byte = 0;
	static int	i = 0;
	int			n;

	(void)context;
	if (signum == SIGUSR1)
	{
		n = 1;
		kill(info->si_pid, SIGUSR1);
	}
	else
	{
		n = 0;
		kill(info->si_pid, SIGUSR2);
	}
	byte <<= 1;
	byte |= n;
	i++;
	if (i == 8)
	{
		write(1, &byte, 1);
		byte = 0;
		i = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	b;

	pid = getpid();
	write(1, "The pid is: ", 12);
	ft_putnbr(pid);
	write(1, "\n", 1);
	b.sa_sigaction = &converter;
	sigemptyset(&b.sa_mask);
	b.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &b, NULL);
	sigaction(SIGUSR2, &b, NULL);
	while (1)
		pause();
}
