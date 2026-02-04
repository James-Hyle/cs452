#include <stdio.h>
#include <stdlib.h>

#include "deq.h"

// TESTING FOR LIST ALLOCATION AND METHODS {PUT, ITH, REM, GET}
int main()
{
    Deq q = deq_new();
    if (!q)
    {
        printf("Error: deq_new returned NULL\n");
        return 1;
    }

    // test put
    printf("Test: putting 5, 10, 20 into list\n");
    deq_head_put(q, (void *)10);
    deq_tail_put(q, (void *)20);
    deq_head_put(q, (void *)5);

    if (deq_len(q) != 3)
    {
        printf("  FAIL: expected len 3, got %d!\n", deq_len(q));
    }
    else
    {
        printf("  PASS: list length is 3!\n");
    }

    // test ith
    printf("Test: checking index 0 from head of list\n");
    if ((long)deq_head_ith(q, 0) != 5)
    {
        printf("  FAIL: expected 5, got %ld!\n", (long)deq_head_ith(q, 0));
    }
    else
    {
        printf("  PASS: got 5!\n");
    }

    // test rem
    printf("Test: removing 10 from Head search\n");
    void *r = deq_head_rem(q, (void *)10);
    if ((long)r != 10 || deq_len(q) != 2)
    {
        printf("  FAIL: rem\n");
    }
    else
    {
        printf("  PASS: removed 10, length now 2\n");
    }

    // test get
    printf("Test: getting from tail\n");
    void *p = deq_tail_get(q); // should be 20
    if ((long)p != 20)
    {
        printf("  FAIL: expected 20, got %ld!\n", (long)p);
    }
    else
    {
        printf("  PASS: got 20!\n");
    }

    // NULL check
    deq_head_get(q);
    if (deq_len(q) == 0 && deq_head_get(q) == NULL)
    {
        printf("PASS: Deque is empty and returns NULL safely\n");
    }

    // cleanup
    deq_del(q, NULL);
    return 0;
}
