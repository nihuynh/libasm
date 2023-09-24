NAME	:=	libasm.a
SRC		:=	say_hi.s
# ft_strlen.s
# ft_strcpy.s

OBJDIR	:=	objs
OBJ		:=	$(addprefix $(OBJDIR)/, $(SRC:.s=.o))
VPATH	:=	./src

OKLOGO	:=	\033[78G\033[32m[Done]\033[0m\n
RM		:=	/bin/rm -f

# Rules :
.DEFAULT_GOAL := all
all: $(NAME)
.PHONY: all

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.s | $(OBJDIR)
	nasm -f elf64 -o $@ $<
	@printf "\033[1;34m$(NAME)\033[25G\033[33mCompile $< $(OKLOGO)"

usage: ## Print out on how to use this Makefile.
	@printf "\n$(NAME)\n  Usage:\n\tmake <target>\n\n  Targets:\n"
	@fgrep -h " ## " $(MAKEFILE_LIST) \
	| fgrep -v fgrep | awk 'BEGIN {FS = ":.*?## "}; {printf $(PHELP), $$1, $$2}'
.PHONY: usage

clean: ## Clean of the project directory (.o & .a).
	$(RM) $(OBJ)
	$(RM) -r $(OBJDIR)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning objs $(OKLOGO)"
.PHONY: clean

fclean: clean ## Delete the library, object files.
	$(RM) $(NAME)
	@printf "\033[1;34m$(NAME)\033[25G\033[31mCleaning $(NAME) $(OKLOGO)"
.PHONY: fclean

re: ## Rebuild the project.
	make clean
	make $(NAME)
.PHONY: re

test: $(NAME)
	gcc tests/exemple.c -o exemple.out -L libasm.a
	./exemple.out

# Specify the target file and the object files it depends on
$(NAME): $(OBJ)
	ar rcs $@ $(OBJ)