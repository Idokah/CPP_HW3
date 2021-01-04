#pragma once
#pragma once
#include <iostream>
#include "ElectionRound.h"
#include "Citizen.h"
#include "District.h"
#include "Party.h"

class SimpleElectionRound : public ElectionRound {
	public:
		SimpleElectionRound();
		SimpleElectionRound(int day, int month, int year, int numOfRepresentative);
		SimpleElectionRound(istream& in);
		virtual void addDistrict(District* district);
		virtual void printAllDistricts() const;
		void save(ostream& out) const;
	private:
};
