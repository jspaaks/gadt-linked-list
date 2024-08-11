/**
 * @mainpage
 *
 * You probably wanted to see include/llist/llist.h
 * @file
 */


#ifndef LLIST_H
#define LLIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct llist LinkedList;

/**
 * @struct llist__Printers
 *
 * @brief  Data structure that holds function pointers to 3 printer
 *         functions.
 */
typedef struct {
    /**
     * @brief         Printer function used to print any preamble,
     *                such as opening brackets to the linked list
     *                elements.
     *
     * @param sink    Where the printer prints its output.
     * @param nelems  The total number of elements in the linked list.
     */
    void (*pre)(FILE * sink, size_t nelems);



    /**
     * @brief         Printer function used to print individual
     *                elements from the linked list.
     *
     * @param sink    Where the printer prints its output.
     * @param ielem   The index of the current element. This may for
     *                example be used in combination with \p nelems to
     *                determine when a comma should be printed to
     *                separate linked list elements.
     * @param nelems  The total number of elements in the linked list.
     *                This may for example be used in combination with
     *                \p ielem to determine when a comma should be
     *                printed to separate linked list elements.
     * @param elem    The linked list element whose contents are going
     *                to be printed.
     */
    void (*elem)(FILE * sink, size_t ielem, size_t nelems, void * elem);




    /**
     * @brief         Printer function used to print any postamble,
     *                such as closing brackets to the linked list
     *                elements.
     *
     * @param sink    Where the printer prints its output.
     * @param nelems  The total number of elements in the linked list.
     *                This may for example be used to print the length
     *                of the array.
     */
    void (*post)(FILE * sink, size_t nelems);
} llist__Printers;




/**
 * @brief       Append an item to an instance of a linked list
 * @details
 * @param lst   The instance of a linked list to which \p item is
 *              going to be appended.
 * @param item  The item that is going to be appended to \p lst.
 */
void llist__append (LinkedList * lst, void * item);




/**
 * @brief    Create an instance of a linked list
 * @returns  A pointer to the created instance of a linked list.
 */
LinkedList * llist__create (void);




/**
 * @brief         Delete an item from an instance of a linked list
 *                using a filter function
 * @details 
 * Below is an example of how to create a linked list with 4 integers and then
 * deleting some elements based on a filter callback function `filter`:
 *\code{.c}
 *     #include "llist/llist.h"
 *     
 *     
 *     static bool filter (void * p) {
 *         int i = *((int *) p);
 *         return i % 2 == 0;
 *     }
 *     
 *     int main (void) {
 *         LinkedList * lst = llist__create();
 *         int arr[] = {100, 101, 102, 103};
 *         llist__append(lst, (void *) &arr[0]);
 *         llist__append(lst, (void *) &arr[1]);
 *         llist__append(lst, (void *) &arr[2]);
 *         llist__append(lst, (void *) &arr[3]);
 *         llist__print(lst, NULL, stdout);
 *         llist__delete(true, lst, filter);
 *         llist__print(lst, NULL, stdout);
 *     }
 *\endcode
 * Should output the following (note that items 0 and 2 were deleted):
 *\code{.unparsed}
 *    [0x7fff246a58b0, 0x7fff246a58b4, 0x7fff246a58b8, 0x7fff246a58bc]
 *    [0x7fff246a58b4, 0x7fff246a58bc]
 *\endcode
 *     
 * @param global  If `true`, the deletion is applied globally, i.e. to
 *                all items in \p lst that match according to \p
 *                filter; if `false`, deletion is applied only to the
 *                first matching item.
 * @param lst     The instance of a linked list from which an item is
 *                going to be deleted.
 * @param filter  The function that is used to determine whether
 *                individual items in \p lst qualify for deletion
 *                (return value `true`) or that they should remain
 *                (return value `false`). The implementation of \p
 *                filter should include freeing any dynamically
 *                allocated memory pertaining to the element that is
 *                going to be deleted.
 */
void llist__delete (const bool global, LinkedList * lst, bool (*filter)(void *));




/**
 * @brief      Destroy an instance of a linked list
 * @details
 * @param lst  The instance of a linked list whose memory is going to
 *             be freed.
 */
