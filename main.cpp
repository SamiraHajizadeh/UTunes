#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "Macros.hpp"
#include "Functions.hpp"
#include "Song.hpp"
#include "User.hpp"
#include "Utunes.hpp"
#include "Exceptions.hpp"

using namespace std;

void read_commands(Utunes* utunes){

	while (true) {
		if (cin.eof())
			break;

		string command;
		getline(cin, command);
		if (command == "")
			continue;

		vector<string> splited_command = split_line(command);
		try{

			if (splited_command[0] == POST_COMMAND){
				if (splited_command[1] == SIGNUP_COMMAND)
					utunes->signup_user(splited_command[4], splited_command[6], splited_command[8]);

				else if (splited_command[1] == LOGIN_COMMAND)
					utunes->log_in_user(splited_command[4], splited_command[6]);

				else if (splited_command[1] == LOGOUT_COMMAND)
					utunes->logout_user();

				else if (splited_command[1] == LIKES_COMMAND)
					utunes->like_song(stoi(splited_command[4]));

				else if (splited_command[1] == PLAYLISTS_COMMAND){
					utunes->make_playlist(splited_command[4], splited_command[6]);
					continue;
				}

				else if (splited_command[1] == PLAYLISTS_SONGS_COMMAND)
					utunes->add_song_to_playlist(stoi(splited_command[4]), stoi(splited_command[6]));

				else if (splited_command[1] == FILTERS_COMMAND){
					if (splited_command[3] == ARTIST_FILTER)
						utunes->add_filter(splited_command[3], combine_strings(splited_command, 4, SPACE));
					else
						utunes->add_filter(splited_command[3], splited_command[4], splited_command[6]);
				}

				else if (splited_command[1] == COMMENTS_COMMAND)
					utunes->comment_song(stoi(splited_command[4]), stoi(splited_command[6]), splited_command[8]);
				else
					throw Not_Found();
				cout << COMMAND_DONE << endl;

			}
			else if (splited_command[0] == GET_COMMAND){
				if (splited_command[1] == GET_SONGS_COMMAND){
					int id = INVALID_NUMBER;
					if (splited_command[3] == ID_AVAILABLE_COMMAND)
						id = stoi(splited_command[4]);
					utunes->print_songs(id);
				}

				else if (splited_command[1] == GET_LIKES_COMMAND)
					utunes->print_liked_songs();

				else if (splited_command[1] == PLAYLISTS_COMMAND)
					utunes->print_playlist(splited_command[4]);

				else if (splited_command[1] == PLAYLISTS_SONGS_COMMAND)
					utunes->print_playlist_songs(stoi(splited_command[4]));

				else if (splited_command[1] == USERS_COMMAND)
					utunes->print_users();

				else if (splited_command[1] == COMMENTS_COMMAND)
					utunes->print_song_comments(stoi(splited_command[4]));
				
				else if (splited_command[1] == SIMILAR_USERS)
					utunes->get_similar_users(stoi(splited_command[4]));
				
				else if (splited_command[1] == RECOMMENDED_SONGS)
					utunes->get_recommended_songs(stoi(splited_command[4]));
				else 
					throw Not_Found();
			}

			else if (splited_command[0] == DELETE_COMMAND){

				if (splited_command[1] == LIKES_COMMAND)
					utunes->delete_song_from_liked(stoi(splited_command[4]));

				else if (splited_command[1] == PLAYLISTS_SONGS_COMMAND)
					utunes->delete_song_from_playlist(stoi(splited_command[4]), stoi(splited_command[6]));

				else if (splited_command[1] == FILTERS_COMMAND)
					utunes->delete_filters();
				else
					throw Not_Found();
				cout << COMMAND_DONE << endl;
			}
			else
				throw Bad_Request();
		}
		catch(exception& e){
			cout << e.what();
		}
		
	}
}


int main(int argc, char *argv[]){

	if (argv[2] != NULL){
		vector<vector<string>> songs = recieve_data_from_csv_file(argv[1]);
		vector<vector<string>> liked_songs = recieve_data_from_csv_file(argv[2]);
		Utunes* utunes = new Utunes(songs, liked_songs);
		read_commands(utunes);
		delete utunes;
	}
	else{
		cerr << FILE_NAME_UNAVAILABLE << endl;
	}	
	return 0;
}
