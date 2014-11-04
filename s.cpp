#include <iostream>
#include <cstdlib>
#include "song.h"
#include <fstream>
using namespace std;

int main(int ac, char *av[]) {
	const int MAX = atoi(av[2]);	
	int x = 0;
	song s[MAX];
	ifstream in;
	in.open(av[1]);
	in >> s[0];
//	while(x < MAX){
//	input >> song[x];
//	x++;
//	}
//	string title = song[0].getTitle();
//	cout << title;
	return 0;
}
