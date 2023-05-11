CC := g++

all: utunes.out 

utunes.out: Functions.o Exceptions.o Comment.o Song.o Recommendation.o Filter.o Playlist.o User.o Utunes.o main.o
	$(CC) Functions.o main.o Exceptions.o Comment.o Song.o Recommendation.o Filter.o Playlist.o User.o Utunes.o $(CCFLAGS) -o utunes.out
	
Functions.o : Functions.cpp Functions.hpp
	$(CC) -std=c++11 -c Functions.cpp -o Functions.o

Exceptions.o: Exceptions.cpp Exceptions.hpp
	$(CC) -std=c++11 -c Exceptions.cpp -o Exceptions.o

Comment.o: Macros.hpp Functions.hpp Exceptions.hpp Comment.cpp Comment.hpp 
	$(CC) -std=c++11 -c Comment.cpp -o Comment.o
	
Song.o: Macros.hpp Functions.hpp Exceptions.hpp Comment.hpp Song.cpp Song.hpp 
	$(CC) -std=c++11 -c Song.cpp -o Song.o

Filter.o: Macros.hpp Functions.hpp Exceptions.hpp Comment.hpp Song.hpp Filter.cpp Filter.hpp 
	$(CC) -std=c++11 -c Filter.cpp -o Filter.o		
	
Playlist.o: Macros.hpp Functions.hpp Exceptions.hpp Comment.hpp Song.hpp Playlist.cpp Playlist.hpp 
	$(CC) -std=c++11 -c Playlist.cpp -o Playlist.o
	
User.o: Macros.hpp Functions.hpp Exceptions.hpp Comment.hpp Song.hpp Filter.hpp Playlist.hpp User.cpp User.hpp 
	$(CC) -std=c++11 -c User.cpp -o User.o
	
Recommendation.o: Macros.hpp Functions.hpp Exceptions.hpp Comment.hpp Song.hpp User.hpp Recommendation.cpp Recommendation.hpp 
	$(CC) -std=c++11 -c Recommendation.cpp -o Recommendation.o
	
Utunes.o: Macros.hpp Functions.hpp Exceptions.hpp Comment.hpp Song.hpp Recommendation.hpp Filter.hpp Playlist.hpp User.hpp Utunes.cpp Utunes.hpp 
	$(CC) -std=c++11 -c Utunes.cpp -o Utunes.o	

main.o: Macros.hpp Functions.hpp Exceptions.hpp Comment.hpp Song.hpp Recommendation.hpp Filter.hpp Playlist.hpp User.hpp Utunes.hpp main.cpp 
	$(CC) -std=c++11 -c main.cpp -o main.o

.PHONY: clean
clean:
	rm -r *.o	
