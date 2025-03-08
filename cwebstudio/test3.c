#include "CWebStudio.h"
CwebNamespace cweb;

CwebHttpResponse *handle_request(CwebHttpRequest *request){
    char *html = "<html> \
                <head><title>My First C Web Page</title></head> \
                <body><h1>Hello from C!</h1></body> \
                </html>";
    return cweb.response.send_var_html(html,200);
}

int main(){
    cweb = newCwebNamespace();
    struct CwebServer server= newCwebSever(8083,handle_request);
    cweb.server.start(&server);
    return 0;
}