#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "artistList.hpp"

std::vector<std::string> array2vec(std::string src[Artist::max_genres]);

std::vector<Artist> linkedList2Vector(ArtistList &l);

bool equalVectorsbyArtistName(std::vector<Artist> a, std::vector<std::string> b);

ArtistList artistListFromName(const std::vector<std::string>& names);

#endif