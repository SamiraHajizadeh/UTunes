#include "Handler.hpp"


#define SONG_TABLE_ROWS_NUM 4
#define RECOMMENDED_SONG_NUM 4
#define LINE_BREAK "<p></p>"

using namespace std;

string button_style(){
	string body;
	body += "input[type=text], select {";
	body += "  width: 100%;";
	body += "  padding: 12px 20px;";
	body += "  margin: 8px 0;";
	body += "  display: inline-block;";
	body += "  border: 1px solid #ccc;";
	body += "  border-radius: 4px;";
	body += "  box-sizing: border-box;";
	body += "}";

	body += "input[type=submit] {";
	body += "  width: 100%;";
	body += "  background-color: #4CAF50;";
	body += "  color: white;";
	body += "  padding: 14px 20px;";
	body += "  margin: 8px 0;";
	body += "  border: none;";
	body += "  border-radius: 4px;";
	body += "  cursor: pointer;";
	body += "}";

	body += "input[type=submit]:hover {";
	body += "  background-color: #00cc6c;";
	body += "}";

	body += "div {";
	body += "  border-radius: 5px;";
	body += "  background-color: #f2f2f2;";
	body += "  padding: 20px;";
	body += "}";
	return body;
}

string table_style(int rows = 1){

	string style;
	style += "table {";
	style += "  font-family: arial, sans-serif;";
	style += "  border-collapse: collapse;";
	style += "  width: 100%;";
	style += "}";

	style += "td, th {";
	style += "  border: 1px solid #dddddd;";
	style += "  text-align: left;";
	style += "  padding: ";
	style += rows;
	style += "px;";
	style += "}";

	style += "tr:nth-child(even) {";
	style += "  background-color: #dddddd;";
	style += "}";

	return style;
}


string style_syntax(int num = 1){
	string syntax;
	syntax += "<style>";
	syntax += button_style();
	syntax += table_style(num);
	syntax += "</style>";
	return  syntax;
}

string form_syntax(string link, string method, string inside_form, bool form_ending = true){
	string syntax;
	syntax += LINE_BREAK;
	syntax += "<form action='";
	syntax += link;
	syntax += "' method='";
	syntax += method;
	syntax += "'>";
	syntax += inside_form;
	if (form_ending)
		syntax += "</form>";
	return syntax;
}

string hidden_input_syntax(string name, string value){
	string syntax;
	syntax += "<input type='hidden' name=\"";
	syntax += name;
	syntax += "\" value=\"";
	syntax += value;
	syntax += "\">";
	return syntax;
}

string button_syntax(string value){
	string syntax;
	syntax += "<input type='submit' value='";
	syntax += value;
	syntax += "'></button>";
	return syntax;
}


string linked_button(string link, string method, string value, string hidden_name = "", string hidden_value = "", bool form_ending = true){

	string body;
	if (hidden_name != "")
		body += hidden_input_syntax(hidden_name, hidden_value);

	body += button_syntax(value);
	return form_syntax(link, method, body, form_ending);
}

string label_syntax(string name, string label){
	string syntax;
	syntax += "<label for=\"";
	syntax += name;
	syntax += "\">";
	syntax += label;
	syntax += "</label>";
	return syntax;
}


string text_input_syntax(string name, string label = "", string placeholder = "", bool button = true){
	string syntax;
	if (label != "")
		syntax += label_syntax(name, label);
	syntax += "<input type=\"text\" name=\"";
	syntax += name;
	if (placeholder != ""){
		syntax += "\" placeholder=\"";
		syntax += placeholder;
	}
	syntax += "\">";
	if (button)
		syntax += "<input type=\"submit\">";
	return syntax;
}





string select_syntax(string name, vector<string> options, string label = ""){
	string syntax;
	if (label != "")
		syntax += label_syntax(name, label);
	syntax += "<select name=\"";
	syntax += name;
	syntax += "\">";
	for (int i = 0; i < options.size(); i++){
		syntax += "<option value=\"";
		syntax += options[i];
		syntax += "\">";
		syntax += options[i];
		syntax += "</option>";
	}
	syntax += "</select>";
	return syntax;
}


string audio_syntax(string link){
	string syntax;
	syntax += "<audio controls>";
	syntax += "<source src=\"";
	syntax += link;
	syntax += "\">";
	syntax += "</audio>";
	return syntax;
}


