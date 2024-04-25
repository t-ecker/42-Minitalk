# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 19:00:52 by tomecker          #+#    #+#              #
#    Updated: 2024/04/25 21:02:08 by tomecker         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Werror -Wextra

all:	$(LIBFT)
	@cc $(CFLAGS) server.c $(LIBFT) -o $(SERVER)
	@cc $(CFLAGS) client.c $(LIBFT) -o $(CLIENT)
	@echo "created server and client"
	
$(LIBFT):
	@make -C $(LIBFT_DIR)
	
bonus:	$(LIBFT)
	@cc $(CFLAGS) server_bonus.c $(LIBFT) -o $(SERVER_BONUS)
	@cc $(CFLAGS) client_bonus.c $(LIBFT) -o $(CLIENT_BONUS)
	@echo "created bonus"

clean:
	@make fclean -C $(LIBFT_DIR)
	@echo "cleaned successfully"
	
fclean:	clean
	@rm -f $(SERVER) $(CLIENT) $(CLIENT_BONUS) $(SERVER_BONUS) a.out
re: fclean all bonus

.PHONY: all bonus clean fclean re