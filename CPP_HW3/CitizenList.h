#pragma once
#include <iostream>
#include "Citizen.h"

using namespace std;

struct node
{
    Citizen* citizen;
    node *next;

    void save(ostream& out) const;
    void load(istream &in, vector<District*> districts);
};


class CitizenList
{
    private:
        node *head,*tail;
        int len;
        node* createNewNode(Citizen* citizen);
    public:
        CitizenList();
        CitizenList(istream& in, vector<Citizen*> citizens);
        ~CitizenList();
        void addNode(Citizen* citizen);
        void printFirstNRepresantives(const int n);

        void save(ostream& out) const;
        void load(istream& in, vector<Citizen*> citizens);
        void saveIDs (ostream& out) const;

        friend ostream& operator<<(ostream&, const CitizenList&);
};