#include <catch_amalgamated.hpp>
#include <test_utils.hpp>
#include "artistList.hpp"

namespace {
  TEST_CASE("HW 4 Artist Entry Test 1", "[aEntryTest]") {
    std::string id = "0du5cEVh5yTK9QJze8zA0C";
    std::string name = "Bruno Mars";
    int total_followers = 43236735;
    std::string genre_a1[Artist::max_genres] = {"dance pop", "pop"};
    int popularity = 87;

    Artist a1(id, name, total_followers, genre_a1, popularity);

    INFO("artist_id artist struct population");
    CHECK(a1.id() == id);

    INFO("artist_name artist struct population");
    CHECK(a1.name() == name);

    INFO("total_followers artist struct population");
    CHECK(a1.total_followers == total_followers);

    INFO("total_followers artist struct population");
    CHECK(a1.popularity == popularity);

    INFO("genres artist struct population");
    CHECK(array2vec(a1.genres) == array2vec(genre_a1));

  }

  TEST_CASE("HW 4 Artist Entry Test 2 Empty", "[aEntryTest]") {
    std::string id = "";
    std::string name = "";
    int total_followers = 0;
    std::string genre_a1[Artist::max_genres];
    int popularity = 0;

    Artist a1(id, name, total_followers, genre_a1, popularity);

    INFO("artist_id artist struct population");
    CHECK(a1.id() == id);

    INFO("artist_name artist struct population");
    CHECK(a1.name() == name);

    INFO("total_followers artist struct population");
    CHECK(a1.total_followers == total_followers);

    INFO("total_followers artist struct population");
    CHECK(a1.popularity == popularity);

    INFO("genres artist struct population");
    CHECK(array2vec(a1.genres) == array2vec(genre_a1));
  }
}