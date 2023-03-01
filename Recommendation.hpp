#ifndef RECOMMENDATION
#define RECOMMENDATION


#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <algorithm>

#include "Functions.hpp"
#include "Song.hpp"
#include "User.hpp"

class Recommendation{

public:
	Recommendation(std::vector<Song*>& _songs);
	void print_similar_users(std::string username, int count, std::vector<User*>& users);
	void print_recommended_songs(std::string username, int count, std::vector<User*> users);  
	std::vector<Song*> get_recommended_songs(std::string username, int count, std::vector<User*> users);

private:
	void add_user_liked_songs(User*& user);
	int count_two_users_common_songs(std::string username1, std::string username2);
	void calculate_common_songs(std::vector<User*>& users);
	void initialize_common_songs();
	void count_common_songs();
	void normalize_common_songs();
	void create_liked_songs_matrix(std::vector<User*>& users);
	float confidence(std::string username, Song* song);
	int count_users();
	std::vector<std::pair<Song*, float>> get_confidences(std::string username);
	std::vector<std::pair<std::string, float>> sort_similar_users(std::string username);


	std::map<std::string, std::map<Song*, int>> liked_songs;
	std::map<std::string, std::map<std::string, float>> common_songs;
	std::vector<Song*> songs;

};



#endif