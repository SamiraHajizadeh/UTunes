#include "Song.hpp"

using namespace std;

Song::Song(int _id, std::string _title, std::string _artist, int _release_year,
		std::string _link){

	id = _id;
	title = _title;
	artist = _artist;
	release_year = _release_year;
	link = _link;
	likes_num = 0;
	playlists_num = 0;
}

Song::~Song(){
	for (int i = 0; i < comments.size(); i++){
		delete comments[i];
	}
}

void Song::print_partially(){
	cout << id << SPACE << title << SPACE << artist << SPACE << release_year << endl;
}

void Song::print_completely(){
	cout << id << endl;
	cout << title << endl;
	cout << artist << endl;
	cout << release_year << endl;
	cout << LIKES_NUM << SPACE << likes_num << endl;
	cout << COMMENTS_NUM << SPACE << comments.size() << endl;
	cout << PLAYLIST_NUM << SPACE << playlists_num << endl;
}

void Song::like(){
	++likes_num;
}

void Song::delete_like(){
	--likes_num;
}


void Song::added_to_playlist(){
	++playlists_num;
}

void Song::deleted_from_playlist(){
	--playlists_num;
}


void Song::comment(string user, string text, int time){
	comments.push_back(new Comment(user, text, time));
}



struct less_than
{
	bool operator() (Comment* comment1, Comment* comment2){
		if (comment1->get_time() == comment2->get_time()){
			return comment1->get_user() < comment2->get_user();
		}
		return (comment1->get_time() < comment2->get_time());
	}
};

void Song::print_comments(){
	if (comments.size() == 0)
		throw Empty();

	sort(comments.begin(), comments.end(), less_than());
	for (int i = 0; i < comments.size(); i++){
		comments[i]->print();
	}
}
