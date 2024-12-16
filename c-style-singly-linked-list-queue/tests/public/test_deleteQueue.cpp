#include <catch_amalgamated.hpp>
#include "llqueue.h"

namespace {
    TEST_CASE("HW 3 deleteQueue Test", "[deleteQueueTest]") {
        Queue *q = newQueue();
        queuePushPlayerEntry(q, newPlayer("John Lennon", 45));
        queuePushPlayerEntry(q, newPlayer("Ringo Star", 55));
        queuePushPlayerEntry(q, newPlayer("Paul McCartney", 67));
        queuePushPlayerEntry(q, newPlayer("George Harrison", 33));
        deleteQueue(q);
        // If ASan is unhappy you have memory leaks!!
        INFO("Check ASan output");

    }
}