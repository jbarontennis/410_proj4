#include <string>
#include <fstream>
#include "stdlib.h"

#include "../includes/waiter.h"

using namespace std;

Waiter::Waiter(int id,std::string filename):id(id),myIO(filename){
}

Waiter::~Waiter()
{
}

//gets next Order(s) from file_IO
int Waiter::getNext(ORDER &anOrder){
	return (getNext(anOrder));

}

void Waiter::beWaiter() {


}

