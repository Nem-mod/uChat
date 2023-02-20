NAME	=	libmx.a
CFLAGS 	=	-std=c11 $(addprefix -W, all extra error pedantic) 
COMP 	= 	clang

COLOUR_GREEN	=	\033[32;1m
# COLOUR_RED		=	\033[0;31m
# COLOUR_BLUE		=	\033[0;34m
COLOUR_END		=	\033[0m

SOURCEDIR 	=	src
OBJECTDIR	=	obj
INCLUDEDIR	=	inc

SRC_FILES = $(wildcard $(SOURCEDIR)/*.c)
OBJ_FILES = $(addprefix $(OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(INCLUDEDIR)/*.h)

all: $(NAME) clean

$(NAME): $(OBJ_FILES)
	@ar rcs $@ $^

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c $(OBJECTDIR)
	@$(COMP) $(CFLAGS) -c $< -o $@ -I $(INCLUDEDIR) --debug

$(OBJECTDIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJECTDIR)

uninstall: clean
	rm -rf $(NAME)

reinstall: uninstall all
