#include <assert.h>
#include <stdlib.h>

#include "../list/single_link.h"

#define LIST_LENGTH 16

int main(void)
{
    sl_node_t *head, *tail, *walk;
    head = tail = 0;

    for (int i = 0; i < LIST_LENGTH; ++i) {
        int *val = malloc(sizeof(int));
        assert(val);
        *val = i;

        sl_node_t *new_node = sl_create_node();
        new_node->val = val;

        sl_add_node(&head, &tail, new_node);
        assert(head && tail);
    }

    walk = head;
    for (int i = 0; i < LIST_LENGTH; ++i) {
        assert(*(int*)(walk->val) == i);
        walk = walk->next;
    }
    assert(!walk);

    puts("list_single_link_test.c: All tests passed");
    return 0;
}
