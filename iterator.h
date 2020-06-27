struct nodo
{
	int n;
	nodo *next;
	nodo *prev;
};

class Iterator
{
private:
    struct nodo* _begin;
    struct nodo* _end;
    struct nodo* _nodo;    
public:
    Iterator(struct nodo* begin, struct nodo* end);
    ~Iterator();
    Iterator& operator++(int);
    Iterator& operator--(int);
    void goToStart();
    struct nodo* begin();
    struct nodo* end();
    struct nodo* nodo(); 
};