NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c
LIB = ar -rc
RAN = ranlib
RM = rm -f

SRCS = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c

SRCS_BONUS = ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstnew.c \
	ft_lstsize.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: bonus

clean:
	@${RM} $(OBJS) $(OBJS_BONUS)
#	@echo "\033[33m"$(NAME)" clean completed\033[0m"

fclean: clean
	@${RM} ${NAME}
#	@echo "\033[33m"$(NAME)" full clean completed\033[0m"

re: fclean all

#Link
$(NAME): $(OBJS)
	@${LIB} $(NAME) $(OBJS)
	@${RAN} ${NAME}
#	@echo "\033[32m"$@" compilation successfull\033[0m"

#Link BONUS
bonus: ${OBJS_BONUS} ${NAME}
	${LIB} $(NAME) $(OBJS_BONUS)
	${RAN} ${NAME}

#Compile
.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
#	@echo "\033[34m"$@" compilation successfull\033[0m"

.PHONY: all clean fclean re