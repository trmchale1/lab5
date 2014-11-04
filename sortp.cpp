#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "song.h"
using namespace std;

const int maxsongs=200000;

int readSongs(song *songs[], int max) {
	string	title, album, artist;
	int	year;
	int	nsongs=0;	// # of songs
	ifstream songinput;

	songinput.open("songs");
	if (songinput.fail()) throw string("cannot open songs");
	songinput >> title;
	while (!songinput.fail() && nsongs<max) {
		songinput >> album;
		songinput >> artist;
		songinput >> year;
		//song onesong(title,album,artist,year);
		//songs[nsongs] = &onesong;
		songs[nsongs] = new song(title,album,artist,year);
		nsongs++;
		songinput >> title;
	}
	songinput.close();
	return nsongs;
}

void printSong(song s) {
	cout << "[" << s.getTitle() << " recorded on " << s.getAlbum() << " by "
		<< s.getArtist() << " in " << s.getYear() << endl;
}

void sort(song *songs[], int n) {
	for (int i=0; i<n-1; i++)
		for (int j=i+1;j<n; j++)
			if (songs[i]->getTitle()>songs[j]->getTitle()) {
				song *stmp = songs[i];
				songs[i] = songs[j];
				songs[j] = stmp;
			}
}

int main(int ac, char *av[]) {
	int	t0,t1;		// timing is everything
	int	nsongs=0;	// # of songs
	song	*songs[maxsongs];// songs[0] .. songs[nsongs-1] will point to actual songs
	nsongs = readSongs(songs, maxsongs);
	int num2sort = ac<2? nsongs: atoi(av[1]);
	bool showSort = ac>2;

	t0 = time(0);
	sort(songs,num2sort);
	t1 = time(0);
	cout << " sorting: " << num2sort << " songs in " << (t1-t0) << " seconds " << endl;

	if (showSort) {
		for (int i=0; i<5; i++) {cout << i << ": "; printSong(*songs[i]);}
		cout << "..." <<endl;
		for (int i=num2sort-5; i<num2sort; i++) {cout << i << ": "; printSong(*songs[i]);}
	}

	return 0;
}
