#include <stdio.h>

size_t len_str(const char *str){
    size_t len = 0;
    while(*(str) != '\0'){
        len++;
        str++;
    }
    return len;
}

int main(){
    const char *p = "abxyabxz";
    const char *t = "xabxyabxz";
    int t_len = len_str(t);
    int p_len = len_str(p);

    for(int i=0;i<t_len;i++){
        int found_start = 0;
        int match = 1;
        if(t[i]==p[0]){
            found_start = 1;
            int k = i+1;
            for(int j=1;j<p_len;j++){
                if(t[k] != p[j]){
                    match = 0;
                    break;
                }
                k++;
            }
        }
        if(match && found_start){
            printf("The pattern begins at position: %d\n",i);
        }
    }

    return 0;
}