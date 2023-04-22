#include "client.h"

int main(int argc, char* argv[])
{
    remove(SYSLOG);
    if(argc != 2){
        mx_log_info(SYSLOG, "usage: ./uchat [port]");
        return 0;
    }

    gtk_init(&argc, &argv);
    t_uchat_application* app = mx_create_app(argv);

    mx_change_scenes(app, SIGNIN);

    gtk_main();
    
    return 0;
}
