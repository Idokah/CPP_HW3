#pragma once
#pragma once
#include <iostream>
#include "ElectionRound.h"
#include "Citizen.h"
#include "District.h"
#include "Party.h"

class RegularElectionRound : public ElectionRound {
	public:
		RegularElectionRound();
		RegularElectionRound(int day, int month, int year);
		RegularElectionRound(istream& in);
		virtual void addDistrict(District* district);
		virtual void printAllDistricts() const;
		void save(ostream& out) const;
	private:
};