void llist__destroy (LinkedList ** lst);




/**
 * @brief       Insert an item at a given position into a linked list.
 * @details
 * @param pos   Zero based pseudo index where \p item should be
 *              inserted into \p lst.
 * @param item  The item to be inserted.
 * @param lst   The linked list into which \p item should be inserted.
 */
void llist__insert (const size_t pos, void * item, LinkedList * lst);




/**
 * @brief      Get the number of items currently stored in an instance
 *             of a linked list
 * @details
 * @param lst  The instance of a linked list whose length is being
 *             queried.
 * @returns    The number of nodes in \p lst.
 */
size_t llist__get_length (const LinkedList * lst);




/**
 * @brief       Prepend an item to an instance of a linked list
 * @details
 * @param lst   The instance of a linked list to which \p item is
 *              going to be prepended.
 * @param item  The item that is going to be prepended to \p lst.
 */
void llist__prepend (LinkedList * lst, void * item);




/**
 * @brief           Print the contents of an instance of a linked
 *                  list, optionally using a custom printer function
 * @details
 *\code{.c}
 *    #include "llist/llist.h"
 *    #include <stdio.h>
 *    #include <stdlib.h>
 *
 *    struct task {
 *        float progress;
 *        char name[10];
 *    };
 *
 *    static void printer_pre (FILE * sink, size_t) {
 *        fprintf(sink, "{\n");
 *    }
 *
 *    static void printer_elem (FILE * sink, size_t idx, size_t nelems, void * p) {
 *        struct task task = *((struct task *) p);
 *        fprintf(sink, "  {\n");
 *        fprintf(sink, "         name: %s,\n", task.name);
 *        fprintf(sink, "     progress: ");
 *        for (size_t i = 10; i <= 100; i+=10) {
 *            fprintf(sink, "%s", task.progress >= i ? "\u2588" : "\u2591");
 *        }
 *        fprintf(sink, "\n");
 *        fprintf(sink, "  }");
 *        fprintf(sink, "%s", idx < nelems - 1 ? ",\n" : "\n");
 *    }
 *
 *    static void printer_post (FILE * sink, size_t) {
 *        fprintf(sink, "}\n");
 *    }
 *
 *    int main (void) {
 *
 *        struct task arr[] = {
 *            { .progress = 0.1,   .name = "task1" },
 *            { .progress = 10.3,  .name = "task2" },
 *            { .progress = 89.9,  .name = "task3" },
 *            { .progress = 90.0,  .name = "task4" },
 *            { .progress = 100.0, .name = "task5" }
 *        };
 *
 *        llist__Printers printers = {
 *            .pre = printer_pre,
 *            .elem = printer_elem,
 *            .post = printer_post
 *        };
 *
 *        LinkedList * lst = llist__create();
 *
 *        llist__append(lst, (void *) &arr[0]);
 *        llist__append(lst, (void *) &arr[1]);
 *        llist__append(lst, (void *) &arr[2]);
 *        llist__append(lst, (void *) &arr[3]);
 *        llist__append(lst, (void *) &arr[4]);
 *
 *        llist__print(lst, &printers, stdout);
 *
 *        llist__destroy(&lst);
 *
 *        return EXIT_SUCCESS;
 *    }
 *\endcode
 * Should output the following:
 *\code{.unparsed}
 *    {
 *      {
 *             name: task1,
 *         progress: ░░░░░░░░░░
 *      },
 *      {
 *             name: task2,
 *         progress: █░░░░░░░░░
 *      },
 *      {
 *             name: task3,
 *         progress: ████████░░
 *      },
 *      {
 *             name: task4,
 *         progress: █████████░
 *      },
 *      {
 *             name: task5,
 *         progress: ██████████
 *      }
 *    }
 *\endcode
 * @param lst       The linked list whose contents should be printed.
 * @param printers  The printer function pointers. A default printer
 *                  function will be substituted for any member that
 *                  is NULL. If \p printers itself is NULL, all of its
 *                  printer functions will be substituted with default
 *                  functions.
 * @param sink      Where the output should be written. Typically,
 *                  `stdout`.
 */
void llist__print (const LinkedList * lst, const llist__Printers * printers, FILE * sink);

#endif
