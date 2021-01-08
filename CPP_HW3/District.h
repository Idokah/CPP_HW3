#pragma once
#include <iostream>
#include "Party.h"
#include "consts.h"
#include "Citizen.h"
#include <math.h>
#include <string>
#include "DynamicArray.h"
#include <map>
#include <vector>
#include "SerializationHelper.h"

using namespace std;

class Citizen;

struct votesPerParty
{
    int partyIndex;
    int numOfVotes;
    int size;
};

class District
{
	public:
		void operator=(const District& other);
		void increaseCitizenNum();
		virtual ~District();
        void addVote(Citizen* voter, const int partyNum);
        int getID();
        string getName();
        string getName() const;
        int getRepresentativeNum();
        int getRepresentativeNum() const;
        int getWinningParty();
        map <int,int> getNumOfRepresantivesPerParty();
        map <int,float> getPercentagePerParty();
        float getVotePercentage();
        void mergeSort(votesPerParty* indexesArr, int size);
        void merge(votesPerParty* indexesArr1, votesPerParty* indexesArr2, int size1, int size2, votesPerParty* res);
        virtual void save(ostream& out) const;
        void load(istream& in);
        map<int, int> getElectionResults();
        friend ostream& operator<<(ostream&, const District&);
        virtual void printType(std::ostream& os) const;
        virtual void printElectionResult(int partiesLogSize, vector<Party*> parties);
        void setGenerateIDtoValue(int val);
    private:

		int generateID(int val=0);
        void increaseArrSize(int*& arr,int &currSize, const int newSize);
        void addToElectionResult(const int partyNum);

    protected:
        District();
        District(string name, int representativeNum);
        District(const District& other);
        string name;
        int id;
        int citizenNum;
        float votersPercentage;
        int representativeNum;
        int voteCount;
        map<int, int> electionResults;  // the key represent the party ID and the value the number of citizens that vote for it.
        int electionResultsSize;
};