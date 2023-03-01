#include "Playlist.hpp"

using namespace std;

Playlist::Playlist(std::string _name, bool _is_public, int _id){
	id = _id;
	is_public = _is_public;
	name = _name;
}

string Playlist::privacy_state(){
	if (is_public)
		return PUBLIC;
	return PRIVATE;
}

void Playlist::print(bool show_private){
	if (is_public || show_private){
		cout << id << SPACE << name << SPACE << privacy_state() << endl;
	}
}

void Playlist::add_song_to_playlist(Song* song){
	song->added_to_playlist();
	songs.push_back(song);
}

struct less_than
{
	inline bool operator() (Song* song1, Song* song2){
		return (song1->get_id() < song2->get_id());
	}
};


void Playlist::print_songs(){
	if (songs.size() == 0)
		throw Empty();
	sort(songs.begin(), songs.end(), less_than());
	for (int i = 0; i < songs.size(); i++){
		songs[i]->print_partially();
	}
}


bool Playlist::has_song(int id){
	for (int i = 0; i < songs.size(); i++){
		if (songs[i]->get_id() == id)
			return true;
	}
	return false;
}

void Playlist::delete_song(int id){
	for (int i = 0; i < songs.size(); i++){
		if (songs[i]->get_id() == id){
			songs[i]->deleted_from_playlist();
			if (songs.size() == 1)
				songs = {};
			else
				songs.erase(songs.begin() + i);
		}
	}
}