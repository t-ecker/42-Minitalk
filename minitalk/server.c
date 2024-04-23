/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:38:43 by tecker            #+#    #+#             */
/*   Updated: 2024/04/23 15:00:33 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void ft_putnbr(int n)
{
	char c;
	if (n > 9)
		{
			ft_putnbr(n / 10);
		}
		c = (n % 10) + '0';
		write(1, &c, 1);
}

void	converter(int signum)
{
	static int i = 0;
	static char str[9];
	int num;
	int p;

	p = 1;
	num = 0;
	if (i == 8)
	{
		str[i] = '\0';
		printf("%s\n", str);
		while (i >= 0)
		{
			if (str[i] == '1')
				num += p;
			p *= 2;
			i--;
		}
		i = 0;
		write (1, &num, sizeof(int));
	}
	else
	{
		if (signum == SIGUSR1)
			str[i++] = '1';
		else if (signum == SIGUSR2)
			str[i++] = '0';
		if (i == 8)
			converter(1);
	}
	// printf("%i\n", signum);
}

int	main(void)
{
    int pid;
	pid = getpid();
	write(1, "The pid is: ", 12);
	ft_putnbr(pid);
	write(1, "\n", 1);
	
	// write(1, "\n", 1);
	
	// char *str = "01101000";
	
	// for (int i = 0; i < 8; i++)
	// {
	// 	// printf("%c", str[i]);
		
	// 	converter(str[i] - '0');
	// }
    struct sigaction b;
    b.sa_handler = converter;
    sigemptyset(&b.sa_mask);
    b.sa_flags = 0;
	if (sigaction(SIGUSR1, &b, NULL) == -1)
	{
        write(1, "sigaction\n", 10);
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGUSR2, &b, NULL) == -1) 
	{
        write(1, "sigaction\n", 10);
        exit(EXIT_FAILURE);
    }
    while(1)
	{
		// signal(SIGUSR1, converter);
		// signal(SIGUSR2, converter);
        pause();
	}
}