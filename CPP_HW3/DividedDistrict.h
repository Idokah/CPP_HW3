#pragma once
#include <iostream>
#include "District.h"
using namespace std;

class DividedDistrict : public District {
	public:
		DividedDistrict();
		DividedDistrict(istream& in);
		DividedDistrict(char* name, int representativeNum);
		virtual void printType(std::ostream& os) const;
		virtual void printElectionResult(int partiesLogSize, Party** parties);
		virtual void save(ostream& out) const;

		void load(istream& in);

	private:

};
