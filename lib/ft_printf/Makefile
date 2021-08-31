NAME		= libftprintf.a

CC		= gcc

RM		= rm -f

CFLAGS		= -Wall -Wextra -Werror -c

LIB		= ar -rc

RAN		= ranlib

SRCS		= ft_printf.c \
		ft_printf_flags.c \
		ft_printf_conv_01.c \
		ft_printf_conv_02.c \
		ft_printf_conv_03.c \
		ft_printf_utils_01.c \
		ft_printf_utils_02.c \
		ft_printf_write_01.c \
		ft_printf_write_02.c \
		ft_printf_write_03.c \

OBJS		= $(SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}


$(NAME): $(OBJS)
	@${LIB} $(NAME) $(OBJS)
	@${RAN} ${NAME}
	@echo "\e[32m"$(NAME)" compilation successfull\e[0m"

all: @$(NAME)

clean:
	@${RM} $(OBJS)
	@echo "\e[33m"$(NAME)" clean completed\e[0m"

fclean: clean
	@${RM} ${NAME}
	@echo "\e[33m"$(NAME)" full clean completed\e[0m"

re: fclean all

.PHONY: all clean fclean re

bonus: $(NAME)