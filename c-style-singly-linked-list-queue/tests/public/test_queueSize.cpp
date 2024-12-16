#include <catch_amalgamated.hpp>
#include "llqueue.h"

namespace {
    TEST_CASE("HW 3 Duplicate Insert Size Test", "[queueSizeTest]") {
        Queue *q = newQueue();
        Player *p0 = newPlayer("Sid", 0);
        Player *p1 = newPlayer("Sid", 0);
        queuePushPlayerEntry(q, p0);
        queuePushPlayerEntry(q, p1);

        CHECK(queueSize(q) == 2);

        deleteQueue(q);
    }

    TEST_CASE("HW 3 queueSize 8000 Insert Size Test", "[queueSizeTest]") {
        Queue *q = newQueue();
        for (size_t i = 0; i < 8000; i++) {
            Player *p = newPlayer("Professor Ahmed", i);
            queuePushPlayerEntry(q, p);

            CHECK(queueSize(q) == i + 1);
        }
        deleteQueue(q);
    }
}