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
    if(request->route=="/"){ //homepage
        return cweb.response.send_file("public/html",CWEB_AUTO_SET_CONTENT,200);
    }

    if((!strcmp(request->route,"/shorten"))){
        char *long_url = cweb.request.get_param(request,"url");
        if(!long_url) return cweb.response.send_text("Missing parameter",400);
        char *short_url = generate_short_url(long_url);
        save_url(short_url,long_url);

        char response[128];
        snprintf(response,sizeof(response),"Short URL: http://localhost:5000/%s",short_url);
        return cweb.response.send_text(response,200);
    }
    char *long_url=get_long_url(request->route + 1); //gets the short code
    if(long_url){
        char response_text[256];
        snprintf(response_text, sizeof(response_text), 
                 "Redirecting to <a href='%s'>%s</a>", long_url, long_url);

        CwebHttpResponse *response = cweb.response.send_text(response_text, 301);
        cweb.response.add_header(response, "Location", long_url); // Set redirect
        return response;
    }

    return cweb.response.send_text("404-Not Found",404);
}

int main(){
    cweb =newCwebNamespace();
    struct CwebServer server =newCwebSever(5000,handle_request);
    cweb.server.start(&server);
}