#ifndef FUNCTIONS
#define FUNCTIONS

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <iostream>

#include "Macros.hpp"

std::vector<std::string> split_line(std::string line, char key = ' ');
std::vector<std::vector<std::string>> recieve_data_from_csv_file(std::string file_name);
std::string combine_strings(std::vector<std::string> vec, int index, std::string in_between = "");
int group_spaces(std::string str);
long long hash_function(std::string str);
std::map<std::string, std::map<int, int>> extract_2Dmap_from_2D_titled_vector(int column1_str, int column2_int, 
	std::vector<std::vector<std::string>> vec2D);
void print_2Dmap(std::map<std::string, std::map<int, int>> map2D);


#endif