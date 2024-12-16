// must complete parse_csv function for code to work properly with .csv files
#include "../include/artistList.hpp"
#include <istream>
#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>

// helper function provided to parse genres WITH square brackets
static void parse_genres(std::istream &file, std::string genres[Artist::max_genres])
{
    std::string temp;

    std::getline(file, temp, '[');
    std::getline(file, temp, ']');

    auto genre_idx = 0u;
    for (auto start = 0u; start < temp.size() and genre_idx < Artist::max_genres;)
    {
        auto start_quote = temp.find_first_of('\'', start) + 1;
        auto end_quote = temp.find_first_of('\'', start_quote);

        genres[genre_idx] = temp.substr(start_quote, end_quote - start_quote);
        ++genre_idx;

        start = end_quote + 1;
    }

    while (genre_idx < Artist::max_genres)
    {
        genres[genre_idx] = "";
        ++genre_idx;
    }
}

// parse_csv needs to be written by the students
ArtistList parse_csv(std::istream &file)
{
    // Insert code here
    // be sure to call the provided parse_genres function to assist you
    // in reading the genres column from the spotify_daily_charts_artists.csv
    ArtistList al = ArtistList();

    std::string lineArray[4];
    Artist a;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (!file.eof())
    {
        for (int c = 0; c < 3; c++)
            std::getline(file, lineArray[c], ',');
        if (lineArray[0].empty() || std::all_of(lineArray[0].begin(), lineArray[0].end(), isspace))
            continue;
        std::string genres[Artist::max_genres];
        parse_genres(file, genres);
        file.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        std::getline(file, lineArray[3], '\n');

        a = Artist(lineArray[0], lineArray[1], std::stoi(lineArray[2]), genres, std::stoi(lineArray[3]));
        al.appendArtist(a);
    }

    return al;
}