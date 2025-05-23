#include "cSnotify.h"

// Compare function for sorting by song title (A-Z)
bool CompareSongsByTitle(const cSong& a, const cSong& b) {
	return a.name < b.name;  // Ascending order (A-Z)
}

// Compare function for sorting by artist name (A-Z)
bool CompareSongsByArtist(const cSong& a, const cSong& b) {
	return a.artist < b.artist;  // Ascending order (A-Z)
}

bool CompareUsersByID(cPerson* a, cPerson* b) {
	if (!a || !b) return false; // Prevent crashes
	return a->getSnotifyUniqueUserID() < b->getSnotifyUniqueUserID(); // Compare by user ID
}

bool CompareUsersByFirstName(const cPerson* a, const cPerson* b) {
	if (!a || !b) return false; // Prevent crashes
	return a->first < b->first; // Compare by user ID
}

bool CompareUsersByMiddleName(const cPerson* a, const cPerson* b) {
	if (!a || !b) return false; // Prevent crashes
	return a->middle < b->middle; // Compare by user ID
}


bool CompareUsersByLastName(cPerson* a, cPerson* b) {
	if (!a || !b) return false; // Prevent crashes
	return a->last < b->last; // Compare by user ID
}

cSnotify::cSnotify()
{
}

cSnotify::~cSnotify()
{
}

bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString)
{
	if (!pPerson) {
		errorString = "Invalid user pointer.";
		return false;
	}
	vectainUsers.addAtEnd(pPerson);
	return true;
}

bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{
	for (unsigned int i = 0; i < vectainUsers.getSize(); i++) {
		if (vectainUsers.getAt(i)->getSnotifyUniqueUserID() == pPerson->getSnotifyUniqueUserID() &&
			vectainUsers.getAt(i)->SIN == pPerson->SIN) {
			vectainUsers.getAt(i) = pPerson;
			return true;
		}
	}
	errorString = "User not found.";
	return false;
}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	for (unsigned int i = 0; i < vectainUsers.getSize(); i++) {
		if (vectainUsers.getAt(i)->getSnotifyUniqueUserID() == SnotifyUserID) {
			std::cout << "i: " << i << std::endl;
			vectainUsers.removeAt(i);
			return true;
		}
	}
	errorString = "User not found.";
	return false;
}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{
	if (!pSong) {
		errorString = "Invalid song pointer.";
		return false;
	}
	vectainSongs.addAtEnd(*pSong);
	return true;
}

bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString)
{
	for (unsigned int i = 0; i < vectainSongs.getSize(); i++) {
		if (vectainSongs.getAt(i).uniqueID == pSong->uniqueID) {
			vectainSongs.getAt(i) = *pSong;
			return true;
		}
	}
	errorString = "Song not found.";
	return false;
}

bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString)
{
	for (unsigned int i = 0; i < vectainSongs.getSize(); i++) {
		if (vectainSongs.getAt(i).getUniqueID() == UniqueSongID) {
			for (unsigned int j = 0; j < vectainUsers.getSize(); j++) {
				for (unsigned int k = 0; k < vectainUsers.getAt(j)->vectainSongLibrary.getSize(); k++) {
					if (vectainUsers.getAt(j)->vectainSongLibrary.getAt(k).getUniqueID() == vectainSongs.getAt(i).getUniqueID()) {
						vectainUsers.getAt(j)->vectainSongLibrary.removeAt(k);
					}
				}
			}
			vectainSongs.removeAt(i);
			std::cout << "vectainSongs.getAt(" << i << ")->name: " << vectainSongs.getAt(i).name << std::endl;
			return true;
		}
	}
	errorString = "Song not found.";
	return false;
}

bool cSnotify::AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString)
{
	if (pNewSong) {
		for (unsigned int i = 0; i < vectainUsers.getSize(); i++) {
			if (vectainUsers.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
				vectainUsers.getAt(i)->vectainSongLibrary.addAtEnd(*pNewSong);
				return true;
			}
		}
	}
	errorString = "User not found.";
	return false;
}

bool cSnotify::RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString)
{
	for (unsigned int i = 0; i < vectainUsers.getSize(); i++) {

		if (vectainUsers.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			for (unsigned int j = 0; j < vectainUsers.getAt(i)->vectainSongLibrary.getSize(); j++) {
				if (vectainUsers.getAt(i)->vectainSongLibrary.getAt(j).getUniqueID() == SnotifySongID) {
					vectainUsers.getAt(i)->vectainSongLibrary.removeAt(j);
					return true;
				}
			}
		}
	}
	errorString = "Song not found in user library.";
	return false;
}

