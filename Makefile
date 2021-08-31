NAME = minishell
TARGET = $(BINDIR)/$(NAME)
CC = gcc
CFLAGS = #-Wall -Werror -Wextra
LDFLAGS="-L/Users/jmartini/homebrew/opt/readline/lib"
CPPFLAGS="-I/Users/jmartini/homebrew/opt/readline/include"

DEBUG = -g -fsanitize=address

SRCDIR = src
OBJDIR = obj
BINDIR = bin
LIBDIR = lib
SRCEXT = c
OBJEXT = o


SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.$(SRCEXT)=$(OBJDIR)/%.$(OBJEXT))
RM = rm -f

LIBFTDIR = $(LIBDIR)/libft
LIBPRINTFDIR = $(LIBDIR)/ft_printf
LIBS = -L$(LIBFTDIR) -L$(LIBPRINTFDIR) -lft -lftprintf -lreadline #$(LDFLAGS) $(CPPFLAGS)

all: build $(NAME)


$(NAME): $(OBJECTS) | libraries
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LIBS)
	@echo "\e[32mminishell compilation successfull\e[0m"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

build:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

libraries:
	@make -C $(LIBFTDIR)
	@make -C $(LIBPRINTFDIR)

test:
	$(CC) $(CFLAGS) test.c $(LIBS)

clean:
	$(RM) $(BINDIR)/$(NAME) $(OBJECTS)
	$(RM) a.out

fclean: clean
	make fclean -C $(LIBFTDIR)
	make fclean -C $(LIBPRINTFDIR)
	rm -rf $(OBJDIR) $(BINDIR)

re: clean all

debug: build $(OBJECTS) | libraries
	$(CC) $(CFLAGS) $(DEBUG) -o $(TARGET) $^ $(LIBS)

redebug: clean debug