Response *UtunesPage::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += style_syntax(4);
	body += "<body>";
	body += "<h3>Welcome to Utunes!</h3>";
	body += "<div>";
	body += linked_button("/utunes/signup_user", "POST", "Sign Up");
	body += linked_button("/utunes/login", "GET", "Login");
	body += linked_button("/utunes/home_page", "GET", "Home");
	body += "</div>";
	body += "</body>";
	body += "</html>";
	res->setBody(body);
	return res;
}


string create_row(vector<string> cols){
	string row;
	row += "<tr>";
	for (int i = 0; i < cols.size(); i++){
		row += "<td>";
		row += cols[i];
		row += "</td>";
	}
	row += "</tr>";
	return row;
}

string create_songs_table_body(vector<Song*> songs, string link, string title = "Songs"){
	string body;

	body += "<h2>";
	body += title;
	body += "</h2>";
	body += "<table>";
	body += "<tr><th>Title</th><th>Artist</th><th>Release Year</th></tr>";
	for (int i = 0; i < songs.size(); i++){
		string value = to_string(songs[i]->get_id()) + "." + songs[i]->get_title();
		body += create_row({linked_button(link, "POST", value, "id", to_string(songs[i]->get_id())),
							songs[i]->get_artist(), to_string(songs[i]->get_release_year())});
	}
	body += "</table>";
	return body;
}


string logout_button_syntax(){
	string syntax;
	syntax += linked_button("/utunes/logout", "GET", "Logout");
	return syntax;
}



Response *Access_Denied::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	string body;

	body += "<head>";
	body += style_syntax();
	body += "</head>";
	body += "<body style=\"text-align: center;\">";
	body += "<h1>Access Denied!</h1>";
	body += "<p>In order to access this page login first.</p>";
	body += linked_button("/utunes", "GET", "Utunes");
	body += linked_button("/utunes/login", "GET", "Login");
	body += "</body>";

	res->setBody(body);
	return res;
}


Response *Home_Page::callback(Request *req){

	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");

	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}

	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax(utunes->get_songs().size());
	body += "</head>";
	body += "<body>";
	body += create_songs_table_body(utunes->get_songs(), "/utunes/home_page/song");
	body += linked_button("/utunes/home_page/liked_songs", "GET", "Liked Songs");
	body += linked_button("/utunes/home_page/playlists", "GET", "Playlists");
	body += logout_button_syntax();
	body += "</body>";
	body += "</html>";
	res->setBody(body);
	
	return res;
}


string create_table_html_syntax(vector<vector<string>> vec){
	string body;
	body += "<table border=\"1\">";
	for (int i = 0; i < vec.size(); i++){
		body += "<tr>";
		for (int j = 0; j < vec[i].size(); j++){
			if (i==0)
				body += "<th>";
			else
				body += "<td>";
			body += vec[i][j];
			if (i==0)
				body += "</th>";
			else
				body += "</td>";
		}
		body += "</tr>";
	}
	body += "</table>";
	return body;
}

Response *Song_Page::callback(Request *req){

	Response *res = new Response;
	Song* song = utunes->find_song_by_id(stoi(req->getBodyParam("id")));

	res->setHeader("Content-Type", "text/html");
	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}
	string body;

	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax(SONG_TABLE_ROWS_NUM); 
	body += "</head>";
	body += "<body>";

	body += "<h2>Song</h2>";
	body += create_table_html_syntax(song->get_data());
	body += linked_button("/utunes/home_page/song/like_song", "POST", "Like", "id", to_string(song->get_id()));
	body += linked_button("/utunes/home_page/song/unlike_song", "POST", "Unlike", "id", to_string(song->get_id()));

	body += LINE_BREAK;
	body += audio_syntax(song->get_link());

	vector<Song*> recommended_songs = utunes->get_recommended_songs(RECOMMENDED_SONG_NUM);
	body +=  create_songs_table_body(recommended_songs, "/utunes/home_page/song", "Recommended Songs") ;

	body += linked_button("/utunes/home_page", "GET", "Back");
	body += logout_button_syntax();
	body += "</body>";
	body += "</html>";

	res->setBody(body);
	return res;	
}


Response *Liked_Songs::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax(utunes->get_liked_songs().size());
	body += "</head>";
	body += "<body>";
	body += create_songs_table_body(utunes->get_liked_songs(), "/utunes/home_page/song", "Liked Songs");
	
	body += "<p>Enter the ID of the song you want to delete</p>";
	body += form_syntax("/utunes/home_page/liked_songs/delete", "POST", text_input_syntax("id", "", "The ID.."));
	body += logout_button_syntax();	
	body += linked_button("/utunes/home_page", "GET", "Back");
	body += "</body>";
	body += "</html>";

	res->setBody(body);
	return res;	
}


