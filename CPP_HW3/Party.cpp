#include "Party.h"

Party::Party() :id(0),name(""),partyHead(nullptr),numberOfVotes(0),numberOfWinningRepresantives(0) {}

Party::Party(istream& in, vector<Citizen*> citizens) :Party()
{
    this->load(in, citizens);
}

Party::Party(const string name, Citizen* head) : numberOfVotes(0),numberOfWinningRepresantives(0)
{
	this->name = name;
	this->partyHead = head;
	this->id = this->generateID();
}

Party::Party(const Party& other)
{
    *this = other;
}

Party& Party::operator=(const Party& other) {
    this->id = other.id;
    this->name = other.name;
    this->partyHead = other.partyHead;
    this->representivesArr = other.representivesArr;
    this->numberOfVotes = other.numberOfVotes;
    this->numberOfWinningRepresantives=other.numberOfWinningRepresantives;
    return *this;
}

Party::~Party() 
{
    for (auto& item : this->representivesArr)
        delete item.second;
}

const Citizen* Party::getPartyHead(){ return this->partyHead; }

int Party::generateID(int val)
{
    static int id = 0;
    if (val != 0)
    {
        id = val;
        return id;
    }
    return ++id;
}

int Party::getID() const { return this->id; }

void Party::addRepresentive(const int districtId, Citizen* newRepresentive)
{
    if (this->representivesArr.find(districtId) == this->representivesArr.end()) //there is no list for this district
    {
        list <Citizen*> *newRepresentativeArr = new list<Citizen*>; //delete this or find another way
        newRepresentativeArr->push_back(newRepresentive);
        representivesArr[districtId] = newRepresentativeArr;
    }
    else
        representivesArr[districtId]->push_back(newRepresentive);
}
const string Party::getName() { return this->name; }

const string Party::getName() const { return this->name; }

void Party::increaseNumberOfVotes() { this->numberOfVotes++; }

int Party::getNumberOfVotes() { return this->numberOfVotes; }

string Party::getPartyHeadName() const { return this->partyHead->getName(); }


void Party::printFirstNRepresantives(int n,const int districtID) const
{
    if (this->representivesArr.find(districtID) == this->representivesArr.end()) //there is no list for this district
    { 
        cout << "            there aren't enough represantives" << endl;
        return;
    }

    list<Citizen*> districtRepresentivesArr = *(this->representivesArr.at(districtID));
    int i = 0;

    for (auto citizen:districtRepresentivesArr)
    {
        if (i == n) break;
        cout << "           " << *(citizen) << endl;
        i++;

    }
    if (i < n) cout << "            there aren't enough represantives" << endl;
}


void Party::increaseNumberOfWinningRepresentives(const int n) { this->numberOfWinningRepresantives+=n; }

int Party::getNumberOfWinningRepresantives(){ return this->numberOfWinningRepresantives; }

ostream& operator<<(ostream& os, const Party& party)
{
    os << "Party ID: " << party.getID() << ", Party Name: " << party.getName() 
        << ", head name : " << party.getPartyHeadName() << endl ;
    for (auto const &pair : party.representivesArr) 
    {
        cout << "        representatives for district number " << pair.first << "- " << endl;
        party.printFirstNRepresantives(pair.second->size(),pair.first);
    }
    return os;
}

void Party::save(ostream& out) const
{
    int nameLen=this->name.length();
    out.write(rcastcc(&nameLen),sizeof(nameLen));
    out.write(&this->name[0], nameLen);

    string partyHeadID = this->partyHead->getID();
    int partyHeadIDLen=partyHeadID.length();
    out.write(rcastcc(&partyHeadIDLen),sizeof(partyHeadIDLen));
    out.write(&partyHeadID[0], partyHeadIDLen);

    out.write(rcastcc(&this->id), sizeof(id));

    int sizeRepresentivesArr = this->representivesArr.size();
    out.write(rcastcc(&sizeRepresentivesArr), sizeof(sizeRepresentivesArr));
    int districtId;
    for (auto & repList : representivesArr)
    {
        districtId = repList.first;
        out.write(rcastcc(&districtId), sizeof(districtId));
        saveRepresentivesList(out, *repList.second);
    }

    out.write(rcastcc(&this->numberOfVotes), sizeof(numberOfVotes));
    out.write(rcastcc(&this->numberOfWinningRepresantives), sizeof(numberOfWinningRepresantives));

}

void Party::saveRepresentivesList(ostream& out, list<Citizen*> list) const
{
    string citizenID;
    int idLen;
    int listLen = list.size();
    out.write(rcastcc(&listLen), sizeof(listLen));
    for (auto rep : list)
    {
        citizenID = rep->getID();
        idLen = citizenID.length();
        out.write(rcastcc(&idLen), sizeof(idLen));
        out.write(&citizenID[0], idLen);
    }
}

void Party::load(istream& in, vector<Citizen*> citizens)
{
    int nameLen, partyHeadIDLen;
    string partyHeadID;

    in.read(rcastc(&nameLen), sizeof(nameLen));
    this->name.resize(nameLen);
    in.read(&this->name[0], nameLen);

    in.read(rcastc(&partyHeadIDLen), sizeof(partyHeadIDLen));
    partyHeadID.resize(partyHeadIDLen);
    in.read(&partyHeadID[0], partyHeadIDLen);
    for (auto citizen : citizens)
    {
        if (citizen->getID().compare(partyHeadID) == 0)
        {
            this->partyHead = citizen;
            break;
        }
    }

    in.read(rcastc(&this->id), sizeof(id));

    int sizeRepresentivesArr;
    in.read(rcastc(&sizeRepresentivesArr), sizeof(sizeRepresentivesArr));
    int districtId;
    for (int i = 0; i < sizeRepresentivesArr; i++)
    {
        in.read(rcastc(&districtId), sizeof(districtId));
        loadRepresentivesList(in, districtId,citizens);
        //this->representivesArr[i] = new CitizenList(in, citizens);
    }
        

    in.read(rcastc(&this->numberOfVotes), sizeof(numberOfVotes));
    in.read(rcastc(&this->numberOfWinningRepresantives), sizeof(numberOfWinningRepresantives));

}
void Party::loadRepresentivesList(istream& in, int districtId, vector<Citizen*> citizens)
{
    string citizenID;
    int idLen;
    int listLen;
    this->representivesArr[districtId] = new list<Citizen*>;
    in.read(rcastc(&listLen), sizeof(listLen));
    for (int i = 0; i < listLen; i++)
    {
        in.read(rcastc(&idLen), sizeof(idLen));
        citizenID.resize(idLen);
        in.read(&citizenID[0], idLen);
        for (auto citizen : citizens)
        {
            if (citizenID.compare(citizen->getID()) == 0)
            {
                this->representivesArr[districtId]->push_back(citizen);
                break;
            }
        }
    }
}

void Party::setGenerateIDtoValue(int val)
{
    this->generateID(val);
}
