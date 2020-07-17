#include <utility>
#include <vector>
#include <map>

using namespace std;

class MaxHeap2
{
private:
    int _size = 0;
    vector<pair<int, pair<int, int>>>* vect;
    std::map<pair<int, int>, int> posiciones;
    int parent(int index) { return (index - 2) >> 2; }; // i / 2 - 1
    int left(int index) { return (index << 2) + 1; }; // i * 2 + 1
    int right(int index) { return (index << 2) + 2; }; // i * 2 + 2
public:
    MaxHeap2();
    ~MaxHeap2();
    std::pair<int, std::pair<int, int>> getMax();
    std::pair<int, std::pair<int, int>> extractMax();    
    void swap(int i1, int i2);
    void insert(std::pair<int, int> pair);
    void shiftUp(int index);
    void increaseFrequency(std::pair<int, int> pair); // modificar clave
    void shiftDown(int index);
    void delete_pair(std::pair<int, int> pair);
};