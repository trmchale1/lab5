#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "song.h"
using namespace std;

const int maxsongs=200000;

int readSongs(song songs[], int max) {
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
		song onesong(title,album,artist,year);
		songs[nsongs] = onesong;
		nsongs++;
		songinput >> title;
	}
	songinput.close();
	return nsongs;
}

int getIndexOfTitle(song songs[], int nsongs, string title) {
	for (int i=0; i<nsongs; i++)
		if (songs[i].getTitle()==title) return i;
	return -1;
}

int _getIndexOfTitleB(song songs[], int left, int right, string title) {
	int mid = (right+left)/2;
	int howMany = right-left+1;
	if (howMany<=3) {
		if (songs[right].getTitle()==title) return right;
		if (songs[mid].getTitle()==title) return mid;
		if (songs[left].getTitle()==title) return left;
		return -1;
	}
	if (title<songs[mid].getTitle())
		return _getIndexOfTitleB(songs, left, mid, title);
	if (title>songs[mid].getTitle())
		return _getIndexOfTitleB(songs, mid, right, title);
	return mid;
}

int getIndexOfTitleB(song songs[], int nsongs, string title) {
	return _getIndexOfTitleB(songs, 0, nsongs-1, title);
}


void printSong(song s) {
	cout << "[" << s.getTitle() << " recorded on " << s.getAlbum() << " by "
		<< s.getArtist() << " in " << s.getYear() << endl;
}

void sort(song songs[], int n) {
	for (int i=0; i<n-1; i++)
		for (int j=i+1;j<n; j++)
			if (songs[i].getTitle()>songs[j].getTitle()) {
				song stmp = songs[i];
				songs[i] = songs[j];
				songs[j] = stmp;
			}
}

int main(int ac, char *av[]) {
	int	t0,t1;		// timing is everything
	int	nsongs=0;	// # of songs
	song	songs[maxsongs];// songs[0] .. songs[n-1] have actual songs

	nsongs = readSongs(songs, maxsongs);
	string	badTitle="junk";
	int lookups = ac==1? 1 : atoi(av[1]);
	int num2sort = ac<3? nsongs: atoi(av[2]);

	t0 = time(0);
	sort(songs,num2sort);
	t1 = time(0);
	cout << " sorting: " << num2sort << " songs in " << (t1-t0) << " seconds " << endl;

//	t0 = time(0);
//	for (int j=0; j<lookups; j++)
//		int i = getIndexOfTitle(songs,nsongs,badTitle);
//	t1 = time(0);
//	cout << lookups << " sequential title searches: " << (t1-t0) << " seconds " << endl;
//
	t0 = time(0);
	for (int j=0; j<lookups; j++)
		int i = getIndexOfTitleB(songs,nsongs,badTitle);
	t1 = time(0);
	cout << lookups << " binary title searches: " << (t1-t0) << " seconds " << endl;

	return 0;
}
