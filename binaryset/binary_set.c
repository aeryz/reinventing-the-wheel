#include "binary_set.h"


void insert(struct BinarySet *set, void *num)
{
    struct BinarySetElement *temp = set->element, *prev = set->element;
 
    if (set->element == NULL)
    {
        set->element = (struct BinarySetElement *)malloc(sizeof(struct BinarySetElement));
        set->element->a = num;
        set->element->left = set->element->right = NULL;
        return;
    }
    else
    {
        while (temp != NULL)
        {
            if (set->comp_func(num,temp->a) == 1)
            {
                prev = temp;
                temp = temp->right;
            }
            else if(set->comp_func(num,temp->a) == -1)
            {
                prev = temp;
                temp = temp->left;
            }
            else
                return;
        }
        temp = (struct BinarySetElement *)malloc(sizeof(struct BinarySetElement));
        temp->a = num;
        if (num >= prev->a)
        {
            prev->right = temp;
            free(temp);
        }
        else
        {
            prev->left = temp;
            free(temp);
        }
    }
}
 
int search(struct BinarySet *set, void* key)
{
    struct BinarySetElement *temp = set->element;
    while (temp != NULL)
    {
        if (set->comp_func(key,temp->a) == 1)
        {
            temp = temp->right;
        }
        else if (set->comp_func(key,temp->a) == -1)
        {
            temp = temp->left;
        }
        else
        {
            return 1;
        }
    }
	return 0;
}
 
void free_set(struct BinarySet *set)
{
    if (set != NULL)
    {
        if(set->element != NULL)
            free(set->element);
        free(set);
    }
}

struct BinarySet *binary_set_init(Comp comp_func)
{
    struct BinarySet *set = malloc(sizeof(struct BinarySet));
    set->comp_func = comp_func;
    return set;
}