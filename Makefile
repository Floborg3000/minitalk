NAME_SERVER		= server
NAME_CLIENT		= client

BNAME_SERVER	= server_bonus
BNAME_CLIENT	= client_bonus

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror -I.

SRCS_SERVER		= server.c utils.c
SRCS_CLIENT		= client.c utils.c

BSRCS_SERVER	= server_bonus.c utils.c
BSRCS_CLIENT	= client_bonus.c utils.c

OBJS_SERVER		= $(SRCS_SERVER:.c=.o)
OBJS_CLIENT		= $(SRCS_CLIENT:.c=.o)

BOBJS_SERVER	= $(BSRCS_SERVER:.c=.o)
BOBJS_CLIENT	= $(BSRCS_CLIENT:.c=.o)

PRINTF			= ft_printf/libftprintf.a
PRINTF_MAKE		= make -C ft_printf
PRINTF_CLEAN	= make clean -C ft_printf
PRINTF_FCLEAN	= make fclean -C ft_printf

all:	$(NAME_SERVER) $(NAME_CLIENT) $(PRINTF)

$(NAME_SERVER):	$(PRINTF) $(OBJS_SERVER)
		@$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER) $(PRINTF)

$(NAME_CLIENT):	$(OBJS_CLIENT) $(PRINTF)
		@$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT) $(PRINTF)

$(PRINTF):
		@$(PRINTF_MAKE)
		@$(PRINTF_CLEAN)

bonus:	$(BNAME_SERVER) $(BNAME_CLIENT) $(PRINTF)

$(BNAME_SERVER):	$(PRINTF) $(BOBJS_SERVER)
		@$(CC) $(CFLAGS) -o $(BNAME_SERVER) $(BOBJS_SERVER) $(PRINTF)

$(BNAME_CLIENT):	$(BOBJS_CLIENT) $(PRINTF)
		@$(CC) $(CFLAGS) -o $(BNAME_CLIENT) $(BOBJS_CLIENT) $(PRINTF)

clean:
		@rm -f $(OBJS_CLIENT) $(OBJS_SERVER) $(BOBJS_CLIENT) $(BOBJS_SERVER)

fclean:	clean
		@rm -f $(NAME_SERVER) $(NAME_CLIENT) $(BNAME_SERVER) $(BNAME_CLIENT)
		@$(PRINTF_FCLEAN)

re:	fclean all

.PHONY:	all clean fclean re bonus