Response *Delete_Liked_Songs::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}
	string body;

	int id = stoi(req->getBodyParam("id"));
	utunes->delete_song_from_liked(id);

	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax();
	body += "</head>";
	body += "<body style=\"text-align: center;\">";
	body += "<h1>Deleted!</h1>";
	body += linked_button("/utunes/home_page/liked_songs", "GET", "Back");
	body += logout_button_syntax();
	body += "</body>";
	body += "</html>";

	res->setBody(body);
	return res;	
}



Response *Playlists::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}
	vector<Playlist*> playlists = utunes->get_playlists();

	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax(playlists.size());
	body += "</head>";
	body += "<body>";
	body += "<h1>Playlists\n</h1>";

	body += "<table>";
	body += "<tr><th>Title</th><th>Privacy State</th></tr>";
	for (int i = 0; i < playlists.size(); i++){
		body += create_row({linked_button("/utunes/home_page/playlists/playlist", "POST", playlists[i]->get_name(), "id",
							 to_string(playlists[i]->get_id())), playlists[i]->privacy_state()});
	}
	body += "</table>";

	body += LINE_BREAK;
	body += "<h1>Add Playlist!\n</h1>";
	body += form_syntax("/utunes/home_page/playlists/add_playlist", "POST", text_input_syntax("playlist_name", "Name:"));
	body += LINE_BREAK;
	body += select_syntax("privacy", {"public", "private"}, "Select Privacy State:");
	body += "</form>";
	body += linked_button("/utunes/home_page", "GET", "Back");
	body += logout_button_syntax();	

	body += "</body>";
	body += "</html>";

	res->setBody(body);
	return res;	
}


Response *Playlist_Page::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}
	int id = stoi(req->getBodyParam("id"));
	Playlist* playlist = utunes->find_playlist_by_id(id);
	string body;

	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax(utunes->get_playlists().size());
	body += "</head>";
	body += "<body>";

	body += "<h1>Playlist</h1>";
	body += "<table>";
	body += "<tr><th>Name</th><th>Privacy State</th></tr>";
	body += create_row({playlist->get_name(), playlist->privacy_state()});
	body += "</table>";

	body += LINE_BREAK;
	body += create_songs_table_body(playlist->get_songs(), "/utunes/home_page/song");
	body += "<p>Add Song to Playlist:</p>";
	body += form_syntax("/utunes/home_page/playlists/playlist/add_song", "POST", hidden_input_syntax("playlist_id", to_string(id))
																			     +text_input_syntax("song_id", "Enter Song ID:"));
	body += "<p>Delete Song from Playlist:</p>";
	body += form_syntax("/utunes/home_page/playlists/playlist/delete_song", "POST", hidden_input_syntax("playlist_id", to_string(id))
																					+text_input_syntax("song_id", "Enter Song ID:"));
	body += linked_button("/utunes/home_page/playlists", "GET", "Back");
	body += logout_button_syntax();

	res->setBody(body);
	return res;	
}



Response *Add_Song_to_Playlist::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}
	string body;
	utunes->add_song_to_playlist(stoi(req->getBodyParam("playlist_id")), stoi(req->getBodyParam("song_id")));//?
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax();
	body += "</head>";
	body += "<body style=\"text-align: center;\">";
	body += "<h1>Song Added to Playlist!</h1>";
	body += linked_button("/utunes/home_page/playlists/playlist", "POST", "Back", "id", req->getBodyParam("playlist_id"));
	body += logout_button_syntax();
	body += "</body>";
	body += "</html>";

	res->setBody(body);
	return res;	
}

Response *Delete_Song_from_Playlist::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}
	string body;

	utunes->delete_song_from_playlist(stoi(req->getBodyParam("playlist_id")), stoi(req->getBodyParam("song_id")));
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax();
	body += "</head>";
	body += "<body style=\"text-align: center;\">";
	body += "<h1>Song Deleted from Playlist!</h1>";
	body += linked_button("/utunes/home_page/playlists/playlist", "POST", "Back", "id", req->getBodyParam("playlist_id"));
	body += logout_button_syntax();

	body += "</body>";
	body += "</html>";

	res->setBody(body);
	return res;	
}


Response *Add_Playlist::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}

	string privacy = req->getBodyParam("privacy");
	string name = req->getBodyParam("playlist_name");
	int id = utunes->make_playlist(name, privacy);

	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += table_style();
	body += "</head>";
	body += "<body style=\"text-align: center;\">";
	body += "<h1>Playlist Added!</h1>";
	body += linked_button("/utunes/home_page/playlists", "GET", "Back");
	body += logout_button_syntax();
	body += "</body>";
	body += "</html>";

	res->setBody(body);
	return res;	
}




