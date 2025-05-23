#include "cSnotify.h"

template <typename T, typename Compare>
void quickSort(T* arr, int low, int high, Compare compareFunc) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, compareFunc);
        quickSort(arr, low, pivotIndex - 1, compareFunc);
        quickSort(arr, pivotIndex + 1, high, compareFunc);
    }
}

template <typename T, typename Compare>
int partition(T* arr, int low, int high, Compare compareFunc) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compareFunc(arr[j], pivot)) {
            i++;
            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    T temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Compare function for sorting by song title (A-Z)
bool CompareSongsByTitle(const cSong& a, const cSong& b) {
    return a.name < b.name;  // Ascending order (A-Z)
}

// Compare function for sorting by artist name (A-Z)
bool CompareSongsByArtist(const cSong& a, const cSong& b) {
    return a.artist < b.artist;  // Ascending order (A-Z)
}

// Updated comparison functions to take cPerson objects instead of pointers
bool CompareUsersByID(const cPerson& a, const cPerson& b) {
    return a.getSnotifyUniqueUserID() < b.getSnotifyUniqueUserID(); // Compare by user ID
}

bool CompareUsersByFirstName(const cPerson& a, const cPerson& b) {
    return a.first < b.first; // Compare by first name
}

bool CompareUsersByMiddleName(const cPerson& a, const cPerson& b) {
    return a.middle < b.middle; // Compare by middle name
}

bool CompareUsersByLastName(const cPerson& a, const cPerson& b) {
    return a.last < b.last; // Compare by last name
}

cSnotify::cSnotify() {
}

cSnotify::~cSnotify() {
    // DLinkedList handles its own memory cleanup, but we need to delete the cPerson objects
    // since listUsers stores pointers to cPerson
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        listUsers.deleteAtCurrent();
        delete user; // Assuming cSnotify owns the cPerson objects
    }
}

bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString) {
    if (!pPerson) {
        errorString = "Invalid user pointer.";
        return false;
    }
    // Check if user already exists
    if (FindUserBySIN(pPerson->SIN) || FindUserBySnotifyID(pPerson->getSnotifyUniqueUserID())) {
        errorString = "User with this SIN or SnotifyID already exists.";
        return false;
    }
    listUsers.moveToLast(); // Add at the end
    listUsers.insertBeforeCurrent(pPerson);
    return true;
}

bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString) {
    if (!pPerson) {
        errorString = "Invalid user pointer.";
        return false;
    }
    if (listUsers.isEmpty()) {
        errorString = "User list is empty.";
        return false;
    }
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* currentUser = listUsers.getCurrent();
        if (currentUser->getSnotifyUniqueUserID() == pPerson->getSnotifyUniqueUserID() &&
            currentUser->SIN == pPerson->SIN) {
            listUsers.deleteAtCurrent();
            listUsers.insertBeforeCurrent(pPerson);
            //delete currentUser; // Free the old user
            return true;
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }
    errorString = "User not found.";
    return false;
}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString) {
    if (listUsers.isEmpty()) {
        errorString = "User list is empty.";
        return false;
    }
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* currentUser = listUsers.getCurrent();
        if (currentUser->getSnotifyUniqueUserID() == SnotifyUserID) {
            listUsers.deleteAtCurrent();
            delete currentUser; // Free the user
            return true;
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }
    errorString = "User not found.";
    return false;
}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString) {
    if (!pSong) {
        errorString = "Invalid song pointer.";
        return false;
    }
    // Check if song already exists
    if (FindSong(pSong->uniqueID)) {
        errorString = "Song with this unique ID already exists.";
        return false;
    }
    listSongs.moveToLast(); // Add at the end
    listSongs.insertBeforeCurrent(*pSong);
    return true;
}

bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString) {
    if (!pSong) {
        errorString = "Invalid song pointer.";
        return false;
    }
    if (listSongs.isEmpty()) {
        errorString = "Song list is empty.";
        return false;
    }
    listSongs.moveToFirst();
    for (unsigned int i = 0; i < listSongs.getSize(); i++) {
        cSong& currentSong = listSongs.getCurrent();
        if (currentSong.uniqueID == pSong->uniqueID) {
            listSongs.deleteAtCurrent();
            listSongs.insertBeforeCurrent(*pSong);
            return true;
        }
        if (i < listSongs.getSize() - 1) listSongs.moveNext();
    }
    errorString = "Song not found.";
    return false;
}

bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString) {
    // First, remove the song from all users' libraries
    if (!listUsers.isEmpty()) {
        listUsers.moveToFirst();
        for (unsigned int i = 0; i < listUsers.getSize(); i++) {
            cPerson* user = listUsers.getCurrent();
            if (!user->listSongLibrary.isEmpty()) {
                user->listSongLibrary.moveToFirst();
                for (unsigned int j = 0; j < user->listSongLibrary.getSize(); ) {
                    cSong& song = user->listSongLibrary.getCurrent();
                    if (song.getUniqueID() == UniqueSongID) {
                        user->listSongLibrary.deleteAtCurrent();
                    }
                    else {
                        j++;
                        if (j < user->listSongLibrary.getSize()) user->listSongLibrary.moveNext();
                    }
                }
            }
            if (i < listUsers.getSize() - 1) listUsers.moveNext();
        }
    }

    // Now delete the song from the main song list
    if (listSongs.isEmpty()) {
        errorString = "Song list is empty.";
        return false;
    }
    listSongs.moveToFirst();
    for (unsigned int i = 0; i < listSongs.getSize(); i++) {
        cSong& song = listSongs.getCurrent();
        if (song.getUniqueID() == UniqueSongID) {
            listSongs.deleteAtCurrent();
            return true;
        }
        if (i < listSongs.getSize() - 1) listSongs.moveNext();
    }
    errorString = "Song not found.";
    return false;
}

bool cSnotify::AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString) {
    if (!pNewSong) {
        errorString = "Invalid song pointer.";
        return false;
    }
    if (listUsers.isEmpty()) {
        errorString = "User list is empty.";
        return false;
    }
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        if (user->getSnotifyUniqueUserID() == snotifyUserID) {
            // Check if the song is already in the user's library
            if (!user->listSongLibrary.isEmpty()) {
                user->listSongLibrary.moveToFirst();
                for (unsigned int j = 0; j < user->listSongLibrary.getSize(); j++) {
                    if (user->listSongLibrary.getCurrent().getUniqueID() == pNewSong->getUniqueID()) {
                        std::cout << "Song " << pNewSong->name << " already exists in user " << snotifyUserID << "'s library.\n";
                        return true; // Song already exists
                    }
                    if (j < user->listSongLibrary.getSize() - 1) user->listSongLibrary.moveNext();
                }
            }
            user->listSongLibrary.moveToLast();
            user->listSongLibrary.insertBeforeCurrent(*pNewSong);
            std::cout << "Added song " << pNewSong->name << " by " << pNewSong->artist << " to user " << snotifyUserID << "'s library.\n";
            return true;
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }
    errorString = "User not found.";
    return false;
}

bool cSnotify::RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString) {
    if (listUsers.isEmpty()) {
        errorString = "User list is empty.";
        return false;
    }
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        if (user->getSnotifyUniqueUserID() == snotifyUserID) {
            if (user->listSongLibrary.isEmpty()) {
                errorString = "User's song library is empty.";
                return false;
            }
            user->listSongLibrary.moveToFirst();
            for (unsigned int j = 0; j < user->listSongLibrary.getSize(); ) {
                if (user->listSongLibrary.getCurrent().getUniqueID() == SnotifySongID) {
                    user->listSongLibrary.deleteAtCurrent();
                    return true;
                }
                else {
                    j++;
                    if (j < user->listSongLibrary.getSize()) user->listSongLibrary.moveNext();
                }
            }
            errorString = "Song not found in user library.";
            return false;
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }
    errorString = "User not found.";
    return false;
}

