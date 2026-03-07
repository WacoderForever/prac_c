#ifndef SET_H
#define SET_H

extern const void* Set;

void *add(void * Set,void *element);
void *find(const void *Set,void *element);
void *drop(void *Set,const void *element);
int contains(const void *Set,const void *element);

#endif