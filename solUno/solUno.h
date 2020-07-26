#include "../LinkedList/LinkedList.h"
#include <iostream>
#include <utility>
#include <vector>
#include <map>

using namespace std;

class solUno
{
private:
    LinkedList *list;
public:
    solUno();
    ~solUno();
    void Compress(LinkedList*);
    pair<pair<int, int>, int> return_most_freq();
    void ParCompress(int, pair<int, int>);
};