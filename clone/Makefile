# Makefile for libasm
# author: nihuynh 2025
# Requirements: 64 bits ASM, compile with nasm, Intel syntax
# Forbidden to use -no-pie

NAME	:=	libasm.a
VERBOSE := 1
SRC 	:=	ft_strlen.s \
		ft_strcpy.s \
		ft_strcmp.s \
		ft_write.s \
		ft_read.s \
		ft_strdup.s

B_SRC	:=	ft_atoi_base.s \
		ft_list_push_front.s \
		ft_list_size.s \
		ft_list_sort.s \
		ft_list_remove_if.s

TESTS   :=	test_len_write.s

VPATH	:=	./src
# ---
NA		:=	nasm
CC      :=  clang
CFLAGS  :=  -Wall -Wextra -Werror
# Compiling on mac ARM
ifeq ($(shell uname -m), arm64)
    CFLAGS  +=   -ld_classic --target=x86_64-apple-darwin
    NFLAGS	:=	-f macho64 -i $(VPATH)
endif
# Compiling on Linux x86
ifeq ($(shell uname -m), x86_64)
    NFLAGS	:=	-f elf64 -i $(VPATH)
endif
OBJDIR		:=	obj
OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.s=.o))
TESTDIR		:=	test
TEST		:=	$(addprefix $(TESTDIR)/, $(TESTS:.s=.o))
TEST_EXEC	:=	$(addprefix $(TESTDIR)/, $(TESTS:.s=))
INCDIR		:=	include
ifndef VERBOSE
.SILENT:
endif
OKLOGO		:=	\033[78G\033[32m[Done]\033[0m\n
PHELP		:=	"\033[36m%-26s\033[0m %s\n"
# ---

# Rules :
.DEFAULT_GOAL := all

all: $(NAME)
.PHONY: all

$(NAME): $(OBJ) ## Built the library (default goal).
	ar rcs $@ $(OBJ)
	ar -t $@
	@printf "\033[1;34m$(NAME)\033[25G\033[33mDone $@ $(OKLOGO)"

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.s | $(OBJDIR)
	$(NA) $(NFLAGS) -o $@ $<
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"

test: $(NAME)
	$(CC) $(CFLAGS) -Iinclude test/main.c -L . -l asm
.PHONY: test

usage: ## Print out on how to use this Makefile.
	@printf "\n$(NAME)\n  Usage:\n\tmake <target>\n\n  Targets:\n"
	@fgrep -h " ## " $(MAKEFILE_LIST) \
	| fgrep -v fgrep | awk 'BEGIN {FS = ":.*?## "}; {printf $(PHELP), $$1, $$2}'
.PHONY: usage

clean: ## Clean of the project directory (.o & .d).
	$(RM) $(OBJ)
	$(RM) $(TEST)
	$(RM) -r $(OBJDIR)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning objects $(OKLOGO)"
.PHONY: clean

fclean: clean ## Delete the library, object files & tests binarys.
	$(RM) $(NAME)
	$(RM) a.out
	$(RM) $(TEST_EXEC)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME) & test executables $(OKLOGO)"
.PHONY: fclean

re: fclean all ## Rebuild the project.
.PHONY: re