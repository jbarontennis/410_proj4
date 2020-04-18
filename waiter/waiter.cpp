/**
 * author James Baron
 * partner Caleb Gondek
 *
 * Caleb completed waiter
 * I completed baker
 * independently completed logger
 * 50/50% completed by both partners
 */
#include <string>
#include <fstream>
#include <condition_variable>
#include <sstream>
#include "stdlib.h"
#include "../includes/externs.h"

#include "../includes/waiter.h"

using namespace std;

Waiter::Waiter(int id,std::string filename):id(id),myIO(filename){
}

Waiter::~Waiter()
{
}

//gets next Order(s) from file_IO
int Waiter::getNext(ORDER &anOrder){
	return (myIO.getNext(anOrder));

}

void Waiter::beWaiter() {
	int check;
		do {
			ORDER anOrder;
			check = getNext(anOrder);
			if (check == SUCCESS) {
				std::lock_guard<mutex> lock(mutex_order_inQ);
				order_in_Q.push(anOrder); // If successful, push to the order queue
				cv_order_inQ.notify_all();
			}

			//Otherwise, fail out of the program (unless it's NO_ORDERS)
			if (check == COULD_NOT_OPEN_FILE || check == FAIL
					|| check == UNINITIALIZED) {
				throw new exception();
			}

		} while (check == SUCCESS);
		b_WaiterIsFinished = true;
}

