#include "cPersonGenerator.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

#include <iostream>
#include <fstream>
#include <sstream>      // String Stream
#include <string>

// Updated function signatures to use DLinkedList
bool readCSVStreetNameFile(std::string fileName, DLinkedList<cPersonGenerator::sStreet>& listStreets);
bool readCSVSurnameFile(std::string fileName, DLinkedList<cPersonGenerator::sSurname>& listSurnames);

// Function to select a name based on frequency
std::string selectFirstNameByFrequency(DLinkedList<cPersonGenerator::sBaby>& list) {
    int totalFrequency = 0;
    if (list.isEmpty()) return "";

    // Calculate total frequency
    list.moveToFirst();
    for (unsigned int i = 0; i < list.getSize(); i++) {
        totalFrequency += list.getCurrent().babyNameFrequency;
        if (i < list.getSize() - 1) list.moveNext();
    }

    int randVal = static_cast<double>(rand()) / RAND_MAX * totalFrequency;
    int cumulativeFreq = 0;

    list.moveToFirst();
    for (unsigned int i = 0; i < list.getSize(); i++) {
        cumulativeFreq += list.getCurrent().babyNameFrequency;
        if (randVal < cumulativeFreq) {
            return list.getCurrent().babyName;
        }
        if (i < list.getSize() - 1) list.moveNext();
    }
    return ""; // Fallback (should never happen)
}

std::string selectMiddleNameByFrequency(DLinkedList<cPersonGenerator::sBaby>& list) {
    int totalFrequency = 0;
    if (list.isEmpty()) return "";

    // Calculate total frequency for male names
    list.moveToFirst();
    for (unsigned int i = 0; i < list.getSize(); i++) {
        if (list.getCurrent().babyGender == "M") {
            totalFrequency += list.getCurrent().babyNameFrequency;
        }
        if (i < list.getSize() - 1) list.moveNext();
    }

    int randVal = static_cast<double>(rand()) / RAND_MAX * totalFrequency;
    int cumulativeFreq = 0;

    list.moveToFirst();
    for (unsigned int i = 0; i < list.getSize(); i++) {
        if (list.getCurrent().babyGender == "M") {
            cumulativeFreq += list.getCurrent().babyNameFrequency;
            if (randVal < cumulativeFreq) {
                return list.getCurrent().babyName;
            }
        }
        if (i < list.getSize() - 1) list.moveNext();
    }
    return ""; // Fallback (should never happen)
}

std::string selectLastNameByFrequency(DLinkedList<cPersonGenerator::sSurname>& list) {
    if (list.isEmpty()) return "";

    // Calculate the total probability (sum of prop100k values)
    double totalProbability = 0.0;
    list.moveToFirst();
    for (unsigned int i = 0; i < list.getSize(); i++) {
        totalProbability += list.getCurrent().prop100k;
        if (i < list.getSize() - 1) list.moveNext();
    }

    // Generate a random number in the range [0, totalProbability)
    double randVal = static_cast<double>(rand()) / RAND_MAX * totalProbability;

    double cumulativeFreq = 0.0;

    // Select the last name based on cumulative probability
    list.moveToFirst();
    for (unsigned int i = 0; i < list.getSize(); i++) {
        cumulativeFreq += list.getCurrent().prop100k;
        if (randVal < cumulativeFreq) {
            return list.getCurrent().name;
        }
        if (i < list.getSize() - 1) list.moveNext();
    }

    return ""; // Fallback (should never happen)
}

// Function to generate random city
std::string generateRandomCity(DLinkedList<std::string>& cities) {
    if (cities.isEmpty()) return "";
    unsigned int index = rand() % cities.getSize();
    cities.moveToFirst();
    for (unsigned int i = 0; i < index; i++) {
        cities.moveNext();
    }
    return cities.getCurrent();
}

// Function to generate random province
std::string generateRandomProvince(DLinkedList<std::string>& provinces) {
    if (provinces.isEmpty()) return "";
    unsigned int index = rand() % provinces.getSize();
    provinces.moveToFirst();
    for (unsigned int i = 0; i < index; i++) {
        provinces.moveNext();
    }
    return provinces.getCurrent();
}

