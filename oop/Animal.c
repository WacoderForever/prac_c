#include <stdio.h>
#include <stdlib.h>

typedef struct Animal{
    int age;
    char *name;
}Animal;

typedef struct Dog{
    Animal* base;    //must be first
    char *breed;
}Dog;

typedef struct Cow{
    Animal* base;
    char *breed;
}Cow;

Animal* init_animal(int age,char *name){
    Animal* an = (Animal*)malloc(sizeof(Animal));
    an->age = age;
    an->name = name;

    return an;
}

Dog* init_dog(int age,char *name,char *breed){
    Dog* dog = (Dog*) malloc(sizeof(Dog));
    dog->base = init_animal(age,name);
    dog->breed = breed;

    return dog;
}

Cow* init_cow(int age,char *name,char *breed){
    Cow* cow = (Cow*) malloc(sizeof(Cow));
    cow->base = init_animal(age,name);
    cow->breed = breed;

    return cow;
}

void print_animal(Animal an){
    printf("Name: %s\nAge: %d\n",an.name,an.age);
}

void print_dog(Dog dog){
    print_animal(*dog.base);
    printf("Breed: %s\n",dog.breed);
}

void print_cow(Cow cow){
    print_animal(*cow.base);
    printf("Breed: %s\n",cow.breed);
}

void free_animal(void* any_animal){
    free(any_animal);
}

int main(){
    Dog* dog = init_dog(3,"Rex","Chihuahua");
    print_dog(*dog);
    free_animal(dog);

    Cow *cow = init_cow(5,"Linda","Freshian");
    print_cow(*cow);
    free_animal(cow);

    return 0;
}