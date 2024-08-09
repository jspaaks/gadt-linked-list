#include "llist/llist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node Node;

struct node {
    void * payload;
    struct node * next;
};

struct llist {
    size_t nelems;
    Node * firstnode;
};

LinkedList * llist__create(void) {
    LinkedList * lst = malloc(sizeof(LinkedList) * 1);
    if (lst == NULL) {
        fprintf(stderr, "Something went wrong allocating memory for linked list.\n");
        exit(EXIT_FAILURE);
    }
    lst->nelems = 0;
    lst->firstnode = NULL;
    return lst;
}

void llist__delete(LinkedList * lst, bool (*filter)(void *), bool global) {
    Node * prev = NULL;
    Node * curr = lst->firstnode;
    while (curr != NULL) {
        bool cond = filter(curr->payload);
        if (cond && prev == NULL) {
            // item is first item
            lst->firstnode = curr->next;
            Node * tmp = curr;
            prev = NULL;
            curr = curr->next;
            lst->nelems--;
            free(tmp);
        } else if (cond) {
            // item is not first
            Node * tmp = curr;
            prev->next = curr->next;
            curr = curr->next;
            lst->nelems--;
            free(tmp);
        } else {
            prev = curr;
            curr = curr->next;
        }
        if (cond && !global) return;
    }
}

void llist__destroy(LinkedList ** lst) {
    Node * curr = (*lst)->firstnode;
    while (curr != NULL) {
        struct node * tmp = curr;
        curr = curr->next;
        free(tmp);
        (*lst)->nelems--;
    }
    assert((*lst)->nelems == 0 && "Expected number of elements in linked list to be 0 after clearing all items.\n");
    free(*lst);
    *lst = NULL;
}

void llist__insert(LinkedList * lst, size_t pos, void * item) {
    Node * new = malloc(sizeof(Node) * 1);
    if (new == NULL) {
        fprintf(stderr, "Something went wrong allocating memory for new node in linked list.\n");
        exit(EXIT_FAILURE);
    }
    new->payload = item;
    new->next = NULL;

    assert(pos <= lst->nelems && "Can't insert element past the end of the list\n");

    Node * prev = NULL;
    Node * curr = lst->firstnode;
    for (size_t i = 0; i < pos && curr != NULL; i++) {
        prev = curr;
        curr = curr->next;
    }
    new->next = curr;
    if (pos == 0) {
        lst->firstnode = new;
    } else {
        prev->next = new;
    }
    lst->nelems++;
}

void llist__append(LinkedList * lst, void * item) {
    size_t n = llist__get_length(lst);
    llist__insert(lst, n, item);  
}

void llist__prepend(LinkedList * lst, void * item) {
    llist__insert(lst, 0, item);  
}

size_t llist__get_length (LinkedList * lst) {
    return lst->nelems;
}

void llist__print(FILE * sink, LinkedList * lst, llist__Printers * printers) {

    // -- print preamble
    if (printers == NULL || printers->pre == NULL) {
        fprintf(sink, "[");
    } else {
        printers->pre(sink, lst->nelems);
    }

    // -- print each elem
    Node * curr = lst->firstnode;
    size_t i = 0;
    while (curr != NULL) {
        if (printers == NULL || printers->elem == NULL) {
            fprintf(sink, "%p%s", curr->payload, curr->next == NULL ? "" : ", ");
        } else {
            printers->elem(sink, i, lst->nelems, curr->payload);
        }
        curr = curr->next;
        i++;
    }

    // -- print postamble
    if (printers == NULL || printers->post == NULL) {
        fprintf(sink, "]\n");
    } else {
        printers->post(sink, lst->nelems);
    }
}
