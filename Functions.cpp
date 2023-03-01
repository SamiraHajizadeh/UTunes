#include "Functions.hpp"

using namespace std;



vector<string> split_line(string line, char key) {

	vector<string> splited_line;
	string word;

	if (line == "")
		return splited_line;
	for (char x : line) {
		if (x == key && word != "") {
			splited_line.push_back(word);
			word = "";
		}
		else {
			word.push_back(x);
		}
	}
	splited_line.push_back(word);
	return splited_line;
}


vector<vector<string>> recieve_data_from_csv_file(string file_name) {
	ifstream file(file_name);
	vector<vector<string>> file_data;
	string line;
	for (int j = 0; getline(file, line); j++) {
		vector<string> splited_line = split_line(line, ',');
		file_data.push_back(splited_line);

	}
	file.close();
	return file_data;
}

string combine_strings(vector<string> vec, int index, string in_between) {
	string combined_string = "";
	for (int i = index; i < vec.size(); i++) {
		combined_string += vec[i];
		combined_string += in_between;
	}

	if (in_between != "")
		combined_string.pop_back();

	return combined_string;
}

int group_spaces(string str) {
	for (int i = 1; i < str.size(); i++){
		if (str[i] == ' ' && str[i - 1] == ' ')
			return 1;
	}
	return 0;
}


long long hash_function(string str){
	int hash_key = HASH_KEY;
	long long m = HASH_REMAINDER;
	long long hash_value = 0;
	long long powered_key = 1;
	for (char c : str){
		hash_value = (hash_value + (c - STARTING_LETTER + 1) * powered_key) % m;
		powered_key = (powered_key * hash_key) % m;
	}
	return hash_value;
}


map<string, map<int, int>> extract_2Dmap_from_2D_titled_vector(int column1_str, int column2_int, vector<vector<std::string>> vec2D){
	map<string, map<int, int>> map2D;
	for (int i = 1; i < vec2D.size(); i++){
		map2D[vec2D[i][column1_str]][stoi(vec2D[i][column2_int])] = 1;
	}
	for (auto m : map2D){
		for (auto n : m.second){
			if (n.second != 1)
				n.second = 0;
		}
	}
	return map2D;
}

void print_2Dmap(map<string, map<int, int>> map2D){

	map<string, map<int, int>>::iterator iter;
	map<int, int>::iterator ptr;

	for (iter = map2D.begin(); iter != map2D.end(); iter++){
		for (ptr = iter->second.begin(); ptr != iter->second.end(); ptr++){
			cout << "First Key: " << iter->first << " Second Key: " 
			<< ptr->first << " Value: " << ptr->second << endl;
		}
	}
}

