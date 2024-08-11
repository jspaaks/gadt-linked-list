#include "llist/llist.h"
#include <math.h>
#include <stdio.h>

typedef llist__Printers Printers;

static void printer_pre (FILE * fd, size_t nelems) {
    fprintf(fd, " -- LinkedList[%zu] = {", nelems);
}

static void printer_int_elem (FILE * fd, size_t idx, size_t nelems, void * p) {
    if (idx < nelems - 1) {
        fprintf(fd, "%d, ", *((int *) p));
    } else {
        fprintf(fd, "%d", *((int *) p));
    }
}

static void printer_float_elem (FILE * fd, size_t idx, size_t nelems, void * p) {
    if (idx < nelems - 1) {
        fprintf(fd, "%.2f, ", *((float *) p));
    } else {
        fprintf(fd, "%.2f", *((float *) p));
    }
}

static void printer_post (FILE * fd, size_t) {
    fprintf(fd, "}\n");
}

static bool filter (void * p) {
    int elem = *((int *) p);
    return elem > 100;
}

int main (void) {

    int arr1[] = { 100, 101, 102, 103 };

    Printers printers1 = { .pre = printer_pre, .elem = printer_int_elem, .post = printer_post };

    fprintf(stdout, " --- LinkedList library demonstrator ---\n");

    fprintf(stdout, "Creating an instance of LinkedList containing ints:\n");
    LinkedList * lst1 = llist__create();
    llist__print(lst1, NULL, stdout);
    fprintf(stdout, "\n");

    fprintf(stdout, "Add an item to the linked list:\n");
    llist__insert(0, (void *) &arr1[2], lst1);
    llist__print(lst1, NULL, stdout);
    fprintf(stdout, "\n");

    fprintf(stdout, "Let's use a custom printer to show what's in the LinkedList nodes:\n");
    llist__print(lst1, &printers1, stdout);
    fprintf(stdout, "\n");

    fprintf(stdout, "Continue inserting but keep using the custom print method:\n");
    llist__insert(0, (void *) &arr1[0], lst1);
    llist__print(lst1, &printers1, stdout);
    llist__insert(2, (void *) &arr1[3], lst1);
    llist__print(lst1, &printers1, stdout);
    llist__insert(1, (void *) &arr1[1], lst1);
    llist__print(lst1, &printers1, stdout);
    fprintf(stdout, "\n");

    fprintf(stdout, "Deleting the first item greater than 100:\n");
    llist__delete(false, lst1, filter);
    llist__print(lst1, &printers1, stdout);
    fprintf(stdout, "\n");

    fprintf(stdout, "Deleting all items greater than 100:\n");
    llist__delete(true, lst1, filter);
    llist__print(lst1, &printers1, stdout);
    fprintf(stdout, "\n");

    // ---------------------------------------------------------- //

    fprintf(stdout, "\n");

    float arr2[] = { 200.0f, 201.0f, 202.0f, 203.0f };

    Printers printers2 = { .pre = NULL, .elem = printer_float_elem, .post = NULL };

    fprintf(stdout, "In the same program, create an instance of LinkedList of float\nand add "
                    "some items to it. Use a custom printer for displaying\nthe payload of each node:\n");
    LinkedList * lst2 = llist__create();
    fprintf(stdout, " -- ");
    llist__print(lst2, &printers2, stdout);

    llist__insert(0, (void *) &arr2[2], lst2);
    fprintf(stdout, " -- ");
    llist__print(lst2, &printers2, stdout);

    llist__insert(0, (void *) &arr2[0], lst2);
    fprintf(stdout, " -- ");
    llist__print(lst2, &printers2, stdout);

    llist__insert(2, (void *) &arr2[3], lst2);
    fprintf(stdout, " -- ");
    llist__print(lst2, &printers2, stdout);

    llist__insert(1, (void *) &arr2[1], lst2);
    fprintf(stdout, " -- ");
    llist__print(lst2, &printers2, stdout);

    fprintf(stdout, "\nDone.\n");

    return EXIT_SUCCESS;
}
