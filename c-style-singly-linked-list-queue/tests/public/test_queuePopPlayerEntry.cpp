#include <catch_amalgamated.hpp>
#include "llqueue.h"

namespace {
    TEST_CASE("HW 3 queuePop Empty Test", "[queuePopTest]") {
        Queue *q = newQueue();

        queuePopPlayerEntry(q);
        INFO("An empty queue is expected to have a size of 0");
        CHECK(queueSize(q) == 0);

        deleteQueue(q);
    }

    TEST_CASE("HW 3 queuePop Double Insert Test", "[queuePopTest]") {
        Queue *q = newQueue();
        Player *p0 = newPlayer("Jared", 0);
        Player *p1 = newPlayer("Josh", 1);
        queuePushPlayerEntry(q, p0);
        queuePushPlayerEntry(q, p1);

        queuePopPlayerEntry(q);
        CHECK(queueFront(q)->name == "Josh");

        queuePopPlayerEntry(q);
        CHECK(queueSize(q) == 0);

        deleteQueue(q);
    }

    TEST_CASE("HW 3 queuePop 8000 Insert test", "[queuePopTest]") {
        Queue *q = newQueue();
        for (int i = 0; i < 8000; i++) {
            Player *p = newPlayer("Professor Ahmed", i);
            queuePushPlayerEntry(q, p);
        }

        for (int i = 0; i < 8000; i++) {
            CHECK(queueSize(q) > 0);
            Player *p = queueFront(q);
            INFO("Expected " << i << "; found " << p->num_goals);
            CHECK(p->num_goals == i);
            queuePopPlayerEntry(q);
        }

        deleteQueue(q);
    }
}