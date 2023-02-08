NAME	=	libdb.a
CFLAGS = -std=c11 
COMP 	= 	clang




OBJECTDIR = obj
INCLUDEDIR = inc
SOURCEDIR = src



SRC_FILES = $(wildcard $(SOURCEDIR)/*.c)
OBJ_FILES = $(addprefix $(OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(INCLUDEDIR)/*.h)


all: $(NAME) clean

$(NAME): $(OBJ_FILES)
	@ar rcs $@ $^
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(OBJ_FILES): | $(OBJECTDIR)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c $(INC_FILES)
	@$(COMP) $(CFLAGS) -c $< -o $@ -I $(INCLUDEDIR) --debug
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"


$(OBJECTDIR):
	@$ mkdir -p $@



clean:
	rm -rf $(OBJECTDIR)

uninstall: clean
	rm -rf $(NAME)

reinstall: uninstall all
