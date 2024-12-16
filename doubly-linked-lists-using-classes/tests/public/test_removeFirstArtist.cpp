#include <catch_amalgamated.hpp>
#include <test_utils.hpp>
#include "artistList.hpp"

namespace {
  ArtistList getPublicTestArtists() {
    return artistListFromName({"Bruno Mars", "Linkin Park", "Whitney Houston", "Stevie Wonder"});
  }

  TEST_CASE("HW 4 removeFirstArtistTest", "[removeFirstArtistTest]") {
    ArtistList l = getPublicTestArtists();
    l.removeFirstArtist();

    INFO("Expect list length of 3 when 4 artist records are added to the artist list and the first is removed.");
    CHECK(l.size() == 3);
    INFO("Remove first artist in linked list is not in the correct order.");
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), {"Linkin Park", "Whitney Houston", "Stevie Wonder"}));
  }

  TEST_CASE("HW 4 removeFirstArtistTest on list with one item", "[removeFirstArtistTest]") {
    std::string id1 = "0du5cEVh5yTK9QJze8zA0C";
    std::string name1 = "Bruno Mars";
    int total_followers1 = 43236735;
    std::string genre_a1[Artist::max_genres] = {"dance pop", "pop"};
    int popularity1 = 87;

    ArtistList l;
    l.appendArtist({id1, name1, total_followers1, genre_a1, popularity1});
    l.removeFirstArtist();

    INFO("Expect list empty after its first and only element is removed");
    CHECK(l.size() == 0);
  }

  TEST_CASE("HW 4 removeFirstArtistTest on empty list", "[removeFirstArtistTest]") {
    ArtistList l;
    l.removeFirstArtist();

    INFO("Expect list stays empty after trying to remove the first artist");
    CHECK(l.size() == 0);
  }

  TEST_CASE("HW 4 Remove First Artist interleaved", "[removeFirstArtistTest]") {
    std::string genre_examples[Artist::max_genres] = {"example", "genre"};

    ArtistList l;
    l.appendArtist({ "id0", "Andrew", 0, genre_examples, 0 });
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { "Andrew" }));

    l.appendArtist({ "id1", "Josh", 0, genre_examples, 0 });
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { "Andrew", "Josh" }));

    l.removeFirstArtist();
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { "Josh" }));

    l.appendArtist({ "id2", "David", 0, genre_examples, 0 });
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { "Josh", "David" }));

    l.removeFirstArtist();
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { "David" }));

    l.removeFirstArtist();
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { }));

    l.appendArtist({ "id3", "Nick", 0, genre_examples, 0 });
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { "Nick" }));

    l.removeFirstArtist();
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { }));
  }
} // namespace