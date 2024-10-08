#include "llist/llist.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

typedef llist__Printers Printers;

static LinkedList * lst = NULL;

static void setup (void) {
    cr_redirect_stdout();
    lst = llist__create();
}

static void teardown (void) {
    llist__destroy(&lst);
}

static void print_elem (FILE * fd, size_t idx, size_t nelems, void * elem) {
    if (idx < nelems - 1) {
        fprintf(fd, "%d, ", *((int *) elem));
    } else {
        fprintf(fd, "%d", *((int *) elem));
    }
}

static Printers printers = { .pre = NULL, .elem = print_elem, .post = NULL };

Test(llist__append, four_items, .init = setup, .fini = teardown) {
    int arr[] = { 100, 101, 102, 103 };
    llist__append(lst, (void *) &arr[0]);
    llist__append(lst, (void *) &arr[1]);
    llist__append(lst, (void *) &arr[2]);
    llist__append(lst, (void *) &arr[3]);
    llist__print(lst, &printers, stdout);
    fflush(stdout);
    cr_assert_stdout_eq_str("[100, 101, 102, 103]\n");
}
