/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:32:10 by tomecker          #+#    #+#             */
/*   Updated: 2024/04/25 21:37:02 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_buffer_size = 512;

void	my_realloc(char **ptr)
{
	char	*new_ptr;

	if (*ptr == NULL)
	{
		*ptr = malloc((g_buffer_size) * sizeof(char));
		if (*ptr == NULL)
		{
			write(1, "Memory allocation failed\n", 25);
			exit(1);
		}
		(*ptr)[0] = '\0';
	}
	else
	{
		new_ptr = malloc((g_buffer_size) * sizeof(char));
		if (new_ptr == NULL)
		{
			write(1, "Memory allocation failed\n", 25);
			free(*ptr);
			exit(1);
		}
		ft_memcpy(new_ptr, *ptr, ft_strlen(*ptr));
		free(*ptr);
		*ptr = new_ptr;
	}
}

void	char_process(int *byte, int *char_count, char **str, siginfo_t **info)
{
	if (*byte == 0)
	{
		write(1, *str, ft_strlen(*str));
		write(1, "\n", 1);
		kill((*info)->si_pid, SIGUSR1);
		free(*str);
		*str = NULL;
		g_buffer_size = 512;
		*char_count = 0;
	}
	else
	{
		if (*char_count < g_buffer_size)
			(*str)[(*char_count)++] = *byte;
	}
	*byte = 0;
}

void	converter(int signum, siginfo_t *info, void *context)
{
	static int	byte = 0;
	static int	i = 0;
	static int	char_count = 0;
	static char	*str = NULL;
	int			n;

	kill(info->si_pid, SIGUSR2);
	(void)context;
	if (signum == SIGUSR1)
		n = 1;
	else
		n = 0;
	byte <<= 1;
	byte |= n;
	i++;
	if (char_count == g_buffer_size || str == NULL)
	{
		g_buffer_size *= 2;
		my_realloc(&str);
	}
	if (i == 8)
	{
		char_process(&byte, &char_count, &str, &info);
		i = 0;
	}
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
