# Oracle is fucking pidoras. To get more pretty version of src structure and makefile - write git switch develop
NAME	=	uchat
CFLAGS 	=	-std=c11 $(addprefix -W, all extra error pedantic) 
COMP 	= 	clang

COLOUR_GREEN	=	\033[32;1m
# COLOUR_RED		=	\033[0;31m
# COLOUR_BLUE		=	\033[0;34m
COLOUR_END		=	\033[0m

# TODO: DELEEEEEEEEEEEEEETEEEEEEEEEEE THIIIIIIIIIIIIIIIIIS BEFORE PUSH INTO UCODE GITLAB PLEEEEASEEEEEEEEE
UNAME_S 	= 	$(shell uname -s)
# DELEEEEEEEEEEEEEETEEEEEEEEEEE THIIIIIIIIIIIIIIIIIS BEFORE PUSH INTO UCODE GITLAB PLEEEEASEEEEEEEEE

UTILSDIR	=	../utils
LIBSDIR		=	$(UTILSDIR)/libs

# SOURCEDIR 	=	src \
# 				$(UTILSDIR)/src
SOURCEDIR 	=	src
OBJECTDIR	=	obj
INCLUDEDIR	=	inc \
				$(UTILSDIR)/inc

LIBMXDIR	=	$(LIBSDIR)/libmx
LIBSSLDIR	=	$(LIBSDIR)/libssl
LIBJSONDIR	=	$(LIBSDIR)/libjson

# DELEEEEEEEEEEEEEETEEEEEEEEEEE THIIIIIIIIIIIIIIIIIS BEFORE PUSH INTO UCODE GITLAB PLEEEEASEEEEEEEEE									
ifeq ($(UNAME_S),Darwin)					
	LIBJSONDIR	=	$(LIBSDIR)/libjson_mac
	LIBSSLDIR	=	$(LIBSDIR)/libssl_mac
endif
# DELEEEEEEEEEEEEEETEEEEEEEEEEE THIIIIIIIIIIIIIIIIIS BEFORE PUSH INTO UCODE GITLAB PLEEEEASEEEEEEEEE

INCLUDEINC	=	$(addprefix -I, $(INCLUDEDIR))
LIBINC		=	$(addprefix -I, $(LIBMXDIR)/inc $(LIBJSONDIR)/inc $(LIBSSLDIR)/include)
GTKINC 		= 	`pkg-config --cflags gtk+-3.0`

LIBLINK		=	-L$(LIBMXDIR) -lmx \
				-L$(LIBSSLDIR) -lssl -lcrypto \
				-L$(LIBJSONDIR) -ljson-c \
				-ldl -lpthread
GTKLINK 	= 	`pkg-config --cflags  --libs gtk+-3.0`

SRC_FILES	=	$(foreach dir, $(SOURCEDIR), $(wildcard $(dir)/*.c))
OBJ_FILES	=	$(addprefix $(OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES	=	$(foreach dir, $(INCLUDEDIR), $(wildcard $(dir)/*.h))

all: libs $(NAME) out
# all: testprint

libs: libmx

testprint:
	@echo $(OBJ_FILES)

libmx:
	@make -sC $(LIBMXDIR)
	@echo "$@ $(COLOUR_GREEN)created$(COLOUR_END)"

$(NAME): $(OBJ_FILES)
	@echo "start linking"	
	@$(COMP) $(CFLAGS) $(OBJ_FILES) $(LIBLINK) $(GTKLINK) -o $@ --debug

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c $(OBJECTDIR)
	@$(COMP) $(CFLAGS) -c $< -o $@ $(INCLUDEINC) $(LIBINC) $(GTKINC) --debug
	@echo "$@ $(COLOUR_GREEN)compiled$(COLOUR_END)"

$(OBJECTDIR):
	@mkdir -p $@
	@echo "$@ $(COLOUR_GREEN)created$(COLOUR_END)"

out: $(NAME)
	@cp $(NAME) ../
	@echo "$< $(COLOUR_GREEN)moved$(COLOUR_END)"

uninstall: clean
	@make -sC $(LIBMXDIR) $@
	@rm -rf $(NAME)
	@echo "$@ $(COLOUR_GREEN)finished$(COLOUR_END)"

clean:
	@make -sC $(LIBMXDIR) $@
	@rm -rf $(OBJECTDIR)
	@rm -rf *.txt
	@echo "$@ $(COLOUR_GREEN)finished$(COLOUR_END)"

reinstall: uninstall all
