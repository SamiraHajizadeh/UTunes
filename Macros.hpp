#ifndef MACROS
#define MACROS

#define INVALID_NUMBER -1
#define SPACE " "
#define COLON ":"
#define PERCENT "%"

#define POST_COMMAND "POST"
#define GET_COMMAND "GET"
#define DELETE_COMMAND "DELETE"
#define FILE_NAME_UNAVAILABLE "file name unavailable"
#define ID_AVAILABLE_COMMAND "id"

#define USER_COLUMN 0
#define LIKED_SONG_COLUMN 3
#define PASS_COLUMN 2
#define EMAIL_COLUMN 1

#define FILTERS_COMMAND "filters"
#define ARTIST_FILTER "artist"
#define MIN_RELEASE_YEAR_FILTER "min_year"
#define MAX_RELEASE_YEAR_FILTER "max_year"
#define MIN_LIKES_FILTER "min_like"
#define MAX_LIKES_FILTER "max_like"
#define COMMENTS_COMMAND "comments"
#define STARTING_LETTER 'a'
#define HASH_KEY 31
#define HASH_REMAINDER 1e9 + 9


#define SIGNUP_COMMAND "signup"
#define LOGIN_COMMAND "login"
#define LOGOUT_COMMAND "logout"
#define GET_SONGS_COMMAND "songs"
#define GET_LIKES_COMMAND "likes"
#define LIKES_COMMAND "likes"
#define PLAYLISTS_COMMAND "playlists"
#define NO_SONG_MESSAGE "Empty"

#define LIKES_NUM "#likes:"
#define COMMENTS_NUM "#comments:"
#define PLAYLIST_NUM "#playlists:" 

#define USERS_COMMAND "users"
#define SIMILAR_USERS "similar_users"
#define RECOMMENDED_SONGS "recommended"
#define PLAYLISTS_SONGS_COMMAND "playlists_songs"


#define PUBLIC "public"
#define PRIVATE "private"

#define COMMAND_DONE "OK"

#define ID_INDEX 0
#define TITLE_INDEX 1
#define ARTIST_INDEX 2
#define RELEASE_YEAR_INDEX 3
#define LINK_INDEX 4


#endif