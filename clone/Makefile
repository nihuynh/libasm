# Makefile for libasm
# author: nihuynh 2025
# Requirements: 64 bits ASM, compile with nasm, Intel syntax
# Forbidden to use -no-pie

NAME		:=	libasm.a
VERBOSE		:=	1
SRC 		:=	ft_strlen.s \
				ft_strcpy.s \
				ft_strcmp.s \
				ft_write.s \
				ft_read.s \
				ft_strdup.s

SRC			+=	ft_atoi_base.s \
				ft_list_push_front.s \
				ft_list_size.s \
				ft_list_sort.s \
				ft_list_remove_if.s

TEST_SRC	:=	main.c \
				cu_test_main.c \
				size_demo.c

VPATH		:=	./src ./test
# ---
NA			:=	nasm
CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror -Iinclude
CLIB_FLAGS	:=	-L . -l asm
# Compiling on mac ARM
ifeq ($(shell uname -m), arm64)
	CFLAGS	+=	-ld_classic --target=x86_64-apple-darwin
	NFLAGS	:=	-f macho64
endif
# Compiling on Linux x86
ifeq ($(shell uname -m), x86_64)
	NFLAGS	:=	-f elf64
endif
OBJDIR		:=	obj
OBJ			:=	$(addprefix $(OBJDIR)/, $(SRC:.s=.o))
TEST		:=	$(addprefix $(OBJDIR)/, $(TEST_SRC:.c=.out))
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

$(OBJDIR)/%.out: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@ $(CLIB_FLAGS)
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile test_SRC $< $(OKLOGO)"

test: tclean $(NAME) $(TEST)
	find $(OBJDIR) -name "*.out" -type f
	@printf "\033[1;34m$(NAME)\033[25G\033[33mTest are ready $(OKLOGO)"
.PHONY: test

usage: ## Print out on how to use this Makefile.
	@printf "\n$(NAME)\n  Usage:\n\tmake <target>\n\n  Targets:\n"
	@fgrep -h " ## " $(MAKEFILE_LIST) \
	| fgrep -v fgrep | awk 'BEGIN {FS = ":.*?## "}; {printf $(PHELP), $$1, $$2}'
.PHONY: usage

format: ## Format the sources
	# TODO: Check if repo is sync/commit
	find . \( -name "*.cpp" -o -name "*.c" -o -name "*.h" \) -exec uncrustify -c uncrust.conf --no-backup {} +
	@printf "\033[1;34m$(NAME)\033[25G\033[33mFormating sources $(OKLOGO)"
.PHONY: format

clean: tclean ## Clean of the project directory (.o & .d).
	$(RM) $(OBJ)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning objects $(OKLOGO)"
.PHONY: clean

fclean: tclean clean ## Delete the library, object files & test_SRC binarys.
	$(RM) $(NAME)
	$(RM) -r $(OBJDIR)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME) & test executables $(OKLOGO)"
.PHONY: fclean

tclean: ## Delete executables.
	$(RM) $(TEST)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning test executables $(OKLOGO)"
.PHONY: fclean

re: fclean all ## Rebuild the project.
.PHONY: re