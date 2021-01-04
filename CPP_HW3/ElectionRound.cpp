#include "ElectionRound.h"
#include "District.h"
#include "DividedDistrict.h"
#include "UnifiedDistrict.h"

ElectionRound::ElectionRound():date({0,0,0}), votersPhySize(1), votersLogSize(0), votersBook(nullptr),
                            parties(nullptr),partiesLogSize(0),partiesPhySize(1),districts(nullptr),districtsLogSize(0), districtsPhySize(1)
{
}

ElectionRound::ElectionRound(const int day, const int month, const int year) : date({ day, month, year }), districtsLogSize(0), districtsPhySize(1), votersLogSize(0), votersPhySize(1), partiesPhySize(1), partiesLogSize(0)
{
	this->parties = new Party*[partiesPhySize];
    this->districts = new District*[districtsPhySize];
    this->votersBook = new Citizen*[votersPhySize];
}

ElectionRound::~ElectionRound()
{
    for (int i = 0; i < this->votersLogSize; ++i) {
        delete this->votersBook[i];
    }
    delete[] this->votersBook;

    for (int i = 0; i < this->partiesLogSize; ++i) {
        delete this->parties[i];
    }
    delete[] this->parties;

    for (int i = 0; i < this->districtsLogSize; ++i) {
        delete this->districts[i];
    }
    delete[] this->districts;
}

void ElectionRound::addDistrict(District* district){}

District** ElectionRound::getDistricts() const { return this->districts; }

int ElectionRound::getDistrictLogSize() const { return this->districtsLogSize; }

int ElectionRound::getPartiesLogSize() const { return this->partiesLogSize; }

Party** ElectionRound::getPartiesArr() const
{
    return parties;
}

void ElectionRound::increaseDistrictsArrSize() {
	this->districtsPhySize *= 2;
	District** newDistricts = new District*[districtsPhySize];
	for (int i = 0; i < districtsLogSize; i++)
	{
		newDistricts[i] = this->districts[i];
	}
    delete[] this->districts;
    this->districts = newDistricts;
}

void ElectionRound::addCitizen(Citizen* citizen)
{
	if (this->votersLogSize == this->votersPhySize)
	{
		this->increaseVotersArrSize();
	}
	this->votersBook[this->votersLogSize++] = citizen;
	citizen->getDistrict()->increaseCitizenNum();
}

void ElectionRound::increaseVotersArrSize() {
	this->votersPhySize *= 2;
	Citizen** newVotersBook = new Citizen*[votersPhySize];
	for (int i = 0; i < this->votersLogSize; i++)
	{
		newVotersBook[i] = this->votersBook[i];
	}
	delete[] this->votersBook;
	this->votersBook = newVotersBook;
}

void ElectionRound::addParty(Party* party)
{
	if (this->partiesLogSize == this->partiesPhySize)
	{
		this->increasePartiesArrSize();
	}
	this->parties[this->partiesLogSize++] = party;
}

void ElectionRound::increasePartiesArrSize() {
	this->partiesPhySize *= 2;
	Party** newParties = new Party*[partiesPhySize];
	for (int i = 0; i < this->partiesLogSize; i++)
	{
		newParties[i] = this->parties[i];
	}
    delete[] this->parties;
    this->parties = newParties;
}

Citizen* ElectionRound::getCitizenByID(const char* representiveID) const
{
	for (int i = 0; i < votersLogSize; ++i)
	{
		if (strcmp(this->votersBook[i]->getID(), representiveID) == 0)
			return this->votersBook[i];
	}

	return nullptr;
}

Party* ElectionRound::getPartyByID(int partyId) const
{
    for (int i = 0; i < this->partiesLogSize; ++i)
    {
        if (this->parties[i]->getID() == partyId)
            return this->parties[i];
    }

    return nullptr;
}

District* ElectionRound::getDistrictByID(const int districtID) const
{
    for (int i = 0; i < this->districtsLogSize; ++i)
    {
        if (this->districts[i]->getID() == districtID)
            return this->districts[i];
    }

    return nullptr;
}

void ElectionRound::printAllDistricts() const {}

void ElectionRound::printAllCitizens() const
{
    for (int i = 0; i < votersLogSize; ++i) {
        cout<<*(votersBook[i])<<endl;
    }
}

void ElectionRound::printAllParties() const
{
    for (int i = 0; i < partiesLogSize; ++i) {
        cout << *(parties[i])<<endl;
    }
}

Party** ElectionRound::getSortedParties()
{
    Party** partiesPointers = new Party*[this->partiesLogSize];
    for (int i = 0; i < this->partiesLogSize; ++i) {
        partiesPointers[i] = this->parties[i];
    }
    mergeSort(partiesPointers, this->partiesLogSize);
    return partiesPointers;
}

bool ElectionRound::isCitizenIdIsAlreadyExist(const char* citizenID) const
{
    for (int i = 0; i < votersLogSize; i++)
    {
        if (strcmp(citizenID, votersBook[i]->getID()) == 0)
        {
            cout << "this ID is already exist." << endl;
            return true;
        }
            
    }
    return false;
}

