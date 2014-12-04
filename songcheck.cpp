#include <iostream>
#include <cstdlib>
#include <string>
#include "song.h"
#include <fstream>
using namespace std;

// need to add getline
int readSongs(song **songs, int const MAX, string file){

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
		song *songPtr = new song;
		*songPtr = construct;
		songs[i] = songPtr;
		i++;
		input >> title; 
	}
	
	input.close();
	return i;
}
string space2underscore(string text)
{
    for(int i = 0; i < text.length(); i++)
    {
        if(text[i] == ' ')
            text[i] = '_';
    }
    return text;
}
void printSongs(song **songs, int isongs){

	for(int i = 0; i < isongs; i++){
		cout << songs[i]->getTitle() << " " << songs[i]->getAlbum() << " " << songs[i]->getArtist() << endl;
}

	cout << "Number of song objects printed " << isongs << endl;


}

	void sortArtist(song **songs, int isongs){
	song *temp;
	for(int i = 0; i < isongs; i++){
		for (int j = i + 1; j < isongs; j++){	
			if(songs[i]->getArtist() > songs[j]->getArtist()){
				temp = songs[i];
				songs[i] = songs[j];
				songs[j] = temp;
			}
		}
	}

}

	void sortAlbum(song **songs, int isongs){
	song *temp;
	for(int i = 0; i < isongs; i++){
		for (int j = i + 1; j < isongs; j++){
		
			if(songs[i]->getAlbum() > songs[j]->getAlbum()){
				temp = songs[i];
				songs[i] = songs[j];
				songs[j] = temp;
			}
		}
	}
}
	void sortTitle(song **songs, int isongs){
	song *temp;
	for(int i = 0; i < isongs; i++){
		for (int j = i + 1; j < isongs; j++){
		
			if(songs[i]->getTitle() > songs[j]->getTitle()){
				temp = songs[i];
				songs[i] = songs[j];
				songs[j] = temp;
			}
		}
	}
}


int artistSearch(song **arr, int first, int last, string value){
	int middle;

	if(first > last)
		return -1;
	middle = (first + last) /2;
	if(arr[middle]->getArtist() == value)
		return middle;
	if(arr[middle]->getArtist() < value)
		return artistSearch(arr, middle+1,last,value);
	else
		return artistSearch(arr,first,middle-1,value);	
}

int albumSearch(song **arr, int first, int last, string value){
	int middle;

	if(first > last)
		return -1;
	middle = (first + last) /2;
	if(arr[middle]->getAlbum() == value)
		return middle;
	if(arr[middle]->getAlbum() < value)
		return albumSearch(arr, middle+1,last,value);
	else
		return albumSearch(arr,first,middle-1,value);	
}



int titleSearch(song **arr, int first, int last, string value){
	int middle;

	if(first > last)
		return -1;
	middle = (first + last) /2;
	if(arr[middle]->getTitle() == value)
		return middle;
	if(arr[middle]->getTitle() < value)
		return titleSearch(arr, middle+1,last,value);
	else
		return titleSearch(arr,first,middle-1,value);	
}

