#include <iostream>
#include <fstream>
#include "Citizen.h"
#include "UnifiedDistrict.h"
#include "DividedDistrict.h"
#include "SimpleElectionRound.h"
#include "RegularElectionRound.h"
#include "Party.h"
#include "consts.h"


void addDistrict(ElectionRound& electionRound);
void addCitizen(ElectionRound& electionRound, ELECTION_ROUND_TYPE electionRoundType);
void addParty(ElectionRound& electionRound);
void setCitizenAsPartyRepresentive(ElectionRound& electionRound, ELECTION_ROUND_TYPE electionRoundType);
void printAllDistricts(ElectionRound& electionRound);
void printAllCitizens(ElectionRound& electionRound);
void printAllParties(ElectionRound& electionRound);
void vote(ElectionRound& electionRound);
void showElectionResults(ElectionRound& electionRound);
ELECTION_ROUND_TYPE loadElectionRound(ElectionRound* &electionRound);
void saveElectionRound(ElectionRound* electionRound);


using namespace std;

int main()
{
    ElectionRound* electionRound = nullptr;
    try {
        OPTIONS option = OPTIONS::showElectionResults;
        ELECTION_ROUND_OPTIONS electionRoundOption;
        int day, month, year, electionRoundTypeNum;
        ELECTION_ROUND_TYPE electionRoundType;
        int optionNum, electionRoundOptionNum;

        cout << "enter one of the options-" << endl
            << "1 - add new election round" << endl
            << "2- load election round" << endl;
        cin >> electionRoundOptionNum;
        if ((electionRoundOptionNum != (int)ELECTION_ROUND_OPTIONS::newElectionRound) && (electionRoundOptionNum != (int)ELECTION_ROUND_OPTIONS::loadElectionRound))
            throw invalid_argument("invalid option");

        electionRoundOption = (ELECTION_ROUND_OPTIONS)electionRoundOptionNum;
        switch (electionRoundOption)
        {
        case ELECTION_ROUND_OPTIONS::newElectionRound:
        {
            cout << "enter elections date DD MM YYYY ";
            cin >> day >> month >> year;
            cout << "enter elections round type (0 for regular, 1 for simple) ";
            cin >> electionRoundTypeNum;

            if ((electionRoundTypeNum != (int)ELECTION_ROUND_TYPE::regular) && (electionRoundTypeNum != (int)ELECTION_ROUND_TYPE::simple))
                throw invalid_argument("invalid election round type");

            electionRoundType = (ELECTION_ROUND_TYPE)electionRoundTypeNum;
            if (electionRoundType == ELECTION_ROUND_TYPE::regular) electionRound = new RegularElectionRound(day, month, year);
            else
            {
                int numOfRepresentative;
                cout << "enter number of representative ";
                cin >> numOfRepresentative;
                electionRound = new SimpleElectionRound(day, month, year, numOfRepresentative);
            }
            break;
        }
        case ELECTION_ROUND_OPTIONS::loadElectionRound:
            electionRoundType = loadElectionRound(electionRound);
        }


        while (option != OPTIONS::exit) {
            try {
                cout << "enter one of the options-" << endl
                    << "1 - add district " << endl
                    << "2- add citizen " << endl
                    << "3- add party " << endl
                    << "4- add citizen as party representive " << endl
                    << "5- show all districts " << endl
                    << "6- show all citizens " << endl
                    << "7- show all parties " << endl
                    << "8- vote " << endl
                    << "9- show election results " << endl
                    << "10- exit the program " << endl
                    << "11- save the election round " << endl
                    << "12- load exist election round " << endl;

                cin >> optionNum;
                option = (OPTIONS)optionNum;
                if (optionNum < (int)OPTIONS::addDistrict || optionNum >(int)OPTIONS::loadElectionRound)
                    throw invalid_argument("invalid option");
                switch (option)
                {
                case OPTIONS::addDistrict:
                    addDistrict(*electionRound);
                    break;
                case OPTIONS::addCitizen:
                    addCitizen(*electionRound, electionRoundType);
                    break;
                case OPTIONS::addParty:
                    addParty(*electionRound);
                    break;
                case OPTIONS::addCitizenAsPartyRepresentive:
                    setCitizenAsPartyRepresentive(*electionRound, electionRoundType);
                    break;
                case OPTIONS::showAllDistricts:
                    printAllDistricts(*electionRound);
                    break;
                case OPTIONS::showAllCitizens:
                    printAllCitizens(*electionRound);
                    break;
                case OPTIONS::showAllParties:
                    printAllParties(*electionRound);
                    break;
                case OPTIONS::vote:
                    vote(*electionRound);
                    break;
                case OPTIONS::showElectionResults:
                    showElectionResults(*electionRound);
                    break;
                case OPTIONS::exit:
                    cout << "see you soon" << endl;
                    break;
                case OPTIONS::saveElectionRound:
                    saveElectionRound(electionRound);
                    break;
                case OPTIONS::loadElectionRound:
                    delete electionRound;
                    electionRound = nullptr;
                    loadElectionRound(electionRound);
                    break;
                }
            }
            catch (invalid_argument ex) {
                cout << "You enter invalid argument :(" << endl << "details: " << ex.what() << endl << "pls try again" << endl;
            }
            catch (out_of_range ex) {
                cout << "You enter out of range argument :(" << endl << "details: " << ex.what() << endl << "pls try again" << endl;
            }
        }
    }
    catch (invalid_argument ex) {
                cout << "You enter out of range argument :(" << endl << "details: " << ex.what() << "." << endl;
    } catch (...) {
        if (electionRound != nullptr) delete electionRound;
        electionRound = nullptr;
    }
    if (electionRound != nullptr) delete electionRound;
}


