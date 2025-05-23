#include "cSong.h"

unsigned int cSong::m_NEXT_Song_UniqueID = 10000000; // Initialize the static member

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
    if (this == &other) return *this;

    this->uniqueID = other.uniqueID;
    this->artist = other.artist;
    this->name = other.name;
    this->numberOfTimesPlayed = other.numberOfTimesPlayed;
    this->rating = other.rating;

    return *this;
}