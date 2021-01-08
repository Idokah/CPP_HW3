#include "DividedDistrict.h"

DividedDistrict::DividedDistrict()
{
}

DividedDistrict::DividedDistrict(istream& in)
{
    this->load(in);
}

DividedDistrict::DividedDistrict(string name, int representativeNum) : District(name, representativeNum) {}

void DividedDistrict::printType(std::ostream& os) const
{
	os << "District Type: Divided";
}

void DividedDistrict::printElectionResult(int partiesLogSize, vector<Party*> parties)
{
    Party* party;
    map<int,int> reprsantivePerParty= this->getNumOfRepresantivesPerParty();
    vector<pair<int, int>> votersPerParty = getMapSortByValue(this->getElectionResults());
    cout << "--- all parties heads --- " << endl;
    for (int i = 0; i < votersPerParty.size(); i++)

    {
        int numOfRepresantive = reprsantivePerParty[votersPerParty[i].first];
        party = parties[votersPerParty[i].first-1];
        if (numOfRepresantive != 0)
        {
            cout << "    " <<  *(party->getPartyHead()) << ", Number of represantives: " << numOfRepresantive << endl;
            party->increaseNumberOfWinningRepresentives(numOfRepresantive);
        }
     }
    District::printElectionResult(partiesLogSize, parties);
}

void DividedDistrict::save(ostream& out) const
{
    int type = (int)DISTRICT_TYPE::divided;
    out.write(rcastcc(&type), sizeof(type));
    this->District::save(out);
}

void DividedDistrict::load(istream& in)
{
    this->District::load(in);

}
