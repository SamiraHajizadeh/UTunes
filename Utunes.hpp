#ifndef UTUNES
#define UTUNES


#include <vector>
#include <string>
#include <algorithm>

#include "Macros.hpp"
#include "Song.hpp"
#include "Playlist.hpp"
#include "User.hpp"
#include "Exceptions.hpp"
#include "Filter.hpp"
#include "Recommendation.hpp"

class Utunes{

public:
	void signup_initial_users(std::vector<std::vector<std::string>> vec);
	Utunes(std::vector<std::vector<std::string>> songs_str,
		std::vector<std::vector<std::string>> liked_songs_str);
	~Utunes();
	std::vector<Song*> get_songs(){ return songs;}
	int signup_user(std::string email, std::string username, std::string password);
	void print_all_songs();
	std::string log_in_user(std::string username, std::string password);
	void print_songs(int id = INVALID_NUMBER);
	void logout_user();
	void print_liked_songs();
	void like_song(int id);
	void delete_song_from_liked(int id);
	int make_playlist(std::string name, std::string privacy);
	void print_playlist(std::string username);
	void add_song_to_playlist(int playlist_id, int song_id);
	void print_playlist_songs(int id);
	void delete_song_from_playlist(int playlist_id, int song_id);
	void print_users();
	void add_filter(std::string filter_identifier1, std::string filter_identifier2,
			 std::string filter_identifier3 = "");
	void delete_filters();
	void comment_song(int song_id, int time, std::string comment);
	void print_song_comments(int id);
	void get_similar_users(int count);
	std::vector<Song*> get_recommended_songs(int count);
	Song* find_song_by_id(int id);
	std::vector<Song*> get_liked_songs();
	std::vector<Playlist*> get_playlists();
	Playlist* find_playlist_by_id(int id);

private:
	bool username_available(std::string username);
	
	User* verify(std::string username, std::string pass);
	bool email_available(std::string email);
	std::vector<Song*> use_all_filters(const std::vector<Song*>& songs);
	void check_logged_in();
	User* find_user(std::string username);
	
	void delete_all_filters();


	std::vector<Song*> songs;
	std::vector<User*> users;
	User* logged_in;
	std::vector<Playlist*> playlists;
	std::vector<Filter*> filters;
	Recommendation* recommendation;
};

#endif