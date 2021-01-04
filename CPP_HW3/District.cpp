#include "District.h"
#include "Citizen.h"
#include <math.h>
#include <iostream>

using namespace std;

char* getString(const char* input);

District::District(): votersPercentage(0), electionResultsSize(0), voteCount(0), citizenNum(0) {
    this->name = nullptr;
    this->id = -1; 
    this->representativeNum = 0;
    this->electionResults = nullptr;
}

District::District(char *name, int representativeNum):
        votersPercentage(0), electionResultsSize(1), voteCount(0), citizenNum(0) {
	this->name = getString(name);
	this->id = this-> generateID();
	this->representativeNum = representativeNum;
    this->electionResults = new int[electionResultsSize];
    for (int i = 0; i < this->electionResultsSize ; ++i) {
        this->electionResults[i]=0;
    }
}

int District::getID() { return this->id; }

char* District::getName() { return this->name; }

char* District::getName() const { return this->name; }

int District::getElectionResultsSize() { return this->electionResultsSize; }

int District::getRepresentativeNum(){return this->representativeNum; }

int District::getRepresentativeNum() const { return this->representativeNum; }

int* District::getElectionResults(){ return this->electionResults; }

void District::printType(std::ostream& os) const{}

District::District(const District& other)
{
    *this = other;
}

void District::operator=(const District& other)
{
    this->voteCount=other.voteCount;
    if (this->name!=nullptr) delete[] name;
    this->name = getString(other.name);
    this->id = other.id;
    this->citizenNum=other.citizenNum;
    this->votersPercentage = other.votersPercentage;
    this->electionResults = new int[other.electionResultsSize];
    this->electionResultsSize=other.electionResultsSize;
    memcpy(this->electionResults, other.electionResults, sizeof(int) * other.electionResultsSize);
    this->representativeNum = other.representativeNum;
}

District::~District()
{
    delete[] name;
    delete[] this->electionResults;
}

int District::generateID(int val)
{
	static int id = 0;
    if (val != 0)
    {
        id = val;
        return id;
    }
	return ++id;
}

void District::addVote(Citizen* voter, const int partyNum)
{
    if (! voter->getIsAlreadyVote()) {
        this->addToElectionResult(partyNum);
        voter->setIsAlreadyVote();
        this->voteCount ++;
        this->votersPercentage= (static_cast<float>(this->voteCount) / static_cast<float>(this->citizenNum)) * 100;
    } else {
        cout << "already voted!" << endl;
    }
}

void District::addToElectionResult(const int partyNum)
{
    if (this->electionResultsSize < partyNum ){
        this->increaseArrSize(this->electionResults,this->electionResultsSize, partyNum);

    }
    this->electionResults[partyNum-1]++;
}

void District::increaseArrSize(int*& arr, int &currSize, const int newSize) {
    int* newArr = new int[newSize];
    for (int i = 0; i < currSize; i++)
    {
        newArr[i] = arr[i];
    }
    for (int i = currSize; i<newSize; i++)
    {
        newArr[i]=0;
    }
    delete[] arr;
    currSize = newSize;
    arr = newArr;
}

void District::increaseCitizenNum()
{
    this->citizenNum++;
}

int District::getWinningParty(){
    int maxIndex = 0, max = 0;
    for (int i = 0; i < this->electionResultsSize; ++i) {
        if (this->electionResults[i] > max){
            max = this->electionResults[i];
            maxIndex = i;
        }
    }
    return (maxIndex + 1);
}

int *District::getNumOfRepresantivesPerParty(int& numOfExistsPartiesInDistrict){
    float *percentagePerParty = this->getPercentagePerParty();
    int *numOfRepresantivesPerParty = new int[electionResultsSize];
    for (int i = 0; i < this->electionResultsSize; ++i) {
        numOfRepresantivesPerParty[i] = round(percentagePerParty[i] * this->representativeNum / 100);
    }
    numOfExistsPartiesInDistrict = this->electionResultsSize;
    return numOfRepresantivesPerParty;
}

float* District::getPercentagePerParty()
{
    float *percentagePerParty = new float[electionResultsSize]; //// the index represent the (party ID - 1) and the value is the percentage.

    for (int i = 0; i < electionResultsSize; ++i)
    {
        percentagePerParty[i] = (this->voteCount == 0) ? 0 : (static_cast<float>(this->electionResults[i]) / static_cast<float>(this->voteCount)) * 100;
    }
    return percentagePerParty;
}

float District::getVotePercentage()
{
    return ((this->citizenNum==0)? 0 : static_cast<float>(this->voteCount) / static_cast<float>(this->citizenNum)) * 100;
}

ostream& operator<<(ostream& os, const District& district)
{
    os << "District ID "<<district.id << " District Name: " << district.getName() << ", num of representative: " << district.getRepresentativeNum()<<" ";
    district.printType(os);
    return os;
}

