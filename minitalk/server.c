/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:38:43 by tecker            #+#    #+#             */
/*   Updated: 2024/04/24 17:31:17 by tecker           ###   ########.fr       */
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

void	converter(int signum)
{
	static int	byte = 0;
	static int	i = 0;
	int			n;

	if (signum == SIGUSR1)
		n = 1;
	else
		n = 0;
	byte <<= 1;
	byte |= n;
	i++;
	if (i == 8)
	{
		if (byte == 0)
			write(1, "\n", 1);
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
	b.sa_handler = converter;
	sigemptyset(&b.sa_mask);
	b.sa_flags = 0;
	sigaction(SIGUSR1, &b, 0);
	sigaction(SIGUSR2, &b, 0);
	while (1)
		pause();
}
