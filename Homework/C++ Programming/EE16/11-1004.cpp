/* 1004 Representing a song with struct */

#include <string>

enum Category{
	CLASSICAL,
	POP,
	FOLK,
	ROCK,
	BLUES,
	NEWAGE
};

struct Time{
	int minutes;
	int seconds;
};

struct Song{
	std::string title;
	std::string album;
	std::string artist;
	Time playingTime;
	Category musicCategory;
};