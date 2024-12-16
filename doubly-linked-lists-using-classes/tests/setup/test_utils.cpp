#include <test_utils.hpp>
#include <iostream>

bool equalVectorsbyArtistName(std::vector<Artist> a, std::vector<std::string> b) {

  for (size_t i = 0; i < std::min(a.size(), b.size()); i++) {
    if (a[i].name() != b[i]) {
      std::cerr << "Expected " << b[i] << "; found " << a[i].name() << '\n';
      return false;
    }
  }

  return a.size() == b.size();
}

std::vector<std::string> array2vec(std::string src[Artist::max_genres]) {
  return {src, src + Artist::max_genres};
}

std::vector<Artist> linkedList2Vector(ArtistList &l) {
  std::vector<Artist> ll_vec;
  for(std::size_t i = 0; i < l.size();++i) {
    ll_vec.push_back(*l.at(i));
  }
  return ll_vec;
}

ArtistList artistListFromName(const std::vector<std::string>& names) {
  ArtistList l;
  for (size_t i = 0; i < names.size(); i++) {
    std::string genres[10] = {};
    Artist a(std::to_string(i), names[i], 0, genres, 0);
    l.appendArtist(a);
  }

  return l;
}