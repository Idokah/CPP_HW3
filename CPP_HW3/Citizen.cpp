#include "Citizen.h"
#include "District.h"
#include <iostream>

using namespace std;

char* getString(const char* input) {
	int inputLen = strlen(input);
	char* str = new char[inputLen + 1];
	memcpy(str, input, inputLen);
	str[inputLen] = '\0';
	return str;
}
Citizen::Citizen() :  name(nullptr), id(nullptr), birthYear(0), district(nullptr), isPartyMember(false), isAlreadyVote(false) {
}

Citizen::Citizen(char* name, char* id, unsigned int birthYear, District* district) : isPartyMember(false), isAlreadyVote(false) {
    this->name = getString(name);
    this->id = getString(id);
    this->birthYear = birthYear;
    this->district = district;
}

Citizen::Citizen(const Citizen& other) {
    *this = other;
}

Citizen::Citizen(istream& in, District** districts, int districtsSize) : Citizen() {
    this->load(in, districts, districtsSize);
}

Citizen::~Citizen() {
    delete[] name;
    delete[] id;
}

char* Citizen::getName() { return this->name; }

char* Citizen::getName() const { return this->name; }

bool Citizen::setIsPartyMember() {
    this->isPartyMember = true;
    return true;
}

bool Citizen::setIsAlreadyVote() {
    this->isAlreadyVote = true;
    return true;
}

bool Citizen::getIsPartyMember() const { return this->isPartyMember;}

bool Citizen::getIsAlreadyVote() const { return this->isAlreadyVote;}

Citizen& Citizen::operator=(const Citizen& other){
    this->name = getString(other.name);
    this->id = getString(other.id);
    this->birthYear = other.birthYear;
    *(this->district) = *(other.district);
    this->isPartyMember = other.isPartyMember;
    this->isAlreadyVote = other.isAlreadyVote;
    return *this;
}

char* Citizen::getID() const { return this->id; }

District* Citizen::getDistrict(){ return this->district;}

District* Citizen::getDistrict() const{ return this->district; }

ostream& operator<<(ostream& os, const Citizen& citizen)
{
    os << "Citizen name: " << citizen.getName() << ", District: " << citizen.getDistrict()->getName() << ", Citizen ID: " << citizen.getID();
    return os;
}

void Citizen::save(ostream& out) const
{
    int nameLen = strlen(this->name);
    out.write(rcastcc(&nameLen), sizeof(nameLen));
    out.write(rcastcc(this->name), sizeof(char) * nameLen);

    int idLen = strlen(this->id);
    out.write(rcastcc(&idLen), sizeof(idLen));
    out.write(rcastcc(this->id), sizeof(char) * idLen);
    int districtID = this->district->getID();
    out.write(rcastcc(&districtID), sizeof(districtID));

    out.write(rcastcc(&this->birthYear), sizeof(this->birthYear));
    out.write(rcastcc(&this->isPartyMember), sizeof(this->isPartyMember));
    out.write(rcastcc(&this->isAlreadyVote), sizeof(this->isAlreadyVote));

}

void Citizen::load(istream& in, District** districts, int districtsSize)
{
    int nameLen;
    in.read(rcastc(&nameLen), sizeof(nameLen));
    this->name = new char[nameLen + 1];
    this->name[nameLen] = '\0';
    in.read(rcastc(this->name), sizeof(char) * nameLen);

    int idLen;
    in.read(rcastc(&idLen), sizeof(idLen));
    this->id = new char[idLen + 1];
    this->id[idLen] = '\0';
    in.read(rcastc(this->id), sizeof(char) * idLen);

    int districtID;
    in.read(rcastc(&districtID), sizeof(districtID));
    for (int i = 0; i < districtsSize; i++)
    {
        if (districts[i]->getID() == districtID)
        {
            this->district = districts[i];
            break;
        }
    }

    in.read(rcastc(&this->birthYear), sizeof(this->birthYear));
    in.read(rcastc(&this->isPartyMember), sizeof(this->isPartyMember));
    in.read(rcastc(&this->isAlreadyVote), sizeof(this->isAlreadyVote));

}