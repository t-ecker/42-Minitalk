# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tecker <tecker@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 19:00:52 by tomecker          #+#    #+#              #
#    Updated: 2024/04/24 18:28:36 by tecker           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

CFLAGS = -Wall -Werror -Wextra

all:
	@cc $(CFLAGS) server.c -o server
	@cc $(CFLAGS) client.c -o $(CLIENT)
	@echo "created server and client"
	
bonus:
	@cc $(CFLAGS) server_bonus.c -o $(SERVER_BONUS)
	@cc $(CFLAGS) client_bonus.c -o $(CLIENT_BONUS)
	@echo "created bonus"

clean:
	@rm -f $(SERVER) $(CLIENT) $(CLIENT_BONUS) $(SERVER_BONUS) a.out
	@echo "cleaned successfully"
	
fclean:	clean

re: fclean all bonus

.PHONY: all bonus clean fclean re