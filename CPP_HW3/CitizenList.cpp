#include "CitizenList.h"
#include "consts.h"

node* CitizenList::createNewNode(Citizen* citizen){
    node* newNode = new node();
    newNode->citizen = citizen;
    newNode->next = NULL;
    return newNode;
}

CitizenList::CitizenList() : len(0) {
    this->head = NULL;
    this->tail = NULL;
}

CitizenList::CitizenList(istream& in, Citizen** citizens, int citizensSize) : CitizenList()
{
    this->load(in,citizens,citizensSize);
}

CitizenList::~CitizenList()
{
    node* head = this->head;
    node* next = nullptr;
    while (head != nullptr)
    {
        next = head->next;
        delete head;
        head=next;
    }
}

void CitizenList::addNode(Citizen* citizen)
{
    node *newNode = this->createNewNode(citizen);
    if(head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail -> next = newNode;
        tail = tail->next;
    }
    this->len++;
}

void CitizenList::printFirstNRepresantives(const int n)
{
    int i;
    node* curr = this->head;
    for (i = 0; (i < n) && (curr != NULL); i++)
    {
        cout << "           " << *(curr->citizen) << endl;
        curr = curr->next;
    }
    if (i < n) cout << "            there aren't enough represantives" << endl;
}

ostream& operator<<(ostream& os, const CitizenList& citizenList)
{
    node* curr = citizenList.head;
    while (curr != nullptr)
    {
        cout << "           " << *(curr->citizen) << endl;
        curr = curr->next;
    }
    return os;
}

void CitizenList::save(ostream& out) const
{
    out.write(rcastcc(&this->len), sizeof(this->len));
    node* curr = this->head;
    while (curr != nullptr)
    {
        curr->save(out);
        curr = curr->next;
    }
}


void CitizenList::load(istream& in, Citizen** citizens, int citizensSize) {
    
    int Len;
    in.read(rcastc(&Len), sizeof(Len));
    int idLen;
    char citizenId[MAX_STRING_LEN];
    for (int i = 0; i < Len; ++i) {
        in.read(rcastc(&idLen), sizeof(idLen));
        in.read(rcastc(citizenId), sizeof(char) * idLen);
        citizenId[idLen] = '\0';
        for (int i = 0; i < citizensSize; i++)
        {
            if (strcmp(citizens[i]->getID(), citizenId) == 0)
            {
                this->addNode(citizens[i]);
                break;
            }
        }
    }
}

void CitizenList::saveIDs(ostream& out) const
{
    node* curr = this->head;
    out.write(rcastcc(&this->len), sizeof(this->len));
    char* citizenID;
    int idLen;
    for (int i = 0; i < this->len; i++)
    {
        citizenID = curr->citizen->getID();
        idLen = strlen(citizenID);
        out.write(rcastcc(&idLen), sizeof(idLen));
        out.write(rcastcc(citizenID), sizeof(char) * idLen);
        curr=curr->next;
    }
}

void node::save(ostream& out) const
{
    this->citizen->save(out);
}

void node::load(istream &in, District** districts, int districtsSize) {
    this->citizen->load(in, districts,districtsSize);
}
