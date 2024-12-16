#include <catch_amalgamated.hpp>
#include "llqueue.h"

namespace {
    TEST_CASE("HW 3 copyPlayer Null", "[copyPlayerTest]") {
        auto * copy = copyPlayer(nullptr);
        CHECK(copy == nullptr);
    }

    TEST_CASE("HW 3 copyPlayer Same Info", "[copyPlayerTest]") {
        auto * original = newPlayer("John Doe", 42);
        auto * copy = copyPlayer(original);
        REQUIRE(copy != original);
        REQUIRE(copy != nullptr);
        CHECK(copy->name == original->name);
        CHECK(copy->num_goals == original->num_goals);
        deletePlayer(original);
        deletePlayer(copy);
    }
}