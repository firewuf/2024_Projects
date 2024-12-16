#include <catch_amalgamated.hpp>
#include "llqueue.h"

namespace {
    TEST_CASE("HW 3 Duplicate Name queuePush Test", "[queuePushTest]") {
        Queue *q = newQueue();
        Player *p0 = newPlayer("Sid", 0);
        Player *p1 = newPlayer("Sid", 1);
        queuePushPlayerEntry(q, p0);
        queuePushPlayerEntry(q, p1);

        CHECK(queueFront(q)->num_goals == 0);
        CHECK(queueBack(q)->num_goals == 1);

        deleteQueue(q);
    }

    TEST_CASE("HW 3 Single Insert queuePush Test", "[queuePushTest]") {
        Queue *q = newQueue();
        Player *p = newPlayer("David", 9);
        queuePushPlayerEntry(q, p);
        
        CHECK(queueFront(q)->name == "David");
        CHECK(queueBack(q)->name == "David");

        deleteQueue(q);
    }
}