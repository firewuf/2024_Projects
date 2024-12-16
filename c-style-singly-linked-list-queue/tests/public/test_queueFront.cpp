#include <catch_amalgamated.hpp>
#include "llqueue.h"

namespace {
    TEST_CASE("HW 3 queueFront Empty Test", "[queueFrontTest]") {
        Queue *q = newQueue();
        INFO("Expecting a nullptr in an empty queue");
        CHECK(queueFront(q) == nullptr);
        deleteQueue(q);
    }

    TEST_CASE("HW 3 queueFront Single Insert Test", "[queueFrontTest]") {
        Queue *q = newQueue();
        Player *p = newPlayer("Andrew", 0);
        queuePushPlayerEntry(q, p);
        Player *p_front = queueFront(q);
        INFO("Front player name expected to match the first pushed name");
        CHECK(p->name == p_front->name);

        deleteQueue(q);
    }
}