// Function to generate random postal code
char* generateRandomPostalCode() {
    static char postalCode[6];  // Canadian postal code length (6 characters, no null terminator)
    const std::string letters = "ABCDEGHJKLMNPRSTVWXYZ";  // Excluding restricted letters
    const std::string digits = "0123456789";

    // Generate the pattern "A1A 1A1"
    postalCode[0] = letters[rand() % letters.size()];
    postalCode[1] = digits[rand() % digits.size()];
    postalCode[2] = letters[rand() % letters.size()];
    postalCode[3] = digits[rand() % digits.size()];
    postalCode[4] = letters[rand() % letters.size()];
    postalCode[5] = digits[rand() % digits.size()];

    return postalCode;
}

cPersonGenerator::cPersonGenerator() {
    // Initialize city and province lists using DLinkedList
    ontarioCities.moveToLast();
    ontarioCities.insertBeforeCurrent("Toronto");
    ontarioCities.moveToLast();
    ontarioCities.insertBeforeCurrent("Ottawa");
    ontarioCities.moveToLast();
    ontarioCities.insertBeforeCurrent("Hamilton");
    ontarioCities.moveToLast();
    ontarioCities.insertBeforeCurrent("London");
    ontarioCities.moveToLast();
    ontarioCities.insertBeforeCurrent("Mississauga");

    quebecCities.moveToLast();
    quebecCities.insertBeforeCurrent("Montreal");
    quebecCities.moveToLast();
    quebecCities.insertBeforeCurrent("Quebec City");
    quebecCities.moveToLast();
    quebecCities.insertBeforeCurrent("Laval");
    quebecCities.moveToLast();
    quebecCities.insertBeforeCurrent("Sherbrooke");
    quebecCities.moveToLast();
    quebecCities.insertBeforeCurrent("Trois-Rivières");

    britishColumbiaCities.moveToLast();
    britishColumbiaCities.insertBeforeCurrent("Vancouver");
    britishColumbiaCities.moveToLast();
    britishColumbiaCities.insertBeforeCurrent("Victoria");
    britishColumbiaCities.moveToLast();
    britishColumbiaCities.insertBeforeCurrent("Surrey");
    britishColumbiaCities.moveToLast();
    britishColumbiaCities.insertBeforeCurrent("Burnaby");
    britishColumbiaCities.moveToLast();
    britishColumbiaCities.insertBeforeCurrent("Kelowna");

    albertaCities.moveToLast();
    albertaCities.insertBeforeCurrent("Calgary");
    albertaCities.moveToLast();
    albertaCities.insertBeforeCurrent("Edmonton");
    albertaCities.moveToLast();
    albertaCities.insertBeforeCurrent("Banff");
    albertaCities.moveToLast();
    albertaCities.insertBeforeCurrent("Red Deer");
    albertaCities.moveToLast();
    albertaCities.insertBeforeCurrent("Fort McMurray");

    novaScotiaCities.moveToLast();
    novaScotiaCities.insertBeforeCurrent("Halifax");
    novaScotiaCities.moveToLast();
    novaScotiaCities.insertBeforeCurrent("Sydney");
    novaScotiaCities.moveToLast();
    novaScotiaCities.insertBeforeCurrent("Dartmouth");
    novaScotiaCities.moveToLast();
    novaScotiaCities.insertBeforeCurrent("Truro");
    novaScotiaCities.moveToLast();
    novaScotiaCities.insertBeforeCurrent("New Glasgow");

    provinces.moveToLast();
    provinces.insertBeforeCurrent("Ontario");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("Quebec");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("British Columbia");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("Alberta");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("Nova Scotia");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("Manitoba");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("Saskatchewan");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("New Brunswick");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("Newfoundland and Labrador");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("Prince Edward Island");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("Northwest Territories");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("Yukon");
    provinces.moveToLast();
    provinces.insertBeforeCurrent("Nunavut");
}

cPersonGenerator::~cPersonGenerator() {
    // DLinkedList handles its own memory cleanup
}

