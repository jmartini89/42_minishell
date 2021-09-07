NAME = minishell
CC = gcc
CFLAGS = $(CWARN) $(HEADERS)
#CWARN = -Wall -Werror -Wextra
HEADERS = -I./inc $(addprefix -I./, $(LIBPATH))
MACOS = -L~/homebrew/opt/readline/lib -I~/homebrew/opt/readline/include
DEBUG = -g -fsanitize=address
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
CFLAGS += $(MACOS)
endif
RM = rm -f

SRCDIR = src
OBJDIR = obj
BINDIR = bin
LIBDIR = lib

SOURCES = $(shell find $(SRCDIR) -name "*.c")
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
TARGET = $(BINDIR)/$(NAME)

LIB = ft ftprintf
LIBNAME = $(addprefix lib, $(addsuffix .a, $(LIB)))
LIBSTAT = $(addprefix lib/,$(LIBNAME))
LIBPATH = $(patsubst %, $(LIBDIR)/$(LIBDIR)%, $(LIB))
LIBINC = $(addprefix -L, $(LIBDIR))
LIBLINK = $(addprefix -l, $(LIB))
INCLUDE = $(LIBINC) $(LIBLINK) -lreadline

all : $(TARGET)

$(NAME) : all

$(LIBSTAT) :
	@make -s -C $(LIBDIR) -f lib.mk

clean :
	@$(RM) $(TARGET) $(OBJECTS)
	@$(RM) $(TESTBIN)
	@echo "\e[33m"$(NAME)" clean completed\e[0m"

fclean : clean
	@make -s clean -C $(LIBDIR) -f lib.mk
	@$(RM) -r $(OBJDIR) $(BINDIR)
	@echo "\e[33mfull clean completed\e[0m"

re : clean all

debug : CFLAGS += $(DEBUG)
debug : re all
	@echo "\e[31mDEBUG\e[0m"

TESTBIN = bin/test.out
$(TESTBIN) :
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) test.c $(INCLUDE) -o $@
	@echo "\e[34m"$@" compiled successfully\e[0m"

#Link
$(TARGET) : $(OBJECTS) | $(TESTBIN)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ $^ $(INCLUDE)
	@echo "\e[32m"$@" compiled successfully\e[0m"

#Compile
$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.c | $(LIBSTAT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\e[34m"$<" compiled successfully\e[0m"