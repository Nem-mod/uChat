NAME	=	uchat
CFLAGS 	=	-std=c11 $(addprefix -W, all extra error pedantic) 
COMP 	= 	clang

COLOUR_GREEN	=	\033[32;1m
# COLOUR_RED		=	\033[0;31m
# COLOUR_BLUE		=	\033[0;34m
COLOUR_END		=	\033[0m

UTILSDIR	=	../utils
LIBSDIR		=	$(UTILSDIR)/libs

SOURCEDIR 	=	src \
				$(UTILSDIR)/src
OBJECTDIR	=	obj
INCLUDEDIR	=	inc \
				$(UTILSDIR)/inc

LIBMXDIR	=	$(LIBSDIR)/libmx
LIBDBDIR	=	$(LIBSDIR)/libdb
LIBSSLDIR	=	$(LIBSDIR)/libssl

INCLUDEINC	=	$(addprefix -I, $(INCLUDEDIR))
LIBINC		=	$(addprefix -I$(LIBSDIR)/, libmx/inc libdb/inc libssl/include) #refactor
GTKINC 		= 	`pkg-config --cflags gtk+-3.0`

LIBLINK		=	-L$(LIBMXDIR) -lmx -L$(LIBDBDIR) -ldb  -L$(LIBSSLDIR) -lssl -lcrypto -ldl -lpthread
GTKLINK 	= 	`pkg-config --cflags  --libs gtk+-3.0`

SRC_FILES	=	$(foreach dir, $(SOURCEDIR), $(wildcard $(dir)/*.c))
OBJ_FILES	=	$(addprefix $(OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES	=	$(foreach dir, $(INCLUDEDIR), $(wildcard $(dir)/*.h))

all: libs $(NAME) clean out

libs: libmx libdb libssl

print:
	@echo $(INC_FILES)

libmx:
	@make -sC $(LIBMXDIR)
	@echo "$@ $(COLOUR_GREEN)created$(COLOUR_END)"

libdb:
	@make -sC $(LIBDBDIR)
	@echo "$@ $(COLOUR_GREEN)created$(COLOUR_END)"

libssl:

$(NAME): $(OBJECTDIR) copy $(OBJ_FILES)
	@$(COMP) $(CFLAGS) $(OBJ_FILES) $(LIBLINK) $(GTKLINK) -o $@ --debug

$(OBJ_FILES): %.o: %.c
	@$(COMP) $(CFLAGS) -c $< -o $@ $(INCLUDEINC) $(LIBINC) $(GTKINC) --debug
	@echo "$@ $(COLOUR_GREEN)compiled$(COLOUR_END)"

$(OBJECTDIR):
	@mkdir -p $@
	@echo "$@ $(COLOUR_GREEN)created$(COLOUR_END)"

copy:
	@cp -f $(SRC_FILES) $(OBJECTDIR)

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
