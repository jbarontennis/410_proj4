#include <mutex>

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
			while(tmp.size()<=DOZEN){
				DONUT tmp2;
				if(!tmp.addDonut(tmp2)){
					break;
				}
			}
			anOrder.boxes.push_back(tmp);

	}
}

void Baker::beBaker() {
	std::queue<ORDER> order_in_Q;
	std::vector<ORDER> order_out_Vector;
	bool b_WaiterIsFinished;
	while(order_in_Q.size()>0|| b_WaiterIsFinished){
		ORDER tmp = order_in_Q.front();
		bake_and_box(tmp);
		order_in_Q.pop();
	}
}
