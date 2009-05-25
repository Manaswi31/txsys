#include <list>
using std::list;
#define iter (list<int>::iterator) 

class Container
{
    public:
	iter lookUp(int);
	void deleteItem(int);
    private:
	list <int> myList;
};

iter Container::lookUp(int toFind)
{
    iter it;
    for (it=myList.begin(); it!=myList.end(); it++) {
	if (*it==toFind) {return it;}
    }
}

void Container::deleteItem(int toDel)
{
    iter it;
    it = lookUp(toDel);
    if (it!=NULL) {
	myList.erase(it);
    }
}

int main()
{
}


