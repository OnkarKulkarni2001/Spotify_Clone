#include "cSong.h"

cSong::cSong(const cSong& other)
{
	this->uniqueID = other.uniqueID;
	this->artist = other.artist;
	this->name = other.name;
	this->numberOfTimesPlayed = other.numberOfTimesPlayed;
	this->rating = other.rating;
}

cSong& cSong::operator=(const cSong& other)
{
	if (this == &other) return *this; // Handle self-assignment

	// Copy all members here
	this->uniqueID = other.uniqueID;
	this->artist = other.artist;
	this->name = other.name;
	this->numberOfTimesPlayed = other.numberOfTimesPlayed;
	this->rating = other.rating;
	//this->age = other.age;
	// Copy any other members accordingly

	return *this;
}
