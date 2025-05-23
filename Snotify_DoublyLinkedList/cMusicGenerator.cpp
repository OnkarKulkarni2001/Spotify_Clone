#include "cMusicGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>      // String Stream
#include <string>

// Updated function signature to use DLinkedList
bool readCSVSongDataFile(std::string fileName, DLinkedList<cSong>& listSongs);

cMusicGenerator::cMusicGenerator()
{
}

cMusicGenerator::~cMusicGenerator()
{

}

bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString)
{
    if (!readCSVSongDataFile(musicFileName, listSongs)) {
        errorString = "Failed to load music file: " + musicFileName;
        return false;
    }
    return true;
}

cSong* cMusicGenerator::getRandomSong(void)
{
    if (listSongs.isEmpty()) return nullptr;
    unsigned int randomIndex = rand() % listSongs.getSize();
    listSongs.moveToFirst();
    for (unsigned int i = 0; i < randomIndex; i++) {
        listSongs.moveNext();
    }
    return &(listSongs.getCurrent());
}

cSong* cMusicGenerator::findSong(std::string songName, std::string artist)
{
    listSongs.moveToFirst();
    for (unsigned int i = 0; i < listSongs.getSize(); i++) {
        cSong& song = listSongs.getCurrent();
        if (song.name == songName && song.artist == artist) {
            return &song;
        }
        if (i < listSongs.getSize() - 1) listSongs.moveNext();
    }
    return nullptr;
}

bool readCSVSongDataFile(std::string fileName, DLinkedList<cSong>& listSongs)
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

        const unsigned int MAX_ID_INCREMENT = 11;
        song.m_NEXT_Song_UniqueID += (rand() % MAX_ID_INCREMENT);

        listSongs.moveToLast();
        listSongs.insertBeforeCurrent(song);
    }
    songsFile.close();

    // Remove the header (first element)
    if (!listSongs.isEmpty()) {
        listSongs.moveToFirst();
        listSongs.deleteAtCurrent();
    }
    return true;
}