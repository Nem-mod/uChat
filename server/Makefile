NAME	=	uchat_server
CFLAGS 	=	-std=c11 $(addprefix -W, all extra error pedantic) 
COMP 	= 	clang

COLOUR_GREEN	=	\033[32;1m
# COLOUR_RED		=	\033[0;31m
# COLOUR_BLUE		=	\033[0;34m
COLOUR_END		=	\033[0m

UTILSDIR	=	../utils

LIBSDIR		=	$(UTILSDIR)/libs
SOURCEDIR 	=	src
OBJECTDIR	=	obj
INCLUDEDIR	=	inc

LIBMXDIR	=	$(LIBSDIR)/libmx
LIBDBDIR	=	$(LIBSDIR)/libdb
LIBSSLDIR	=	$(LIBSDIR)/libssl
LIBJSONDIR	=	$(LIBSDIR)/libjson

LIBINC		=	$(addprefix -I$(LIBSDIR)/, libmx/inc libdb/inc libssl/include libjson/inc)

LIBLINK		=	-L$(LIBMXDIR) -lmx -L$(LIBDBDIR) -ldb  -L$(LIBSSLDIR) -lssl -lcrypto -L$(LIBJSONDIR) -ljson-c

SRC_FILES	=	$(wildcard $(SOURCEDIR)/*.c $(UTILSDIR)/$(SOURCEDIR)/*.c)
OBJ_FILES	=	$(addprefix $(OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES	=	$(wildcard $(INCLUDEDIR)/*.h $(UTILSDIR)/$(INCLUDEDIR)/*.h)

all: libs $(NAME) clean out

libs: libmx libdb libssl

libmx:
	@make -sC $(LIBMXDIR)
	@echo "$@ $(COLOUR_GREEN)created$(COLOUR_END)"

libdb:
	@make -sC $(LIBDBDIR)
	@echo "$@ $(COLOUR_GREEN)created$(COLOUR_END)"

libssl:

$(NAME): $(OBJ_FILES)
	@$(COMP) $(CFLAGS) $(OBJ_FILES) $(LIBLINK) -ldl -lpthread -o $@ --debug

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c $(OBJECTDIR)
	@$(COMP) $(CFLAGS) -c $< -o $@ -I $(INCLUDEDIR) -I $(UTILSDIR)/$(INCLUDEDIR) $(LIBINC) --debug
	@echo "$@ $(COLOUR_GREEN)compiled$(COLOUR_END)"

$(OBJECTDIR)/%.o: $(UTILSDIR)/$(SOURCEDIR)/%.c $(OBJECTDIR)
	@$(COMP) $(CFLAGS) -c $< -o $@ -I $(INCLUDEDIR) -I $(UTILSDIR)/$(INCLUDEDIR) $(LIBINC) --debug
	@echo "$@ $(COLOUR_GREEN)compiled$(COLOUR_END)"

$(OBJECTDIR):
	@mkdir -p $@
	@echo "$@ $(COLOUR_GREEN)created$(COLOUR_END)"

out: $(NAME)
	@cp $(NAME) ../
	@echo "$< $(COLOUR_GREEN)moved$(COLOUR_END)"

uninstall: clean
	@make -sC $(LIBMXDIR) $@
	@make -sC $(LIBDBDIR) $@
	@rm -rf $(NAME)
	@echo "$@ $(COLOUR_GREEN)finished$(COLOUR_END)"

clean:
	@make -sC $(LIBMXDIR) $@
	@make -sC $(LIBDBDIR) $@
	@rm -rf $(OBJECTDIR)
	@rm -rf *.txt
	@echo "$@ $(COLOUR_GREEN)finished$(COLOUR_END)"

reinstall: uninstall all
