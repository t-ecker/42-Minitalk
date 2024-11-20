/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:09:34 by tecker            #+#    #+#             */
/*   Updated: 2024/11/20 18:35:37 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	handler_function(int sig)
{
	if (sig == SIGUSR1)
	{
		usleep(42);
		exit(0);
	}
	else if (sig == SIGUSR2)
		usleep(42);
}

void	converter_int(int num, int pid)
{
	struct sigaction	sa;
	int					i;

	sa.sa_handler = handler_function;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR2, &sa, NULL);
	i = 31;
	while (i >= 0)
	{
		if (1 == ((num >> i) & 1))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
		i--;
	}
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
	int					len;

	if (argc != 3 || (ft_strlen(argv[1]) > 5 && ft_strlen(argv[1]) < 4))
		return (write(1, "Error\n", 6), 1);
	i = 0;
	pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	converter_int(len, pid);
	b.sa_handler = handler_function;
	sigemptyset(&b.sa_mask);
	b.sa_flags = 0;
	sigaction(SIGUSR1, &b, NULL);
	while (argv[2][i])
		converter(argv[2][i++], pid);
	converter('\0', pid);
	pause();
	return (0);
}
