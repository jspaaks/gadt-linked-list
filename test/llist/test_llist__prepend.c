#include "llist/llist.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

typedef llist__Printers Printers;

static LinkedList * lst = NULL;

void setup (void) {
    cr_redirect_stdout();
    lst = llist__create();
}

static void teardown (void) {
    llist__destroy(&lst);
}

static void print_elem (FILE * sink, size_t idx, size_t nelems, void * elem) {
    if (idx < nelems - 1) {
        fprintf(sink, "%d, ", *((int *) elem));
    } else {
        fprintf(sink, "%d", *((int *) elem));
    }
}

static Printers printers = { .pre = NULL, .elem = print_elem, .post = NULL };

Test(llist__prepend, four_items, .init = setup, .fini = teardown) {
    int arr[] = { 100, 101, 102, 103 };
    llist__prepend(lst, (void *) &arr[3]);
    llist__prepend(lst, (void *) &arr[2]);
    llist__prepend(lst, (void *) &arr[1]);
    llist__prepend(lst, (void *) &arr[0]);
    llist__print(stdout, lst, &printers);
    fflush(stdout);
    cr_assert_stdout_eq_str("[100, 101, 102, 103]\n");
}
