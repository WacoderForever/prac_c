#include "../../../../release/doTheWorld.h"





int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwHash *my_hash = dtw.hash.newHash();

    dtw.hash.digest_entity_last_modification(my_hash,"tests/target/a.txt");

    printf("after a file :%s\n",my_hash->hash);

    dtw.hash.digest_folder_by_last_modification(my_hash,"tests/target");
    printf("after a folder %s\n",my_hash->hash);

    dtw.hash.free(my_hash);
}
