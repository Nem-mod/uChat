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

LBA = libmx/libmx.a 
LBMX = libmx
LBI = libmx/inc/


SERV_SRC_FILES = $(wildcard $(SERV_SOURCEDIR)/*.c)
SERV_OBJ_FILES = $(addprefix $(SERV_OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
SERV_INC_FILES = $(wildcard $(SERV_INCLUDEDIR)/*.h)

SRC_FILES = $(wildcard $(CLIENT_SOURCEDIR)/*.c)
OBJ_FILES = $(addprefix $(CLIENT_OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(CLIENT_INCLUDEDIR)/*.h)

all: $(LBA) $(NAME_SERV) $(NAME_CLIENT) clean

$(NAME_SERV): $(SERV_OBJ_FILES)
	@$(COMP) $(CFLAGS) $(SERV_OBJ_FILES) -L$(LBMX) -lmx -o $@ 


$(SERV_OBJ_FILES): | $(SERV_OBJECTDIR)


$(SERV_OBJECTDIR)/%.o: $(SERV_SOURCEDIR)/%.c $(SERV_INC_FILES)
	@$(COMP) $(CFLAGS) -c $< -o $@ -I $(SERV_INCLUDEDIR) -I$(LBI)
$(SERV_OBJECTDIR):
	@$ mkdir -p $@


$(NAME_CLIENT): $(OBJ_FILES)
	@$(COMP) $(CFLAGS) $(OBJ_FILES) -L$(LBMX) -lmx -o $@ 


$(OBJ_FILES): | $(CLIENT_OBJECTDIR)


$(CLIENT_OBJECTDIR)/%.o: $(CLIENT_SOURCEDIR)/%.c $(INC_FILES)
	@$(COMP) $(CFLAGS) -c $< -o $@ -I $(CLIENT_INCLUDEDIR) -I$(LBI)
$(CLIENT_OBJECTDIR):
	@$ mkdir -p $@




$(LBA):
	@make -sC libmx all

clean:
	rm -rf server/obj
	rm -rf client/obj

uninstall: clean
	rm -rf $(NAME_SERV)
	rm -rf $(NAME_CLIENT)

reinstall: uninstall all
