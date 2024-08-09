#ifndef LLIST_H
#define LLIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct llist LinkedList;

typedef struct printers {
    void (*pre)(FILE *, size_t);
    void (*elem)(FILE *, size_t, size_t, void *);
    void (*post)(FILE *, size_t);
} llist__Printers;

void llist__append (LinkedList *, void *);
LinkedList * llist__create (void);
void llist__delete (const bool, LinkedList *, bool (*)(void *));
void llist__destroy (LinkedList **);
void llist__insert (const size_t, void *, LinkedList *);
size_t llist__get_length (const LinkedList *);
void llist__prepend (LinkedList *, void *);
void llist__print (const LinkedList *, const llist__Printers *, FILE *);

#endif
