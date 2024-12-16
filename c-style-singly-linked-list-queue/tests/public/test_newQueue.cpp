#include <catch_amalgamated.hpp>
#include "llqueue.h"

namespace {
    TEST_CASE("HW 3 newQueue Test 1", "[newQueueTest]") {
        Queue *q = newQueue();
        deleteQueue(q);
    }
}