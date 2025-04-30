SRCS	= ft_strlen.c ft_strncmp.c ft_atoi.c \
	ft_strdup.c ft_strtrim.c ft_itoa.c ft_split.c

OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

CC		= cc
RM		= rm -f

CFLAGS 	= -Wall -Wextra -Werror


.SILENT:

all: $(NAME)

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all