#include "client.h"


int main(int argc, char* argv[])
{
    remove(SYSLOG);
    if(argc != 2){
        mx_log_info(SYSLOG, "usage: ./uchat [port]");
        return 0;
    }
    gtk_init(&argc, &argv);
    t_UchatApplication* app = mx_create_app(argv);
    gtk_widget_show(app->scenes->signUp_scene->w_signup);

    char *json = "{ \"type\": \"POST\", \
        \"url\": \"/auth/register\", \
        \"property\": { \"login\": \"nemmmmmmmdadmm\", \
            \"password\": \"1223\", \
            \"first_name\": \"1223\", \
            \"last_name\": \"1223\" \
        }" \
    "}";



    mx_strcpy(app->serv_conection->wbuffer, json);
    mx_write_to_server(app->serv_conection->ssl, app->serv_conection->wbuffer); 
  
    
    char *json2 = "{ \"type\": \"POST\", \
        \"url\": \"/auth/register\", \
        \"property\": { \"login\": \"hema\", \
            \"password\": \"ss\", \
            \"first_name\": \"122Art3\", \
            \"last_name\": \"Bruh\" \
        }" \
    "}";
    
    mx_strcpy(app->serv_conection->wbuffer, json2);
    g_print ("%s", app->serv_conection->wbuffer);
    mx_write_to_server(app->serv_conection->ssl, app->serv_conection->wbuffer); 

    //g_signal_connect (app->scenes->signUp_scene->b_signup, "clicked", G_CALLBACK (callva), app);
    gtk_main ();

    return 0;
}
