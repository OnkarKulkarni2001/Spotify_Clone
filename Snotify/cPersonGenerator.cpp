#include "cPersonGenerator.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>
bool readCSVStreetNameFile(std::string fileName, cVectainer<cPersonGenerator::sStreet>& vectainStreets);
bool readCSVSurnameFile(std::string fileName, cVectainer<cPersonGenerator::sSurname>& vectainSurnames);


// Function to select a name based on frequency
std::string selectFirstNameByFrequency(cVectainer<cPersonGenerator::sBaby>& list) {
	int totalFrequency = 0;
	for (size_t i = 0; i < list.getSize(); i++) {
		totalFrequency += list.getAt(i).babyNameFrequency;
	}

	int randVal = static_cast<double>(rand()) / RAND_MAX * totalFrequency;
	int cumulativeFreq = 0;

	for (size_t i = 0; i < list.getSize(); i++) {
		cumulativeFreq += list.getAt(i).babyNameFrequency;
		if (randVal < cumulativeFreq) {
			return list.getAt(i).babyName;
		}
	}
	return ""; // Fallback (should never happen)
}

std::string selectMiddleNameByFrequency(cVectainer<cPersonGenerator::sBaby>& list) {
	int totalFrequency = 0;
	for (size_t i = 0; i < list.getSize(); i++) {
		if (list.getAt(i).babyGender == "M") {
			totalFrequency += list.getAt(i).babyNameFrequency;
		}
	}

	int randVal = static_cast<double>(rand()) / RAND_MAX * totalFrequency;
	int cumulativeFreq = 0;

	for (size_t i = 0; i < list.getSize(); i++) {
		if (list.getAt(i).babyGender == "M") {
			cumulativeFreq += list.getAt(i).babyNameFrequency;
			if (randVal < cumulativeFreq) {
				return list.getAt(i).babyName;
			}
		}
	}
	return ""; // Fallback (should never happen)
}

std::string selectLastNameByFrequency(cVectainer<cPersonGenerator::sSurname>& list) {

	// Calculate the total probability (sum of prop100k values)
	double totalProbability = 0.0;
	for (unsigned int i = 0; i < list.getSize(); i++) {
		totalProbability += list.getAt(i).prop100k;
	}

	// Generate a random number in the range [0, totalProbability)
	double randVal = static_cast<double>(rand()) / RAND_MAX * totalProbability;

	double cumulativeFreq = 0.0;

	// Select the last name based on cumulative probability
	for (unsigned int j = 0; j < list.getSize(); j++) {
		cumulativeFreq += list.getAt(j).prop100k;
		if (randVal < cumulativeFreq) {
			return  list.getAt(j).name;
		}
	}

	return ""; // Fallback (should never happen)
}

// Function to generate random city
std::string generateRandomCity(cVectainer<std::string>& cities) {
	int index = rand() % cities.getSize();  // Random index for cities
	return cities.getAt(index);
}

