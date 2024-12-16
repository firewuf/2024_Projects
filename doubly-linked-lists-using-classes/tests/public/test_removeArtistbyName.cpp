#include <catch_amalgamated.hpp>
#include <test_utils.hpp>
#include "artistList.hpp"

namespace {
  ArtistList getPublicTestArtists() {
    return artistListFromName({"Bruno Mars", "Linkin Park", "Whitney Houston", "Stevie Wonder"});
  }

  TEST_CASE("HW 4 removeArtistNameTest remove first", "[removeArtistNameTest]") {
    ArtistList l = getPublicTestArtists();

    l.removeArtistbyName("Bruno Mars");
    INFO("Original list having a length of 4 should now be of length 3");
    CHECK(l.size() == 3);
    INFO("Order of remaining elements should be preserved after removal");
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), {"Linkin Park", "Whitney Houston", "Stevie Wonder"}));
  }

  TEST_CASE("HW 4 removeArtistNameTest remove second", "[removeArtistNameTest]") {
    ArtistList l = getPublicTestArtists();

    l.removeArtistbyName("Linkin Park");
    INFO("Original list having a length of 4 should now be of length 3");
    CHECK(l.size() == 3);
    INFO("Order of remaining elements should be preserved after removal");
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), {"Bruno Mars", "Whitney Houston", "Stevie Wonder"}));
  }

  TEST_CASE("HW 4 removeArtistNameTest remove third", "[removeArtistNameTest]") {
    ArtistList l = getPublicTestArtists();

    l.removeArtistbyName("Whitney Houston");
    INFO("Original list having a length of 4 should now be of length 3");
    CHECK(l.size() == 3);
    INFO("Order of remaining elements should be preserved after removal");
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), {"Bruno Mars", "Linkin Park", "Stevie Wonder"}));
  }

  TEST_CASE("HW 4 removeArtistNameTest remove fourth", "[removeArtistNameTest]") {
    ArtistList l = getPublicTestArtists();

    l.removeArtistbyName("Stevie Wonder");
    INFO("Original list having a length of 4 should now be of length 3");
    CHECK(l.size() == 3);
    INFO("Order of remaining elements should be preserved after removal");
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), {"Bruno Mars", "Linkin Park", "Whitney Houston"}));
  }

  TEST_CASE("HW 4 removeArtistNameTest remove first and second", "[removeArtistNameTest]") {
    ArtistList l = getPublicTestArtists();

    l.removeArtistbyName("Bruno Mars");
    INFO("Original list having a length of 4 should now be of length 3");
    CHECK(l.size() == 3);
    INFO("Order of remaining elements should be preserved after removal");
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), {"Linkin Park", "Whitney Houston", "Stevie Wonder"}));

    l.removeArtistbyName("Linkin Park");
    INFO("Modified list having a length of 3 should now be of length 2");
    CHECK(l.size() == 2);
    INFO("Order of remaining elements should be preserved after removal");
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), {"Whitney Houston", "Stevie Wonder"}));
  }
} // namespace