bool cSnotify::UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating) {
    if (listUsers.isEmpty()) return false;
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        if (user->getSnotifyUniqueUserID() == SnotifyUserID) {
            if (user->listSongLibrary.isEmpty()) return false;
            user->listSongLibrary.moveToFirst();
            for (unsigned int j = 0; j < user->listSongLibrary.getSize(); j++) {
                cSong& song = user->listSongLibrary.getCurrent();
                if (song.getUniqueID() == songUniqueID) {
                    song.rating = newRating;
                    return true;
                }
                if (j < user->listSongLibrary.getSize() - 1) user->listSongLibrary.moveNext();
            }
            return false;
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }
    return false;
}

cSong* cSnotify::GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString) {
    if (listUsers.isEmpty()) {
        errorString = "User list is empty.";
        return nullptr;
    }
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        if (user->getSnotifyUniqueUserID() == SnotifyUserID) {
            if (user->listSongLibrary.isEmpty()) {
                errorString = "User's song library is empty.";
                return nullptr;
            }
            user->listSongLibrary.moveToFirst();
            for (unsigned int j = 0; j < user->listSongLibrary.getSize(); j++) {
                cSong& song = user->listSongLibrary.getCurrent();
                if (song.getUniqueID() == songUniqueID) {
                    song.numberOfTimesPlayed++; // Increment play count
                    return &song;
                }
                if (j < user->listSongLibrary.getSize() - 1) user->listSongLibrary.moveNext();
            }
            errorString = "Song not found in user library.";
            return nullptr;
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }
    errorString = "User not found.";
    return nullptr;
}

bool cSnotify::GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& songRating) {
    if (listUsers.isEmpty()) return false;
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        if (user->getSnotifyUniqueUserID() == snotifyUserID) {
            if (user->listSongLibrary.isEmpty()) return false;
            user->listSongLibrary.moveToFirst();
            for (unsigned int j = 0; j < user->listSongLibrary.getSize(); j++) {
                cSong& song = user->listSongLibrary.getCurrent();
                if (song.getUniqueID() == songUniqueID) {
                    songRating = song.rating;
                    return true;
                }
                if (j < user->listSongLibrary.getSize() - 1) user->listSongLibrary.moveNext();
            }
            return false;
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }
    return false;
}

bool cSnotify::GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& numberOfPlays) {
    if (listUsers.isEmpty()) return false;
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        if (user->getSnotifyUniqueUserID() == snotifyUserID) {
            if (user->listSongLibrary.isEmpty()) return false;
            user->listSongLibrary.moveToFirst();
            for (unsigned int j = 0; j < user->listSongLibrary.getSize(); j++) {
                cSong& song = user->listSongLibrary.getCurrent();
                if (song.getUniqueID() == songUniqueID) {
                    numberOfPlays = song.numberOfTimesPlayed;
                    return true;
                }
                if (j < user->listSongLibrary.getSize() - 1) user->listSongLibrary.moveNext();
            }
            return false;
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }
    return false;
}

cPerson* cSnotify::FindUserBySIN(unsigned int SIN) {
    if (listUsers.isEmpty()) return nullptr;
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        if (user->SIN == SIN) {
            return user;
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }
    return nullptr;
}

cPerson* cSnotify::FindUserBySnotifyID(unsigned int SnotifyID) {
    if (listUsers.isEmpty()) return nullptr;
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        if (user->getSnotifyUniqueUserID() == SnotifyID) {
            return user;
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }
    return nullptr;
}

cSong* cSnotify::FindSong(std::string title, std::string artist) {
    if (listSongs.isEmpty()) return nullptr;
    listSongs.moveToFirst();
    for (unsigned int i = 0; i < listSongs.getSize(); i++) {
        cSong& song = listSongs.getCurrent();
        if (song.name == title && song.artist == artist) {
            return &song;
        }
        if (i < listSongs.getSize() - 1) listSongs.moveNext();
    }
    return nullptr;
}

