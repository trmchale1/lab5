#include "song.h"
#include <string>
using namespace std;

	song::song(): title(""), album(""), artist(""), year(0){}
	song::song(string title, string album, string artist, int year):
		title(title), album(album), artist(artist), year(year) {}
	string song::getTitle() {return title;}
	string song::getAlbum() {return album;}
	string song::getArtist() {return artist;}
	int song::getYear() {return year;}
	bool song::lesserTitle(song other) {return title<other.title;}
	bool song::lesserAlbum(song other) {return album<other.album;}
	bool song::lesserArtist(song other) {return artist<other.artist;}


