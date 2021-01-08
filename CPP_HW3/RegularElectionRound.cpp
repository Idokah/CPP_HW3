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
	this->districts.push_back(district);

}

void RegularElectionRound::printAllDistricts () const
{
	printVector(this->districts);
}

void RegularElectionRound::save(ostream& out) const
{
	int type = (int)ELECTION_ROUND_TYPE::regular;
	out.write(rcastcc(&type), sizeof(type));
	this->ElectionRound::save(out);
}
