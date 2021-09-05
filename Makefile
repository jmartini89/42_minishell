NAME = minishell
CC = gcc
CFLAGS = $(DEBUG) $(CEXTRA)
#CEXTRA = -Wall -Werror -Wextra
#DEBUG = -g -fsanitize=address
LDFLAGS="-L/Users/jmartini/homebrew/opt/readline/lib"
CPPFLAGS="-I/Users/jmartini/homebrew/opt/readline/include"
#MACOS = $(LDFLAGS) $(CPPFLAGS)

SRCDIR = src
OBJDIR = obj
BINDIR = bin
LIBDIR = lib
SRCEXT = c
OBJEXT = o

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.$(SRCEXT), $(OBJDIR)/%.$(OBJEXT), $(SOURCES))

LIB = ft ftprintf
LIBPATH = $(patsubst %, -L$(LIBDIR)/$(LIBDIR)%, $(LIB))
LIBLINK = $(addprefix -l, $(LIB))

INCLUDE = $(LIBPATH) $(LIBLINK) -lreadline $(MACOS)

# use same as LIBPATH
LFT = lib/libft/libft.a
LPRINTF = lib/libftprintf/libftprintf.a

RM = rm -f

all: $(BINDIR)/$(NAME)

$(OBJDIR) :
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

libraries : $(LFT) $(LPRINTF)

$(LFT) :
	@make -C $(LIBDIR)/libft

$(LPRINTF) :
	@make -C $(LIBDIR)/libftprintf

clean :
	@$(RM) $(BINDIR)/$(NAME) $(OBJECTS)
	@$(RM) $(BINDIR)/a.out
	@echo "\e[33m"$(NAME)" clean completed\e[0m"

fclean : clean
	@make fclean -C $(LIBDIR)/libft
	@make fclean -C $(LIBDIR)/libftprintf
	@rm -rf $(OBJDIR) $(BINDIR)
	@echo "\e[33m"$(NAME)" full clean completed\e[0m"

re : clean all

test:
	$(CC) $(CFLAGS) test.c $(INCLUDE) -o a.out

$(LIBRARIES)

#Link
$(BINDIR)/$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDE)
	@echo "\e[32m"$@" compiled successfully\e[0m"

#Compile
$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR) libraries
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\e[34m"$<" compiled successfully\e[0m"
