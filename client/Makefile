NAME = uchat
NAME_ROOT = ../$(NAME)
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g
COMP 	= 	clang


OBJECTDIR = obj
INCLUDEDIR = inc
SOURCEDIR = src

LBA = libs/libmx/libmx.a 
LBMX = libs/libmx
LBI = libs/libmx/inc/



SRC_FILES = $(wildcard $(SOURCEDIR)/*.c)
OBJ_FILES = $(addprefix $(OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(INCLUDEDIR)/*.h)

all: $(LBA) $(NAME) clean out

$(NAME): $(OBJ_FILES)
	@$(COMP) $(CFLAGS) $(OBJ_FILES) -L$(LBMX) -lmx -o $@ 


$(OBJ_FILES): | $(OBJECTDIR)


$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c $(INC_FILES)
	@$(COMP) $(CFLAGS) -c $< -o $@ -I $(INCLUDEDIR) -I$(LBI)
$(OBJECTDIR):
	@$ mkdir -p $@

out: $(NAME_ROOT)

$(NAME_ROOT): $(NAME)
	@cp $(NAME) ../
	@printf "\r\33[2K$< \033[32;1mcopied to the root\033[0m\n"

$(LBA):
	@make -sC libmx all

clean:
	rm -rf obj

uninstall: clean
	rm -rf $(NAME)

reinstall: uninstall all
