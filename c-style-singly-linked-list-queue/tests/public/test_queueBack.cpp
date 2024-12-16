#include <catch_amalgamated.hpp>
#include "llqueue.h"

namespace {
    TEST_CASE("HW 3 queueBack Empty Test", "[queueBackTest]") {
        Queue *q = newQueue();
        INFO("The back of an empty queue is expected to be a nullptr.");
        CHECK(queueBack(q) == nullptr);
        deleteQueue(q);
    }

    TEST_CASE("HW 3 queueBack Single Insert Test", "[queueBackTest]") {
        Queue *q = newQueue();
        Player *p = newPlayer("Nick", 0);
        queuePushPlayerEntry(q, p);
        Player *p_back = queueBack(q);
        INFO("The back of the queue should be the same player as the recently inserted one.");
        CHECK(p->name == p_back->name);

        deleteQueue(q);
    }
}