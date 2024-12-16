#include <catch_amalgamated.hpp>
#include <test_utils.hpp>
#include "artistList.hpp"
#include <iostream>
#include <fstream>

namespace {
  TEST_CASE("HW 4 Parse CSV", "[csvtest]") {
      std::stringstream ss{
        "artist_id,artist_name,total_followers,genres,popularity\n"
        "0du5cEVh5yTK9QJze8zA0C,Bruno Mars, 43236735, \"['dance pop', 'pop']\",87\n"
        "4IWBUUAFIplrNtaOHcJPRM,James Arthur, 10293374, \"['pop', 'talent show', 'uk pop']\",80\n"
        "5X4LWwbUFNzPkEas04uU82,DVBBS,1001797,\"['canadian electronic', 'dance pop', 'edm', 'electro house', 'pop', 'pop dance', 'pop edm', 'progressive electro house', 'slap house', 'tropical house']\",64\n"
        "1Fr6agZ6iSM5Ynn2k4C8sc,VÉRITÉ,292642,\"['alt z', 'brooklyn indie', 'dark pop', 'electropop', 'indie electropop', 'indie pop', 'indie poptimism', 'metropopolis', 'nyc pop', 'pop', 'vapor pop', 'vapor soul']\",52\n"
        "69GGBxA162lTqCwzJG5jLp,The Chainsmokers, 19465938, \"['dance pop', 'edm', 'electropop', 'pop', 'pop dance', 'tropical house']\", 80\n"
        "46GXASE9LHzyssNqKOInUu,Dawin,222284,['nyc pop'],52\n"
        "3r3Rkuc4jmZHXgchgaXwnv,Suzi,8411,[],43\n"
      };
      
      auto list = parse_csv(ss);
      
      REQUIRE(list.size() == 7);
      CHECK(list.at(0)->name() == "Bruno Mars");
      CHECK(list.firstArtist()->genres[1] == "pop");
  }

  TEST_CASE("HW 4 Parse CSV Test 2", "[csvtest]") {
    std::ifstream file("src/spotify_daily_charts_artists.csv");
    ArtistList list = parse_csv(file);

    CHECK(list.at(0)->name() == "Bruno Mars");
    CHECK(list.at(942)->name() == "Kenaniah");
    CHECK(list.size() == 943);

    file.close();
  }
}