Response *Like_Song::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}
	int song_id = stoi(req->getBodyParam("id"));
	utunes->like_song(song_id);

	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax();
	body += "</head>";
	body += "<body style=\"text-align: center;\">";
	body += "<h1>Liked!</h1>";
	body += "<p>";
	body += "Song Added to Liked Songs!";
	body += "</p>";
	body += linked_button("/utunes/home_page/song", "POST", "Back", "id", to_string(song_id));
	body += "</body>";
	body += "</html>";

	body += logout_button_syntax();

	res->setBody(body);
	return res;			
}

Response *Unlike_Song::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}
	int song_id = stoi(req->getBodyParam("id"));
	utunes->delete_song_from_liked(song_id);

	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax();
	body += "</head>";
	body += "<body style=\"text-align: center;\">";
	body += "<h1>Unliked!</h1>";
	body += "<p>Song Removed from Liked Songs!</p>";
	body += linked_button("/utunes/home_page/song", "POST", "Back", "id", to_string(song_id));
	body += "</body>";
	body += "</html>";
	body += logout_button_syntax();

	res->setBody(body);
	return res;			
}


Response *Signup::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	string body;

	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax(3);
	body += "</head>";
	body += "<body>";
	body += "<h3>Signup in Utunes!</h3>";
	body += "<div>";
	body += form_syntax("/utunes/signup_check", "POST", text_input_syntax("username", "Username", "Your username..", false) 
													   +text_input_syntax("password", "Password", "Your password..", false)
													   +text_input_syntax("email", "Email", "Your email..", false)
													   +button_syntax("Submit"));
	body += "</div>";
	body += "</body>";
	body += "</html>";

	res->setBody(body);
	return res;
}


Response *Signup_Check::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	string body;

	string username = req->getBodyParam("username");
	string password = req->getBodyParam("password");
	string email = req->getBodyParam("email");

	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += style_syntax();
	body += "</head>";
	body += "<body style=\"text-align: center;\">";
	body += "<h1>Sign Up Check</h1>";

	if (utunes->signup_user(email, username, password)){
		body += "<p>Sign Up Successful!</p>";
		body += linked_button("/utunes", "GET", "Utunes");
		body += linked_button("/utunes/login", "GET", "Login");
		utunes->logout_user();
	}
	else{
		body += "<p>Sign Up Unsuccessful!\n username or email already available</p>";
		body += linked_button("/utunes", "GET", "Utunes");
		body += linked_button("/utunes/signup_user", "POST", "Sign Up");
	}
	body += "</body>";
	body += "</html>";

	res->setBody(body);
	return res;
}	


Response *Login::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += style_syntax(4);
	body += "<body>";
	body += "<h3>Login to Utunes!</h3>";	  
	body += "<div>";
	body += form_syntax("/utunes/login_check", "POST", text_input_syntax("username", "Username", "Your username..", false) 
													   +text_input_syntax("password", "Password", "Your password..", false)
													   +button_syntax("Login"));

	body += "</div>";
	body += "</body>";
	body += "</html>";
	res->setBody(body);
	return res;
}	


Response *Login_Check::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	string body;

	string username = req->getBodyParam("username");
	string password = req->getBodyParam("password");
	string email;

	if ((email = utunes->log_in_user(username, password)) != ""){
		res->setBody(body);
		res = Response::redirect("/utunes/home_page");
		res->setSessionId(email);
	}
	else{
		body += "<!DOCTYPE html>";
		body += "<html>";
		body += "<head>";
		body += style_syntax();
		body += "</head>";
		body += "<body style=\"text-align: center;\">";
		body += "<h1>Login Check</h1>";
		body += "<p>Login Unsuccessful!</p>";
		body += linked_button("/utunes", "GET", "Utunes");
		body += linked_button("/utunes/login", "GET", "Login");
		body += "</body>";
		body += "</html>";
		res->setBody(body);
	}
	return res;
}	



Response *Logout::callback(Request *req){
	Response *res = new Response;
	res->setHeader("Content-Type", "text/html");
	if (req->getSessionId() == ""){
		res = Response::redirect("/utunes/access_denied");
		return res;
	}
	utunes->logout_user();
	res = Response::redirect("/utunes/login");
	res->setSessionId("");
	return res;
}