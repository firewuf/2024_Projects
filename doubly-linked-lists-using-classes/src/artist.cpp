#include "../include/artistList.hpp"
#include <iostream>

// place header file includes here

// Allocate a new artist record
Artist::Artist(const std::string &artist_id, const std::string &artist_name, int total_followers, std::string genres[Artist::max_genres], int popularity)
{
  this->artist_id = artist_id;
  this->artist_name = artist_name;
  this->total_followers = total_followers;
  duplicateList(genres, this->genres, Artist::max_genres);
  this->popularity = popularity;
}

// Print an artist record
void Artist::printArtist() const
{
  std::cout << "Artist ID: " << artist_id << std::endl
            << "Artist Name: " << artist_name << std::endl
            << "Total Followers: " << total_followers << std::endl
            << "Genres: ";
  for (std::string g : genres)
    std::cout << g << ", ";
  std::cout << std::endl
            << "Popularity: " << popularity << std::endl;
}

const std::string &Artist::name() const
{
  return artist_name;
}
const std::string &Artist::id() const
{
  return artist_id;
}