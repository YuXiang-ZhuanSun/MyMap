#include "MyMap.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	MyMap<int,int> * m= new MyMap<int,int>();
	for(int i=1;i<=100;i++){
		m->insert_MyPair(i,100-i);
	} 
	

	
	std::cout<<"ÖÐÐò±éÀú£º"<<std::endl;
	
	m->in_order();
	



	
	
	
	return 0;
}
