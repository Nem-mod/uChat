NAME_SERV	=	uchat
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g
COMP 	= 	clang


INC_SERV	=	server/inc/server.h
OBJECTDIR = server/obj
INCLUDEDIR = server/inc
SOURCEDIR = server/src


SRC_FILES = $(wildcard $(SOURCEDIR)/*.c)
OBJ_FILES = $(addprefix $(OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(INCLUDEDIR)/*.h)


all: $(LBA) $(NAME_SERV) clean

$(NAME_SERV): $(OBJ_FILES)
	@$(COMP) $(CFLAGS) $(OBJ_FILES) -o $@ 

$(OBJ_FILES): | $(OBJECTDIR)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c $(INC_FILES)
	@$(COMP) $(CFLAGS) -c $< -o $@
$(OBJECTDIR):
	@$ mkdir -p $@

clean:
	rm -rf $(OBJECTDIR)

uninstall: clean
	rm -rf $(NAME_SERV)

reinstall: uninstall all
