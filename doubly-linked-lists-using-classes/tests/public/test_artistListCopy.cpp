#include <catch_amalgamated.hpp>
#include <test_utils.hpp>
#include "artistList.hpp"

namespace {
    TEST_CASE("HW 4 Copy Artist List Test 1", "[copyArtistListTest]") {
        ArtistList l;
        ArtistList l2(l);

        INFO("Copying from empty list, expected size of 0.");
        CHECK(l2.size() == 0);
    }    
    
    TEST_CASE("HW 4 Copy Artist List Test 2", "[copyArtistListTest]") {
        std::string id1 = "0du5cEVh5yTK9QJze8zA0C";
        std::string name1 = "Nick";
        int total_followers1 = 43236735;
        std::string genre_a1[Artist::max_genres] = {"dance pop", "pop"};
        int popularity1 = 87;

        std::string id2 = "6XyY86QOPPrYVGvF9ch6wz";
        std::string name2 = "David";
        int total_followers2 = 21735103;
        std::string genre_a2[Artist::max_genres] = {"alternative metal", "nu metal", "post-grunge", "rap metal"};
        int popularity2 = 83;

        std::string id3 = "6XpaIBNiVzIetEPCWDvAFP"; 
        std::string name3 = "Josh";
        int total_followers3 = 8378337;
        std::string genre_a3[Artist::max_genres] = {"dance pop", "pop", "urban contemporary"};
        int popularity3 = 75;
        
        std::string id4 = "7guDJrEfX3qb6FEbdPA5qi"; 
        std::string name4 = "Andrew";
        int total_followers4 = 5791721;
        std::string genre_a4[Artist::max_genres] = {"funk", "indie r&b", "motown", "quiet storm", "soul"};
        int popularity4 = 74;

        ArtistList l;
        l.appendArtist({ id1, name1, total_followers1, genre_a1, popularity1 });
        l.appendArtist({ id2, name2, total_followers2, genre_a2, popularity2 });
        l.appendArtist({ id3, name3, total_followers3, genre_a3, popularity3 });
        l.appendArtist({ id4, name4, total_followers4, genre_a4, popularity4 });

        ArtistList l2(l);

        CHECK(l2.size() == 4);
        CHECK(equalVectorsbyArtistName(linkedList2Vector(l2), { "Nick", "David", "Josh", "Andrew" }));
        
        for(auto i = std::size_t{}; i < l2.size(); ++i) {
          CHECK(l.at(i) != l2.at(i));
        }
    }
}