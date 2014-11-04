#ifndef SONG_H
#define SONG_H

#include <string>

class song {
    private:
	std::string	title, album, artist;
	int		year;
    public:
	song();
	song(std::string title, std::string album, std::string artist, int year);
	std::string getTitle();
	std::string getAlbum();
	std::string getArtist();
	int getYear();
	bool lesserTitle(song other);
	bool lesserAlbum(song other); 
	bool lesserArtist(song other);
};

#endif
