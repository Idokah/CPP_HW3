#include "Party.h"

Party::Party() :id(0),name(""),partyHead(nullptr),representivesArr(nullptr),numberOfVotes(0),numberOfWinningRepresantives(0),sizeRepresentivesArr(0) {}

Party::Party(istream& in, Citizen** citizens, int citizensSize) :Party()
{
    this->load(in, citizens, citizensSize);
}

Party::Party(const string name, Citizen* head) : sizeRepresentivesArr(1), numberOfVotes(0),numberOfWinningRepresantives(0)
{
	this->name = name;
	this->partyHead = head;
	this->id = this->generateID();
	this->representivesArr = new CitizenList*[sizeRepresentivesArr];
    this->representivesArr[0] = new CitizenList();
}

Party::Party(const Party& other)
{
    *this = other;
}

Party& Party::operator=(const Party& other) {
    this->id = other.id;
    this->name = other.name;
    this->sizeRepresentivesArr = other.sizeRepresentivesArr;
    this->partyHead = other.partyHead;
    this->representivesArr= new CitizenList*[other.sizeRepresentivesArr];
    this->numberOfVotes = other.numberOfVotes;
    this->numberOfWinningRepresantives=other.numberOfWinningRepresantives;
    memcpy(this->representivesArr, other.representivesArr, sizeof(CitizenList*) * other.sizeRepresentivesArr);
    return *this;
}

Party::~Party() {
   for (int i = 0; i < this->sizeRepresentivesArr; i++)
       if (representivesArr[i] != nullptr) delete representivesArr[i];
   if (representivesArr != nullptr) delete[] representivesArr;
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
    if (this->sizeRepresentivesArr < districtId ){
        this->increaseArrSize(districtId);

    }
	this->representivesArr[districtId-1]->addNode(newRepresentive);
}

void Party::increaseArrSize(const int newSize) {
    CitizenList** newArr = new CitizenList*[newSize];
    for (int i = 0; i < newSize; i++)
    {
        newArr[i] = (i < this->sizeRepresentivesArr) ? this->representivesArr[i] : new CitizenList();
    }
    this->sizeRepresentivesArr = newSize;
    delete[] this->representivesArr;
    this->representivesArr = newArr;
}
const string Party::getName() { return this->name; }

const string Party::getName() const { return this->name; }

void Party::increaseNumberOfVotes() { this->numberOfVotes++; }

int Party::getNumberOfVotes() { return this->numberOfVotes; }

string Party::getPartyHeadName() const { return this->partyHead->getName(); }

void Party::printNRepresantive(const int districtID,const int n)
{ 
    if (districtID > sizeRepresentivesArr) {
        cout << "            there aren't enough represantives" << endl;
        return;
    }
    representivesArr[districtID-1]->printFirstNRepresantives(n);
}

void Party::increaseNumberOfWinningRepresentives(const int n) { this->numberOfWinningRepresantives+=n; }

int Party::getNumberOfWinningRepresantives(){ return this->numberOfWinningRepresantives; }

ostream& operator<<(ostream& os, const Party& party)
{
    os << "Party ID: " << party.getID() << ", Party Name: " << party.getName() 
        << ", head name : " << party.getPartyHeadName() << endl ;
    for (int i = 0; i < party.sizeRepresentivesArr; i++)
    {
        cout << "        representatives for district number " << i+1 << "- " << endl;
        cout << *(party.representivesArr[i]);
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

    out.write(rcastcc(&this->sizeRepresentivesArr), sizeof(sizeRepresentivesArr));
    for (int i = 0; i < sizeRepresentivesArr; i++)
        representivesArr[i]->saveIDs(out);

    out.write(rcastcc(&this->numberOfVotes), sizeof(numberOfVotes));
    out.write(rcastcc(&this->numberOfWinningRepresantives), sizeof(numberOfWinningRepresantives));

}

void Party::load(istream& in, Citizen** citizens, int citizensSize)
{
    int nameLen, partyHeadIDLen;
    string partyHeadID;

    in.read(rcastc(&nameLen), sizeof(nameLen));
    this->name.resize(nameLen);
    in.read(&this->name[0], nameLen);

    in.read(rcastc(&partyHeadIDLen), sizeof(partyHeadIDLen));
    partyHeadID.resize(partyHeadIDLen);
    in.read(&partyHeadID[0], partyHeadIDLen);

    for (int i = 0; i < citizensSize; i++)
    {
        if (citizens[i]->getID().compare(partyHeadID) == 0)
        {
            this->partyHead = citizens[i];
            break;
        }
    }

    in.read(rcastc(&this->id), sizeof(id));

    in.read(rcastc(&this->sizeRepresentivesArr), sizeof(sizeRepresentivesArr));
   this->representivesArr = new CitizenList*[sizeRepresentivesArr];
    for (int i = 0; i < this->sizeRepresentivesArr; i++)
        this->representivesArr[i] = new CitizenList(in, citizens, citizensSize);

    in.read(rcastc(&this->numberOfVotes), sizeof(numberOfVotes));
    in.read(rcastc(&this->numberOfWinningRepresantives), sizeof(numberOfWinningRepresantives));

}

void Party::setGenerateIDtoValue(int val)
{
    this->generateID(val);
}
