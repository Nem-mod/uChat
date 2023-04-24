NAME_SERV	= uchat_server
NAME_CLIENT = uchat

CFLAGS 	= -std=c11 -Wall -Wextra -Werror -Wpedantic -g
COMP 	= clang

SERV_DIR 	= server/
CLIENT_DIR 	= client/

all: @brew install gtk+3 @brew install openssl@3 @brew install json-c @brew install sqlite3 userver uclient 

userver: 
	@make -sC $(SERV_DIR)

uclient: 
	@make -sC $(CLIENT_DIR)
	
clean:
	@make clean -sC $(SERV_DIR)
	@make clean -sC $(CLIENT_DIR)
	

uninstall: clean
	@make uninstall -sC $(SERV_DIR)
	@make uninstall -sC $(CLIENT_DIR)
	rm -rf $(NAME_CLIENT)
	rm -rf $(NAME_SERV)
	rm -rf *.txt

reinstall: uninstall all
