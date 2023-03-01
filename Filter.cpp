#include "Filter.hpp"

using namespace std;

vector<Song*> Filter::filter_songs(const vector<Song*>& songs){
	vector<Song*> filtered_songs;
	for (int i = 0; i < songs.size(); i++){
		if ((songs[i]->get_artist() == artist_name || artist_name == "")
			&&((songs[i]->get_release_year() >= min_year && songs[i]->get_release_year() <= max_year)
				|| min_year == INVALID_NUMBER)
			&& ((songs[i]->get_likes() >= min_like && songs[i]->get_likes() <= max_like)
				|| min_like == INVALID_NUMBER))
			filtered_songs.push_back(songs[i]);
		}
	return filtered_songs;
}


void Filter::set_artist(std::string artist){
	artist_name = artist;
}

void Filter::set_like_limits(int min, int max){
	min_like = min;
	max_like = max;
}


void Filter::set_year_limits(int min, int max){
	min_year = min;
	max_year = max;
}