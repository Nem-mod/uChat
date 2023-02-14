NAME	= libmx.a
CFLAGS 	= -std=c11 -Wall -Wextra -Werror -Wpedantic -g
COMP 	= clang
AR 		= ar rcs

OBJECTDIR 	= obj
INCLUDEDIR 	= inc
SOURCEDIR 	= src

SRC_FILES = $(wildcard $(SOURCEDIR)/*.c)
OBJ_FILES = $(addprefix $(OBJECTDIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(INCLUDEDIR)/*.h)

all: $(NAME) clean

$(NAME): $(OBJ_FILES)
	@$(AR) $@ $^

$(OBJ_FILES): | $(OBJECTDIR)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c $(INC_FILES)
	@$(COMP) $(CFLAGS) -c $< -o $@ -I $(INCLUDEDIR)

$(OBJECTDIR):
	@$ mkdir -p $@

clean:
	rm -rf $(OBJECTDIR)

uninstall: clean
	rm -rf $(NAME)

reinstall: all
