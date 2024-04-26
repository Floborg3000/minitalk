
SERVER = server
CLIENT = client
PRINTF = ./ft_printf/
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(PRINTF) -L$(PRINTF) -lftprintf

all:
	@make -s -C $(PRINTF)
	@$(CC) $(CFLAGS) server.c utils.c -o $(SERVER)
	@$(CC) $(CFLAGS) client.c utils.c -o $(CLIENT)

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f $(O_DIRECT)*.o
	@make clean -s -C $(PRINTF)

fclean:	clean
	@make fclean -s -C $(PRINTF)
	rm -f $(SERVER) $(CLIENT)

re:	fclean all

.PHONY:	all clean fclean


