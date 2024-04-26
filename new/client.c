/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:09:34 by tecker            #+#    #+#             */
/*   Updated: 2024/04/25 22:01:05 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_function(int sig)
{
	if (sig == SIGUSR2)
		usleep(20);
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
	int	i;
	int	pid;

	i = 0;
	if (argc != 3 || (ft_strlen(argv[1]) > 5 && ft_strlen(argv[1]) < 4))
		return (write(1, "Error\n", 6), 1);
	pid = ft_atoi(argv[1]);
	while (argv[2][i])
		converter(argv[2][i++], pid);
	converter('\0', pid);
	return (0);
}
