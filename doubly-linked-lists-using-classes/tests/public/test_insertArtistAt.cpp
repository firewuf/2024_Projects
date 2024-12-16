#include <catch_amalgamated.hpp>
#include <test_utils.hpp>
#include "artistList.hpp"
#include <iostream>

namespace {
  TEST_CASE("HW 4 Insert Artist Test 1", "[insertArtistTest]") {
    std::string id1 = "0du5cEVh5yTK9QJze8zA0C";
    std::string name1 = "Bruno Mars";
    int total_followers1 = 43236735;
    std::string genre_a1[Artist::max_genres] = {"dance pop", "pop"};
    int popularity1 = 87;

    std::string id2 = "6XyY86QOPPrYVGvF9ch6wz";
    std::string name2 = "Linkin Park";
    int total_followers2 = 21735103;
    std::string genre_a2[Artist::max_genres] = {"alternative metal", "nu metal", "post-grunge", "rap metal"};
    int popularity2 = 83;

    std::string id3 = "6XpaIBNiVzIetEPCWDvAFP";
    std::string name3 = "Whitney Houston";
    int total_followers3 = 8378337;
    std::string genre_a3[Artist::max_genres] = {"dance pop", "pop", "urban contemporary"};
    int popularity3 = 75;
    
    std::string id4 = "7guDJrEfX3qb6FEbdPA5qi"; 
    std::string name4 = "Stevie Wonder";
    int total_followers4 = 5791721;
    std::string genre_a4[Artist::max_genres] = {"funk", "indie r&b", "motown", "quiet storm", "soul"};
    int popularity4 = 74;

    ArtistList l;
    l.appendArtist({id1, name1, total_followers1, genre_a1, popularity1});

    INFO("Check entry artist equals added artist");
    REQUIRE(l.firstArtist() != nullptr);
    CHECK(l.firstArtist()->name() == name1);

    l.insertArtistAt(1, {id2, name2, total_followers2, genre_a2, popularity2});
    l.insertArtistAt(0, {id3, name3, total_followers3, genre_a3, popularity3});
    l.insertArtistAt(2, {id4, name4, total_followers4, genre_a4, popularity4});

    std::vector<std::string> artist_name{name3, name1, name4, name2};
    std::vector<Artist> ll2vec = linkedList2Vector(l);

    INFO("Artist names are not inserted in the correct order.");
    CHECK(equalVectorsbyArtistName(ll2vec, artist_name));

    INFO("Expect list length of 4 when 4 artist records are added to the artist list.");
    CHECK(l.size() == 4);
  }

  TEST_CASE("HW 4 Insert Artist Test 2", "[insertArtistTest]") {
    std::string id = "7guDJrEfX3qb6FEbdPA5qi"; 
    std::string name = "Stevie Wonder";
    int total_followers = 5791721;
    std::string genre_a[Artist::max_genres] = {"funk", "indie r&b", "motown", "quiet storm", "soul"};
    int popularity = 74;

    ArtistList l;
    l.insertArtistAt(1, { id, name, total_followers, genre_a, popularity });

    INFO("Artist list should not have anything inserted.");
    CHECK(l.size() == 0);
  }

  TEST_CASE("HW 4 Insert Artist Test 3", "[insertArtistTest]") {
    std::string genre_examples[Artist::max_genres] = {"example", "genre"};

    ArtistList l;
    l.insertArtistAt(0, { "id0", "Andrew", 0, genre_examples, 0 });
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { "Andrew" }));
    l.insertArtistAt(0, { "id1", "Josh", 0, genre_examples, 0 });
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { "Josh", "Andrew" }));
    l.insertArtistAt(0, { "id2", "David", 0, genre_examples, 0 });
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { "David", "Josh", "Andrew" }));
    l.insertArtistAt(0, { "id3", "Nick", 0, genre_examples, 0 });
    CHECK(equalVectorsbyArtistName(linkedList2Vector(l), { "Nick", "David", "Josh", "Andrew" }));
  }
}