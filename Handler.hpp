#ifndef HANDLER
#define HANDLER

#include "Utunes.hpp"
#include "Song.hpp"
#include "Playlist.hpp"
#include <vector>
#include <string>

#include "server/server.hpp"
#include "utils/utilities.hpp"
#include "utils/response.hpp"
#include "utils/request.hpp"
#include "utils/include.hpp"


class Request_Handler : public RequestHandler{

public:
	Request_Handler(Utunes* _utunes){
		utunes = _utunes;
	}
	virtual ~Request_Handler(){}
	virtual Response *callback(Request *) = 0;

protected:
	Utunes* utunes;
};


class UtunesPage: public Request_Handler{
public:
	UtunesPage(Utunes* _utunes): Request_Handler{_utunes}{}
	~UtunesPage(){}
	Response *callback(Request *req);
};


class Home_Page: public Request_Handler{
public:
	Home_Page(Utunes* _utunes): Request_Handler{_utunes}{}
	~Home_Page(){}
	Response *callback(Request *req);
};


class Access_Denied: public Request_Handler{
public:
	Access_Denied(Utunes* _utunes): Request_Handler{_utunes}{}
	~Access_Denied(){}
	Response *callback(Request *req);
};


class Song_Page: public Request_Handler{
public:
	Song_Page(Utunes* _utunes): Request_Handler{_utunes}{}
	~Song_Page(){}
	Response *callback(Request *req);
};

class Like_Song: public Request_Handler{
public:
	Like_Song(Utunes* _utunes): Request_Handler{_utunes}{}
	~Like_Song(){}
	Response *callback(Request *req);
};

class Liked_Songs: public Request_Handler{
public:
	Liked_Songs(Utunes* _utunes): Request_Handler{_utunes}{}
	~Liked_Songs(){}
	Response *callback(Request *req);
};


class Delete_Liked_Songs: public Request_Handler{
public:
	Delete_Liked_Songs(Utunes* _utunes): Request_Handler{_utunes}{}
	~Delete_Liked_Songs(){}
	Response *callback(Request *req);
};

class Playlists: public Request_Handler{
public:
	Playlists(Utunes* _utunes): Request_Handler{_utunes}{}
	~Playlists(){}
	Response *callback(Request *req);
};

class Playlist_Page: public Request_Handler{
public:
	Playlist_Page(Utunes* _utunes): Request_Handler{_utunes}{}
	~Playlist_Page(){}
	Response *callback(Request *req);
};



class Add_Song_to_Playlist: public Request_Handler{
public:
	Add_Song_to_Playlist(Utunes* _utunes): Request_Handler{_utunes}{}
	~Add_Song_to_Playlist(){}
	Response *callback(Request *req);
};

class Delete_Song_from_Playlist: public Request_Handler{
public:
	Delete_Song_from_Playlist(Utunes* _utunes): Request_Handler{_utunes}{}
	~Delete_Song_from_Playlist(){}
	Response *callback(Request *req);
};

class Add_Playlist: public Request_Handler{
public:
	Add_Playlist(Utunes* _utunes): Request_Handler{_utunes}{}
	~Add_Playlist(){}
	Response *callback(Request *req);
};


class Unlike_Song: public Request_Handler{
public:
	Unlike_Song(Utunes* _utunes): Request_Handler{_utunes}{}
	~Unlike_Song(){}
	Response *callback(Request *req);
};

class Login: public Request_Handler{
public:
	Login(Utunes* _utunes): Request_Handler{_utunes}{}
	~Login(){}
	Response *callback(Request *req);
};


class Login_Check: public Request_Handler{
public:
	Login_Check(Utunes* _utunes): Request_Handler{_utunes}{}
	~Login_Check(){}
	Response *callback(Request *req);
};


class Signup: public Request_Handler{
public:
	Signup(Utunes* _utunes): Request_Handler{_utunes}{}
	virtual ~Signup(){}
	Response *callback(Request *req);
};

class Signup_Check: public Request_Handler{
public:
	Signup_Check(Utunes* _utunes): Request_Handler{_utunes}{}
	virtual ~Signup_Check(){}
	Response *callback(Request *req);
};


class Logout: public Request_Handler{
public:
	Logout(Utunes* _utunes): Request_Handler{_utunes}{}
	virtual ~Logout(){}
	Response *callback(Request *req);
};


#endif