#include "CWebStudio.h"

CwebNamespace cweb;

CwebHttpResponse *main_server(CwebHttpRequest *request){
    char *name = cweb.request.get_param(request,"name");
    if(name){
        printf("%s\n",name);
    }
    else{
        printf("Not found\n");
    }
    return cweb.response.send_text("Hello World",200);
}

int main(int argc,char **argv){
    cweb = newCwebNamespace();
    struct CwebServer server=newCwebSever(5001,main_server);
    cweb.server.start(&server);
    return 0;
}