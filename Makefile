NAME_SERVER = server
NAME_CLIENT = client
NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = server.o
OBJS_CLIENT = client.o

SRCS_SERVER_BONUS = server_bonus.c
SRCS_CLIENT_BONUS = client_bonus.c
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o) 
RM = rm -f

all: $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT)

$(NAME_SERVER_BONUS): $(OBJS_SERVER_BONUS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) $(LIBFT) $(PRINTF) -o $(NAME_SERVER_BONUS)


$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_BONUS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) $(LIBFT) $(PRINTF) -o $(NAME_CLIENT_BONUS)

server.o: server.c
	$(CC) $(CFLAGS) -c server.c -o server.o

client.o: client.c
	$(CC) $(CFLAGS) -c client.c -o client.o

clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)

fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

re: fclean all

.PHONY: all clean fclean re
