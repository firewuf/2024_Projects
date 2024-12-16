#include <catch_amalgamated.hpp>
#include "llqueue.h"

namespace {
    TEST_CASE("HW 3 newLLNode Test 1", "[newLLNodeTest]") {
        Player *p = newPlayer("Andrew", 0);
        LLNode *ll = newLLNode(p);
        deleteLLNode(ll);
    }
}