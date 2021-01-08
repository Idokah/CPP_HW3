#include "ElectionRound.h"
#include "District.h"
#include "DividedDistrict.h"
#include "UnifiedDistrict.h"
#include "SerializationHelper.h"
#include "Builders.h"

const int DAYS_IN_MONTH[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


ElectionRound::ElectionRound():date({0,0,0}){}

ElectionRound::ElectionRound(const int day, const int month, const int year)
{
    if (year < 0)
        throw out_of_range("year cannot be negative");
    if (month < 1 || month>12)
        throw out_of_range("month is out of range");
    if (day > DAYS_IN_MONTH[month - 1] || day < 1)
        throw out_of_range("day is out of range");
    this->date = { day, month, year };
}

ElectionRound::~ElectionRound()
{
    for (auto party : this->parties) delete party;
    for (auto district : this->districts) delete district;
    for (auto citizen : this->votersBook) delete citizen;
}

vector<District*> ElectionRound::getDistricts() const { return this->districts; }

vector<Party*> ElectionRound::getParties() const { return this->parties;}

int ElectionRound::getYear() const { return this->date.year; }

void ElectionRound::addCitizen(Citizen* citizen)
{
	this->votersBook.push_back(citizen);
	citizen->getDistrict()->increaseCitizenNum();
}

void ElectionRound::addParty(Party* party)
{
    this->parties.push_back(party);
}

Citizen* ElectionRound::getCitizenByID(const string representiveID) const
{
    return this->getItemByID(this->votersBook, representiveID, "There is no such citizen.", [](string a, string b) -> bool {return a.compare(b)==0; });
}

Party* ElectionRound::getPartyByID(int partyId) const
{
    return this->getItemByID(this->parties, partyId, "There is no such party.", [](int a, int b) -> bool { return a == b; });
}

District* ElectionRound::getDistrictByID(const int districtID) const
{
    return this->getItemByID(this->districts, districtID, "There is no such district.", [](int a, int b) -> bool { return a == b; });
}

void ElectionRound::printAllCitizens() const
{
    printVector(this->votersBook);
}

void ElectionRound::printAllParties() const
{
    printVector(this->parties);
}

bool comparePartyRepresantives(Party *party1, Party *party2) {
    int num1 = party1->getNumberOfWinningRepresantives();
    int num2 = party2->getNumberOfWinningRepresantives();
    return num1 > num2;
}

vector<Party*> ElectionRound::getSortedParties()
{
    std::sort(this->parties.begin(), this->parties.end(), comparePartyRepresantives);
    return this->parties;
}

bool ElectionRound::isCitizenIdIsAlreadyExist(const string citizenID) const
{
    for (auto citizen : this->votersBook) 
        if (citizenID.compare(citizen->getID()) == 0) return true;
  return false;
}

void ElectionRound::save(ostream& out) const
{
    this->date.save(out);
    saveVector(out, this->districts);
    saveVector(out, this->votersBook);
    saveVector(out, this->parties);
}

void ElectionRound::showElectionRoundDate() const
{
    cout << "-------- Election Round Date: " << this->date.day << "/" <<
        this->date.month << "/" << this->date.year << "--------" << endl;
}

void ElectionRound::Date::save(ostream& out) const
{
    out.write(rcastcc(&year), sizeof(year));
    out.write(rcastcc(&month), sizeof(month));
    out.write(rcastcc(&day), sizeof(day));
}

void ElectionRound::load(istream& in)
{
    int day, month, year;
    in.read(rcastc(&year), sizeof(year));
    in.read(rcastc(&month), sizeof(month));
    in.read(rcastc(&day), sizeof(day));
    this->date.year = year;
    this->date.month = month;
    this->date.day = day;
    this->districts=loadVector(in, this->districts, new DistrictBuilder());
    if (this->districts.size()!=0)
        this->districts[this->districts.size()-1]->setGenerateIDtoValue(this->districts[this->districts.size() - 1]->getID());
    this->votersBook=loadVector(in, this->votersBook, new CitizenBuilder(this->districts));
    this->parties = loadVector(in, this->parties, new PartyBuilder(this->votersBook));
    if (this->parties.size() != 0)
        this->parties[this->parties.size() - 1]->setGenerateIDtoValue(this->parties[this->parties.size() - 1]->getID());
}

