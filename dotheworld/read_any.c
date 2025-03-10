#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();
    const char *path = "tests/target/blob.png";
    bool is_binary;
    long size;
    unsigned char *content = dtw.load_any_content(path,&size,&is_binary);
    if(!content){
        printf("Error opening: %s\n",path);
        return 1;
    }
    printf("Size: %ld\n",size);
    printf("is_binary: %s\n", is_binary ? "true" : "false");
    dtw.write_any_content("tests/target/blob2.png",content,size);
    return 0;
}