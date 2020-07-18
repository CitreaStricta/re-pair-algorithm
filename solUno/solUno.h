#include "../LinkedList/LinkedList.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>

using namespace std;

class solUno
{
private:
    LinkedList *list;
public:
    solUno(LinkedList*);
    ~solUno();
    vector<pair<int, pair<int, int>>>* Compress();
    void ParCompress(int, pair<int, int>);
    map<pair<int, int>, int>* fillMap();
};