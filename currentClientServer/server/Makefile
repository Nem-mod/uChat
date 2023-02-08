NAME	=	uchat_server
NAME_ROOT = ../$(NAME)
CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic) 
COMP 	= 	clang


INC		=	libmx.h
INCS	=	$(addprefix $(INCD)/, $(INC))


LMXDIR	=	libmx
OBJECTDIR = obj
INCLUDEDIR = inc
SOURCEDIR = src

LIBSDIR = libs/
LBA = $(addprefix $(LIBSDIR)/, libmx.a libdb.a)
LBMX = $(LIBSDIR)/libmx
LBDB = $(LIBSDIR)/libdb
LBI = $(addprefix -I$(LIBSDIR)/, libmx/inc libdb/inc openssl/include)
LBSSL = $(LIBSDIR)/openssl
LIBLINK = -L$(LBMX) -lmx -L$(LBDB) -ldb  -L$(LBSSL) #-lssl -lcrypto

SRC_FILES = $(wildcard $(SOURCEDIR)/*.c)
OBJ_FILES = $(addprefix $(OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(INCLUDEDIR)/*.h)


all: $(LBA) $(NAME) clean out

$(NAME): $(OBJ_FILES)
	@$(COMP) $(CFLAGS) $(OBJ_FILES) $(LIBLINK) -ldl -lpthread -o $@ --debug
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"


$(OBJ_FILES): | $(OBJECTDIR)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c $(INC_FILES)
	@$(COMP) $(CFLAGS) -c $< -o $@ -I $(INCLUDEDIR) $(LBI) --debug
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"


$(OBJECTDIR):
	@$ mkdir -p $@

$(LBA):
	@make -sC $(LIBSDIR)/libmx all
	@make -sC $(LIBSDIR)/libdb all

out: $(NAME_ROOT)

$(NAME_ROOT): $(NAME)
	@cp $(NAME) ../
	@printf "\r\33[2K$< \033[32;1mcopied to the root\033[0m\n"

clean:
	rm -rf $(OBJECTDIR)
	rm  -rf *.db

uninstall: clean
	rm -rf $(NAME)
	@make -C $(LIBSDIR)/libmx uninstall
	@make -C $(LIBSDIR)/libdb uninstall

reinstall: uninstall all
