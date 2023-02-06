NAME_SERV	= uchat_server
NAME_CLIENT = uchat

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g
COMP = clang

SERV_DIR = server/
CLIENT_DIR = client/

all: install

install: 
	@make all -C $(SERV_DIR)
	@make all -C $(CLIENT_DIR)
	
clean:
	@make clean -C $(SERV_DIR)
	@make clean -C $(CLIENT_DIR)
	

uninstall: clean
	@make uninstall -C $(SERV_DIR)
	@make uninstall -C $(CLIENT_DIR)
	rm -rf $(NAME_CLIENT)
	rm -rf $(NAME_SERV)
	rm -rf *.db
	rm -rf *.txt

reinstall: uninstall all
