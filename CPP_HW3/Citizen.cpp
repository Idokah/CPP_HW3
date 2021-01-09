#include "Citizen.h"
#include "District.h"
#include <iostream>

using namespace std;

Citizen::Citizen() :  name(""), id(""), birthYear(0), district(nullptr), isPartyMember(false), isAlreadyVote(false) {
}

Citizen::Citizen(string name, string id, unsigned int birthYear, District* district) : isPartyMember(false), isAlreadyVote(false) {
    if (id.length() != 9) {
        throw invalid_argument("id len must be 9 digits");
    }
    this->name = name;
    this->id = id;
    this->birthYear = birthYear;
    this->district = district;
}

Citizen::Citizen(const Citizen& other) {
    *this = other;
}

Citizen::Citizen(istream& in, vector<District*> districts) : Citizen() {
    this->load(in, districts);
}

Citizen::~Citizen() {
}

string Citizen::getName() { return this->name; }

string Citizen::getName() const { return this->name; }

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
    this->name = other.name;
    this->id = other.id;
    this->birthYear = other.birthYear;
    *(this->district) = *(other.district);
    this->isPartyMember = other.isPartyMember;
    this->isAlreadyVote = other.isAlreadyVote;
    return *this;
}

string Citizen::getID() const { return this->id; }

District* Citizen::getDistrict(){ return this->district;}

District* Citizen::getDistrict() const{ return this->district; }

ostream& operator<<(ostream& os, const Citizen& citizen)
{
    os << "Citizen name: " << citizen.getName() << ", District: " << citizen.getDistrict()->getName() << ", Citizen ID: " << citizen.getID();
    return os;
}

void Citizen::save(ostream& out) const
{
    int nameLen=this->name.length();
    out.write(rcastcc(&nameLen),sizeof(nameLen));
    out.write(&this->name[0], nameLen);

    int idLen=this->name.length();
    out.write(rcastcc(&idLen),sizeof(idLen));
    out.write(&this->id[0], idLen);

    int districtID = this->district->getID();
    out.write(rcastcc(&districtID), sizeof(districtID));

    out.write(rcastcc(&this->birthYear), sizeof(this->birthYear));
    out.write(rcastcc(&this->isPartyMember), sizeof(this->isPartyMember));
    out.write(rcastcc(&this->isAlreadyVote), sizeof(this->isAlreadyVote));

}
void Citizen::load(istream& in, vector<District*> districts)
{
    int nameLen, idLen;

    in.read(rcastc(&nameLen), sizeof(nameLen));
    this->name.resize(nameLen);
    in.read(&this->name[0], nameLen);


    in.read(rcastc(&idLen), sizeof(idLen));
    this->id.resize(nameLen);
    in.read(&this->id[0], idLen);

    int districtID;
    in.read(rcastc(&districtID), sizeof(districtID));
    for (auto district : districts) {
        if (district->getID() == districtID)
            {
                this->district = district;
                break;
            }
    }
    in.read(rcastc(&this->birthYear), sizeof(this->birthYear));
    in.read(rcastc(&this->isPartyMember), sizeof(this->isPartyMember));
    in.read(rcastc(&this->isAlreadyVote), sizeof(this->isAlreadyVote));
}