#include "MyMap.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {

	clock_t begin = clock();
	
	//ɾ��MyMap.h��217�У��ɲ���BST���ν���ʱ�� 
	MyMap<int, int> * m = new MyMap<int, int>();
	for (int i = 1; i <= 100000; i++) {
		m->insert_MyPair(i, 1000 - i);
	}
	clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "������ʱ��" <<time_spent<< std::endl;
    
	std::cout << "���Ҳ�����" << std::endl;
	MyPair<int, int> * p = m->find(6);
	if(p){
		p->print();
	}

	std::cout << "���������" << std::endl;
	m->in_order();







	return 0;
}
