SERVER = server
CLIENT = client

# CFLAGS = -Wall -Werror -Wextra

all:
	@cc $(CFLAGS) server.c -o $(SERVER)
	@cc $(CFLAGS) client.c -o $(CLIENT)
	@echo "created server and client"
clean:
	@rm -f $(SERVER) $(CLIENT) a.out
	@echo "cleaned successfully"
fclean:	clean

re: fclean all