bool cSnotify::UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating)
{
	for (unsigned int i = 0; i < vectainUsers.getSize(); i++) {

		if (vectainUsers.getAt(i)->getSnotifyUniqueUserID() == SnotifyUserID) {
			for (unsigned int j = 0; j < vectainUsers.getAt(i)->vectainSongLibrary.getSize(); j++) {
				if (vectainUsers.getAt(i)->vectainSongLibrary.getAt(j).getUniqueID() == songUniqueID) {
					vectainUsers.getAt(i)->vectainSongLibrary.getAt(j).rating = newRating;
					return true;
				}
			}
		}
	}
	return false;
}

cSong* cSnotify::GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString)
{
	for (unsigned int i = 0; i < vectainUsers.getSize(); i++) {

		if (vectainUsers.getAt(i)->getSnotifyUniqueUserID() == SnotifyUserID) {
			for (unsigned int j = 0; j < vectainUsers.getAt(i)->vectainSongLibrary.getSize(); j++) {
				if (vectainUsers.getAt(i)->vectainSongLibrary.getAt(j).getUniqueID() == songUniqueID) {
					return &vectainUsers.getAt(i)->vectainSongLibrary.getAt(j);
				}
			}
		}
	}
	errorString = "Song not found.";
	return nullptr;
}

bool cSnotify::GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& songRating)
{
	for (unsigned int i = 0; i < vectainUsers.getSize(); i++) {

		if (vectainUsers.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			for (unsigned int j = 0; j < vectainUsers.getAt(i)->vectainSongLibrary.getSize(); j++) {
				if (vectainUsers.getAt(i)->vectainSongLibrary.getAt(j).getUniqueID() == songUniqueID) {
					songRating = vectainUsers.getAt(i)->vectainSongLibrary.getAt(j).rating;
					return true;
				}
			}
		}
	}
	return false;
}

bool cSnotify::GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& numberOfPlays)
{
	for (unsigned int i = 0; i < vectainUsers.getSize(); i++) {

		if (vectainUsers.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			for (unsigned int j = 0; j < vectainUsers.getAt(i)->vectainSongLibrary.getSize(); j++) {
				if (vectainUsers.getAt(i)->vectainSongLibrary.getAt(j).getUniqueID() == songUniqueID) {
					numberOfPlays = vectainUsers.getAt(i)->vectainSongLibrary.getAt(j).numberOfTimesPlayed;
					return true;
				}
			}
		}
	}
	return false;
}

cPerson* cSnotify::FindUserBySIN(unsigned int SIN)
{
	for (unsigned int i = 0; i < vectainUsers.getSize(); ++i) {
		cPerson* user = vectainUsers.getAt(i);
		if (user->SIN == SIN) {
			return user;
		}
	}
	return nullptr;
}

cPerson* cSnotify::FindUserBySnotifyID(unsigned int SnotifyID)
{
	for (unsigned int i = 0; i < vectainUsers.getSize(); ++i) {
		cPerson* user = vectainUsers.getAt(i);
		if (user->getSnotifyUniqueUserID() == SnotifyID) {
			return user;
		}
	}
	return nullptr;
}

cSong* cSnotify::FindSong(std::string title, std::string artist)
{
	for (unsigned int i = 0; i < vectainSongs.getSize(); ++i) {
		cSong* song = &vectainSongs.getAt(i);
		if (song->name == title && song->artist == artist) {
			return song;
		}
	}
	return nullptr;
}

cSong* cSnotify::FindSong(unsigned int uniqueID)
{
	for (unsigned int i = 0; i < vectainSongs.getSize(); ++i) {
		cSong* song = &vectainSongs.getAt(i);
		if (song->getUniqueID() == uniqueID) {
			return song;
		}
	}
	return nullptr;
}

bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	// Find the user by SnotifyUserID
	cPerson* user = new cPerson();
	for (unsigned int i = 0; i < vectainUsers.getSize(); ++i) {
		if (vectainUsers.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			user = vectainUsers.getAt(i);
			break;
		}
	}

	if (!user) return false; // User not found

	// Copy the song library to pLibraryArray
	sizeOfLibary = user->vectainSongLibrary.getSize();
	pLibraryArray = new cSong[sizeOfLibary];
	for (unsigned int i = 0; i < sizeOfLibary; ++i) {
		pLibraryArray[i] = user->vectainSongLibrary.getAt(i);
	}

	return true;
}

bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	// Find the user by SnotifyUserID
	cPerson* user = nullptr;
	for (unsigned int i = 0; i < vectainUsers.getSize(); ++i) {
		if (vectainUsers.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			user = vectainUsers.getAt(i);
			break;
		}
	}

	if (!user) return false; // User not found

	// Sort the library by song title (ascending)
	user->vectainSongLibrary.sort(CompareSongsByTitle);

	// Copy the song library to pLibraryArray
	sizeOfLibary = user->vectainSongLibrary.getSize();
	pLibraryArray = new cSong[sizeOfLibary];
	for (unsigned int i = 0; i < sizeOfLibary; ++i) {
		pLibraryArray[i] = user->vectainSongLibrary.getAt(i);
	}

	return true;
}


bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	// Find the user by SnotifyUserID
	cPerson* user = nullptr;
	for (unsigned int i = 0; i < vectainUsers.getSize(); ++i) {
		if (vectainUsers.getAt(i)->getSnotifyUniqueUserID() == snotifyUserID) {
			user = vectainUsers.getAt(i);
			break;
		}
	}

	if (!user) return false; // User not found

	// Sort the library by song title (ascending)
	user->vectainSongLibrary.sort(CompareSongsByArtist);

	// Copy the song library to pLibraryArray
	sizeOfLibary = user->vectainSongLibrary.getSize();
	pLibraryArray = new cSong[sizeOfLibary];
	for (unsigned int i = 0; i < sizeOfLibary; ++i) {
		pLibraryArray[i] = user->vectainSongLibrary.getAt(i);
	}

	return true;
}


bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	if (!vectainUsers.isEmpty()) {
		sizeOfUserArray = vectainUsers.getSize();
		pAllTheUsers = new cPerson[sizeOfUserArray];
		for (unsigned int i = 0; i < sizeOfUserArray; ++i) {
			pAllTheUsers[i] = *vectainUsers.getAt(i);
		}
		return true;
	}
	return false;
}

bool cSnotify::GetUsersByID(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	if (!vectainUsers.isEmpty()) {
		vectainUsers.sort(CompareUsersByID);
		sizeOfUserArray = vectainUsers.getSize();
		pAllTheUsers = new cPerson[sizeOfUserArray];
		for (unsigned int i = 0; i < sizeOfUserArray; ++i) {
			pAllTheUsers[i] = *vectainUsers.getAt(i);
		}
		return true;
	}
	return false;
}

bool cSnotify::FindUsersFirstName(std::string firstName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	if (!vectainUsers.isEmpty()) {
		cVectainer<cPerson*> vectainFirstNameUsers;
		vectainUsers.sort(CompareUsersByLastName);
		for (unsigned int j = 0; j < vectainUsers.getSize(); j++) {
			if (vectainUsers.getAt(j)->first == firstName) {
				vectainFirstNameUsers.addAtEnd(vectainUsers.getAt(j));
			}
		}
		sizeOfUserArray = vectainFirstNameUsers.getSize();
		pAllTheUsers = new cPerson[sizeOfUserArray];
		for (unsigned int i = 0; i < sizeOfUserArray; ++i) {
			pAllTheUsers[i] = *vectainFirstNameUsers.getAt(i);
		}
		return true;
	}
	return false;
}

bool cSnotify::FindUsersLastName(std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	if (!vectainUsers.isEmpty()) {
		cVectainer<cPerson*> vectainLastNameUsers;
		vectainUsers.sort(CompareUsersByFirstName);
		for (unsigned int j = 0; j < vectainUsers.getSize(); j++) {
			if (vectainUsers.getAt(j)->last == lastName) {
				vectainLastNameUsers.addAtEnd(vectainUsers.getAt(j));
			}
		}
		sizeOfUserArray = vectainLastNameUsers.getSize();
		pAllTheUsers = new cPerson[sizeOfUserArray];
		for (unsigned int i = 0; i < sizeOfUserArray; ++i) {
			pAllTheUsers[i] = *vectainLastNameUsers.getAt(i);
		}
		return true;
	}
	return false;
}

bool cSnotify::FindUsersFirstLastNames(std::string firstName, std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	if (!vectainUsers.isEmpty()) {
		cVectainer<cPerson*> vectainLastNameUsers;
		for (unsigned int j = 0; j < vectainUsers.getSize(); j++) {
			if (vectainUsers.getAt(j)->last == lastName && vectainUsers.getAt(j)->first == firstName) {
				vectainLastNameUsers.addAtEnd(vectainUsers.getAt(j));
			}
		}
		vectainLastNameUsers.sort(CompareUsersByMiddleName);

		sizeOfUserArray = vectainLastNameUsers.getSize();
		pAllTheUsers = new cPerson[sizeOfUserArray];
		for (unsigned int i = 0; i < sizeOfUserArray; ++i) {
			pAllTheUsers[i] = *vectainLastNameUsers.getAt(i);
		}
		return true;
	}
	return false;
}