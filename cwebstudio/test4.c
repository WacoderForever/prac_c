#include "CWebStudio.h"

CwebNamespace cweb;

CwebHttpResponse *handle_request(CwebHttpRequest *request){
    return cweb.response.send_file("public/index.html",CWEB_AUTO_SET_CONTENT,200);
}

int main(){
    cweb= newCwebNamespace();
    struct CwebServer server =newCwebSever(8084,handle_request);
    cweb.server.start(&server);
    return 0;
}