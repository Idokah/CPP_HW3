#pragma once
#include <iostream>
#include "Citizen.h"
#include "District.h"
#include "Party.h"
#include "consts.h"
#include "Builders.h"

class ElectionRound
{
	public:
        void operator=(const ElectionRound& other) = delete;
        virtual ~ElectionRound();
		virtual void addDistrict(District* district) = 0;
		void addCitizen(Citizen* citizen);
		void addParty(Party* party);
		Citizen* getCitizenByID(const string representiveID) const;
        Party* getPartyByID(int partyID) const;
        District* getDistrictByID(const int districtID) const;
		vector <District*> getDistricts() const;
		vector<Party*> getParties() const;
		int getYear() const;
		virtual void printAllDistricts() const = 0;
        void printAllCitizens() const;
        void printAllParties() const;
		vector<Party*> getSortedParties();
		bool isCitizenIdIsAlreadyExist(const string citizenID) const;
		virtual void save(ostream& out) const;
		void showElectionRoundDate() const;
		void load(istream& in);

		template <class T, class S, class C>
		T* getItemByID(vector<T*> arr, const S id, const string errMsg, C compare) const
		{
			for (auto item : arr) {
				if (compare(item->getID(), id))
					return item;
			}
				throw invalid_argument(errMsg);
		}


private:
		struct Date {
			int day;
			int month;
			int year;
			void save(ostream& out) const;
		};
		Date date;
		vector<Citizen*> votersBook;
		vector<Party*> parties;
	protected:
		ElectionRound();
		ElectionRound(const int day, const int month, const int year);
		ElectionRound(ElectionRound& electionRound) = delete;
		vector<District*> districts;
		
		template<class K, class T>
		vector<K> loadVector(istream& in, vector<K> vec, Builder<T>* builder)
		{
			int size;
			in.read(rcastc(&size), sizeof(size));
			for (int i = 0; i < size; ++i)
			{
				vec.push_back(builder->construct(in));
			}
			return vec;
		}

};

