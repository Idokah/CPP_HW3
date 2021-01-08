#pragma once
#include "Citizen.h"
#include "Party.h"
#include "vector"
#include "District.h"
#include "DividedDistrict.h"
#include "UnifiedDistrict.h"

template <class T>
class Builder {
public:
    virtual T construct(istream& in) = 0;
};

class CitizenBuilder : public Builder<Citizen*> {
public:
    CitizenBuilder(vector<District*> districts) {
        this->districts = districts;
    }
    virtual Citizen* construct(istream& in) {
        return new Citizen(in, this->districts);
    };
private:
    vector<District*> districts;
};

class PartyBuilder : public Builder<Party*> {
public:
    PartyBuilder(vector<Citizen*> citizens) {
        this->citizens = citizens;
    }
    virtual Party* construct(istream& in) {
        return new Party(in, this->citizens);
    };
private:
    vector<Citizen*> citizens;
};

class DistrictBuilder : public Builder<District*> {
public:
    virtual District* construct(istream& in) {
        int typenum;
        in.read(rcastc(&typenum), sizeof(typenum));
        DISTRICT_TYPE type = (DISTRICT_TYPE)typenum;
        switch (type) {
        case DISTRICT_TYPE::divided:
            return new DividedDistrict(in);
        case DISTRICT_TYPE::unified:
            return new UnifiedDistrict(in);
        }
    };
};