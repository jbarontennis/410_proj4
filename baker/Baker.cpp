/**
 * author James Baron
 * partner Caleb Gondek
 *
 * Caleb completed waiter
 * I completed baker
 * independently completed logger
 * 50/50% completed by both partners
 */
#include <mutex>
#include <condition_variable>
#include "../includes/externs.h"
#include "../includes/baker.h"
using namespace std;

Baker::Baker(int id):id(id)
{

}

Baker::~Baker()
{
}

void Baker::bake_and_box(ORDER &anOrder) {
	int numDonuts = anOrder.number_donuts;
	while(numDonuts>0){
			Box tmp;
			while(tmp.size()<=DOZEN && numDonuts>0){
				DONUT tmp2;
				if(!tmp.addDonut(tmp2)){
					break;
				}
				numDonuts--;
			}
			anOrder.boxes.push_back(tmp);

	}
}

void Baker::beBaker() {
	{
		std::unique_lock<mutex> lck(mutex_order_inQ);
		while(order_in_Q.size()==0 && !b_WaiterIsFinished){
			cv_order_inQ.wait(lck);
		}
		}
	while(!b_WaiterIsFinished || order_in_Q.size() > 0){
		ORDER tmp;
		{
		std::lock_guard<mutex> lck(mutex_order_inQ);
		tmp = order_in_Q.front();
		order_in_Q.pop();
		}
		bake_and_box(tmp);

		{
			std::lock_guard<mutex> lck(mutex_order_outQ);
			order_out_Vector.push_back(tmp);
		}
	}
}
