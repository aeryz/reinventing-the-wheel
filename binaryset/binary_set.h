#include <stdio.h>
#include <stdlib.h>
 
typedef int (*Comp)(const void*, const void*);

struct BinarySetElement
{
    void *a;
    struct BinarySetElement *left;
    struct BinarySetElement *right;
};

struct BinarySet{
    Comp comp_func;
    struct BinarySetElement *element;
};
 
struct BinarySet *binary_set_init(Comp comp_func);

void insert(struct BinarySet *set, void *num);
int search(struct BinarySet *set, void* key);
void free_set(struct BinarySet *set);