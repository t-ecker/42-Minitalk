# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 19:00:52 by tomecker          #+#    #+#              #
#    Updated: 2024/05/06 19:15:10 by tomecker         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Werror -Wextra

all: $(SERVER) $(CLIENT)

$(SERVER): server.o $(LIBFT)
	@cc $(CFLAGS) server.o $(LIBFT) -o $(SERVER)

$(CLIENT): client.o $(LIBFT)
	@cc $(CFLAGS) client.o $(LIBFT) -o $(CLIENT)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): server_bonus.o $(LIBFT)
	@cc $(CFLAGS) server_bonus.o $(LIBFT) -o $(SERVER_BONUS)

$(CLIENT_BONUS): client_bonus.o $(LIBFT)
	@cc $(CFLAGS) client_bonus.o $(LIBFT) -o $(CLIENT_BONUS)

clean:
	@rm -f *.o
	@make clean -C $(LIBFT_DIR)
	@echo "Cleaned successfully"
	
fclean: clean
	@rm -f $(SERVER) $(CLIENT) $(CLIENT_BONUS) $(SERVER_BONUS) *.o
	@make fclean -C $(LIBFT_DIR)
	@echo "Fully cleaned"

re: fclean all bonus

.PHONY: all bonus clean fclean re
