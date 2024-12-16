#include <catch_amalgamated.hpp>
#include "llqueue.h"

namespace {
    TEST_CASE("HW 3 newPlayer Test 1", "[newPlayerTest]") {
        Player *p = newPlayer("Andrew", 0);
        deletePlayer(p);
    }
}