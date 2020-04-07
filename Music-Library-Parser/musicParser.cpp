/* 
 * Conner Brinkley
 * January 22, 2019
 * Project 1 -- Lib Info 
 *
 * INPUT: a text file with songs in the format { title m:ss artist album genre track }
 * OUTPUT: a parsed music library, sorted lexicographically by artist, then album, then track number
 *
 * */

#include <fstream>
#include <string>
#include <cstdio>
#include <map>
using namespace std;


class Song {
	public:
		string title;
		int time;
		int track;
};

class Album {
	public:
		map <int, Song *> songs;
		string name;
		int time;
		int num_songs;
};
	
class Artist {
	public:
		map <string, Album *> albums;
		string name;
		int time;
		int num_songs;
};


int main(int argc, char *argv[]) {


	ifstream file;                                          // input file stream
	string line;                                            // used for parsing
	map <string, Artist *> artists;                         // map of artists, keyed by name
	map <string, Artist *>::iterator it;                    // iterator for artist map
	map <string, Album *>::iterator alit;                   // iterator for album map
	map <int, Song *>::iterator sit;                        // iterator for song map
	char track[500], artist[100], album[500], genre[50];    // used for parsing strings
	int minutes, seconds, total_seconds, track_num, i;      // used for parsing numbers


	/* open file and read line by line */

	file.open(argv[1]);
	while (getline(file, line)) {
		
		/* parse each line */
		
		sscanf(line.c_str(), "%s %d:%d %s %s %s %d", track, &minutes, &seconds, artist, album, genre, &track_num);
		
		/* turns m:ss to seconds and converts all underscores to spaces */
		
		total_seconds = (60 * minutes) + seconds;
		for (i = 0; i < 500; i++) {
			if (track[i] == '_') {
				track[i] = ' ';
			}
		}
		for (i = 0; i < 100; i++) {
			if (artist[i] == '_') {
				artist[i] = ' ';
			}
		}
		for (i = 0; i < 500; i++) {
			if (album[i] == '_') {
				album[i] = ' ';
			}
		}
		for (i = 0; i < 50; i++) {
			if (genre[i] == '_') {
				genre[i] = ' ';
			}
		}
	
		/* create new song */

		Song *newSong = new Song;
		newSong->title = track;
		newSong->time = total_seconds;
		newSong->track = track_num;

		/* check to see if artist already exists. 
		 *  - If it doesn't, create artist and add it to the map 
		 *  - If it does, update the total time and # of songs */

		it = artists.find(artist);
		if (it == artists.end()) {

			Artist *newArtist = new Artist;
			newArtist->name = artist;
			newArtist->time = total_seconds;
			newArtist->num_songs = 1;

			artists[artist] = newArtist;
			it = artists.find(artist);
		} 
		
		else {

			it->second->time += total_seconds;
			it->second->num_songs += 1;
		}

		
		/* check to see if album already exists. 
		 *  - If it doesn't, create album and add it to the map
		 *  - If it does, updata the total time and # of songs */

		if (it->second->albums.find(album) == it->second->albums.end()) {
			
			Album *newAlbum = new Album;
			newAlbum->name = album;
			newAlbum->time = total_seconds;
			newAlbum->num_songs = 1;

			it->second->albums[album] = newAlbum;
		}
		
		else {

			it->second->albums.find(album)->second->time += total_seconds;
			it->second->albums.find(album)->second->num_songs += 1;
		}

		/* add the song to the album's song map */

		it->second->albums.find(album)->second->songs[track_num] = newSong;
	}

	
	/* traverse artists and print them out */

	for (it = artists.begin(); it != artists.end(); it++) {
		printf("%s: %d, %d:", it->first.c_str(), it->second->num_songs, (it->second->time) / 60);
		if ((it->second->time % 60) > 9) {
			printf("%d\n", it->second->time % 60);
		}
		else {
			printf("0%d\n", it->second->time % 60);
		}
		
		/* traverse albums and print them out */

		for (alit = it->second->albums.begin(); alit != it->second->albums.end(); alit++) {
			printf("        %s: %d, %d:", alit->first.c_str(), alit->second->num_songs, (alit->second->time) / 60);
			if ((alit->second->time % 60) > 9) {
				printf("%d\n", alit->second->time % 60);
			}
			else {
				printf("0%d\n", alit->second->time % 60);
			}
			
			/* traverse songs and print them out */

			for (sit = alit->second->songs.begin(); sit != alit->second->songs.end(); sit++) {
				printf("                %d. %s: %d:", sit->second->track, sit->second->title.c_str(), (sit->second->time) / 60);
				if ((sit->second->time % 60) > 9) {
					printf("%d\n", sit->second->time % 60);
				}
				else {
					printf("0%d\n", sit->second->time % 60);
				}
			}
		}
	}	

	file.close();
	
	return 0;
}
