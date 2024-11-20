SERVER = server
CLIENT = client
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Werror -Wextra
CC = cc


SRC =		./src/server.c \
			./src/client.c

SRC_BONUS =	./src/bonus/server_bonus.c \
			./src/bonus/client_bonus.c

OBJ_DIR = ./obj
SRC_DIR = ./src

OBJ_FILES		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_FILES_BONUS	=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_BONUS))

all: $(SERVER) $(CLIENT)
	clear;
	@$(MAKE) loading
	clear;

$(SERVER): $(LIBFT) $(OBJ_FILES)
	$(CC) $(CFLAGS) $< $(OBJ_DIR)/server.o -o $@

$(CLIENT): $(LIBFT) $(OBJ_FILES)
	$(CC) $(CFLAGS) $< $(OBJ_DIR)/client.o -o $@

$(LIBFT):	$(LIBFT_DIR)/.git
	@make extra -C $(LIBFT_DIR)

$(LIBFT_DIR)/.git:
	@echo "\033[33mInitializing Libft submodule...\033[0m"
	@git submodule update --init --recursive
	@echo "\033[32mLibft submodule initialized.\033[0m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

bonus:	$(SERVER_BONUS) $(CLIENT_BONUS)
	clear;
	@$(MAKE) loading
	clear;

$(SERVER_BONUS):	$(LIBFT) $(OBJ_FILES_BONUS) 
	$(CC) $(CFLAGS) $< $(OBJ_DIR)/bonus/server_bonus.o -o $@

$(CLIENT_BONUS):	$(LIBFT) $(OBJ_FILES_BONUS) 
	$(CC) $(CFLAGS) $< $(OBJ_DIR)/bonus/client_bonus.o -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(SERVER) $(CLIENT) $(CLIENT_BONUS) $(SERVER_BONUS)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

loading:
	@for i in {1..42}; do \
		printf '%s' "█"; \
		sleep 0.01; \
	done

.PHONY: all clean fclean re loading bonus
