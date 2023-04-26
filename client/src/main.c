#include "client.h"

int main(int argc, char* argv[])
{
    // system("open ~/");
    remove(SYSLOG);
    if(argc != 3){
        mx_log_info(SYSLOG, "usage: ./uchat [ip] [port]");
        mx_printerr("usage: ./uchat [ip] [port]\n");
        return 0;
    }

    gtk_init(&argc, &argv);
    t_uchat_application* app = mx_create_app(argv);

    mx_change_scenes(app, SIGNIN);

    gtk_main();
    
    return 0;
}
