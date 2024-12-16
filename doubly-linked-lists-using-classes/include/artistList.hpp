#ifndef _ArtistLIST_H_
#define _ArtistLIST_H_

#include <string>
#include <vector>

class Artist {
  std::string artist_id;
  std::string artist_name;

public:
  int total_followers;
  static constexpr std::size_t max_genres = 10;
  std::string genres[max_genres];
  int popularity;
  Artist() : artist_id{""}, artist_name{""} {};
  Artist(const std::string& artist_id, const std::string& artist_name, int total_followers = 0, std::string[Artist::max_genres] = {}, int popularity = 0);

  void printArtist() const;
  
  const std::string& id() const;
  const std::string& name() const;
};

class ArtistList {
  struct ArtistEntry {
    ArtistList *list;
    ArtistEntry *next;
    ArtistEntry *prev;
    Artist artist;
    
    ArtistEntry(ArtistList *, const Artist&);
  };

  size_t length;
  ArtistEntry *first;
  ArtistEntry *last;

public:
  ArtistList();
  ArtistList(const ArtistList&);
  ~ArtistList() noexcept;
  
  // Do NOT modify the following 3 special member functions
  ArtistList(ArtistList&& src) noexcept
  {
    length = src.length;
    src.length = 0;
    
    first = src.first;
    src.first = nullptr;

    last = src.last;
    src.last = nullptr;
  }
  ArtistList& operator=(const ArtistList&) = delete;
  ArtistList& operator=(ArtistList&&) noexcept = delete;
  
  // prepend/append an artist at the beginning/end of list
  void prependArtist(const Artist&);
  void appendArtist(const Artist&);
  
  // insert an artist before the index
  // if the insertion cannot happen, do nothing
  void insertArtistAt(size_t index, const Artist&);

  // remove the first/last artist from the list
  void removeFirstArtist();
  void removeLastArtist();

  // print the artist list
  void printArtistList() const;

  // find an artist by name
  Artist *findArtistName(const std::string & name) const;

  // find an artist by indexing
  Artist* at(std::size_t i);
  const Artist* at(std::size_t i) const;

  // remove an artist by name 
  void removeArtistbyName(const std::string & name);
  
  bool is_empty() const;
  std::size_t size() const;
  
  Artist* firstArtist();
  const Artist* firstArtist() const;

  Artist* lastArtist();
  const Artist* lastArtist() const;
};

ArtistList parse_csv(std::istream& file);

void duplicateList(std::string oldList[], std::string newList[], size_t size);

#endif