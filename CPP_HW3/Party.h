#pragma once
#include "Citizen.h"
#include "CitizenList.h"
#include <iostream>
using namespace std;

class Party {
	public:
		Party();
		Party(istream& in,Citizen** citizens, int citizensSize);
		Party(const char* name, Citizen* head);
		Party(const Party& other);
		~Party();
		int getID() const;
        void addRepresentive(const int districtId, Citizen* newRepresentive);
        Party& operator=(const Party& other);
		const Citizen* getPartyHead();
		const char* getName();
        const char* getName() const;
		char* getPartyHeadName() const;
		void printNRepresantive(const int districtID,const int n); ////prints the first n represantives of the party in district - districtID
		int getNumberOfVotes();
		void increaseNumberOfVotes();
        void increaseNumberOfWinningRepresentives(const int n);
        int getNumberOfWinningRepresantives();

		void save(ostream& out) const;
		void load(istream& in, Citizen** citizens, int citizensSize);

		friend ostream& operator<<(ostream&, const Party&);
		void setGenerateIDtoValue(int val);

    private:
		char* name;
		Citizen* partyHead;
		int id;
		CitizenList** representivesArr; 
        int sizeRepresentivesArr;
		int generateID(int val=0);
        void increaseArrSize(const int newSize);
		int numberOfVotes;
		int numberOfWinningRepresantives;
};

