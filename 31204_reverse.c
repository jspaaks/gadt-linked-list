#include <stdio.h>

int main (int argc, char **argv) {
    for (int i = argc - 1; i > 0; i--) {
        printf("%s", argv[i]);
        if (i > 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
}