bool cPersonGenerator::LoadCensusFiles(
    std::string babyNameFile,
    std::string surnameFile,
    std::string streetNameFile,
    std::string& errorString) {
    std::ifstream babyNames_IF(babyNameFile);
    if (!babyNames_IF.is_open()) {
        std::cout << "Didn't open baby names file" << std::endl;
        errorString = "Failed to open baby names file: " + babyNameFile;
        return false;
    }

    std::string theLine;
    unsigned int lineCount = 0;

    while (std::getline(babyNames_IF, theLine)) {
        std::stringstream ssLine(theLine);

        std::string babyName;
        std::string babyGender;
        unsigned int babyNameFrequency;

        if (!(std::getline(ssLine, babyName, ',') &&
            std::getline(ssLine, babyGender, ',') &&
            (ssLine >> babyNameFrequency))) {
            std::cerr << "Error parsing line: " << theLine << std::endl;
            continue;
        }

        sBaby Baby;
        Baby.babyName = babyName;
        Baby.babyGender = babyGender;
        Baby.babyNameFrequency = babyNameFrequency;

        listBabies.moveToLast();
        listBabies.insertBeforeCurrent(Baby);

        lineCount++;
    }
    babyNames_IF.close();

    if (!readCSVStreetNameFile(streetNameFile, listStreets)) {
        errorString = "Failed to load street names file: " + streetNameFile;
        return false;
    }

    if (!readCSVSurnameFile(surnameFile, listSurnames)) {
        errorString = "Failed to load surnames file: " + surnameFile;
        return false;
    }

    return true;
}

unsigned int cPersonGenerator::getNumberOfNamesLoaded(void) {
    return listBabies.getSize();
}

unsigned int cPersonGenerator::getNumberOfSurnamesLoaded(void) {
    return listSurnames.getSize();
}

unsigned int cPersonGenerator::getNumberOfStreetsLoaded(void) {
    return listStreets.getSize();
}

cPerson* cPersonGenerator::generateRandomPerson(void) {
    if (listBabies.getSize() == 0 || listSurnames.getSize() == 0 || listStreets.getSize() == 0) return nullptr;

    cPerson* randomPerson = new cPerson();

    // Assign first, middle, and last names using frequency-based selection
    randomPerson->first = selectFirstNameByFrequency(listBabies);
    randomPerson->middle = selectMiddleNameByFrequency(listBabies);
    randomPerson->last = selectLastNameByFrequency(listSurnames);

    // Determine gender based on first name
    listBabies.moveToFirst();
    for (unsigned int i = 0; i < listBabies.getSize(); i++) {
        if (randomPerson->first == listBabies.getCurrent().babyName) {
            if (listBabies.getCurrent().babyGender == "F") {
                randomPerson->gender = randomPerson->FEMALE;
            }
            if (listBabies.getCurrent().babyGender == "M") {
                randomPerson->gender = randomPerson->MALE;
            }
            break;
        }
        if (i < listBabies.getSize() - 1) listBabies.moveNext();
    }

    unsigned int randomAge = rand() % 91 + 5;
    randomPerson->age = randomAge;

    // Select a random street
    unsigned int randomIndex = rand() % listStreets.getSize();
    listStreets.moveToFirst();
    for (unsigned int i = 0; i < randomIndex; i++) {
        listStreets.moveNext();
    }
    randomPerson->streetName = listStreets.getCurrent().streetName;
    randomPerson->streetType = listStreets.getCurrent().streetType;
    randomPerson->streetDirection = listStreets.getCurrent().postDirection;

    // Extracting street number from street name
    for (char c : randomPerson->streetName) {
        if (std::isdigit(c)) {
            randomPerson->streetNumber = randomPerson->streetNumber * 10 + (c - '0');
        }
    }

    // Generate a random SIN (13 digits)
    for (int i = 0; i < 13; ++i) {
        randomPerson->SIN = randomPerson->SIN * 10 + (rand() % 10);  // Shift left by multiplying by 10, then add a random digit
    }

    // Select a random city and province
    int randVal = rand() % 5;
    switch (randVal) {
    case 0:
        randomPerson->city = generateRandomCity(ontarioCities);
        break;
    case 1:
        randomPerson->city = generateRandomCity(quebecCities);
        break;
    case 2:
        randomPerson->city = generateRandomCity(albertaCities);
        break;
    case 3:
        randomPerson->city = generateRandomCity(britishColumbiaCities);
        break;
    case 4:
        randomPerson->city = generateRandomCity(novaScotiaCities);
        break;
    }

    randomPerson->province = generateRandomProvince(provinces);

    // Generate a random postal code
    char* generatedPostalCode = generateRandomPostalCode();
    for (int i = 0; i < 6; ++i) {
        randomPerson->postalCode[i] = generatedPostalCode[i];
    }

    return randomPerson;
}