cSong* cSnotify::FindSong(unsigned int uniqueID) {
    if (listSongs.isEmpty()) return nullptr;
    listSongs.moveToFirst();
    for (unsigned int i = 0; i < listSongs.getSize(); i++) {
        cSong& song = listSongs.getCurrent();
        if (song.getUniqueID() == uniqueID) {
            return &song;
        }
        if (i < listSongs.getSize() - 1) listSongs.moveNext();
    }
    return nullptr;
}

bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibrary) {
    cPerson* user = FindUserBySnotifyID(snotifyUserID);
    if (!user) {
        std::cout << "User with SnotifyID " << snotifyUserID << " not found.\n";
        return false;
    }

    sizeOfLibrary = user->listSongLibrary.getSize();
    std::cout << "User " << snotifyUserID << " has " << sizeOfLibrary << " songs in their library.\n";

    if (sizeOfLibrary == 0) {
        pLibraryArray = nullptr;
        return true;
    }

    if (user->listSongLibrary.isEmpty()) {
        std::cout << "Warning: listSongLibrary is empty despite size being " << sizeOfLibrary << ".\n";
        pLibraryArray = nullptr;
        sizeOfLibrary = 0;
        return true;
    }

    pLibraryArray = new cSong[sizeOfLibrary];
    std::cout << "Allocated array for " << sizeOfLibrary << " songs.\n";

    user->listSongLibrary.moveToFirst();
    std::cout << "Moved to first element.\n";

    for (unsigned int i = 0; i < sizeOfLibrary; i++) {
        cSong currentSong = user->listSongLibrary.getCurrent();
        pLibraryArray[i] = currentSong;
        std::cout << "Copied song " << i << ": " << currentSong.name << " by " << currentSong.artist << " (ID: " << currentSong.getUniqueID() << ")\n";
        if (i < sizeOfLibrary - 1) {
            user->listSongLibrary.moveNext();
            std::cout << "Moved to next element.\n";
        }
    }

    std::cout << "Successfully copied " << sizeOfLibrary << " songs.\n";
    return true;
}

//bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibrary) {
//    cPerson* user = FindUserBySnotifyID(snotifyUserID);
//    if (!user) return false; // User not found
//
//    sizeOfLibrary = user->listSongLibrary.getSize();
//    if (sizeOfLibrary == 0) {
//        pLibraryArray = nullptr;
//        return true;
//    }
//
//    // Copy the song library to an array for sorting
//    pLibraryArray = new cSong[sizeOfLibrary];
//    user->listSongLibrary.moveToFirst();
//    for (unsigned int i = 0; i < sizeOfLibrary; i++) {
//        pLibraryArray[i] = user->listSongLibrary.getCurrent();
//        if (i < sizeOfLibrary - 1) user->listSongLibrary.moveNext();
//    }
//
//    // Sort the array by title
//    std::sort(pLibraryArray, pLibraryArray + sizeOfLibrary, CompareSongsByTitle);
//    return true;
//}
//
//bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibrary) {
//    cPerson* user = FindUserBySnotifyID(snotifyUserID);
//    if (!user) return false; // User not found
//
//    sizeOfLibrary = user->listSongLibrary.getSize();
//    if (sizeOfLibrary == 0) {
//        pLibraryArray = nullptr;
//        return true;
//    }
//
//    // Copy the song library to an array for sorting
//    pLibraryArray = new cSong[sizeOfLibrary];
//    user->listSongLibrary.moveToFirst();
//    for (unsigned int i = 0; i < sizeOfLibrary; i++) {
//        pLibraryArray[i] = user->listSongLibrary.getCurrent();
//        if (i < sizeOfLibrary - 1) user->listSongLibrary.moveNext();
//    }
//
//    // Sort the array by artist
//    std::sort(pLibraryArray, pLibraryArray + sizeOfLibrary, CompareSongsByArtist);
//    return true;
//}
//
//bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
//    if (listUsers.isEmpty()) {
//        pAllTheUsers = nullptr;
//        sizeOfUserArray = 0;
//        return false;
//    }
//
//    sizeOfUserArray = listUsers.getSize();
//    pAllTheUsers = new cPerson[sizeOfUserArray];
//    listUsers.moveToFirst();
//    for (unsigned int i = 0; i < sizeOfUserArray; i++) {
//        pAllTheUsers[i] = *listUsers.getCurrent();
//        if (i < sizeOfUserArray - 1) listUsers.moveNext();
//    }
//    return true;
//}
//
//bool cSnotify::GetUsersByID(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
//    if (listUsers.isEmpty()) {
//        pAllTheUsers = nullptr;
//        sizeOfUserArray = 0;
//        return false;
//    }
//
//    sizeOfUserArray = listUsers.getSize();
//    pAllTheUsers = new cPerson[sizeOfUserArray];
//    listUsers.moveToFirst();
//    for (unsigned int i = 0; i < sizeOfUserArray; i++) {
//        pAllTheUsers[i] = *listUsers.getCurrent();
//        if (i < sizeOfUserArray - 1) listUsers.moveNext();
//    }
//
//    // Sort the array by SnotifyID
//    std::sort(pAllTheUsers, pAllTheUsers + sizeOfUserArray, CompareUsersByID);
//    return true;
//}
//
//bool cSnotify::FindUsersFirstName(std::string firstName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
//    if (listUsers.isEmpty()) {
//        pAllTheUsers = nullptr;
//        sizeOfUserArray = 0;
//        return false;
//    }
//
//    // Collect matching users
//    DLinkedList<cPerson*> matchingUsers;
//    listUsers.moveToFirst();
//    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
//        cPerson* user = listUsers.getCurrent();
//        if (user->first == firstName) {
//            matchingUsers.moveToLast();
//            matchingUsers.insertBeforeCurrent(user);
//        }
//        if (i < listUsers.getSize() - 1) listUsers.moveNext();
//    }
//
//    sizeOfUserArray = matchingUsers.getSize();
//    if (sizeOfUserArray == 0) {
//        pAllTheUsers = nullptr;
//        return false;
//    }
//
//    pAllTheUsers = new cPerson[sizeOfUserArray];
//    matchingUsers.moveToFirst();
//    for (unsigned int i = 0; i < sizeOfUserArray; i++) {
//        pAllTheUsers[i] = *matchingUsers.getCurrent();
//        if (i < sizeOfUserArray - 1) matchingUsers.moveNext();
//    }
//
//    // Sort by first name
//    std::sort(pAllTheUsers, pAllTheUsers + sizeOfUserArray, CompareUsersByFirstName);
//    return true;
//}
//
//bool cSnotify::FindUsersLastName(std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
//    if (listUsers.isEmpty()) {
//        pAllTheUsers = nullptr;
//        sizeOfUserArray = 0;
//        return false;
//    }
//
//    // Collect matching users
//    DLinkedList<cPerson*> matchingUsers;
//    listUsers.moveToFirst();
//    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
//        cPerson* user = listUsers.getCurrent();
//        if (user->last == lastName) {
//            matchingUsers.moveToLast();
//            matchingUsers.insertBeforeCurrent(user);
//        }
//        if (i < listUsers.getSize() - 1) listUsers.moveNext();
//    }
//
//    sizeOfUserArray = matchingUsers.getSize();
//    if (sizeOfUserArray == 0) {
//        pAllTheUsers = nullptr;
//        return false;
//    }
//
//    pAllTheUsers = new cPerson[sizeOfUserArray];
//    matchingUsers.moveToFirst();
//    for (unsigned int i = 0; i < sizeOfUserArray; i++) {
//        pAllTheUsers[i] = *matchingUsers.getCurrent();
//        if (i < sizeOfUserArray - 1) matchingUsers.moveNext();
//    }
//
//    // Sort by last name
//    std::sort(pAllTheUsers, pAllTheUsers + sizeOfUserArray, CompareUsersByLastName);
//    return true;
//}
//
//bool cSnotify::FindUsersFirstLastNames(std::string firstName, std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
//    if (listUsers.isEmpty()) {
//        pAllTheUsers = nullptr;
//        sizeOfUserArray = 0;
//        return false;
//    }
//
//    // Collect matching users
//    DLinkedList<cPerson*> matchingUsers;
//    listUsers.moveToFirst();
//    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
//        cPerson* user = listUsers.getCurrent();
//        if (user->first == firstName && user->last == lastName) {
//            matchingUsers.moveToLast();
//            matchingUsers.insertBeforeCurrent(user);
//        }
//        if (i < listUsers.getSize() - 1) listUsers.moveNext();
//    }
//
//    sizeOfUserArray = matchingUsers.getSize();
//    if (sizeOfUserArray == 0) {
//        pAllTheUsers = nullptr;
//        return false;
//    }
//
//    pAllTheUsers = new cPerson[sizeOfUserArray];
//    matchingUsers.moveToFirst();
//    for (unsigned int i = 0; i < sizeOfUserArray; i++) {
//        pAllTheUsers[i] = *matchingUsers.getCurrent();
//        if (i < sizeOfUserArray - 1) matchingUsers.moveNext();
//    }
//
//    // Sort by last name, then first name
//    std::sort(pAllTheUsers, pAllTheUsers + sizeOfUserArray, [](cPerson a, cPerson b) {
//        if (a.last == b.last) return a.first < b.first;
//        return a.last < b.last;
//        });
//    return true;
//}
bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibrary) {
    cPerson* user = FindUserBySnotifyID(snotifyUserID);
    if (!user) return false;

    sizeOfLibrary = user->listSongLibrary.getSize();
    if (sizeOfLibrary == 0) {
        pLibraryArray = nullptr;
        return true;
    }

    pLibraryArray = new cSong[sizeOfLibrary];
    user->listSongLibrary.moveToFirst();
    for (unsigned int i = 0; i < sizeOfLibrary; i++) {
        pLibraryArray[i] = user->listSongLibrary.getCurrent();
        if (i < sizeOfLibrary - 1) user->listSongLibrary.moveNext();
    }

    quickSort(pLibraryArray, 0, sizeOfLibrary - 1, CompareSongsByTitle);
    return true;
}

bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibrary) {
    cPerson* user = FindUserBySnotifyID(snotifyUserID);
    if (!user) return false;

    sizeOfLibrary = user->listSongLibrary.getSize();
    if (sizeOfLibrary == 0) {
        pLibraryArray = nullptr;
        return true;
    }

    pLibraryArray = new cSong[sizeOfLibrary];
    user->listSongLibrary.moveToFirst();
    for (unsigned int i = 0; i < sizeOfLibrary; i++) {
        pLibraryArray[i] = user->listSongLibrary.getCurrent();
        if (i < sizeOfLibrary - 1) user->listSongLibrary.moveNext();
    }

    quickSort(pLibraryArray, 0, sizeOfLibrary - 1, CompareSongsByArtist);
    return true;
}

bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
    if (listUsers.isEmpty()) {
        pAllTheUsers = nullptr;
        sizeOfUserArray = 0;
        return false;
    }

    sizeOfUserArray = listUsers.getSize();
    pAllTheUsers = new cPerson[sizeOfUserArray];
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < sizeOfUserArray; i++) {
        pAllTheUsers[i] = *listUsers.getCurrent();
        if (i < sizeOfUserArray - 1) listUsers.moveNext();
    }
    return true;  // Note: This function wasn't sorted originally
}

bool cSnotify::GetUsersByID(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
    if (listUsers.isEmpty()) {
        pAllTheUsers = nullptr;
        sizeOfUserArray = 0;
        return false;
    }

    sizeOfUserArray = listUsers.getSize();
    pAllTheUsers = new cPerson[sizeOfUserArray];
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < sizeOfUserArray; i++) {
        pAllTheUsers[i] = *listUsers.getCurrent();
        if (i < sizeOfUserArray - 1) listUsers.moveNext();
    }

    quickSort(pAllTheUsers, 0, sizeOfUserArray - 1, CompareUsersByID);
    return true;
}

