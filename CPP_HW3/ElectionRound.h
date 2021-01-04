#pragma once
#include <iostream>
#include "Citizen.h"
#include "District.h"
#include "Party.h"
#include "consts.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class ElectionRound
{
	public:
        void operator=(const ElectionRound& other) = delete;
        virtual ~ElectionRound();
		virtual void addDistrict(District* district);
		void addCitizen(Citizen* citizen);
		void addParty(Party* party);
		Citizen* getCitizenByID(const char* representiveID) const;
        Party* getPartyByID(int partyID) const;
        District* getDistrictByID(const int districtID) const;
        int getDistrictLogSize() const;
        int getPartiesLogSize() const;
        District** getDistricts() const;
		Party** getPartiesArr() const;
        virtual void printAllDistricts() const;
        void printAllCitizens() const;
        void printAllParties() const;
        Party** getSortedParties();
		bool isCitizenIdIsAlreadyExist(const char* citizenID) const;
		virtual void save(ostream& out) const;
		void showElectionRoundDate() const;
		void load(istream& in);

private:
		struct Date {
			int year;
            int month;
            int day;
			void save(ostream& out) const;
		};
		Date date;
		// voters
		Citizen** votersBook;
		int votersLogSize;
		int votersPhySize;
		void increaseVotersArrSize();

		// parties
		Party** parties;
		int partiesLogSize;
		int partiesPhySize;
		void increasePartiesArrSize();
		
        void mergeSort(Party** pointersArr, int size);
		void merge(Party** pointersArr1, Party** pointersArr2, int size1, int size2, Party** res);
	protected:
		ElectionRound();
		ElectionRound(const int day, const int month, const int year);
		ElectionRound(ElectionRound& electionRound) = delete;
		// districts
		int districtsLogSize;
		int districtsPhySize;
		District** districts;
		void increaseDistrictsArrSize();
};

