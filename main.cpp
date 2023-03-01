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


#include "server/server.hpp"
#include "utils/utilities.hpp"
#include "utils/response.hpp"
#include "utils/request.hpp"
#include "utils/include.hpp"
#include "Handler.hpp"

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

		Server server(8080);

		server.post("/utunes/signup_user", new Signup(utunes));
		server.get("/utunes/signup_user", new ShowPage("/utunes/signup_user.html"));
		server.post("/utunes/signup_check", new Signup_Check(utunes));

		server.get("/utunes/home_page", new Home_Page(utunes));
		server.get("/utunes/home_page", new ShowPage("/utunes/home_page.html"));

		server.get("/utunes/access_denied", new Access_Denied(utunes));
		server.get("/utunes/access_denied", new ShowPage("/utunes/access_deniedhtml"));

		server.post("/utunes/home_page/song", new Song_Page(utunes));
		server.get("/utunes/home_page/song", new ShowPage("/utunes/home_page/song.html"));

		server.post("/utunes/home_page/song/like_song", new Like_Song(utunes));
		server.get("/utunes/home_page/song/like_song", new ShowPage("/utunes/home_page/song/like_song.html"));

		server.post("/utunes/home_page/song/unlike_song", new Unlike_Song(utunes));
		server.get("/utunes/home_page/song/unlike_song", new ShowPage("/utunes/home_page/song/unlike_song.html"));


		server.get("/utunes/home_page/liked_songs", new Liked_Songs(utunes));
		server.get("/utunes/home_page/liked_songs", new ShowPage("/utunes/home_page/liked_songs.html"));

		server.post("/utunes/home_page/liked_songs/delete", new Delete_Liked_Songs(utunes));
		server.get("/utunes/home_page/liked_songs/delete", new ShowPage("/utunes/home_page/liked_songs/delete.html"));

		server.get("/utunes/home_page/playlists", new Playlists(utunes));
		server.get("/utunes/home_page/playlists", new ShowPage("/utunes/home_page/playlists.html"));

		server.post("/utunes/home_page/playlists/playlist", new Playlist_Page(utunes));
		server.get("/utunes/home_page/playlists/playlist", new ShowPage("/utunes/home_page/playlists/playlist.html"));


		server.post("/utunes/home_page/playlists/playlist/add_song", new Add_Song_to_Playlist(utunes));
		server.get("/utunes/home_page/playlists/playlist/add_song", new ShowPage("/utunes/home_page/playlists/playlist/add_song.html"));

		server.post("/utunes/home_page/playlists/playlist/delete_song", new Delete_Song_from_Playlist(utunes));
		server.get("/utunes/home_page/playlists/playlist/delete_song", new ShowPage("/utunes/home_page/playlists/playlist/delete_song.html"));

		server.post("/utunes/home_page/playlists/add_playlist", new Add_Playlist(utunes));
		server.get("/utunes/home_page/playlists/add_playlist", new ShowPage("/utunes/home_page/playlists/add_playlist.html"));

		server.get("/utunes/login", new Login(utunes));
		server.get("/utunes/login", new ShowPage("/utunes/login.html"));
		server.post("/utunes/login_check", new Login_Check(utunes));


		server.get("/utunes/logout", new Logout(utunes));
		server.get("/utunes/logout", new ShowPage("/utunes/logout.html"));


		server.get("/utunes", new UtunesPage(utunes));
		server.get("/utunes", new ShowPage("utunes.html"));		

		server.run();
		delete utunes;
	}
	else{
		cerr << FILE_NAME_UNAVAILABLE << endl;
	}	
	return 0;
}
