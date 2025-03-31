#include "CWebStudio.h"

CwebNamespace cweb;

CwebHttpResponse *main_server(CwebHttpRequest *request){
    CwebDict *query_params=request->params;
    for(int i=0;i<query_params->size;i++){
        CwebKeyVal *key_val = query_params->keys_vals[i];
        char *key=key_val->key;
        char *value=key_val->value;
        printf("%s: %s\n",key,value);
    }
    printf("---------------------------------\n");
    return cweb.response.send_text("Hello world\n",200);
}

int main(int argc,char **argv){
    cweb = newCwebNamespace();
    struct CwebServer server=newCwebSever(5002,main_server);
    cweb.server.start(&server);
    return 0;
}