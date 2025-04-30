CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar rcs
RM          = rm -f

NAME        = liblst.a

SRCS = ft_lst_utils.c ft_lst_modifications.c ft_lst_extra.c
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