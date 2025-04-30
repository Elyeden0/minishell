CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar rcs
RM          = rm -f

NAME = libftprintf.a
SRCS = printf.c ft_toa.c handle_int.c handle_char.c apply_flags.c parse_format.c handle_flag.c utils.c
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