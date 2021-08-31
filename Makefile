NAME = minishell
CC = gcc
CFLAGS = #-Wall -Werror -Wextra
LDFLAGS="-L/Users/jmartini/homebrew/opt/readline/lib"
CPPFLAGS="-I/Users/jmartini/homebrew/opt/readline/include"
DEBUG = -g -fsanitize=address

SRCDIR = ./src
SRCFILES = main.c
SRC = $(addprefix $(SRCDIR)/,$(SRCFILES))
OBJ = ${SRC:.c=.o}

LDIR = ./lib
LFTDIR = $(LDIR)/libft
LPRINTFDIR = $(LDIR)/ft_printf
LFT = libft.a
LPRINTF = libftprintf.a
LIBS = -L$(LFTDIR) -L$(LPRINTFDIR) -lft -lftprintf -lreadline #$(LDFLAGS) $(CPPFLAGS)

all: $(NAME)

$(NAME): $(OBJ) | libraries test
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

libraries:
	make -C $(LFTDIR)
	make -C $(LPRINTFDIR)

test:
	$(CC) $(CFLAGS) test.c $(LIBS)

clean:
	rm -f $(NAME) $(OBJ)
	rm -f a.out

fclean: clean
	make fclean -C $(LFTDIR)
	make fclean -C $(LPRINTFDIR)

re: clean all

debug : $(OBJ) | libraries test
	$(CC) $(CFLAGS) $(DEBUG) -o $(NAME) $^ $(LIBS)

redebug: clean debug