void District::printElectionResult(int partiesLogSize, Party** parties)
{
    Party* party;
    char* headName;
    int numOfExistsPartiesInDistrict, * numOfRepresantivesPerParty = nullptr, * electionResults , partyIndex;
    float* percentagePerParty = nullptr;
    int numOfParties = this->getElectionResultsSize();
    electionResults = this->getElectionResults();
    percentagePerParty = this->getPercentagePerParty();
    numOfRepresantivesPerParty = this->getNumOfRepresantivesPerParty(numOfExistsPartiesInDistrict);
    cout << "total voters percentage- " << this->votersPercentage << "%" << endl;
    cout << "--- parties results --- " << endl;
    votesPerParty* votersPerParty = this->getPartiesSortedByVotes(this->getElectionResults(), numOfParties);

    for (int j = 0; j < partiesLogSize; ++j) {
        partyIndex = votersPerParty->size > j ? votersPerParty[j].partyIndex : j;
        cout << "    Party " << (parties[partyIndex]->getName()) <<":"<< endl;       
        if (j < numOfExistsPartiesInDistrict)
        {
            cout << "        number of voters- " << electionResults[partyIndex] << endl
                << "        percentage of all votes - " << percentagePerParty[partyIndex] << "%" << endl;
            if (numOfRepresantivesPerParty[j] > 0) {
                cout << "        represantives - " << endl;
                party = parties[j];
                party->printNRepresantive(this->getID(), numOfRepresantivesPerParty[partyIndex]);
            }
        }
        else {
            cout << "        number of voters" << " - 0" << endl
                << "        percentage of all votes - 0%" << endl;
        }
    }
}

votesPerParty* District::getPartiesSortedByVotes(int* electionResult, int electionResultLogSize)
{
    votesPerParty* votesPerPartyArr = new votesPerParty[electionResultLogSize];
    votesPerPartyArr->size = electionResultLogSize;
    for (int i = 0; i < electionResultLogSize; i++)
    {
        votesPerPartyArr[i] = { i,electionResult[i] };
    }
    mergeSort(votesPerPartyArr, electionResultLogSize);
    return votesPerPartyArr;
}

void District::setGenerateIDtoValue(int val)
{
    this->generateID(val);
}

void District::mergeSort(votesPerParty* indexesArr, int size) {
    votesPerParty* temp;
    if (size <= 1) return;
    else {
        mergeSort(indexesArr, size / 2);
        mergeSort(indexesArr + size / 2, size - size / 2);
        temp = new votesPerParty[size];
        merge(indexesArr, indexesArr + size / 2, size / 2, size - size / 2, temp);
        for (int i = 0; i < size; i++) {
            indexesArr[i] = temp[i];
        }

        delete[] temp;
    }
}

void District::merge(votesPerParty* indexesArr1, votesPerParty* indexesArr2, int size1, int size2, votesPerParty* res)
{
    votesPerParty currentValue1;
    votesPerParty currentValue2;
    int i1 = 0, i2 = 0, iRes = 0;
    while (i1 < size1 && i2 < size2)
    {
        currentValue1 = *(indexesArr1 + i1);
        currentValue2 = *(indexesArr2 + i2);
        if (currentValue1.numOfVotes > currentValue2.numOfVotes)
        {
            res[iRes] = indexesArr1[i1];
            iRes++;
            i1++;
        }
        else
        {
            res[iRes] = indexesArr2[i2];
            iRes++;
            i2++;
        }
    }
    while (i1 < size1)
    {
        res[iRes] = indexesArr1[i1];
        iRes++;
        i1++;
    }
    while (i2 < size2)
    {
        res[iRes] = indexesArr2[i2];
        iRes++;
        i2++;
    }
}

void District::save(ostream& out) const
{
    int nameLen = strlen(this->name);
    out.write(rcastcc(&nameLen), sizeof(nameLen));
    out.write(rcastcc(this->name), sizeof(char) * nameLen);

    out.write(rcastcc(&this->id), sizeof(this->id));
    out.write(rcastcc(&this->citizenNum), sizeof(this->citizenNum));
    out.write(rcastcc(&this->votersPercentage), sizeof(this->votersPercentage));
    out.write(rcastcc(&this->voteCount), sizeof(this->voteCount));

    int electionResultsLen = this->electionResultsSize;
    out.write(rcastcc(&electionResultsLen), sizeof(electionResultsLen));
    out.write(rcastcc(this->electionResults), sizeof(int) * electionResultsLen);
    out.write(rcastcc(&this->representativeNum), sizeof(this->representativeNum));
    
}

void District::load(istream& in)
{
    int nameLen;
    in.read(rcastc(&nameLen), sizeof(nameLen));
    this->name = new char[nameLen + 1];
    this->name[nameLen] = '\0';
    in.read(rcastc(this->name), sizeof(char) * nameLen);
    in.read(rcastc(&this->id), sizeof(this->id));
    in.read(rcastc(&this->citizenNum), sizeof(this->citizenNum));
    in.read(rcastc(&this->votersPercentage), sizeof(this->votersPercentage));
    in.read(rcastc(&this->voteCount), sizeof(this->voteCount));

    int electionResultsLen;
    in.read(rcastc(&electionResultsLen), sizeof(electionResultsLen));
    this->electionResultsSize = electionResultsLen;
    this->electionResults = new int[electionResultsLen];
    in.read(rcastc(this->electionResults), sizeof(int) * electionResultsLen);
    in.read(rcastc(&this->representativeNum), sizeof(this->representativeNum)); 
}

