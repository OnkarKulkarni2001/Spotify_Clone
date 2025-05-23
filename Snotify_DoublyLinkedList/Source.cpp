#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include "cSnotify.h"

int main(int argc, char* argv) {
    // TESTING ----------------------------------------------------------------------------------------------------------------------------------------------------------------

    //std::string errorString;
    //cPersonGenerator personGenerator;
    //personGenerator.LoadCensusFiles("Popular Baby Names/names/yob1993.txt", "surnames/Names_2010Census.csv", "Street Names (San Francisco)/Street_Names.csv", errorString);
    //std::cout << "personGenerator.listBabies.getSize(): " << personGenerator.listBabies.getSize() << std::endl;

    //// Access the first baby
    //personGenerator.listBabies.moveToFirst();
    //std::cout << "personGenerator.listBabies.getAt(0): " << &(personGenerator.listBabies.getCurrent()) << std::endl;

    //// Access the second baby
    //personGenerator.listBabies.moveToFirst();
    //personGenerator.listBabies.moveNext(); // Move to the second element (index 1)
    //cPersonGenerator::sBaby babyPtr = personGenerator.listBabies.getCurrent();
    //std::cout << "babyPtr.babyName: " << babyPtr.babyName << std::endl;
    //std::cout << "babyPtr.babyGender: " << babyPtr.babyGender << std::endl;
    //std::cout << "babyPtr.babyNameFrequency: " << babyPtr.babyNameFrequency << std::endl;

    //// Access the first street
    //personGenerator.listStreets.moveToFirst();
    //cPersonGenerator::sStreet street = personGenerator.listStreets.getCurrent();
    //std::cout << "street.fullStreetName: " << street.fullStreetName << std::endl;
    //std::cout << "street.streetName: " << street.streetName << std::endl;
    //std::cout << "street.streetType: " << street.streetType << std::endl;
    //std::cout << "street.postDirection: " << street.postDirection << std::endl;

    //// Access the second surname
    //personGenerator.listSurnames.moveToFirst();
    //personGenerator.listSurnames.moveNext(); // Move to the second element (index 1)
    //cPersonGenerator::sSurname surname = personGenerator.listSurnames.getCurrent();
    //std::cout << "surname.name: " << surname.name << std::endl;
    //std::cout << "surname.rank: " << surname.rank << std::endl;
    //std::cout << "surname.count: " << surname.count << std::endl;
    //std::cout << "surname.prop100k: " << surname.prop100k << std::endl;
    //std::cout << "surname.cum_prop100k: " << surname.cum_prop100k << std::endl;
    //std::cout << "surname.pctwhite: " << surname.pctwhite << std::endl;
    //std::cout << "surname.pctblack: " << surname.pctblack << std::endl;
    //std::cout << "surname.pctapi: " << surname.pctapi << std::endl;
    //std::cout << "surname.pctaian: " << surname.pctaian << std::endl;
    //std::cout << "surname.pct2prace: " << surname.pct2prace << std::endl;
    //std::cout << "surname.pcthispanic: " << surname.pcthispanic << std::endl;

    //cMusicGenerator musicGenerator;
    //musicGenerator.LoadMusicInformation("billboard/kcmillersean-billboard-hot-100-1958-2017/data/hot_stuff_2.csv", errorString);
    //// Access the second song
    //musicGenerator.listSongs.moveToFirst();
    //musicGenerator.listSongs.moveNext(); // Move to the second element (index 1)
    //cSong song = musicGenerator.listSongs.getCurrent();
    //std::cout << "song.getUniqueID(): " << song.getUniqueID() << std::endl;
    //std::cout << "song.name: " << song.name << std::endl;
    //std::cout << "song.artist: " << song.artist << std::endl;

    //std::cout << "----------------------------random song below----------------------------" << std::endl;
    //song = *musicGenerator.getRandomSong();
    //std::cout << "randomsong.getUniqueID(): " << song.getUniqueID() << std::endl;
    //std::cout << "randomsong.name: " << song.name << std::endl;
    //std::cout << "randomsong.artist: " << song.artist << std::endl;

    //std::cout << "----------------------------finding specific song-------------------------" << std::endl;
    //if (musicGenerator.findSong("ATLiens", "OutKast")) {
    //    std::cout << "Found the song!" << std::endl;
    //}
    //else {
    //    std::cout << "Didn't find song" << std::endl;
    //}

    //cSnotify snotify;
    //std::cout << "\n\n--------------------------Testing AddUser(cPerson* pPerson, std::string& errorString) ---------------------------------------" << std::endl;
    //cPerson* randomPerson = new cPerson();
    //for (int i = 0; i < 100; i++) {
    //    randomPerson = personGenerator.generateRandomPerson();
    //    snotify.AddUser(randomPerson, errorString);
    //}

    //snotify.AddSong(&song, errorString);
    //snotify.AddSongToUserLibrary(randomPerson->getSnotifyUniqueUserID(), &song, errorString);
    //song = *musicGenerator.getRandomSong();
    //snotify.AddSong(&song, errorString);
    //snotify.AddSongToUserLibrary(randomPerson->getSnotifyUniqueUserID(), &song, errorString);
    //song = *musicGenerator.getRandomSong();
    //snotify.AddSong(&song, errorString);
    //snotify.AddSongToUserLibrary(randomPerson->getSnotifyUniqueUserID(), &song, errorString);

    //snotify.UpdateRatingOnSong(randomPerson->getSnotifyUniqueUserID(), song.getUniqueID(), 69);
    //cSong* retrievedSong = snotify.GetSong(randomPerson->getSnotifyUniqueUserID(), song.getUniqueID(), errorString);

    //std::cout << "retrievedSong->name: " << retrievedSong->name << " retrievedSong->artist: " << retrievedSong->artist << " retrievedSong->getUniqueID(): " << retrievedSong->getUniqueID() << std::endl;

    //unsigned int retrievedSongRating;
    //snotify.GetCurrentSongRating(randomPerson->getSnotifyUniqueUserID(), song.getUniqueID(), retrievedSongRating);

    //unsigned int retrievedNumberOfPlays;
    //snotify.GetCurrentSongNumberOfPlays(randomPerson->getSnotifyUniqueUserID(), song.getUniqueID(), retrievedNumberOfPlays);

    //cPerson* retrivedPersonUsingSIN = snotify.FindUserBySIN(randomPerson->SIN);

    //std::cout << "Name: " << retrivedPersonUsingSIN->first << " " << retrivedPersonUsingSIN->middle << " " << retrivedPersonUsingSIN->last << " retrivedPersonUsingSIN->SIN: " << retrivedPersonUsingSIN->SIN << " retrivedPersonUsingSIN->getSnotifyUniqueUserID(): " << retrivedPersonUsingSIN->getSnotifyUniqueUserID() << std::endl;

    //cPerson* retrievedPersonUsingSnotifyUID = snotify.FindUserBySnotifyID(randomPerson->getSnotifyUniqueUserID());

    //std::cout << "Name: " << retrievedPersonUsingSnotifyUID->first << " " << retrievedPersonUsingSnotifyUID->middle << " " << retrievedPersonUsingSnotifyUID->last << " retrievedPersonUsingSnotifyUID->SIN: " << retrievedPersonUsingSnotifyUID->SIN << " retrievedPersonUsingSnotifyUID->getSnotifyUniqueUserID(): " << retrievedPersonUsingSnotifyUID->getSnotifyUniqueUserID() << std::endl;

    //cSong* retrievedSongUsingTitleArtist = snotify.FindSong(song.name, song.artist);

    //std::cout << "retrievedSongUsingTitleArtist->name: " << retrievedSongUsingTitleArtist->name << " retrievedSongUsingTitleArtist->artist: " << retrievedSongUsingTitleArtist->artist << " retrievedSongUsingTitleArtist->getUniqueID(): " << retrievedSongUsingTitleArtist->getUniqueID() << std::endl;

    //cSong* retrievedSongUsingID = snotify.FindSong(song.getUniqueID());

    //std::cout << "retrievedSongUsingID->name: " << retrievedSongUsingID->name << " retrievedSongUsingID->artist: " << retrievedSongUsingID->artist << " retrievedSongUsingID->getUniqueID(): " << retrievedSongUsingID->getUniqueID() << std::endl;

    //unsigned int sizeOfLibrary;
    //cSong* pLibraryArray;
    //snotify.GetUsersSongLibrary(randomPerson->getSnotifyUniqueUserID(), pLibraryArray, sizeOfLibrary);

    //std::cout << "first: " << pLibraryArray[0].name << "\nsecond: " << pLibraryArray[1].name << "\nthird: " << pLibraryArray[2].name << std::endl;

    //snotify.GetUsersSongLibraryAscendingByTitle(randomPerson->getSnotifyUniqueUserID(), pLibraryArray, sizeOfLibrary);
    //std::cout << "AscendingByTitle\nfirst: " << pLibraryArray[0].name << "\nsecond: " << pLibraryArray[1].name << "\nthird: " << pLibraryArray[2].name << std::endl;

    //snotify.GetUsersSongLibraryAscendingByArtist(randomPerson->getSnotifyUniqueUserID(), pLibraryArray, sizeOfLibrary);
    //std::cout << "AscendingByArtist\nfirst: " << pLibraryArray[0].artist << "\nsecond: " << pLibraryArray[1].artist << "\nthird: " << pLibraryArray[2].artist << std::endl;

    //cPerson* pAllTheUsers;
    //unsigned int sizeOfUserArray;
    //snotify.GetUsers(pAllTheUsers, sizeOfUserArray);
    //for (unsigned int i = 0; i < sizeOfUserArray; i++) {
    //    std::cout << pAllTheUsers[i].first << " " << pAllTheUsers[i].middle << " " << pAllTheUsers[i].last << std::endl;
    //}
    //randomPerson->first = "Onkar";
    //snotify.UpdateUser(randomPerson, errorString);

    //snotify.GetUsersByID(pAllTheUsers, sizeOfUserArray);
    //for (unsigned int i = 0; i < sizeOfUserArray; i++) {
    //    std::cout << pAllTheUsers[i].getSnotifyUniqueUserID() << std::endl;
    //    std::cout << pAllTheUsers[i].first << " " << pAllTheUsers[i].middle << " " << pAllTheUsers[i].last << std::endl;
    //}

    //snotify.FindUsersFirstName("Jessica", pAllTheUsers, sizeOfUserArray);
    //for (unsigned int i = 0; i < sizeOfUserArray; i++) {
    //    std::cout << pAllTheUsers[i].getSnotifyUniqueUserID() << std::endl;
    //    std::cout << pAllTheUsers[i].first << " " << pAllTheUsers[i].middle << " " << pAllTheUsers[i].last << std::endl;
    //}

    //snotify.FindUsersLastName("JOHNSON", pAllTheUsers, sizeOfUserArray);
    //for (unsigned int i = 0; i < sizeOfUserArray; i++) {
    //    std::cout << pAllTheUsers[i].getSnotifyUniqueUserID() << std::endl;
    //    std::cout << pAllTheUsers[i].first << " " << pAllTheUsers[i].middle << " " << pAllTheUsers[i].last << std::endl;
    //}

    //snotify.FindUsersFirstLastNames("Meagan", "ROGERS", pAllTheUsers, sizeOfUserArray);
    //for (unsigned int i = 0; i < sizeOfUserArray; i++) {
    //    std::cout << pAllTheUsers[i].getSnotifyUniqueUserID() << std::endl;
    //    std::cout << pAllTheUsers[i].first << " " << pAllTheUsers[i].middle << " " << pAllTheUsers[i].last << std::endl;
    //}

    //delete[] pLibraryArray;
    //delete[] pAllTheUsers;

    return 0;
}