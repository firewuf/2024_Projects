#include <catch_amalgamated.hpp>
#include "test_utils.hpp"
#include "artistList.hpp"

namespace {  
  ArtistList getPublicTestArtists() {
    return artistListFromName({"Bruno Mars", "Linkin Park", "Whitney Houston", "Stevie Wonder"});
  }

  TEST_CASE("HW 4 removeLastTest Test 1", "[removeLastTest]") {
    ArtistList l = getPublicTestArtists();

    l.removeLastArtist();

    INFO("Expect list length of 3 when 4 artist records are added to the artist list and the last is removed.");
    CHECK(l.size() == 3);
    INFO("Final list artist names are not in the correct order.");
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), {"Bruno Mars", "Linkin Park", "Whitney Houston"}));
  }

  TEST_CASE("HW 4 removeLastTest remove last single element", "[removeLastTest]") {
    std::string id1 = "abc";
    std::string name1 = "Andrew";
    int total_followers1 = 123;
    std::string genre_a1[Artist::max_genres] = {"dance pop", "pop"};
    int popularity1 = 321;

    ArtistList l;
    l.appendArtist({id1, name1, total_followers1, genre_a1, popularity1});
    l.removeLastArtist();

    INFO("Check list should be empty when its only element is removed");
    CHECK(l.size() == 0);
  }

  TEST_CASE("HW 4 removeLastTest remove on empty list", "[removeLastTest]") {
    ArtistList l;
    INFO("Code should not crash if removeLastArtist() is called on an empty list");

    std::string id1 = "abc";
    std::string name1 = "Andrew";
    int total_followers1 = 123;
    std::string genre_a1[Artist::max_genres] = {"dance pop", "pop"};
    int popularity1 = 321;

    l.appendArtist({id1, name1, total_followers1, genre_a1, popularity1});
    l.removeLastArtist();

    INFO("Check that list is empty after calling removeLastArtist on an already empty list.");
    CHECK(l.size() == 0);
  } 
} // namespace