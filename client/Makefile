# Oracle is fucking pidoras. To get more pretty version of src structure and makefile - write git switch develop
NAME	=	uchat
CFLAGS 	=	-std=c11 $(addprefix -W, all extra error pedantic) 
COMP 	= 	clang

COLOUR_GREEN	=	\033[32;1m
# COLOUR_RED		=	\033[0;31m
# COLOUR_BLUE		=	\033[0;34m
COLOUR_END		=	\033[0m


UTILSDIR	=	../utils
LIBSDIR		=	$(UTILSDIR)/libs

# SOURCEDIR 	=	src \
# 				$(UTILSDIR)/src
SOURCEDIR 	=	src
OBJECTDIR	=	obj
INCLUDEDIR	=	inc \
				$(UTILSDIR)/inc

LIBMXDIR	=	$(LIBSDIR)/libmx
# LIBSSLDIR	=	$(LIBSDIR)/libssl
# LIBJSONDIR	=	$(LIBSDIR)/libjson
					
LIBJSONDIR	=	$(LIBSDIR)/libjson_mac
LIBSSLDIR	=	$(LIBSDIR)/libssl_mac

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

libs: libmx

libmx:
	@make -sC $(LIBMXDIR)

$(NAME): $(OBJ_FILES)
	@$(COMP) $(CFLAGS) $(OBJ_FILES) $(LIBLINK) $(GTKLINK) -o $@ --debug

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c $(OBJECTDIR)
	@$(COMP) $(CFLAGS) -c $< -o $@ $(INCLUDEINC) $(LIBINC) $(GTKINC) --debug

$(OBJECTDIR):
	@mkdir -p $@

out: $(NAME)
	@cp $(NAME) ../

uninstall: clean
	@make -sC $(LIBMXDIR) $@
	@rm -rf $(NAME)

clean:
	@make -sC $(LIBMXDIR) $@
	@rm -rf $(OBJECTDIR)
	@rm -rf *.txt

reinstall: uninstall all