bool readCSVStreetNameFile(std::string fileName, DLinkedList<cPersonGenerator::sStreet>& listStreets) {
    // Open the file
    std::ifstream namesFile(fileName);
    if (!namesFile.is_open()) {
        std::cout << "Didn't open file" << std::endl;
        return false;
    }

    std::string theLine;
    unsigned int lineCount = 0;
    while (std::getline(namesFile, theLine)) {
        cPersonGenerator::sStreet street;
        lineCount++;
        std::stringstream ssLine(theLine);

        std::string token;
        unsigned int tokenCount = 0;
        while (std::getline(ssLine, token, ',')) {
            if (tokenCount == 0) {
                street.fullStreetName = token;
            }
            if (tokenCount == 1) {
                street.streetName = token;
            }
            if (tokenCount == 2) {
                street.streetType = token;
            }
            if (tokenCount == 3) {
                street.postDirection = token;
            }
            tokenCount++;
        }

        listStreets.moveToLast();
        listStreets.insertBeforeCurrent(street);
    }
    namesFile.close();

    // Remove the header (first element)
    if (!listStreets.isEmpty()) {
        listStreets.moveToFirst();
        listStreets.deleteAtCurrent();
    }
    return true;
}

bool readCSVSurnameFile(std::string fileName, DLinkedList<cPersonGenerator::sSurname>& listSurnames) {
    // Open the file
    std::ifstream namesFile(fileName);
    if (!namesFile.is_open()) {
        std::cout << "Didn't open file" << std::endl;
        return false;
    }

    std::string theLine;
    unsigned int lineCount = 0;
    while (std::getline(namesFile, theLine)) {
        cPersonGenerator::sSurname surname;
        lineCount++;
        std::stringstream ssLine(theLine);

        std::string token;
        unsigned int tokenCount = 0;

        // Read the name separately to handle the first token
        std::getline(ssLine, token, ',');
        surname.name = token;

        while (std::getline(ssLine, token, ',')) {
            std::stringstream tokenStream(token);
            if (tokenCount == 0) {
                tokenStream >> surname.rank;
            }
            else if (tokenCount == 1) {
                tokenStream >> surname.count;
            }
            else if (tokenCount == 2) {
                tokenStream >> surname.prop100k;
            }
            else if (tokenCount == 3) {
                tokenStream >> surname.cum_prop100k;
            }
            else if (tokenCount == 4) {
                tokenStream >> surname.pctwhite;
            }
            else if (tokenCount == 5) {
                tokenStream >> surname.pctblack;
            }
            else if (tokenCount == 6) {
                tokenStream >> surname.pctapi;
            }
            else if (tokenCount == 7) {
                tokenStream >> surname.pctaian;
            }
            else if (tokenCount == 8) {
                tokenStream >> surname.pct2prace;
            }
            else if (tokenCount == 9) {
                tokenStream >> surname.pcthispanic;
            }
            tokenCount++;
        }

        listSurnames.moveToLast();
        listSurnames.insertBeforeCurrent(surname);
    }
    namesFile.close();

    // Remove the header (first element)
    if (!listSurnames.isEmpty()) {
        listSurnames.moveToFirst();
        listSurnames.deleteAtCurrent();
    }
    return true;
}