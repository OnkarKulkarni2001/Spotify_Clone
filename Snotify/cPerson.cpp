#include "cPerson.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

cPerson::cPerson()
{
	// In here, set the default information
	this->gender = cPerson::RATHER_NOT_SAY_UNKNOWN;
	this->streetNumber = 0;
	this->age = -1;
	this->SIN = 0;

	// Generate unique Snotify ID
	this->m_Snotify_UniqueUserID = cPerson::m_NEXT_Snotify_UniqueUSerID;
	// Increment for next created user by a small random amount 
	const unsigned int MAX_ID_INCREEMNT = 11;
	cPerson::m_NEXT_Snotify_UniqueUSerID += (rand() % MAX_ID_INCREEMNT);
}

// The 1st Snotify user will have ID: 10,000,000
// static 
unsigned int cPerson::m_NEXT_Snotify_UniqueUSerID = 10000000;

cPerson::~cPerson()
{
	
}

cPerson::cPerson(const cPerson& other)
{
	this->m_Snotify_UniqueUserID = other.m_Snotify_UniqueUserID;
	this->age = other.age;
	this->city = other.city;
	this->first = other.first;
	this->gender = other.gender;
	this->last = other.last;
	this->middle = other.middle;
	this->postalCode[0] = other.postalCode[0];
	this->postalCode[1] = other.postalCode[1];
	this->postalCode[2] = other.postalCode[2];
	this->postalCode[3] = other.postalCode[3];
	this->postalCode[4] = other.postalCode[4];
	this->postalCode[5] = other.postalCode[5];
	this->province = other.province;
	this->SIN = other.SIN;
	this->streetDirection = other.streetDirection;
	this->streetName = other.streetName;
	this->streetNumber = other.streetNumber;
	this->streetType = other.streetType;
	this->vectainSongLibrary = other.vectainSongLibrary;
}

cPerson& cPerson::operator=(const cPerson& other)
{
	if (this == &other) return *this; // Handle self-assignment

	this->m_Snotify_UniqueUserID = other.m_Snotify_UniqueUserID;
	this->age = other.age;
	this->city = other.city;
	this->first = other.first;
	this->gender = other.gender;
	this->last = other.last;
	this->middle = other.middle;
	this->postalCode[0] = other.postalCode[0];
	this->postalCode[1] = other.postalCode[1];
	this->postalCode[2] = other.postalCode[2];
	this->postalCode[3] = other.postalCode[3];
	this->postalCode[4] = other.postalCode[4];
	this->postalCode[5] = other.postalCode[5];
	this->province = other.province;
	this->SIN = other.SIN;
	this->streetDirection = other.streetDirection;
	this->streetName = other.streetName;
	this->streetNumber = other.streetNumber;
	this->streetType = other.streetType;
	this->vectainSongLibrary = other.vectainSongLibrary;

	return *this;
}

std::string cPerson::getGenderAsString(void)
{
	switch (this->gender)
	{
	case cPerson::MALE:
		return "MALE";
		break;
	case cPerson::FEMALE:
		return "FEMALE";
		break;
	case cPerson::NON_BINARY:
		return "NON_BINARY";
		break;
	case cPerson::RATHER_NOT_SAY_UNKNOWN:
		return "RATHER_NOT_SAY_UNKNOWN";
		break;
//	default:
//		break;
	}

	// This should never happen
//	return "RATHER_NOT_SAY_UNKNOWN";
	return "OMG! CALL THE DEV TEAM!! SOMEONE SCREWED UP!!!";
}

unsigned int cPerson::getSnotifyUniqueUserID(void)
{
	return m_Snotify_UniqueUserID;
}
