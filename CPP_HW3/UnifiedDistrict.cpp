#include "UnifiedDistrict.h"

UnifiedDistrict::UnifiedDistrict()
{
}

UnifiedDistrict::UnifiedDistrict(istream& in)
{
    this->load(in);
}

UnifiedDistrict::UnifiedDistrict(char* name, int representativeNum) : District(name, representativeNum){}


void UnifiedDistrict::printType(std::ostream& os) const
{
	os << "District Type: Unified";
}

void UnifiedDistrict::printElectionResult(int partiesLogSize, Party** parties)
{
	Party* winningParty;
    const char* headName;
    winningParty = parties[this->getWinningParty()-1];
    headName = winningParty->getPartyHead()->getName();
    cout << "--- the winning party head --- " << endl;
    cout << "    head of the winning party- " << headName << endl
        << "    vote percentage- " << this->getVotePercentage() << "%" << endl;
    winningParty->increaseNumberOfWinningRepresentives(this->getRepresentativeNum());
	District::printElectionResult(partiesLogSize, parties);
}
void UnifiedDistrict::save(ostream& out) const
{
    int type = (int)DISTRICT_TYPE::unified;
    out.write(rcastcc(&type), sizeof(type));
    this->District::save(out);
}

void UnifiedDistrict::load(istream& in)
{
    this->District::load(in);

}