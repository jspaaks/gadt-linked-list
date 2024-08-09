#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "llist/llist.h"
#include <unistd.h>

typedef llist__Printers Printers;

typedef struct {
    bool marked;
    int data;
} MyStruct;

static MyStruct arr[] = {
    {
        .marked = false,
        .data = 100
    },
    {
        .marked = false,
        .data = 101
    },
    {
        .marked = false,
        .data = 102
    },
    {
        .marked = false,
        .data = 103
    }
};

static LinkedList * lst = NULL; 

static void setup (void) {
    cr_redirect_stdout();
    lst = llist__create();
    llist__prepend(lst, (void *) &arr[3]);
    llist__prepend(lst, (void *) &arr[2]);
    llist__prepend(lst, (void *) &arr[1]);
    llist__prepend(lst, (void *) &arr[0]);
}

static void teardown (void) {
    llist__destroy(&lst);
}

static void print_elem (FILE * sink, size_t idx, size_t nelems, void * elem) {
    MyStruct my_struct = *((MyStruct *) elem);
    if (idx < nelems - 1) {
        fprintf(sink, "{.marked: %s, .data: %d}, ", my_struct.marked ? "true" : "false", my_struct.data);
    } else {
        fprintf(sink, "{.marked: %s, .data: %d}", my_struct.marked ? "true" : "false", my_struct.data);
    }
}

static Printers printers = {
    .pre = NULL,
    .elem = print_elem,
    .post = NULL
};

static bool filter (void * p) {
    MyStruct my_struct = *((MyStruct *) p);
    return my_struct.data % 2 == 0;
}

Test(llist__delete, global, .init = setup, .fini = teardown) {
    llist__delete(lst, filter, true);
    llist__print(stdout, lst, &printers);
    fflush(stdout);
    cr_assert_stdout_eq_str("[{.marked: false, .data: 101}, {.marked: false, .data: 103}]\n");
}

Test(llist__delete, local, .init = setup, .fini = teardown) {
    llist__delete(lst, filter, false);
    llist__print(stdout, lst, &printers);
    fflush(stdout);
    cr_assert_stdout_eq_str("[{.marked: false, .data: 101}, {.marked: false, .data: 102}, {.marked: false, .data: 103}]\n");
}
