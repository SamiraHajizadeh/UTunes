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

signup: Creates a new user account.
login: Logs in to an existing user account.
logout: Logs out of the current user account.
like <song_id>: Likes a specific song.
create <playlist_name>: Creates a new playlist with the given name.
add <song_id> <playlist_name>: Adds a specific song to a playlist.
filter <field> <value>: Filters songs by a specific field (id, title, artist, or release year).
comment <song_id> <comment>: Adds a comment to a specific song.
post <id> <title> <artist> <release_year> <link>: Posts a new song to the system.
Contributing
If you would like to contribute to UTunes, please follow these steps:

Fork this repository.
Create a new branch with your changes:
css
Copy code
git checkout -b my-feature-branch
Make your changes and commit them:
sql
Copy code
git commit -m "Add my feature"
Push your changes to your forked repository:
perl
Copy code
git push origin my-feature-branch
Create a pull request to merge your changes into the main branch.
License
This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgments
This project was developed as part of a C++ programming course. Special thanks to our instructor and TAs for their support.
