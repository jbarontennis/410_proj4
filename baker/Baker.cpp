#include <mutex>
#include <condition_variable>
#include "../includes/externs.h"
#include "../includes/baker.h"
using namespace std;
mutex m;

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
			while(tmp.size()<=DOZEN){
				DONUT tmp2;
				if(!tmp.addDonut(tmp2)){
					break;
				}
			}
			anOrder.boxes.push_back(tmp);

	}
}
//#ifdef USE_CONDITION_VAR
void Baker::beBaker() {
	{
		std::unique_lock<mutex> lck(mutex_order_inQ);
		cv_order_inQ.wait(lck);
	}
	while(!b_WaiterIsFinished && order_in_Q.size() > 0){
		std::unique_lock<mutex> lock(m);
		ORDER tmp = order_in_Q.front();
		bake_and_box(tmp);
		order_in_Q.pop();
		order_out_Vector.push_back(tmp);

	}
}
//#endif
