CC := g++

all: utunes.out 

utunes.out: Functions.o Exceptions.o Comment.o Song.o Recommendation.o Filter.o Playlist.o User.o Utunes.o my_server.o response.o request.o utilities.o server.o route.o template_parser.o Handler.o main.o
	$(CC) Functions.o Exceptions.o Comment.o Song.o Recommendation.o Filter.o Playlist.o User.o Utunes.o my_server.o response.o request.o utilities.o server.o route.o template_parser.o Handler.o main.o $(CCFLAGS) -o utunes.out
	
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
	
	
	
template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o template_parser.o

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o response.o

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o request.o

utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o utilities.o

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o server.o

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o route.o



my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server.cpp -o my_server.o

Handler.o:server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp Utunes.hpp Handler.cpp Handler.hpp Playlist.hpp 
	$(CC) $(CF) -c Handler.cpp -o Handler.o


main.o: Macros.hpp Functions.hpp Exceptions.hpp Comment.hpp Song.hpp Recommendation.hpp Filter.hpp Playlist.hpp User.hpp Utunes.hpp utils/server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp Handler.hpp main.cpp 
	$(CC) -std=c++11 -c main.cpp -o main.o

.PHONY: clean
clean:
	rm -r *.o	
