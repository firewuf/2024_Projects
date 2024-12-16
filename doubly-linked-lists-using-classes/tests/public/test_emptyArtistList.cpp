#include <catch_amalgamated.hpp>
#include "artistList.hpp"

namespace {
  // there is no private test case for this. students are still expected to pass the public test case -Andrew
  TEST_CASE("HW 4 Basic Empty List Extra Checks", "[emptyListTest]") {
    ArtistList l;

    INFO("Expect list length 0");
    CHECK(l.size() == 0);
    CHECK(l.is_empty());    

    INFO("Expect nullptr from l->first");
    CHECK(l.firstArtist() == nullptr);

    INFO("Expect nullptr from l->last");
    CHECK(l.lastArtist() == nullptr);
    }
}
