#ifndef SONG_H
#define SONG_H
#include <string>

class song {
    private:
	std::string title, album, artist;
	int year;
    public:
	song();
	song(std::string, std::string, std::string, int);
	std::string getTitle();
	std::string getAlbum();
	std::string getArtist();
	int getYear();
	bool lesserTitle(song);
	bool lesserAlbum(song); 
	bool lesserArtist(song);
};

#endif
