#pragma once
#include "District.h"

class UnifiedDistrict : public District {
public:
	UnifiedDistrict();
	UnifiedDistrict(istream& in);
	UnifiedDistrict(string name, int representativeNum);
	virtual void printType(std::ostream& os) const;
	virtual void printElectionResult(int partiesLogSize, vector<Party*> parties);

	void save(ostream& out) const;
	void load(istream& in);

};
