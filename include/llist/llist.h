#ifndef LLIST_H
#define LLIST_H
#include <stdlib.h>
#include <stdio.h>

typedef struct llist LinkedList;
typedef struct printers {
    void (*pre)(FILE *, size_t);
    void (*elem)(FILE *, size_t, size_t, void *);
    void (*post)(FILE *, size_t);
} llist__Printers;

void llist__append(LinkedList *, void *);
LinkedList * llist__create (void);
void llist__delete(LinkedList *, bool (*)(void *), bool);
void llist__destroy (LinkedList **);
void llist__insert (LinkedList *, size_t, void *);
size_t llist__get_length (LinkedList *);
void llist__prepend(LinkedList *, void *);
void llist__print(FILE *, LinkedList *, llist__Printers *);

#endif
