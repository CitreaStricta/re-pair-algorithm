#include <utility>
using namespace std;
class HeapNode
{
private:
    int* first;
    int* last;    
public:    
    HeapNode* parent;
    HeapNode* left;
    HeapNode* right;
    int frequency = 1;
    std::pair<int, int> _pair;
    HeapNode(std::pair<int, int> pair, int* address);
    ~HeapNode();
    void swap(HeapNode* node);
    void insert(HeapNode* node);
    void shiftUp();
    void increaseFrequency(int* address);
    void shiftDown();
};