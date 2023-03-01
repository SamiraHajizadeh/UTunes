#include "Utunes.hpp"

using namespace std;


void Utunes::signup_initial_users(vector<vector<string>> vec){

	for (int i = 1; i < vec.size(); i++){
		if (!username_available(vec[i][USER_COLUMN])){
			signup_user(vec[i][EMAIL_COLUMN], vec[i][USER_COLUMN], vec[i][PASS_COLUMN]);
		}
		else
			log_in_user(vec[i][EMAIL_COLUMN], vec[i][PASS_COLUMN]);

		like_song(stoi(vec[i][LIKED_SONG_COLUMN]));
	}

}

Utunes::Utunes(vector<vector<string>> songs_str, vector<vector<string>> liked_songs_str){
	for (int i = 1; i < songs_str.size(); i++){
		songs.push_back(new Song(stoi(songs_str[i][ID_INDEX]), songs_str[i][TITLE_INDEX],
		 	                     songs_str[i][ARTIST_INDEX], stoi(songs_str[i][RELEASE_YEAR_INDEX]),
		 	                     songs_str[i][LINK_INDEX]));
	}

	signup_initial_users(liked_songs_str);
	recommendation = new Recommendation(songs);
	logout_user();
}

Utunes::~Utunes(){
	for (int i = 0; i < songs.size(); i++){
		delete songs[i];
	}
	for (int i = 0; i < users.size(); i++){
		delete users[i];
	}
	delete recommendation;
}


void Utunes::check_logged_in(){
	if (logged_in == nullptr)
		throw Permission_Denied();
}


bool Utunes::email_available(string email){
	for (int i = 0; i < users.size(); i++){
		if (users[i]->get_email() == email)
			return true;
	}
	return false;
}

bool Utunes::username_available(string username){
	for (int i = 0; i < users.size(); i++){
		if (users[i]->get_username() == username)
			return true;
	}
	return false;
}

int Utunes::signup_user(string email, string username, string password){
	if (email_available(email) || username_available(username))
		return 0;
	users.push_back(new User(username, password, email));
	logged_in = users[users.size() - 1];
	return 1;
}



vector<Song*> Utunes::use_all_filters(const vector<Song*>& songs){

	vector<Song*> filtered_songs = songs;
	for (int i = 0; i < filters.size(); i++){
		filtered_songs = filters[i]->filter_songs(filtered_songs);
	}
	return filtered_songs;
}


void Utunes::print_all_songs(){
	vector<Song*> filtered_songs = use_all_filters(songs);
	if (filtered_songs.size() == 0)
		throw Empty();

	for (int i = 0; i < filtered_songs.size(); i++){
		filtered_songs[i]->print_partially();
	}
}


User* Utunes::verify(string username, string pass){
	
	for (int i = 0; i < users.size(); i++){
		if (users[i]->get_username() == username){
			if(users[i]->get_password() == hash_function(pass)){
				return users[i];
			}
		}
	}
	return nullptr;
}

string Utunes::log_in_user(string username, string password){
	if (verify(username, password) == nullptr)
		return "";
	logged_in = verify(username, password);
	return logged_in->get_email();
}


void Utunes::logout_user(){
	//check_logged_in();
	logged_in = nullptr;
	delete_all_filters();
}

Song* Utunes::find_song_by_id(int id){
	for (int i = 0; i < songs.size(); i++){
		if (songs[i]->get_id() == id)
			return songs[i];
	}
	return nullptr;
}

void Utunes::print_songs(int id){

	check_logged_in();
	if (id == INVALID_NUMBER)
		print_all_songs();
	else{
		if (find_song_by_id(id) == nullptr)
			throw Not_Found();
		find_song_by_id(id)->print_completely();
	}
}

void Utunes::like_song(int id){
	check_logged_in();
	if (find_song_by_id(id) == nullptr)
		return;
	logged_in->like_song(find_song_by_id(id));
}


vector<Song*> Utunes::get_liked_songs(){
	check_logged_in();
	return logged_in->get_liked_songs();
}

void Utunes::print_liked_songs(){
	check_logged_in();
	logged_in->print_liked_songs();
}


void Utunes::delete_song_from_liked(int id){
	check_logged_in();
	if (logged_in->song_already_liked(find_song_by_id(id)))
		logged_in->delete_song_from_liked(id);
}


int Utunes::make_playlist(string name, string privacy){
	check_logged_in();

	bool _public = true;
	if (privacy == PRIVATE)
		_public = false;

	playlists.push_back(logged_in->make_playlist(name, _public, playlists.size()+1));
	return playlists.size();
}