void addDistrict(ElectionRound &electionRound) {
    string name;
    int representativeNum; 
    int districtTypeNum;
    DISTRICT_TYPE districtType;
    District* district;
    cout << "enter name, number of representative and district type (1 for divided, 0 for unified) ";
    cin >> name >> representativeNum >> districtTypeNum;
    if ((districtTypeNum != (int)DISTRICT_TYPE::divided) && (districtTypeNum != (int)DISTRICT_TYPE::unified))
        throw invalid_argument("invalid district type");
    districtType = (DISTRICT_TYPE)districtTypeNum;
    if (representativeNum <= 0) 
        throw invalid_argument("Sorry a district have a positive number of represenative number");
    if (districtType == DISTRICT_TYPE::unified) district = new UnifiedDistrict(name, representativeNum);
    else district = new DividedDistrict(name, representativeNum);
    electionRound.addDistrict(district);
}


void addCitizen(ElectionRound& electionRound, ELECTION_ROUND_TYPE electionRoundType) {
    string name;
    string id;
    int birthYear, districtNum;
    cout << "enter name, id, birth year, district number ";
    cin >> name >> id >> birthYear >> districtNum;
    if (electionRound.isCitizenIdIsAlreadyExist(id)) throw invalid_argument("This Citizen id already exists");
    if (electionRound.getYear() - birthYear < 18) throw out_of_range("citizen must be at least 18 years old");

    districtNum = (electionRoundType == ELECTION_ROUND_TYPE::regular) ? districtNum : 1;
    District* district = electionRound.getDistrictByID(districtNum); 
    Citizen* citizen = new Citizen(name, id, birthYear, district);
    electionRound.addCitizen(citizen);
}

void addParty(ElectionRound& electionRound) {
    string name;
    string id;
    cout << "enter name and the party head's id ";
    cin >> name >> id;
    Citizen* head = electionRound.getCitizenByID(id);
    if (head->getIsPartyMember()) {
        throw invalid_argument("This citizen already set as party head.");
    }
    Party* party = new Party(name, head);
    electionRound.addParty(party);
    head->setIsPartyMember();
}

void setCitizenAsPartyRepresentive(ElectionRound& electionRound, ELECTION_ROUND_TYPE electionRoundType) {
    string representiveId;
    int partyId;
    int districtId;
    cout << "enter representive ID, party ID, district ID ";
    cin >> representiveId >> partyId >> districtId;
    districtId = (electionRoundType == ELECTION_ROUND_TYPE::regular) ? districtId : 1;
    electionRound.getDistrictByID(districtId);
    Citizen *citizen = electionRound.getCitizenByID(representiveId);
    if (citizen->getIsPartyMember()) {
        throw invalid_argument("This citizen already set as represantive or head.");
    }
    citizen->setIsPartyMember();
    Party *party = electionRound.getPartyByID(partyId);
    party->addRepresentive(districtId, citizen);
}

void printAllDistricts(ElectionRound& electionRound) {
    electionRound.printAllDistricts();
}

void printAllCitizens(ElectionRound& electionRound) {
    electionRound.printAllCitizens();
}

void printAllParties(ElectionRound& electionRound) {
    electionRound.printAllParties();
}



void vote(ElectionRound& electionRound){
    string citizenId;
    int partyId;
    cout << "enter citizen ID, party ID ";
    cin >> citizenId >> partyId;
    Party* party = electionRound.getPartyByID(partyId);
    Citizen* voter = electionRound.getCitizenByID(citizenId);
    District* district=voter->getDistrict();
    district->addVote(voter, partyId);
    party->increaseNumberOfVotes();
}

void showElectionResults(ElectionRound& electionRound)
{
    electionRound.showElectionRoundDate();
    map <int, int> winningRep; //the key is paryID and the value is the number of winning representatives for each party.
    for (auto district: electionRound.getDistricts())
    {
        cout << "--------------" << *district << " -------------------" << endl;
        district->printElectionResult(electionRound.getParties(),winningRep);
    }
    cout << "-------------- Summary -------------------" << endl;
    vector<Party*> sortedParties = electionRound.getSortedParties();
    for (auto party : sortedParties)
    {
        cout << *party << endl
            << "   winning number of represantives-  " << winningRep[party->getID()] << endl
             << "   total number of votes from all districts- "<< party->getNumberOfVotes() << endl;
    }

}

ELECTION_ROUND_TYPE loadElectionRound(ElectionRound* &electionRound)
{
    int typenum;
    ELECTION_ROUND_TYPE type;
    string fileName;
    cout << "enter file name ";
    cin >> fileName;
    ifstream infile(fileName, ios::binary);
    if (!infile) {
        cout << "Error with infile" << endl;
        exit(-1);
    }
    infile.read(rcastc(&typenum), sizeof(typenum));
    type = (ELECTION_ROUND_TYPE)typenum;
    switch (type) {
    case ELECTION_ROUND_TYPE::regular:
        electionRound = new RegularElectionRound(infile);
        break;
    case ELECTION_ROUND_TYPE::simple:
        electionRound = new SimpleElectionRound(infile);
        break;
    }
    infile.close();
    return type;
}

void saveElectionRound(ElectionRound* electionRound)
{
    string fileName;
    cout << "enter file name ";
    cin >> fileName;
    ofstream outfile(fileName, ios::binary | ios::trunc);
    if (!outfile) {
        cout << "Error with infile" << endl;
        exit(-1);
    }
    electionRound->save(outfile);
    outfile.close();
}

