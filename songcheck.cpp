#include <iostream>
#include <cstdlib>
#include <string>
#include "song.h"
#include <fstream>
using namespace std;

int readSongs(song *songs, int const MAX, string file){

	string title, album, artist;
	int year;
	int i =0;
	fstream input;
	input.open(file);

	if(input.fail()) throw string("cannot open songs.200000");
	
	input >> title;
	while(!input.fail() && i < MAX){

		input >> album;
		input >> artist;
		input >> year;
		song construct(title, album, artist, year);
		songs[i] = construct;
		i++;
		input >> title; 
	}
	
	input.close();
	return i;
}

void printSongs(song songs[], int isongs){

	for(int i = 0; i < isongs; i++){
		cout << songs[i].getTitle() << " " << songs[i].getAlbum() << " " << songs[i].getArtist() << endl;
}

	cout << "Number of song objects printed " << isongs << endl;


}

	void sortArtist(song songs[], int isongs){
	song temp;
	for(int i = 0; i < isongs; i++){
		for (int j = i + 1; j < isongs; j++){	
			if(songs[i].getArtist() > songs[j].getArtist()){
				temp = songs[i];
				songs[i] = songs[j];
				songs[j] = temp;
			}
		}
	}

}

	void sortAlbum(song songs[], int isongs){
	song temp;
	for(int i = 0; i < isongs; i++){
		for (int j = i + 1; j < isongs; j++){
		
			if(songs[i].getAlbum() > songs[j].getAlbum()){
				temp = songs[i];
				songs[i] = songs[j];
				songs[j] = temp;
			}
		}
	}
}
	void sortTitle(song songs[], int isongs){
	song temp;
	for(int i = 0; i < isongs; i++){
		for (int j = i + 1; j < isongs; j++){
		
			if(songs[i].getTitle() > songs[j].getTitle()){
				temp = songs[i];
				songs[i] = songs[j];
				songs[j] = temp;
			}
		}
	}
}


int artistSearch(song arr[], int first, int last, string value){
	int middle;

	if(first > last)
		return -1;
	middle = (first + last) /2;
	if(arr[middle].getArtist() == value)
		return middle;
	if(arr[middle].getArtist() < value)
		return artistSearch(arr, middle+1,last,value);
	else
		return artistSearch(arr,first,middle-1,value);	
}

int albumSearch(song arr[], int first, int last, string value){
	int middle;

	if(first > last)
		return -1;
	middle = (first + last) /2;
	if(arr[middle].getAlbum() == value)
		return middle;
	if(arr[middle].getAlbum() < value)
		return albumSearch(arr, middle+1,last,value);
	else
		return albumSearch(arr,first,middle-1,value);	
}



int titleSearch(song arr[], int first, int last, string value){
	int middle;

	if(first > last)
		return -1;
	middle = (first + last) /2;
	if(arr[middle].getTitle() == value)
		return middle;
	if(arr[middle].getTitle() < value)
		return titleSearch(arr, middle+1,last,value);
	else
		return titleSearch(arr,first,middle-1,value);	
}

int main(int ac, char *av[]) {
	string file = av[1];	
	const int MAX = atoi(av[2]);	

	song *songTitle = new song [MAX];
	song *songAlbum = new song [MAX];
	song *songArtist = new song [MAX];

	int iSongsTitle, iSongsAlbum, iSongsArtist = 0; 
	iSongsTitle = readSongs(songTitle, MAX, file);
	iSongsAlbum = readSongs(songAlbum, MAX, file);
	iSongsArtist = readSongs(songArtist, MAX, file);

	string input;


//	printSongs(songTitle,iSongsTitle);

//	printSongs(songAlbum,iSongsAlbum);

//	printSongs(songArtist,iSongsArtist);

	cout << "Enter t for TITLE, alb for ALBUM, or art for ARTIST" << endl;
		
	cin >> input;


// This will find at most one element from the array that matches the search term
// How to get more and know you iterated over the entire data structure


	if(input == "alb"){		
		sortAlbum(songAlbum,iSongsAlbum);
		cout << "Enter the name of the album you want..." << endl;
		string inputAlbum;
		cin >> inputAlbum;
		int albumElement  = albumSearch(songAlbum, 0, iSongsAlbum, inputAlbum);
		if(albumElement == -1){cout << "no such song" << endl;}	
	}

	if (input == "t"){
		sortTitle(songTitle,iSongsTitle);
		cout << "Enter the title of the song you want..." << endl;
		string inputTitle;
		cin >> inputTitle;
		int titleElement = titleSearch(songTitle, 0, iSongsTitle, inputTitle);	
		if(titleElement == -1){cout << "no such song" << endl;}	
	}

	if(input == "art"){
		sortArtist(songArtist,iSongsArtist);
		cout << "Enter the name of the artist you want..." << endl;
		string inputArtist;
		cin >> inputArtist;	
		int artistElement = albumSearch(songArtist, 0, iSongsArtist, inputArtist);	
		if(artistElement == -1){cout << "no such song" << endl;}	
	}
	
	delete [] songTitle;
	delete [] songAlbum;
	delete [] songArtist;

	return 0;
}
