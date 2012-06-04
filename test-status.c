#include <stdio.h>

#include "status.h"

void notify(void)
{
    printf("notify: %s\n", status());
}

int main(int argc, char *argv[])
{
    printf("initial: %s\n", status());

    status_set("lemon");
    printf("%s\n", status());

    status_printf("%s", "carrot");
    printf("%s\n", status());

    status_notify(notify);

    status_set("apple");
    status_set("orange");

    return 0;
}