int main(int ac, char *av[]) {
	string file = av[1];	
	const int MAX = atoi(av[2]);	

	song **songTitle = new song* [MAX];
	song **songAlbum = new song* [MAX];
	song **songArtist = new song* [MAX];

	int iSongsTitle, iSongsAlbum, iSongsArtist = 0; 
	iSongsTitle = readSongs(songTitle, MAX, file);
	iSongsAlbum = readSongs(songAlbum, MAX, file);
	iSongsArtist = readSongs(songArtist, MAX, file);

	string input;

	cout << "Enter title for TITLE, album for ALBUM, or artist for ARTIST" << endl;
		
	cin >> input;


// This will find at most one element from the array that matches the search term
// How to get more and know you iterated over the entire data structure

	if(input == "album"){		
		int i = 1;
		sortAlbum(songAlbum,iSongsAlbum);
		printSongs(songAlbum,iSongsAlbum);
		cout << "Enter the name of the album you want..." << endl;
		string inputAlbum;
		getline(cin>>ws,inputAlbum);
	inputAlbum = space2underscore(inputAlbum);
	int albumElement  = albumSearch(songAlbum, 0, iSongsAlbum, inputAlbum);
	if(albumElement == -1){cout << "no such song" << endl;}
	else{
		int beginAlbumElement, endAlbumElement;
		beginAlbumElement = albumElement;
		endAlbumElement = albumElement;
		if(songAlbum[albumElement-i]->getAlbum() == songAlbum[albumElement]->getAlbum()){	
			while(songAlbum[albumElement-i]->getAlbum() == songAlbum[albumElement]->getAlbum()){
				i++;
				beginAlbumElement = albumElement-i;
				beginAlbumElement = beginAlbumElement+1;
			}
		}
		int n = 1;
		if(songAlbum[albumElement+n]->getAlbum() == songAlbum[albumElement]->getAlbum()){
			while(songAlbum[albumElement+n]->getAlbum() == songAlbum[albumElement]->getAlbum()){
				n++;
				endAlbumElement = albumElement+n;
				endAlbumElement = endAlbumElement-1;
			}
		}
		for(i = beginAlbumElement; i <= endAlbumElement; i++)
			cout << songAlbum[i]->getTitle() << " " << songAlbum[i]->getAlbum() << " " << songAlbum[i]->getArtist() << endl;		
		}		
	}

	if (input == "title"){
		int i = 1;
		sortTitle(songTitle,iSongsTitle);		
		printSongs(songTitle,iSongsTitle);
		cout << "Enter the TITLE of the song you want..." << endl;
		string inputTitle;	
		getline(cin>>ws,inputTitle);
		inputTitle = space2underscore(inputTitle);
		int titleElement = titleSearch(songTitle, 0, iSongsTitle, inputTitle);	
		if(titleElement == -1){cout << "no such song" << endl;}	
		else {
			int beginTitleElement, endTitleElement;
			beginTitleElement = titleElement;
			endTitleElement = titleElement;		
		if(songTitle[titleElement-i]->getTitle() == songTitle[titleElement]->getTitle()){	
			while(songTitle[titleElement-i]->getTitle() == songTitle[titleElement]->getTitle()){	
				i++;
				beginTitleElement = titleElement-i;
				beginTitleElement = beginTitleElement+1;
			}
		}
		int n = 1;
		if(songTitle[titleElement+n]->getTitle() == songTitle[titleElement]->getTitle()){
			while(songTitle[titleElement+n]->getTitle() == songTitle[titleElement]->getTitle()){
				n++;
				endTitleElement = titleElement+n;
				endTitleElement = endTitleElement-1;
		}	
	}	
		for(i = beginTitleElement; i <= endTitleElement; i++)
			cout << songTitle[i]->getTitle() << " " << songTitle[i]->getAlbum() << " " << songTitle[i]->getArtist() << endl;		
		}
	}

	if(input == "artist"){		
		int i = 1;
		sortArtist(songArtist,iSongsArtist);		
		printSongs(songArtist,iSongsArtist);
		cout << "Enter the ARTIST of the song you want..." << endl;
		string inputArtist;		
		inputArtist = space2underscore(inputArtist);
		getline(cin>>ws,inputArtist);
		int artistElement = artistSearch(songArtist, 0, iSongsArtist, inputArtist);	
		if(artistElement == -1){cout << "no such song" << endl;}	
		else {
			int beginArtistElement, endArtistElement;
			beginArtistElement = artistElement;
			endArtistElement = artistElement;		
		if(songArtist[artistElement-i]->getArtist() == songArtist[artistElement]->getArtist()){	
			while(songArtist[artistElement-i]->getArtist() == songArtist[artistElement]->getArtist()){	
				i++;
				beginArtistElement = artistElement-i;
				beginArtistElement = beginArtistElement+1;
			}
		}
		int n = 1;
		if(songArtist[artistElement+n]->getArtist() == songArtist[artistElement]->getArtist()){
			while(songArtist[artistElement+n]->getArtist() == songArtist[artistElement]->getArtist()){
				n++;
				endArtistElement = artistElement+n;
				endArtistElement = endArtistElement-1;
		}	
	}	
		for(i = beginArtistElement; i <= endArtistElement; i++)
			cout << songArtist[i]->getTitle() << " " << songArtist[i]->getAlbum() << " " << songArtist[i]->getArtist() << endl;		
		}
	}
	
	delete [] songTitle;
	delete [] songAlbum;
	delete [] songArtist;

	return 0;
}
