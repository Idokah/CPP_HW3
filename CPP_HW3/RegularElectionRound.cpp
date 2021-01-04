#include "RegularElectionRound.h"

RegularElectionRound::RegularElectionRound()
{
}

RegularElectionRound::RegularElectionRound(int day, int month, int year) : ElectionRound(day, month, year) {}

RegularElectionRound::RegularElectionRound(istream& in)
{
	this->load(in);
}

void RegularElectionRound::addDistrict(District* district)
{
	if (this->districtsLogSize == this->districtsPhySize)
	{
		this->increaseDistrictsArrSize();
	}
	this->districts[this->districtsLogSize++] = district;
}

void RegularElectionRound::printAllDistricts () const
{
	for (int i = 0; i < districtsLogSize; ++i) {
		cout << *(districts[i]) << endl;
	}
}

void RegularElectionRound::save(ostream& out) const
{
	int type = (int)ELECTION_ROUND_TYPE::regular;
	out.write(rcastcc(&type), sizeof(type));
	this->ElectionRound::save(out);
}
