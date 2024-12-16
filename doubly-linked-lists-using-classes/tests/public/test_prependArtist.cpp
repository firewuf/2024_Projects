#include <catch_amalgamated.hpp>
#include <test_utils.hpp>
#include "artistList.hpp"

namespace {
  TEST_CASE("HW 4 Prepend Artist List", "[prependArtistTest]") {
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
    l.prependArtist({id1, name1, total_followers1, genre_a1, popularity1});
    l.prependArtist({id2, name2, total_followers2, genre_a2, popularity2});
    l.prependArtist({id3, name3, total_followers3, genre_a3, popularity3});
    l.prependArtist({id4, name4, total_followers4, genre_a4, popularity4});

    std::vector<std::string> artist_name{name4, name3, name2, name1};
    std::vector<Artist> ll2vec = linkedList2Vector(l);

    INFO("Expect list length of 4 when 4 artist records are added to the artist list.");
    CHECK(l.size() == 4);

    INFO("Artist names are not prepended in the correct order.");
    CHECK(equalVectorsbyArtistName(ll2vec, artist_name));
  }
}
