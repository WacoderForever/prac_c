#include "CWebStudio.h"

CwebNamespace cweb;

char *html(){
    char *code = "\
        <!DOCTYPE html>\n\
        <html lang=\"en\">\n\
        <head>\n\
            <meta charset=\"UTF-8\">\n\
            <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\
            <title>Basic HTML Page</title>\n\
            <style>\n\
                body {\n\
                    font-family: Arial, sans-serif;\n\
                    margin: 20px;\n\
                    padding: 20px;\n\
                    background-color: #f4f4f4;\n\
                }\n\
                h1 {\n\
                    color: #333;\n\
                }\n\
            </style>\n\
        </head>\n\
        <body>\n\
            <h1>Welcome to My Basic HTML Page</h1>\n\
            <p>This is a simple HTML page with basic styling.</p>\n\
        </body>\n\
        </html>\n";
    return code;
}

CwebHttpResponse *main_sever(CwebHttpRequest *request){
    return cweb.response.send_text(html(), 200);
}

int main(int argc, char *argv[]){
    cweb = newCwebNamespace();
    struct CwebServer server = newCwebSever(5001, main_sever);
    cweb.server.start(&server);
    return 0;
}
