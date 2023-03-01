#ifndef FILTER
#define FILTER

#include <vector>
#include <string>

#include "Song.hpp"
#include "Macros.hpp"


class Filter{

public:
	Filter(){}
	std::vector<Song*> filter_songs(const std::vector<Song*>& songs);
	std::string get_artist(){ return artist_name;}
	int get_min_year(){ return min_year;}
	int get_min_like(){ return min_like;}
	void set_artist(std::string artist);
	void set_like_limits(int min, int max);
	void set_year_limits(int min, int max);

protected:
	std::string artist_name;
	int min_year;
	int max_year;
	int min_like;
	int max_like;

};



class Artist_Filter: public Filter{

public:
	Artist_Filter(std::string _artist_name){
		artist_name = _artist_name;
		min_year = INVALID_NUMBER;
		max_year = INVALID_NUMBER;
		min_like = INVALID_NUMBER;
		max_like = INVALID_NUMBER;
	}
};


class Release_Year_Filter: public Filter{

public:
	Release_Year_Filter(int _min_year, int _max_year){
		min_year = _min_year;
		max_year = _max_year;

		artist_name = "";
		min_like = INVALID_NUMBER;
		max_like = INVALID_NUMBER;
	}
};


class Like_Filter: public Filter{

public:
	Like_Filter(int _min_like, int _max_like){
		min_like = _min_like;
		max_like = _max_like;

		artist_name = "";
		min_year = INVALID_NUMBER;
		max_year = INVALID_NUMBER;
	}

};



#endif