// Function to generate random province
std::string generateRandomProvince(cVectainer<std::string>& provinces) {
	int index = rand() % provinces.getSize();  // Random index for provinces
	return provinces.getAt(index);
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
cPersonGenerator::cPersonGenerator()
{
	ontarioCities.addAtEnd("Toronto");
	ontarioCities.addAtEnd("Ottawa");
	ontarioCities.addAtEnd("Hamilton");
	ontarioCities.addAtEnd("London");
	ontarioCities.addAtEnd("Mississauga");

	quebecCities.addAtEnd("Montreal");
	quebecCities.addAtEnd("Quebec City");
	quebecCities.addAtEnd("Laval");
	quebecCities.addAtEnd("Sherbrooke");
	quebecCities.addAtEnd("Trois-Rivières");

	britishColumbiaCities.addAtEnd("Vancouver");
	britishColumbiaCities.addAtEnd("Victoria");
	britishColumbiaCities.addAtEnd("Surrey");
	britishColumbiaCities.addAtEnd("Burnaby");
	britishColumbiaCities.addAtEnd("Kelowna");

	albertaCities.addAtEnd("Calgary");
	albertaCities.addAtEnd("Edmonton");
	albertaCities.addAtEnd("Banff");
	albertaCities.addAtEnd("Red Deer");
	albertaCities.addAtEnd("Fort McMurray");

	novaScotiaCities.addAtEnd("Halifax");
	novaScotiaCities.addAtEnd("Sydney");
	novaScotiaCities.addAtEnd("Dartmouth");
	novaScotiaCities.addAtEnd("Truro");
	novaScotiaCities.addAtEnd("New Glasgow");

	provinces.addAtEnd("Ontario");
	provinces.addAtEnd("Quebec");
	provinces.addAtEnd("British Columbia");
	provinces.addAtEnd("Alberta");
	provinces.addAtEnd("Nova Scotia");
	provinces.addAtEnd("Manitoba");
	provinces.addAtEnd("Saskatchewan");
	provinces.addAtEnd("New Brunswick");
	provinces.addAtEnd("Newfoundland and Labrador");
	provinces.addAtEnd("Prince Edward Island");
	provinces.addAtEnd("Northwest Territories");
	provinces.addAtEnd("Yukon");
	provinces.addAtEnd("Nunavut");
}

cPersonGenerator::~cPersonGenerator()
{
}

bool cPersonGenerator::LoadCensusFiles(
	std::string babyNameFile,
	std::string surnameFile,
	std::string streetNameFile,
	std::string& errorString)
{
	// TODO: Put YOUR amazing code here!
	std::ifstream babyNames_IF(babyNameFile);
	if (!babyNames_IF.is_open()) {
		std::cout << "Didn't open baby names file" << std::endl;
		return false;
	}
	
	std::string babyName;
	std::string babyGender;
	unsigned int babyNameFrequency;
	std::string discard;
	std::string theLine;
	unsigned int lineCount = 0;

	while (std::getline(babyNames_IF, theLine))
	{
		std::stringstream ssLine(theLine);

		std::string babyName;
		std::string babyGender;
		unsigned int babyNameFrequency;

		if (!(std::getline(ssLine, babyName, ',') &&
			std::getline(ssLine, babyGender, ',') &&
			(ssLine >> babyNameFrequency)))
		{
			std::cerr << "Error parsing line: " << theLine << std::endl;
			continue;
		}

		sBaby Baby;
		Baby.babyName = babyName;
		Baby.babyGender = babyGender;
		Baby.babyNameFrequency = babyNameFrequency;

		vectainBabies.addAtEnd(Baby);

		lineCount++;
	}

	readCSVStreetNameFile(streetNameFile, vectainStreets);
	readCSVSurnameFile(surnameFile, vectainSurnames);
	return true;
}

unsigned int cPersonGenerator::getNumberOfNamesLoaded(void)
{
	return vectainBabies.getSize();
}

unsigned int cPersonGenerator::getNumberOfSurnamesLoaded(void)
{
	return vectainSurnames.getSize();
}

unsigned int cPersonGenerator::getNumberOfStreetsLoaded(void)
{
	return vectainStreets.getSize();
}

cPerson* cPersonGenerator::generateRandomPerson(void)
{
	if (vectainBabies.getSize() == 0 || vectainSurnames.getSize() == 0) return nullptr;

	cPerson* randomPerson = new cPerson();

	// Assign first, middle, and last names using frequency-based selection
	randomPerson->first = selectFirstNameByFrequency(vectainBabies);
	randomPerson->middle = selectMiddleNameByFrequency(vectainBabies);
	randomPerson->last = selectLastNameByFrequency(vectainSurnames);

	for (unsigned int i = 0; i < vectainBabies.getSize(); i++) {
		if (randomPerson->first == vectainBabies.getAt(i).babyName) {
			if (vectainBabies.getAt(i).babyGender == "F") {
				randomPerson->gender = randomPerson->FEMALE;
			}
			if (vectainBabies.getAt(i).babyGender == "M") {
				randomPerson->gender = randomPerson->MALE;
			}
		}
	}

	unsigned int randomAge = rand() % 91 + 5;
	randomPerson->age = randomAge;

	int randomIndex = rand() % vectainStreets.getSize();
	for (unsigned int j = 0; j < vectainStreets.getSize(); j++) {
		randomPerson->streetName = vectainStreets.getAt(randomIndex).streetName;
		randomPerson->streetType = vectainStreets.getAt(randomIndex).streetType;
		randomPerson->streetDirection = vectainStreets.getAt(randomIndex).postDirection;
	}

	// Extracting street number from street name
	for (char c : randomPerson->streetName) {
		if (std::isdigit(c)) {
			randomPerson->streetNumber = randomPerson->streetNumber * 10 + (c - '0');
		}
	}

	for (int i = 0; i < 13; ++i) {
		randomPerson->SIN= randomPerson->SIN * 10 + (rand() % 10);  // Shift left by multiplying by 10, then add a random digit
	}

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

	char* generatedPostalCode = generateRandomPostalCode();
	for (int i = 0; i < 6; ++i) {
		randomPerson->postalCode[i] = generatedPostalCode[i];
	}

	return randomPerson;
}


// Here's a simple way to load the comma delimited files:
bool readCSVStreetNameFile(std::string fileName, cVectainer<cPersonGenerator::sStreet>& vectainStreets)
{
	// Open the file
	std::ifstream namesFile(fileName);
	if (!namesFile.is_open())
	{
		std::cout << "Didn't open file" << std::endl;
		return false;
	}

	// name,rank,count,prop100k,cum_prop100k,pctwhite,pctblack,pctapi,pctaian,pct2prace,pcthispanic
	// SMITH,1,2442977,828.19,828.19,70.9,23.11,0.5,0.89,2.19,2.4
	//
	// - rank is how popular the last name is, like 1st, 2nd, etc.
	// - count is how many people have that last name, so 2,442,977 people have last name "Smith"
	// - prop100k is the ratio per 100,000 people. Smith is 828.19, 
	//            meaning that there's a 828.19 out of 100,000 chance (0.82819% chance)
	//            that someone is named "Smith"

	std::string theLine;

	unsigned int lineCount = 0;
	while (std::getline(namesFile, theLine))
	{
		cPersonGenerator::sStreet street;
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 0)
			{
				//std::cout << token << std::endl;
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
			// Ignore the other parts of the line
			tokenCount++;
		}

		vectainStreets.addAtEnd(street);
	}

	vectainStreets.removeAt(0);		// removing headers --> FullStreetName StreetName StreetType PostDirection
	return true;
}

