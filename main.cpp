#include "MyMap.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {

	MyMap<int, int> * m = new MyMap<int, int>();
	for (int i = 1; i <= 1000; i++) {
		m->insert_MyPair(i, 1000 - i);
	}

	std::cout << "查找操作：" << std::endl;
	MyPair<int, int> * p = m->find(6);
	p->print();

	std::cout << "中序遍历：" << std::endl;
	m->in_order();







	return 0;
}
