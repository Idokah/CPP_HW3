#pragma once
#include "Citizen.h"
#include <iostream>
#include <list>
#include <map>

using namespace std;

class Party {
	public:
		Party();
		Party(istream& in,vector<Citizen*> citizens);
		Party(const string name, Citizen* head);
		Party(const Party& other);
		~Party();
		int getID() const;
        void addRepresentive(const int districtId, Citizen* newRepresentive);
        Party& operator=(const Party& other);
		const Citizen* getPartyHead();
		const string getName();
        const string getName() const;
		string getPartyHeadName() const;
		int getNumberOfVotes();
		void increaseNumberOfVotes();
        int getNumberOfWinningRepresantives();

		void save(ostream& out) const;
		void saveRepresentivesList(ostream& out, list<Citizen*> list) const;
		void load(istream& in, vector<Citizen*> citizens);

		void loadRepresentivesList(istream& in, int districtId, vector<Citizen*> citizens);

		friend ostream& operator<<(ostream&, const Party&);
		void setGenerateIDtoValue(int val);

		void printFirstNRepresantives(int n, const int districtID) const;


    private:
        string name;
		Citizen* partyHead;
		int id;
		map <int,list<Citizen*>*> representivesArr;  //key is the district id, value is pointer to list of citizen* (representative from this district)

		int generateID(int val=0);
		int numberOfVotes;
		int numberOfWinningRepresantives;
};

