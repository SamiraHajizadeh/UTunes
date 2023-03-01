#include "User.hpp"

using namespace std;

User::User(string _username, string _password, string _email){

	email = _email;
	username = _username;
	hash_password = hash_function(_password);
}


User::~User(){
	for (int i = 0; i < playlists.size(); i++){
		delete playlists[i];
	}
}

bool User::song_already_liked(Song* song){
	if (song != nullptr){
		for (int i = 0; i < liked_songs.size(); i++){
			if (liked_songs[i]->get_id() == song->get_id())
				return true;
		}
	}
	return false;
}

void User::like_song(Song* song){
	if (!song_already_liked(song)){
		song->like();
		liked_songs.push_back(song);
	}
}


struct song_less_than
{
	inline bool operator() (Song* song1, Song* song2){
		return (song1->get_id() < song2->get_id());
	}
};


void User::print_liked_songs(){
	if (liked_songs.size() == 0)
		throw Empty();
	sort(liked_songs.begin(), liked_songs.end(), song_less_than());
	for (int i = 0; i < liked_songs.size(); i++){
		liked_songs[i]->print_partially();
	}
}

void User::delete_song_from_liked(int id){
	for (int i = 0; i < liked_songs.size(); i++){
		if (liked_songs[i]->get_id() == id){
			liked_songs[i]->delete_like();
			if (liked_songs.size() == 1)
				liked_songs = {};
			else
				liked_songs.erase(liked_songs.begin() + i);
		}
	}
}


struct less_than
{
	inline bool operator() (Playlist* playlist1, Playlist* playlist2){
		return (playlist1->get_id() < playlist2->get_id());
	}
};

void User::print_playlists(bool show_private){
	if (playlists.size() == 0)
		throw Empty();

	sort(playlists.begin(), playlists.end(), less_than());
	for (int i = 0; i < playlists.size(); i++){
		playlists[i]->print(show_private);
	}
}

Playlist* User::make_playlist(string name, bool _public, int id){
	playlists.push_back(new Playlist(name, _public, id));
	return playlists[playlists.size() - 1];
}

bool User::has_playlist(int id){
	for (int i = 0; i < playlists.size(); i++){
		if (playlists[i]->get_id() == id)
			return true;
	}
	return false;
}

void User::print_username(){
	cout << username << endl;
}

vector<int> User::get_liked_songs_strVec() const{
	vector<int> liked_songs_strVec;
	for (int i = 0; i < liked_songs.size(); i++){
		liked_songs_strVec.push_back(liked_songs[i]->get_id());
	}
	return liked_songs_strVec;
}