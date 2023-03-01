#ifndef COMMENT
#define COMMENT

#include <string>
#include <iostream>
#include <vector>

#include "Exceptions.hpp"
#include "Macros.hpp"


class Comment{
public:
	Comment(std::string _user, std::string _text, int _time);
	std::string get_text(){ return text;}
	std::string get_user(){ return user;}
	int get_time(){ return time;}
	void print();
private:
	std::string user;
	std::string text;
	int time;
};



#endif