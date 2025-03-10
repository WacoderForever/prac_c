#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();
    const char *path = "tests/target/a.txt";
    char *content = dtw.load_string_file_content(path);
    if(!content){
        printf("Error opening:%s\n",path);
        return 1;
    }
    printf("content: %s\n",content);
    free(content);
}