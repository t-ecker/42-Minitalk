/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:38:43 by tecker            #+#    #+#             */
/*   Updated: 2024/05/02 17:06:31 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	char_process(int *byte, int *char_count, siginfo_t **info)
{
	static char	*str = NULL;

	if (*char_count == 0)
	{
		str = malloc(*byte + 1);
		if (str == NULL)
			return (write(1, "Memory allocation failed\n", 25), exit(1));
		(str)[0] = '\0';
		(*char_count)++;
		*byte = 0;
		return ;
	}
	if (*byte == 0)
	{
		(str)[(*char_count)++ - 1] = '\0';
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		kill((*info)->si_pid, SIGUSR1);
		free(str);
		str = NULL;
		*char_count = 0;
	}
	else
		(str)[(*char_count)++ - 1] = *byte;
	*byte = 0;
}

void	converter(int signum, siginfo_t *info, void *context)
{
	static int	byte = 0;
	static int	i = 0;
	static int	char_count = 0;

	(void)context;
	if (char_count == 0)
	{
		byte = (byte << 1) | (signum == SIGUSR1);
		if (++i > 31)
		{
			char_process(&byte, &char_count, &info);
			i = 0;
		}
	}
	else
	{
		byte = (byte << 1) | (signum == SIGUSR1);
		if (++i == 8)
		{
			char_process(&byte, &char_count, &info);
			i = 0;
		}
	}
	usleep(100);
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	int					pid;
	struct sigaction	b;

	pid = getpid();
	write(1, "The pid is: ", 12);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	b.sa_sigaction = &converter;
	sigemptyset(&b.sa_mask);
	b.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &b, NULL);
	sigaction(SIGUSR2, &b, NULL);
	while (1)
		pause();
}
