#include <iostream>
#include <fstream>
using namespace std;

class mflood
{
    public:
	mflood();
	~mflood();
	void writeLog();
    private:
	fstream log;
};

mflood::mflood()
{
    log.open("log", fstream::in | fstream::out | fstream::app);
}

mflood::~mflood()
{
    log.close();
}

void mflood::writeLog()
{
    log << "success" << endl;
}

int main()
{
    mflood m;
    m.writeLog();
}
