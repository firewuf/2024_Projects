// main_menu.cpp: main function (different than the driver provided) that implements
// the menu driven interface as outlined in the directions of the README.md. Adapt as needed
// to assist with development.

#include "../include/artistList.hpp"
#include "../include/parse_csv.hpp"
#include <iostream>
#include <fstream>

int main() {
	std::ifstream in_file("spotify_daily_charts_artists.csv");
	ArtistList l = parse_csv(in_file);

	// count artist names who begin with a, b, c, d, ...
	int artist_begin_with[26] = {};
	int artist_begin_not_alpha = 0;

	for (size_t i = 0; i < l.size(); i++) {
		if (l.at(i)->name().size() == 0) 
			continue;

		char first_letter = l.at(i)->name()[0];

		if (isalpha(first_letter)) {
			int char_idx = toupper(first_letter) - 'A';
			artist_begin_with[char_idx]++;
		} else {
			artist_begin_not_alpha++;
		}
	}

	for (int i = 0; i < 26; i++) {
		std::cout << "Artist names beginning with " <<  (char)('A'+i) << ": " << artist_begin_with[i] << std::endl;
	}

	std::cout << "Artist names not beginning with a letter: " << artist_begin_not_alpha << std::endl;

	return 0;
	
}
