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

Test(llist__get_length, noop, .init = setup, .fini = teardown) {
    size_t expected = 0;
    size_t actual = llist__get_length(lst);
    cr_assert(actual == expected, "Instance of LinkedList should be of length %zu but was %zu.\n", expected, actual);
    llist__print(lst, &printers, stdout);
    fflush(stdout);
    cr_assert_stdout_eq_str("[]\n");
}

Test(llist__get_length, after_inserting_four_items, .init = setup, .fini = teardown) {
    int arr[] = { 100, 101, 102, 103 };
    llist__insert(0, (void *) &arr[3], lst);
    llist__insert(0, (void *) &arr[2], lst);
    llist__insert(0, (void *) &arr[1], lst);
    llist__insert(0, (void *) &arr[0], lst);
    constexpr size_t expected = sizeof(arr) / sizeof(arr[0]);
    size_t actual = llist__get_length(lst);
    cr_assert(actual == expected, "Instance of LinkedList should be of length %zu but was %zu.\n", expected, actual);
    llist__print(lst, &printers, stdout);
    fflush(stdout);
    cr_assert_stdout_eq_str("[100, 101, 102, 103]\n");
}
