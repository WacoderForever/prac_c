#include "CWebStudio.h"
#include <stdint.h>

CwebNamespace cweb;

uint32_t fnv1a_hash(const char *str) {
    uint32_t hash = 2166136261u; 
    while (*str) {
        hash ^= (uint8_t)(*str);
        hash *= 16777619u; 
        str++;
    }
    return hash;
}

char *generate_short_url(char *long_url){
    char *short_url=(char*)malloc(sizeof(char)*7);
    if(short_url == NULL) printf("Memory allocation failed");
    snprintf(short_url,sizeof(short_url),"%06X",fnv1a_hash(long_url) % 0xFFFFFF );
    return short_url;

}

void save_url(const char *short_url,const char *long_url){
    FILE *fp=fopen("url.db","a"); //open file in append mode
    if(fp){
        fprintf(fp,"%s %s\n",short_url,long_url);
        fclose(fp);
    }
    fclose(fp);
}

char *get_long_url(const char *short_url){
    static char long_url[1024];
    char short_code[10];
    FILE *fp=fopen("url.db","r");   //open file in read mode
    if(!fp) return NULL;
    while(fscanf(fp,"%s %s",short_code,long_url) != EOF){
        if(!strcmp(short_code,short_url)){
            fclose(fp);
            return long_url;
        }
    }
    return NULL;
}

CwebHttpResponse *handle_request(CwebHttpRequest *request){
    if(!strcmp(request->route,"/")){ //homepage
        return cweb.response.send_file("public/index.html",CWEB_AUTO_SET_CONTENT,200);
    }

    return cweb.response.send_text("404-Not Found",404);
}

int main(){
    cweb =newCwebNamespace();
    struct CwebServer server =newCwebSever(5002,handle_request);
    cweb.server.start(&server);
}