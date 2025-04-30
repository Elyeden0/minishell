CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar rcs
RM          = rm -f

NAME        = libmalloc.a

SRCS        = ft_malloc.c ft_free.c ft_realloc.c utils.c

OBJS        = $(SRCS:.c=.o)

.SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all