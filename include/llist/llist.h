/**
 * \mainpage 
 *
 * You probably wanted to see include/llist/llist.h
 * @file
 */


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




/**
 * @brief       Append an item to an instance of a linked list
 * @details
 * @param lst   The instance of a linked list to which \p item is going
 *              to be appended.
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
 * Also make sure to check out the documentation on custom printer methods \p llist__print()
 *     
 * @param global  If `true`, the deletion is applied globally, i.e. to
 *                all items in \p lst that match according to \p
 *                filter; if `false`, deletion is applied only to the
 *                first matching item.
 * @param lst     The instance of a linked list from which an item is
 *                going to be deleted.
 * @param filter  The function that is used to determine whether
 *                individual items in \p lst qualify for deletion.
 */
void llist__delete (const bool global, LinkedList * lst, bool (*filter)(void *));



/**
 * @brief      Destroy an instance of a linked list
 * @details
 * @param lst  The instance of a linked list whose memory is going to be
 *                      freed.
 */
void llist__destroy (LinkedList ** lst);




/**
 * @brief       Insert an item at a given position into a linked list.
 * @details
 * @param pos   Zero based pseudo index where \p item should be inserted
 *              into \p lst.
 * @param item  The item to be inserted.
 * @param lst   The linked list into which \p item should be inserted.
 */
void llist__insert (const size_t pos, void * item, LinkedList * lst);




/**
 * @brief      Get the number of items currently stored in an instance of a
 *             linked list
 * @details
 * @param lst  The instance of a linked list whose length is being queried.
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
 * @brief           Print the contents of an instance of a linked list, 
 *                  optionally using a custom printer function
 * @details
 * @param lst       The linked list whose contents should be printed.
 * @param printers  The printer methods. If any of its members are NULL,
 *                  default methods will be substituted. If \p printers
 *                  itself is NULL, all of its methods will be substituted
 *                  by default methods.
 * @param sink      Where the output should be written. Typically, `stdout`.
 */
void llist__print (const LinkedList * lst, const llist__Printers * printers, FILE * sink);

#endif