User* Utunes::find_user(string username){
	for (int i = 0; i < users.size(); i++){
		if (users[i]->get_username() == username)
			return users[i];
	}
	return nullptr;
}


vector<Playlist*> Utunes::get_playlists(){
	return logged_in->get_playlists();
}

void Utunes::print_playlist(string username){
	check_logged_in();
	bool show_private = false;
	if (username == logged_in->get_username())
		show_private = true;
	find_user(username)->print_playlists(show_private);	
}


Playlist* Utunes::find_playlist_by_id(int id){
	for (int i = 0; i < playlists.size(); i++){
		if (playlists[i]->get_id() == id)
			return playlists[i];
	}
	return nullptr;
}

void Utunes::add_song_to_playlist(int playlist_id, int song_id){
	check_logged_in();
	if (find_playlist_by_id(playlist_id) == nullptr || !logged_in->has_playlist(playlist_id)
		|| find_song_by_id(song_id) == nullptr)
		return;
	find_playlist_by_id(playlist_id)->add_song_to_playlist(find_song_by_id(song_id));
}

void Utunes::print_playlist_songs(int id){
	check_logged_in();
	if (find_playlist_by_id(id) == nullptr)
		throw Not_Found();

	if (!logged_in->has_playlist(id) && find_playlist_by_id(id)->is_private())
		throw Permission_Denied();

	find_playlist_by_id(id)->print_songs();
}

void Utunes::delete_song_from_playlist(int playlist_id, int song_id){
	check_logged_in();

	if (find_playlist_by_id(playlist_id) == nullptr || !find_playlist_by_id(playlist_id)->has_song(song_id))
		return;

	if (!logged_in->has_playlist(playlist_id))
		return;
	find_playlist_by_id(playlist_id)->delete_song(song_id);
}

struct less_than
{
	bool operator() (User* user1, User* user2){
		return (user1->get_username() < user2->get_username());
	}
};

void Utunes::print_users(){
	check_logged_in();
	if (users.size() == 1)
		throw Empty();

	sort(users.begin(), users.end(), less_than());

	for (int i = 0; i < users.size(); i++){
		if (users[i]->get_username() != logged_in->get_username())
			users[i]->print_username();
	}
}

void Utunes::delete_all_filters(){
	for (int i = 0; i < filters.size(); i++){
		delete filters[i];
	}
	filters.clear();
}


void Utunes::add_filter(string filter_identifier1, string filter_identifier2,
			 string filter_identifier3){

	check_logged_in();

	if (filter_identifier1 == ARTIST_FILTER){
		for (int i = 0; i < filters.size(); i++){
			if (filters[i]->get_artist() != ""){
				filters[i]->set_artist(filter_identifier2);
				return;
			}
		}
		filters.push_back(new Artist_Filter(filter_identifier2));
	}
	else{

		if (stoi(filter_identifier3) < stoi(filter_identifier2)
			||stoi(filter_identifier2) < 0 || stoi(filter_identifier3) < 0)
			throw Bad_Request();

		if (filter_identifier1 == MIN_RELEASE_YEAR_FILTER){


			for (int i = 0; i < filters.size(); i++){
				if (filters[i]->get_min_year() != INVALID_NUMBER){
					filters[i]->set_year_limits(stoi(filter_identifier2), stoi(filter_identifier3));
					return;
				}
			}
			filters.push_back(new Release_Year_Filter(stoi(filter_identifier2), stoi(filter_identifier3)));
		}
		if (filter_identifier1 == MIN_LIKES_FILTER){
			for (int i = 0; i < filters.size(); i++){
				if (filters[i]->get_min_like() != INVALID_NUMBER){
					filters[i]->set_like_limits(stoi(filter_identifier2), stoi(filter_identifier3));
					return;
				}
			}

			filters.push_back(new Like_Filter(stoi(filter_identifier2), stoi(filter_identifier3)));
		}
	}
}


void Utunes::delete_filters(){
	check_logged_in();
	delete_all_filters();
}


void Utunes::comment_song(int song_id, int time, string comment){

	check_logged_in();
	if (find_song_by_id(song_id) == nullptr)
		throw Not_Found();

	find_song_by_id(song_id)->comment(logged_in->get_username(), comment, time);
}


void Utunes::print_song_comments(int id){
	check_logged_in();
	if (find_song_by_id(id) == nullptr)
		throw Not_Found();
	find_song_by_id(id)->print_comments();
}


void Utunes::get_similar_users(int count){
	check_logged_in();
	recommendation->print_similar_users(logged_in->get_username(), count, users);
}


vector<Song*> Utunes::get_recommended_songs(int count){
	check_logged_in();
	return recommendation->get_recommended_songs(logged_in->get_username(), count, users);
}
