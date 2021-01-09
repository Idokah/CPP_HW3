#pragma once
#include "District.h"

class UnifiedDistrict : public District {
public:
	UnifiedDistrict();
	UnifiedDistrict(istream& in);
	UnifiedDistrict(string name, int representativeNum);
	virtual void printType(std::ostream& os) const;
	virtual void printElectionResult(vector<Party*> parties, map<int,int>& winningRep);

	void save(ostream& out) const;
	void load(istream& in);

};
