#include "rtw_bset.h"

void rtw_bset_insert(rtw_bset *self, void *elem) {
    rtw_bset_elem_ *temp = self->element, *prev = self->element;

    if (self->element == NULL) {
        self->element = (rtw_bset_elem_ *)malloc(sizeof(rtw_bset_elem_));
        self->element->a = elem;
        self->element->left = self->element->right = NULL;
        return;
    } else {
        while (temp != NULL) {
            if (self->comp_func(elem, temp->a) == 1) {
                prev = temp;
                temp = temp->right;
            } else if (self->comp_func(elem, temp->a) == -1) {
                prev = temp;
                temp = temp->left;
            } else
                return;
        }
        temp = (rtw_bset_elem_ *)malloc(sizeof(rtw_bset_elem_));
        temp->a = elem;
        if (elem >= prev->a) {
            prev->right = temp;
            free(temp);
        } else {
            prev->left = temp;
            free(temp);
        }
    }
}

int rtw_bset_search(rtw_bset *self, void *elem) {
    rtw_bset_elem_ *temp = self->element;
    while (temp != NULL) {
        if (self->comp_func(elem, temp->a) == 1) {
            temp = temp->right;
        } else if (self->comp_func(elem, temp->a) == -1) {
            temp = temp->left;
        } else {
            return 1;
        }
    }
    return 0;
}

void rtw_bset_free(rtw_bset *self) {
    if (self != NULL) {
        if (self->element != NULL)
            free(self->element);
        free(self);
    }
}

rtw_bset rtw_bset_init(rtw_bset_cmp_fn comp_func) {
    rtw_bset set;
    set.comp_func = comp_func;
    return set;
}
