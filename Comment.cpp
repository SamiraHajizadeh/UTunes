#include "Comment.hpp"

using namespace std;

Comment::Comment(string _user, string _text, int _time){
	user = _user;
	text = _text;
	time = _time;
}

void Comment::print(){
	cout << time << SPACE << user << COLON << SPACE << text << endl;
}