void ElectionRound::mergeSort(Party** pointersArr, int size) {
    Party** temp;
    if (size <= 1) return;
    else {
        mergeSort(pointersArr, size/2);
        mergeSort(pointersArr + size/2, size - size/2);
        temp = new Party*[size];
        merge(pointersArr,pointersArr + size/2,size/2, size - size/2, temp);
        for (int i=0; i < size; i++){
            pointersArr[i] = temp[i];
        }

        delete[] temp;
    }
}

void ElectionRound::merge(Party** pointersArr1, Party** pointersArr2,int size1,int size2,Party** res)
{
    Party* currentValue1;
    Party* currentValue2;
    int i1=0,i2=0,iRes=0;
    while (i1<size1 && i2<size2)
    {
        currentValue1=*(pointersArr1+i1);
        currentValue2=*(pointersArr2+i2);
        if (currentValue1->getNumberOfWinningRepresantives() > currentValue2->getNumberOfWinningRepresantives())
        {
            res[iRes] = pointersArr1[i1];
            iRes++;
            i1++;
        }
        else
        {
            res[iRes] = pointersArr2[i2];
            iRes++;
            i2++;
        }
    }
    while (i1<size1)
    {
        res[iRes] = pointersArr1[i1];
        iRes++;
        i1++;
    }
    while (i2<size2)
    {
        res[iRes] = pointersArr2[i2];
        iRes++;
        i2++;
    }
}

void ElectionRound::save(ostream& out) const
{
    District** districts;
    Citizen** votersBook;
    Party** parties;
    this->date.save(out);

    out.write(rcastcc(&this->districtsLogSize), sizeof(this->districtsLogSize));
    out.write(rcastcc(&this->districtsPhySize), sizeof(this->districtsPhySize));
    for (int i = 0; i < this->districtsLogSize; i++)
        this->districts[i]->save(out);

    out.write(rcastcc(&this->votersLogSize), sizeof(this->votersLogSize));
    out.write(rcastcc(&this->votersPhySize), sizeof(this->votersPhySize));
    for (int i = 0; i < this->votersLogSize; i++)
        this->votersBook[i]->save(out);

    out.write(rcastcc(&this->partiesLogSize), sizeof(this->partiesLogSize));
    out.write(rcastcc(&this->partiesPhySize), sizeof(this->partiesPhySize));
    for (int i = 0; i < this->partiesLogSize; i++)
        this->parties[i]->save(out);
}

void ElectionRound::showElectionRoundDate() const
{
    cout << "-------- Election Round Date: " << this->date.day << "/" <<
        this->date.month << "/" << this->date.year << "--------" << endl;
}

void ElectionRound::Date::save(ostream& out) const
{
    out.write(rcastcc(&year), sizeof(year));
    out.write(rcastcc(&month), sizeof(month));
    out.write(rcastcc(&day), sizeof(day));
}

void ElectionRound::load(istream& in)
{
    District** districts;
    Citizen** votersBook;
    Party** parties;

    
    int day, month, year;
    in.read(rcastc(&year), sizeof(year));
    in.read(rcastc(&month), sizeof(month));
    in.read(rcastc(&day), sizeof(day));
    this->date.year = year;
    this->date.month = month;
    this->date.day = day;

    in.read(rcastc(&this->districtsLogSize), sizeof(this->districtsLogSize));
    in.read(rcastc(&this->districtsPhySize), sizeof(this->districtsPhySize));
    this->districts = new District * [this->districtsPhySize];
    int typenum;
    DISTRICT_TYPE type;
    for (int i = 0; i < this->districtsLogSize; i++)
    {
        in.read(rcastc(&typenum), sizeof(typenum));
        type = (DISTRICT_TYPE)typenum;
        switch (type) {
        case DISTRICT_TYPE::divided:
            this->districts[i] = new DividedDistrict(in);
            break;
        case DISTRICT_TYPE::unified:
            this->districts[i] = new UnifiedDistrict(in);
            break;
        }
        if (i == this->districtsLogSize - 1)//last iteration
            this->districts[i]->setGenerateIDtoValue(this->districts[i]->getID());
    }

    in.read(rcastc(&this->votersLogSize), sizeof(this->votersLogSize));
    in.read(rcastc(&this->votersPhySize), sizeof(this->votersPhySize));
    this->votersBook = new Citizen* [this->votersPhySize];
    for (int i = 0; i < this->votersLogSize; i++)
    {
        this->votersBook[i] = new Citizen(in,this->districts, this->districtsLogSize);
    }

    in.read(rcastc(&this->partiesLogSize), sizeof(this->partiesLogSize));
    in.read(rcastc(&this->partiesPhySize), sizeof(this->partiesPhySize));
    this->parties = new Party * [this->partiesPhySize];
    for (int i = 0; i < this->partiesLogSize; i++)
    {
        this->parties[i] = new Party(in, this->votersBook,this->votersLogSize);
    }
}