bool cSnotify::FindUsersFirstName(std::string firstName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
    if (listUsers.isEmpty()) {
        pAllTheUsers = nullptr;
        sizeOfUserArray = 0;
        return false;
    }

    DLinkedList<cPerson*> matchingUsers;
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        if (user->first == firstName) {
            matchingUsers.moveToLast();
            matchingUsers.insertBeforeCurrent(user);
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }

    sizeOfUserArray = matchingUsers.getSize();
    if (sizeOfUserArray == 0) {
        pAllTheUsers = nullptr;
        return false;
    }

    pAllTheUsers = new cPerson[sizeOfUserArray];
    matchingUsers.moveToFirst();
    for (unsigned int i = 0; i < sizeOfUserArray; i++) {
        pAllTheUsers[i] = *matchingUsers.getCurrent();
        if (i < sizeOfUserArray - 1) matchingUsers.moveNext();
    }

    quickSort(pAllTheUsers, 0, sizeOfUserArray - 1, CompareUsersByFirstName);
    return true;
}

bool cSnotify::FindUsersLastName(std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
    if (listUsers.isEmpty()) {
        pAllTheUsers = nullptr;
        sizeOfUserArray = 0;
        return false;
    }

    DLinkedList<cPerson*> matchingUsers;
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        if (user->last == lastName) {
            matchingUsers.moveToLast();
            matchingUsers.insertBeforeCurrent(user);
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }

    sizeOfUserArray = matchingUsers.getSize();
    if (sizeOfUserArray == 0) {
        pAllTheUsers = nullptr;
        return false;
    }

    pAllTheUsers = new cPerson[sizeOfUserArray];
    matchingUsers.moveToFirst();
    for (unsigned int i = 0; i < sizeOfUserArray; i++) {
        pAllTheUsers[i] = *matchingUsers.getCurrent();
        if (i < sizeOfUserArray - 1) matchingUsers.moveNext();
    }

    quickSort(pAllTheUsers, 0, sizeOfUserArray - 1, CompareUsersByLastName);
    return true;
}

bool cSnotify::FindUsersFirstLastNames(std::string firstName, std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray) {
    if (listUsers.isEmpty()) {
        pAllTheUsers = nullptr;
        sizeOfUserArray = 0;
        return false;
    }

    DLinkedList<cPerson*> matchingUsers;
    listUsers.moveToFirst();
    for (unsigned int i = 0; i < listUsers.getSize(); i++) {
        cPerson* user = listUsers.getCurrent();
        if (user->first == firstName && user->last == lastName) {
            matchingUsers.moveToLast();
            matchingUsers.insertBeforeCurrent(user);
        }
        if (i < listUsers.getSize() - 1) listUsers.moveNext();
    }

    sizeOfUserArray = matchingUsers.getSize();
    if (sizeOfUserArray == 0) {
        pAllTheUsers = nullptr;
        return false;
    }

    pAllTheUsers = new cPerson[sizeOfUserArray];
    matchingUsers.moveToFirst();
    for (unsigned int i = 0; i < sizeOfUserArray; i++) {
        pAllTheUsers[i] = *matchingUsers.getCurrent();
        if (i < sizeOfUserArray - 1) matchingUsers.moveNext();
    }

    quickSort(pAllTheUsers, 0, sizeOfUserArray - 1,
        [](const cPerson& a, const cPerson& b) {
            if (a.last == b.last) return a.first < b.first;
            return a.last < b.last;
        });
    return true;
}