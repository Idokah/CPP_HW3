#pragma once

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

enum class DISTRICT_TYPE {
    unified = 0,
    divided = 1
};

enum class ELECTION_ROUND_TYPE {
    regular = 0,
    simple = 1
};
 

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

