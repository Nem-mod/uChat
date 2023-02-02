NAME_SERV	= uchat_server
NAME_CLIENT = uchat
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g
COMP 	= 	clang


SERV_OBJECTDIR = server/obj
SERV_INCLUDEDIR = server/inc
SERV_SOURCEDIR = server/src

CLIENT_OBJECTDIR = client/obj
CLIENT_INCLUDEDIR = client/inc
CLIENT_SOURCEDIR = client/src

SERV_SRC_FILES = $(wildcard $(SERV_SOURCEDIR)/*.c)
SERV_OBJ_FILES = $(addprefix $(SERV_OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
SERV_INC_FILES = $(wildcard $(SERV_INCLUDEDIR)/*.h)

SRC_FILES = $(wildcard $(CLIENT_SOURCEDIR)/*.c)
OBJ_FILES = $(addprefix $(CLIENT_OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(CLIENT_INCLUDEDIR)/*.h)

all: $(NAME_CLIENT) $(NAME_SERV) clean

$(NAME_CLIENT): $(OBJ_FILES)
	@$(COMP) $(CFLAGS) $(OBJ_FILES) -o $@ 


$(OBJ_FILES): | $(CLIENT_OBJECTDIR)


$(CLIENT_OBJECTDIR)/%.o: $(CLIENT_SOURCEDIR)/%.c $(INC_FILES)
	@$(COMP) $(CFLAGS) -c $< -o $@
$(CLIENT_OBJECTDIR):
	@$ mkdir -p $@


$(NAME_SERV): $(SERV_OBJ_FILES)
	@$(COMP) $(CFLAGS) $(SERV_OBJ_FILES) -o $@ 


$(SERV_OBJ_FILES): | $(SERV_OBJECTDIR)


$(SERV_OBJECTDIR)/%.o: $(SERV_SOURCEDIR)/%.c $(SERV_INC_FILES)
	@$(COMP) $(CFLAGS) -c $< -o $@
$(SERV_OBJECTDIR):
	@$ mkdir -p $@

clean:
	rm -rf server/obj
	rm -rf client/obj

uninstall: clean
	rm -rf $(NAME_SERV)
	rm -rf $(NAME_CLIENT)

reinstall: uninstall all
