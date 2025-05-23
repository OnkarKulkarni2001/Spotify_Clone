#include "cMusicGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>

bool readCSVSongDataFile(std::string fileName, cVectainer<cSong>& vectainSongs);

cMusicGenerator::cMusicGenerator()
{
}

cMusicGenerator::~cMusicGenerator()
{
}

bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString)
{
	return readCSVSongDataFile(musicFileName, vectainSongs);
}

cSong* cMusicGenerator::getRandomSong(void)
{
	if (vectainSongs.getSize() == 0) return nullptr;
	int randomIndex = rand() % vectainSongs.getSize();
	return &vectainSongs.getAt(randomIndex);
}

cSong* cMusicGenerator::findSong(std::string songName, std::string artist)
{
	for (size_t i = 0; i < vectainSongs.getSize(); i++) {
		if (vectainSongs.getAt(i).name == songName && vectainSongs.getAt(i).artist == artist) {
			return &vectainSongs.getAt(i);
		}
	}
	return nullptr;
}

bool readCSVSongDataFile(std::string fileName, cVectainer<cSong>& vectainSongs)
{
	// Open the file
	std::ifstream songsFile(fileName);
	if (!songsFile.is_open())
	{
		std::cout << "Didn't open file" << std::endl;
		return false;
	}

	std::string theLine;
	cSong song;
	song.m_NEXT_Song_UniqueID = 10000000;

	unsigned int lineCount = 0;
	while (std::getline(songsFile, theLine))
	{
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 3)
			{
				song.name = token;
			}
			if (tokenCount == 4) {
				song.artist = token;
			}
			// Ignore the other parts of the line
			tokenCount++;
		}

		song.uniqueID = song.m_NEXT_Song_UniqueID;

		const unsigned int MAX_ID_INCREEMNT = 11;
		song.m_NEXT_Song_UniqueID += (rand() % MAX_ID_INCREEMNT);

		vectainSongs.addAtEnd(song);
	}


	vectainSongs.removeAt(0);		// removing headers --> url	weekid	week_position	song	performer	songid	instance	previous_week_position	peak_position	weeks_on_chart
	return true;
}