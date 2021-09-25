NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c
LIB = ar -rc
RAN = ranlib
RM = rm -f

SRCS = ft_printf.c \
	ft_printf_flags.c \
	ft_printf_conv_01.c \
	ft_printf_conv_02.c \
	ft_printf_conv_03.c \
	ft_printf_utils_01.c \
	ft_printf_utils_02.c \
	ft_printf_write_01.c \
	ft_printf_write_02.c \
	ft_printf_write_03.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

bonus: $(NAME)

clean:
	@${RM} $(OBJS)
#	@echo "\033[33m"$(NAME)" clean completed\033[0m"

fclean: clean
	@${RM} ${NAME}
#	@echo "\033[33m"$(NAME)" full clean completed\033[0m"

re: fclean all

.PHONY: all clean fclean re

#Link
$(NAME): $(OBJS)
	@${LIB} $(NAME) $(OBJS)
	@${RAN} ${NAME}
#	@echo "\033[32m"$(NAME)" compilation successfull\033[0m"

#Compile
.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
#	@echo "\033[34m"$@" compilation successfull\033[0m"