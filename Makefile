NAME = minishell
CC = gcc
CFLAGS = $(CWARN) $(HEADERS)
CWARN = -Wall -Werror -Wextra
HEADERS = -I./inc $(addprefix -I./, $(LIBPATH))
MACOS_INC = -I$(HOME)/homebrew/opt/readline/include
MACOS_LIB = -L$(HOME)/homebrew/opt/readline/lib
DEBUG = -g
DEBUG_ADDR = -fsanitize=address
UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
CFLAGS += $(MACOS_INC)
MACOS_LINK = $(MACOS_INC) $(MACOS_LIB)
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
INCLUDE = $(LIBINC) $(LIBLINK) -lreadline $(MACOS_LINK)

all : $(TARGET)

$(NAME) : all

$(LIBSTAT) :
	@make -s -C $(LIBDIR) -f lib.mk

clean :
	@$(RM) $(TARGET) $(OBJECTS)
	@echo "\033[33m"$(NAME)" clean completed\033[0m"

fclean : clean
	@make -s clean -C $(LIBDIR) -f lib.mk
	@$(RM) -r $(OBJDIR) $(BINDIR)
	@echo "\033[33mfull clean completed\033[0m"

re : clean all

debug : CFLAGS += $(DEBUG)
debug : all
	@echo "\033[31mDEBUG\033[0m"

leak : CFLAGS += $(DEBUG) $(DEBUG_ADDR)
leak : all
	@echo "\033[31mDEBUG ADDRESS\033[0m"

#Link
$(TARGET) : $(OBJECTS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ $^ $(INCLUDE)
	@echo "\033[32m"$@" compiled successfully\033[0m"

#Compile
$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.c | $(LIBSTAT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[34m"$<" compiled successfully\033[0m"