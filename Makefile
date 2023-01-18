NAME_SERV	=uchat_server
NAME_CLIENT = uchat
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g
COMP 	= 	clang


INC_SERV	=	server/inc/server.h
OBJECTDIR = server/obj
INCLUDEDIR = server/inc
SOURCEDIR = server/src


SRC_FILES = $(wildcard $(SOURCEDIR)/*.c)
OBJ_FILES = $(addprefix $(OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(INCLUDEDIR)/*.h)


all: $(NAME_SERV) $(NAME_CLIENT) clean

$(NAME_SERV): $(OBJ_FILES)
	@$(COMP) $(CFLAGS) $(OBJ_FILES) -o $@ 

$(NAME_CLINET): 
	@$(COMP) $(CFLAGS) client/*.c -o uchat 

$(OBJ_FILES): | $(OBJECTDIR)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c $(INC_FILES)
	@$(COMP) $(CFLAGS) -c $< -o $@
$(OBJECTDIR):
	@$ mkdir -p $@

clean:
	rm -rf $(OBJECTDIR)

uninstall: clean
	rm -rf $(NAME_SERV)
	rm -rf $(NAME_CLIENT)

reinstall: uninstall all