bool readCSVSurnameFile(std::string fileName, cVectainer<cPersonGenerator::sSurname>& vectainSurnames)
{
	// Open the file
	std::ifstream namesFile(fileName);
	if (!namesFile.is_open())
	{
		std::cout << "Didn't open file" << std::endl;
		return false;
	}

	// name,rank,count,prop100k,cum_prop100k,pctwhite,pctblack,pctapi,pctaian,pct2prace,pcthispanic
	// SMITH,1,2442977,828.19,828.19,70.9,23.11,0.5,0.89,2.19,2.4
	//
	// - rank is how popular the last name is, like 1st, 2nd, etc.
	// - count is how many people have that last name, so 2,442,977 people have last name "Smith"
	// - prop100k is the ratio per 100,000 people. Smith is 828.19, 
	//            meaning that there's a 828.19 out of 100,000 chance (0.82819% chance)
	//            that someone is named "Smith"

	std::string theLine;

	unsigned int lineCount = 0;
	while (std::getline(namesFile, theLine))
	{
		cPersonGenerator::sSurname surname;
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 1;

		std::istringstream ss(theLine);

		std::getline(ss, token, ',');
		surname.name = token;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 0)
			{
				//std::cout << token << std::endl;
				surname.name = token;
			}
			if (tokenCount == 1) {
				ssLine >> surname.rank;
			}
			if (tokenCount == 2) {
				ssLine >> surname.count;
			}
			if (tokenCount == 3) {
				ssLine >> surname.prop100k;
			}
			if (tokenCount == 4) {
				ssLine >> surname.cum_prop100k;
			}
			if (tokenCount == 5) {
				ssLine >> surname.pctwhite;
			}
			if (tokenCount == 6) {
				ssLine >> surname.pctblack;
			}
			if (tokenCount == 7) {
				ssLine >> surname.pctapi;
			}
			if (tokenCount == 8) {
				ssLine >> surname.pctaian;
			}
			if (tokenCount == 9) {
				ssLine >> surname.pct2prace;
			}
			if (tokenCount == 10) {
				ssLine >> surname.pcthispanic;
			}
			// Ignore the other parts of the line
			tokenCount++;
		}

		vectainSurnames.addAtEnd(surname);
	}

	vectainSurnames.removeAt(0);		// removing headers --> name	rank	count	prop100k	cum_prop100k	pctwhite	pctblack	pctapi	pctaian	pct2prace	pcthispanic
	return true;
}