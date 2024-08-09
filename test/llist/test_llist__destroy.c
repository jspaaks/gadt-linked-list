#include "llist/llist.h"
#include <criterion/criterion.h>

Test(llist__destroy, noop) {
    LinkedList * lst = llist__create();
    llist__destroy(&lst);
    cr_assert(lst == NULL, "Instance of LinkedList should be NULL after it has been destroyed.\n");
}
