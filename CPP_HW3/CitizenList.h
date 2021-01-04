#pragma once
#include <iostream>
#include "Citizen.h"

using namespace std;

struct node
{
    Citizen* citizen;
    node *next;

    void save(ostream& out) const;
    void load(istream &in, District** districts, int districtsSize);
};


class CitizenList
{
    private:
        node *head,*tail;
        int len;
        node* createNewNode(Citizen* citizen);
    public:
        CitizenList();
        CitizenList(istream& in, Citizen** citizens, int citizensSize);
        ~CitizenList();
        void addNode(Citizen* citizen);
        void printFirstNRepresantives(const int n);

        void save(ostream& out) const;
        void load(istream& in, Citizen** citizens, int citizensSize);
        void saveIDs (ostream& out) const;

        friend ostream& operator<<(ostream&, const CitizenList&);
};