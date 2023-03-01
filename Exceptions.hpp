#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <exception>

class Bad_Request: public std::exception{
	virtual const char* what() const throw(){
		return "Bad Request\n";
	}
};

class Permission_Denied: public std::exception{
	virtual const char* what() const throw(){
		return "Permission Denied\n";
	}
};

class Not_Found: public std::exception{
	virtual const char* what() const throw(){
		return "Not Found\n";
	}
};

class Empty: public std::exception{
	virtual const char* what() const throw(){
		return "Empty\n";
	}
};


#endif