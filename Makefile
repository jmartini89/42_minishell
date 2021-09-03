NAME = minishell
CC = gcc
CFLAGS = #-Wall -Werror -Wextra
LDFLAGS="-L/Users/jmartini/homebrew/opt/readline/lib"
CPPFLAGS="-I/Users/jmartini/homebrew/opt/readline/include"

DEBUG = minishell_debug
DFLAGS = -g -fsanitize=address

SRCDIR = src
OBJDIR = obj
BINDIR = bin
LIBDIR = lib
SRCEXT = c
OBJEXT = o

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.$(SRCEXT)=$(OBJDIR)/%.$(OBJEXT))
LIBS = -L$(LIBDIR)/libft -L$(LIBDIR)/ft_printf -lft -lftprintf -lreadline #$(LDFLAGS) $(CPPFLAGS)
RM = rm -f

all: directories libraries test $(BINDIR)/$(NAME)

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

libraries:
	@make -C $(LIBDIR)/libft
	@make -C $(LIBDIR)/ft_printf

clean:
	@$(RM) $(BINDIR)/$(NAME) $(OBJECTS)
	@$(RM) $(BINDIR)/$(DEBUG)
	@$(RM) $(BINDIR)/a.out
	@echo "\e[33m"$(NAME)" clean completed\e[0m"

fclean: clean
	@make fclean -C $(LIBDIR)/libft
	@make fclean -C $(LIBDIR)/ft_printf
	@rm -rf $(OBJDIR) $(BINDIR)
	@echo "\e[33m"$(NAME)" full clean completed\e[0m"

re: clean all

test:
	$(CC) $(CFLAGS) test.c $(LIBS) -o $(BINDIR)/a.out

debug: directories libraries $(BINDIR)/$(DEBUG)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\e[34m"$<" compiled successfully\e[0m"

$(BINDIR)/$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "\e[32m"$@" compiled successfully\e[0m"

$(BINDIR)/$(DEBUG): $(OBJECTS)
	@$(CC) $(CFLAGS) $(DFLAGS) -o $(BINDIR)/$(DEBUG) $^ $(LIBS)
	@echo "\e[32m"$@" compiled successfully\e[0m"