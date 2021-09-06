NAME = minishell
CC = gcc
CFLAGS = $(DEBUG) $(CWARN) -I./inc $(MACOS)
#CWARN = -Wall -Werror -Wextra
#DEBUG = -g -fsanitize=address
MACOS = -L~/homebrew/opt/readline/lib -I~/homebrew/opt/readline/include
RM = rm -f

SRCDIR = src
OBJDIR = obj
BINDIR = bin
LIBDIR = lib

#SOURCES = $(wildcard $(SRCDIR)/*.c)
SOURCES = $(shell find $(SRCDIR) -name "*.c")
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

LIB = ft ftprintf
#LIBNAME = $(addprefix lib, $(addsuffix .a, $(LIB)))
LIBPATH = $(patsubst %, $(LIBDIR)/$(LIBDIR)%, $(LIB))
LIBINC = $(addprefix -L, $(LIBPATH))
LIBLINK = $(addprefix -l, $(LIB))
INCLUDE = $(LIBINC) $(LIBLINK) -lreadline

all: $(BINDIR)/$(NAME)

libraries : lib/libft/libft.a lib/libftprintf/libftprintf.a
lib/libft/libft.a :
	@make -C $(LIBDIR)/libft
lib/libftprintf/libftprintf.a :
	@make -C $(LIBDIR)/libftprintf

clean :
	@$(RM) $(BINDIR)/$(NAME) $(OBJECTS)
	@$(RM) $(TESTBIN)
	@echo "\e[33m"$(NAME)" clean completed\e[0m"

fclean : clean
	@make fclean -C $(LIBDIR)/libft
	@make fclean -C $(LIBDIR)/libftprintf
	@$(RM) -r $(OBJDIR) $(BINDIR)
	@echo "\e[33m"$(NAME)" full clean completed\e[0m"

re : clean all

TESTBIN = bin/test.out
$(TESTBIN) :
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) test.c $(INCLUDE) -o $@
	@echo "\e[34m"$@" compiled successfully\e[0m"

#Link
$(BINDIR)/$(NAME) : $(OBJECTS) | $(TESTBIN)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ $^ $(INCLUDE)
	@echo "\e[32m"$@" compiled successfully\e[0m"

#Compile
$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.c | libraries
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\e[34m"$<" compiled successfully\e[0m"