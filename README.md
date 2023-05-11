# UTunes - Audio Streaming System

UTunes is a C++ project that simulates an audio streaming system. It uses a Command Line Interface (CLI) to store user information (including their username, password, liked songs, and email) and recommend songs using a specific formula. Users can also post songs in the system by providing their id, title, artist, release year, and link. Each user can sign up, login, logout, like songs, and create playlists. The system also allows users to filter songs using their id, title, artist, or release year. Additionally, users can write comments for each song. Passwords are hashed before being stored in the system. The sign-up, login, logout, home, song details page, liked songs page, and playlist management page have been implemented using HTML and CSS.

## Installation
To install and run UTunes on your system, follow these steps:

1. Clone this repository using the following command:

```
git clone https://github.com/yourusername/utunes.git
```

2. Navigate to the cloned repository directory:
```
cd utunes
```

3. Compile the project using the Makefile:
```
make
```
4. Run the project:
```
./utunes
```
## Usage
Once you have installed and run UTunes, you can use the following commands to interact with the system:

- POST signup ? email < email > username < username > password < password >: Creates a new user account.
- POST login ? email < email > password < password >: Logs in to an existing user account.
- POST logout: Logs out of the current user account.
- POST likes ? id <id>: Likes a specific song.
- POST playlists ? name <name> privacy <public / private>: Creates a new playlist with the given name.
- POST playlists_songs ? playlist_id <playlist_id> song_id <song_id>
- POST filters ? artist <artist>: Filters songs by a specific field (id, title, artist, or release year).
- POST comments ? song_id <song_id> time <time> comment <comment>: Adds a comment to a specific song.
- ...

## Contributing
If you would like to contribute to UTunes, please follow these steps:

1. Fork this repository
2. Create a new branch with your changes
3. Make your changes and commit them
4. Push your changes to your forked repository
5. Create a pull request to merge your changes into the main branch.

## Acknowledgments
This project was created by me as part of the Advanced Programming course at University of Tehran.
