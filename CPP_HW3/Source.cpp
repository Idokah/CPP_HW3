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
void loadElectionRound(ElectionRound* &electionRound);
void saveElectionRound(ElectionRound* electionRound);
bool isValidCitizen(const char* action, Citizen* citizen);
bool isValidParty(const char* action, Party* party);
bool isValidDistrictId(const int districtsLogSize, const int districtId);


using namespace std;

enum class OPTIONS {
    addDistrict = 1,
    addCitizen = 2,
    addParty = 3,
    addCitizenAsPartyRepresentive = 4,
    showAllDistricts = 5,
    showAllCitizens = 6,
    showAllParties = 7,
    vote = 8,
    showElectionResults = 9,
    exit = 10,
    saveElectionRound = 11,
    loadElectionRound = 12
};

enum class ELECTION_ROUND_OPTIONS {
    newElectionRound = 1,
    loadElectionRound = 2
};


int main()
{
    ElectionRound* electionRound=nullptr;
    OPTIONS option=OPTIONS::showElectionResults;
    ELECTION_ROUND_OPTIONS electionRoundOption=ELECTION_ROUND_OPTIONS::newElectionRound;
    int day = 1, month = 1, year = 1, electionRoundTypeNum = 0;
    ELECTION_ROUND_TYPE electionRoundType;
    int optionNum, electionRoundOptionNum = 0;
    
    cout << "enter one of the options-" << endl
        << "1 - add new election round" << endl
        << "2- load election round" << endl;
    cin >> electionRoundOptionNum;
    electionRoundOption = (ELECTION_ROUND_OPTIONS)electionRoundOptionNum;
    switch (electionRoundOption)
    {
        case ELECTION_ROUND_OPTIONS::newElectionRound:
        {
            cout << "enter elections date DD MM YYYY ";
            cin >> day >> month >> year;
            cout << "enter elections round type (0 for regular, 1 for simple) ";
            cin >> electionRoundTypeNum;
            while (electionRoundTypeNum != 0 && electionRoundTypeNum != 1)
            {
                cout << "Wrong input please try again" << endl;
                cout << "enter elections round type (0 for regular, 1 for simple) ";
                cin >> electionRoundTypeNum;
            }
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
        {
            loadElectionRound(electionRound);

        }
    }
   


    while (option != OPTIONS::exit) {
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

        switch (option)
        {
            case OPTIONS::addDistrict :
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
    delete electionRound;
}



void addDistrict(ElectionRound &electionRound) {
    char name[MAX_STRING_LEN];
    int representativeNum; 
    int districtTypeNum;
    DISTRICT_TYPE districtType;
    District* district;
    cout << "enter name, number of representative and district type (1 for divided, 0 for unified) ";
    cin >> name >> representativeNum >> districtTypeNum;
    districtType = (DISTRICT_TYPE)districtTypeNum;
    if (representativeNum <= 0) {
        cout << "Sorry a district have a positive number of represenative number" << endl;
        return;
    }
    if (districtType == DISTRICT_TYPE::unified) district = new UnifiedDistrict(name, representativeNum);
    else district = new DividedDistrict(name, representativeNum);
    electionRound.addDistrict(district);
}

void addCitizen(ElectionRound& electionRound, ELECTION_ROUND_TYPE electionRoundType) {
    char name[MAX_STRING_LEN];
    char id[MAX_STRING_LEN];
    int birthYear, districtNum;
    cout << "enter name, id, birth year, district number ";
    cin >> name >> id >> birthYear >> districtNum;
    districtNum = (electionRoundType == ELECTION_ROUND_TYPE::regular) ? districtNum : 1;
    District* district = electionRound.getDistrictByID(districtNum);
    if (electionRound.isCitizenIdIsAlreadyExist(id) || !isValidDistrictId(electionRound.getDistrictLogSize(), districtNum)) return;
    Citizen* citizen = new Citizen(name, id, birthYear, district);
    electionRound.addCitizen(citizen);
}

void addParty(ElectionRound& electionRound) {
    char name[MAX_STRING_LEN];
    char id[MAX_STRING_LEN];
    cout << "enter name and the party head's id ";
    cin >> name >> id;
    Citizen* head = electionRound.getCitizenByID(id);
    if (!isValidCitizen("addParty", head)) return;
    Party* party = new Party(name, head);
    electionRound.addParty(party);
    head->setIsPartyMember();
}

void setCitizenAsPartyRepresentive(ElectionRound& electionRound, ELECTION_ROUND_TYPE electionRoundType) {
    char representiveId[MAX_STRING_LEN];
    int partyId;
    int districtId;
    cout << "enter representive ID, party ID, district ID ";
    cin >> representiveId >> partyId >> districtId;
    districtId = (electionRoundType == ELECTION_ROUND_TYPE::regular) ? districtId : 1;
    Citizen *citizen = electionRound.getCitizenByID(representiveId);
    if (!isValidCitizen("setCitizenAsPartyRepresentive", citizen) || !isValidDistrictId(electionRound.getDistrictLogSize(), districtId)) return;
    citizen->setIsPartyMember();
    Party *party = electionRound.getPartyByID(partyId);
    if (!isValidParty("setCitizenAsPartyRepresentive", party)) return;
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
    char citizenId[MAX_STRING_LEN];
    int partyId;
    cout << "enter citizen ID, party ID ";
    cin >> citizenId >> partyId;
    Party* party = electionRound.getPartyByID(partyId);
    if (!isValidParty("vote", party)) return;

    Citizen* voter = electionRound.getCitizenByID(citizenId);
    if (voter == NULL) { 
        cout << "there is no such citizen" << endl;
        return;
    };

    District* district=voter->getDistrict();
    district->addVote(voter, partyId);
    party->increaseNumberOfVotes();
}

void showElectionResults(ElectionRound& electionRound){
    District* district;
    Party* party;
    char* headName;
    int numOfExistsPartiesInDistrict, *numOfRepresantivesPerParty=nullptr, *electionResults;
    float *percentagePerParty=nullptr;
    electionRound.showElectionRoundDate();
    for (int i = 0; i < electionRound.getDistrictLogSize(); ++i) {

        district = electionRound.getDistricts()[i];
        cout << "--------------" << *district << " -------------------" << endl;
        district->printElectionResult(electionRound.getPartiesLogSize(),electionRound.getPartiesArr());
    }
    cout << "-------------- Summary -------------------" << endl;
    Party** parties = electionRound.getSortedParties();
    for (int i = 0; i < electionRound.getPartiesLogSize(); i++) {
        cout <<*parties[i]<<endl
             << "   winning number of represantives-  " << parties[i]->getNumberOfWinningRepresantives() << endl
             << "   total number of votes from all districts- "<< parties[i]->getNumberOfVotes() << endl;
    }

    delete[] percentagePerParty;
    delete[] numOfRepresantivesPerParty;
    delete[] parties;
}

void loadElectionRound(ElectionRound* &electionRound)
{
    char filePrefix;
    int typenum;
    ELECTION_ROUND_TYPE type;
    char fileName[MAX_STRING_LEN];
    cout << "enter file name ";
    cin >> fileName;
    ifstream infile(fileName, ios::binary);
    if (!infile) {
        cout << "Error with infile" << endl;
        exit(-1);
    }
    infile.read(&filePrefix, 1);
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
}

void saveElectionRound(ElectionRound* electionRound)
{
    char fileName[MAX_STRING_LEN];
    cout << "enter file name ";
    cin >> fileName;
    ofstream outfile(fileName, ios::binary | ios::trunc);
    outfile.write(fileName, sizeof(char));
    if (!outfile) {
        cout << "Error with infile" << endl;
        exit(-1);
    }
    electionRound->save(outfile);
    outfile.close();
}

// ------------------------ validation function -----------------------


bool isValidCitizen(const char* action, Citizen* citizen)  {
    if (citizen == NULL) {
        cout << action << " -there is no such citizen." << endl;
        return false;
    }
    if (citizen->getIsPartyMember()) {
        cout << action << " -already set as represantive or head." << endl;
        return false;
    }
    return true;
}

bool isValidParty(const char* action, Party* party)  {
    if (party == NULL) {
        cout << action << " -there is no such party." << endl;
        return false;
    }
    return true;
}

bool isValidDistrictId(const int districtsLogSize, const int districtId) 
{
    if (districtId > districtsLogSize)
    {
        cout << "There is no such District." << endl;
        return false;
    }
    return true;
}
