#include "doTheWorld.h"

int main(){
    DtwNamespace dtw = newDtwNamespace();
    bool result = dtw.write_string_file_content("tests/target/a.txt","Hello World!");
    printf("result: %s\n", result ? "true" : "false");
    return 0;
}