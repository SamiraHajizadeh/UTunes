#ifndef SONG
#define SONG

#include <iostream>
#include <vector>
#include <string>
#include "Exceptions.hpp"
#include "Macros.hpp"
#include "Comment.hpp"
#include <algorithm>

class Song{

public:

	Song(int _id, std::string _title, std::string _artist, int _release_year,
		std::string _link);

	~Song();
	int get_id(){ return id;}
	std::string get_title(){ return title;}
	std::string get_artist(){ return artist;}
	std::string get_link(){ return link;}
	int get_release_year(){ return release_year;}
	int get_likes(){ return likes_num;}
	int get_playlists(){ return playlists_num;}
	void print_partially();
	void print_completely();
	void like();
	void delete_like();
	void added_to_playlist();
	void deleted_from_playlist();
	void comment(std::string user, std::string text, int time);
	void print_comments();
	std::vector<std::vector<std::string>> get_data();
	std::vector<std::string> get_partial_data();

private:
	int id;
	std::string title;
	std::string artist;
	int release_year;
	std::string link;

	int likes_num;
	std::vector<Comment*> comments;
	int playlists_num;
};


#endif