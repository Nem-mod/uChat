NAME		=	uchat_utils
#NAME_ROOT 	=	../$(NAME)
CFLAGS 		=	-std=c11 $(addprefix -W, all extra error pedantic) 
COMP 		=	clang

LIBSDIR		=	libs
SOURCEDIR 	=	src
OBJECTDIR	=	obj
INCLUDEDIR	=	inc

LIBMXDIR	=	$(LIBSDIR)/libmx
LIBDBDIR	=	$(LIBSDIR)/libdb
LIBSSLDIR	=	$(LIBSDIR)/libssl

LIBMX		=	$(LIBSDIR)/libmx.a
LIBDB		=	$(LIBSDIR)/libdb.a
LIBSSL		=	$(LIBSDIR)/libssl.a

LIBS		=	$(LIBMX) $(LIBDB) $(LIBSSL)

LIBINC		=	$(addprefix -I$(LIBSDIR)/, libmx/inc libdb/inc libssl/include)

LIBLINK		=	-L$(LBMX) -lmx -L$(LBDB) -ldb  -L$(LBSSL) -lssl -lcrypto

SRC_FILES	=	$(wildcard $(SOURCEDIR)/*.c)
OBJ_FILES	=	$(addprefix $(OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES	=	$(wildcard $(INCLUDEDIR)/*.h)

all: $(LIBS) $(OBJ_FILES)

$(LIBMX):
	make -sC $(LIBMXDIR)

$(LIBDB):
	make -sC $(LIBDBDIR)

$(LIBSSL):

$(OBJ_FILES): | $(OBJECTDIR)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c $(INC_FILES)
	$(COMP) $(CFLAGS) -c $< -o $@ -I $(INCLUDEDIR) $(LIBINC)

$(OBJECTDIR):
	mkdir -p $@

uninstall: clean
	make -sC $(LIBMXDIR) $@
	make -sC $(LIBDBDIR) $@

clean:
	make -sC $(LIBMXDIR) $@
	make -sC $(LIBDBDIR) $@
	rm -rf $(OBJECTDIR)

reinstall: uninstall all

