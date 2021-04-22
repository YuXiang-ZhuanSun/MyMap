#include "MyMap.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {

	clock_t begin = clock();
	
	//删除MyMap.h的217行，可测试BST情形建树时间 
	MyMap<int, int> * m = new MyMap<int, int>();
	for (int i = 1; i <= 100000; i++) {
		m->insert_MyPair(i, 1000 - i);
	}
	clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "建树耗时：" <<time_spent<< std::endl;
    
	std::cout << "查找操作：" << std::endl;
	MyPair<int, int> * p = m->find(6);
	if(p){
		p->print();
	}

	std::cout << "中序遍历：" << std::endl;
	m->in_order();







	return 0;
}
