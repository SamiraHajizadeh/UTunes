#ifndef PLAYLIST
#define PLAYLIST


#include <string>
#include <vector>

#include "Song.hpp"

class Playlist{

public:
	Playlist(std::string _name, bool _is_public, int _id);
	void print(bool show_private);
	std::string privacy_state();
	int get_id(){ return id;}
	bool is_private() { return !is_public;}
	void add_song_to_playlist(Song* song);
	void print_songs();
	bool has_song(int id);
	void delete_song(int id);

private:
	int id;
	std::string name;
	std::vector<Song*> songs;
	bool is_public;

};


#endif
