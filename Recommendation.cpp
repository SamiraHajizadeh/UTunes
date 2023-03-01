#include "Recommendation.hpp"

using namespace std;

Recommendation::Recommendation(std::vector<Song*>& _songs){
	songs = _songs;
}


void Recommendation::add_user_liked_songs(User*& user){

	vector<Song*> _songs = user->get_liked_songs();
	for (int i = 0; i < _songs.size(); i++){
		liked_songs[user->get_username()][_songs[i]] = 1;
	}
	for (int i = 0; i < _songs.size(); i++){
		if (liked_songs[user->get_username()][_songs[i]] != 1)
			liked_songs[user->get_username()][_songs[i]] = 0;
	}
}


void Recommendation::create_liked_songs_matrix(vector<User*>& users){
	
	liked_songs.clear();
	for (int i = 0; i < users.size(); i++){
		add_user_liked_songs(users[i]);
	}
}

void Recommendation::initialize_common_songs(){
	common_songs.clear();
	for (pair<string, map<Song*, int>> p : liked_songs){
		for (pair<string, map<Song*, int>> p2 : liked_songs){
			common_songs[p.first][p2.first] = 0;
		}
	}
}

int Recommendation::count_two_users_common_songs(string username1, string username2){
	int counter = 0;
	for (pair<Song*, int> p : liked_songs[username1]){
		if (p.second == 1 && liked_songs[username2][p.first] == 1)
			++counter;
	}
	return counter;
}

void Recommendation::count_common_songs(){
	map<string, map<string, float>>::iterator iter, iter2;

	for (iter = common_songs.begin(); iter != common_songs.end(); iter++){
		for (iter2 = common_songs.begin(); iter2 != common_songs.end(); iter2++){
			if (iter->first != iter2->first){
				common_songs[iter->first][iter2->first] = 
					count_two_users_common_songs(iter->first, iter2->first);
			}
		}
	}
}

void Recommendation::normalize_common_songs(){

	map<string, map<string, float>>::iterator iter, iter2;
	for (iter = common_songs.begin(); iter != common_songs.end(); iter++){
		for (iter2 = common_songs.begin(); iter2 != common_songs.end(); iter2++){
			if (iter->first != iter2->first){
				common_songs[iter->first][iter2->first] /= songs.size();
			}
		}
	}
}


void Recommendation::calculate_common_songs(vector<User*>& users){
	create_liked_songs_matrix(users);
	initialize_common_songs();
	count_common_songs();
	normalize_common_songs();
}


int Recommendation::count_users(){
	int counter = 0;
	for (pair<string, map<Song*, int>> m : liked_songs){
		counter++;
	}
	return counter;
}

float Recommendation::confidence(string username, Song* song){

	float confidence = 0;

	for (pair<string, map<Song*, int>> m : liked_songs){
		confidence += common_songs[username][m.first]*liked_songs[m.first][song];
	}
	confidence /= (count_users()-1);
	return confidence;
}

vector<pair<Song*, float>> Recommendation::get_confidences(string username){

	vector<pair<Song*, float>> confidences;
	for(int i = 0; i < songs.size(); i++){
		if (liked_songs[username][songs[i]] == 0)
			confidences.push_back(pair<Song*, float>(songs[i], confidence(username, songs[i])));
	}
	return confidences;
}


vector<pair<string, float>> Recommendation::sort_similar_users(string username){
	
	vector<pair<string, float>> pairs;
	for (auto itr = common_songs[username].begin(); itr != common_songs[username].end(); ++itr){
		if ((*itr).first != username)
			pairs.push_back(*itr);
	}
	sort(pairs.begin(), pairs.end(), [=](pair<string, float>& a, pair<string, float>& b){
		if (a.second == b.second)
			return (a.first < b.first);
		return (a.second > b.second);
	});
	return pairs;
}


void Recommendation::print_similar_users(string username, int count, vector<User*>& users){

	calculate_common_songs(users);
	vector<pair<string, float>> pairs = sort_similar_users(username);
	for (int i = 0; i < pairs.size() && i < count; i++){
		if (username != pairs[i].first)
			cout << fixed << setprecision(2) << 100*(pairs[i].second) << PERCENT << SPACE << pairs[i].first << endl;
	}
}

vector<Song*> Recommendation::get_recommended_songs(std::string username, int count, vector<User*> users){
	calculate_common_songs(users);

	vector<pair<Song*, float>> confidences = get_confidences(username);
	sort(confidences.begin(), confidences.end(), [=](pair<Song*, float>& a, pair<Song*, float>& b){
		if (a.second == b.second)
			return (a.first->get_id() < b.first->get_id());
		return (a.second > b.second);
	});

	vector<Song*> recommended;
	for (int i = 0; i < count && i < confidences.size(); i++){
		recommended.push_back(confidences[i].first);
	}
	return recommended;
}


void Recommendation::print_recommended_songs(std::string username, int count, vector<User*> users){
	calculate_common_songs(users);

	vector<pair<Song*, float>> confidences = get_confidences(username);
	sort(confidences.begin(), confidences.end(), [=](pair<Song*, float>& a, pair<Song*, float>& b){
		if (a.second == b.second)
			return (a.first->get_id() < b.first->get_id());
		return (a.second > b.second);
	});

	for (int i = 0; i < count && i < confidences.size(); i++){
		cout << confidences[i].first->get_id() << SPACE << fixed << setprecision(2) << 100*confidences[i].second 
			<< PERCENT << SPACE << confidences[i].first->get_title() << SPACE 
			<< confidences[i].first->get_artist() << SPACE <<
			confidences[i].first->get_release_year() << endl;
	}
}
