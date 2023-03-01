#ifndef USER
#define USER


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Exceptions.hpp"
#include "Functions.hpp"
#include "Song.hpp"
#include "Playlist.hpp"


class User{
public:
	User(std::string _username, std::string _password, std::string _email);
	~User();
	std::string get_username(){ return username;}
	std::string get_email(){ return email;}
	std::vector<Playlist*> get_playlists(){ return playlists;}
	int get_password(){ return hash_password;}
	bool song_already_liked(Song* song);
	void like_song(Song* song);
	void print_liked_songs();
	void delete_song_from_liked(int id);
	void print_playlists(bool show_private);
	Playlist* make_playlist(std::string name, bool _public, int id);
	bool has_playlist(int id);
	void print_username();
	std::vector<Song*> get_liked_songs(){ return liked_songs;}
	std::vector<int> get_liked_songs_strVec() const; //delete

private:
	std::string email;
	std::string username;
	int hash_password;
	std::vector<Song*> liked_songs;
	std::vector<Playlist*> playlists;
};


#endif