#include<bits/stdc++.h>



enum COLOR {
	RED = 0,
	BLACK = 1
};

template<typename t1, typename t2>
class MyPair {
	public:
		t1 name;
		t2 value;
		COLOR color;
		MyPair<t1, t2>* parent;
		MyPair<t1, t2>* left;
		MyPair<t1, t2>* right;


		MyPair(t1 n, t2 v, COLOR c = RED, MyPair<t1, t2>* p = NULL, MyPair<t1, t2>* l = NULL, MyPair<t1, t2>* r = NULL): name(n), value(v), color(c), parent(p), left(l), right(r) {

		}

		void set_position(MyPair<t1, t2>* p, MyPair<t1, t2>* l = NULL, MyPair<t1, t2>* r = NULL) {
			parent = p;
			left = l;
			right = r;
		}

		void print() {
			std::cout << "key: " << name << ", value: " << value;

			if (color == RED) {
				std::cout << ", color: RED ";
			} else {
				std::cout << ", color: BLACK";
			}
			std::cout << std::endl;
		}

		~MyPair() {

		}

};

template<typename t1, typename t2>
class  MyMap {
	public:
		MyPair<t1, t2>* root;

		MyMap(MyPair<t1, t2>* r = NULL): root(r) {

		}

		MyPair<t1, t2>* find(t1 n) {
			MyPair<t1, t2>* p = root;
			while (p && p->name != n) {
				if (n < p->name) {
					p = p->left;
				} else {
					p = p->right;
				}
			}
			return p;
		}


		void rotate(MyPair<t1, t2>* p) {
			MyPair<t1, t2>* parent = p->parent;
			
		

			//1,����p���ϲ�
			if (p->parent->parent) {
				MyPair<t1, t2>* grandpa = p->parent->parent;
				if (grandpa->left == p->parent) {
					grandpa->left = p;
					
				} else {
					grandpa->right = p;
				}
				p->parent = grandpa;
				parent->parent = p;
			}else{
				root=p;	
				p->parent=NULL;
			}

			//2,����p���²�
			if (p == parent->right ) {
				//����
				
				MyPair<t1, t2>* rot = p->left;
				p->left = parent;
				parent->parent=p;
				parent->right=rot;
				if(rot){
					rot->parent = parent;			
				}				
			} else if (p == parent->left) {
				//����
				MyPair<t1, t2>* rot = p->right;
				p->right = parent;
				parent->parent=p;
				parent->left = rot;
				if(rot){
					rot->parent = parent;
				}
			}
			return;
		}

		void balance(MyPair<t1, t2>* p) { 
			if (p == root) {
				p->color = BLACK;
				return ;
			}
			//��������Ǻ�ɫ��ֱ�Ӳ����ok
			if (p->parent->color == BLACK) {
				return ;
			}

			//����һ���Ǻ�ɫ��үүһ���Ǻ�ɫ
			MyPair<t1, t2>* grandpa = p->parent->parent;
			
			//ȷ������
			MyPair<t1, t2>* uncle;
			if (grandpa->left == p->parent) {
				uncle = grandpa->right;
			} else {
				uncle = grandpa->left;
			}
			
			//���1���ְֺ죬үү�ڣ�����죨�����壩   ���1��Ҫ����ƽ��
			//��үү��ɺ�ɫ�ģ������ɺ�ɫ��
			if (uncle && uncle->color == RED) {
				uncle->color = BLACK;
				grandpa->color = RED;
				p->parent->color = BLACK;
				balance(grandpa);//��ʱүү���ܻ��ɺ������������үү�Ǹ���������ƽ�⣩
				return ;
			}

			//���2���ְֺ죬үү�ڣ�����ڣ�����û�����壩   ���2����Ҫ����ƽ��
			//�ְ������������
			if (grandpa->left == p->parent) {

				if (p == p->parent->right) {
					//���2.1  �������󣬶�������
					rotate(p);
					p->color = BLACK;
					p->parent->color = RED;
					rotate(p);
				} else {
					//���2.2  �������󣬶�������
					p->parent->color = BLACK;
					grandpa->color = RED;
					rotate(p->parent);
				}
			} else {
				//�ְ����Ҷ���
				if (p == p->parent->left) {
					//���2.1 �������ң���������
					rotate(p);
					p->color = BLACK;
					p->parent->color = RED;
					rotate(p);
				} else {
					//���2.2  �������ң���������
					p->parent->color = BLACK;
					grandpa->color = RED;
					rotate(p->parent);
				}
			}
			return;
		}

		void insert_MyPair(t1 n, t2 v) {
			MyPair<t1, t2>* p0 = root;
			MyPair<t1, t2>* p = root;


			if (!root) {
				MyPair<t1, t2>* new_p = new MyPair<t1, t2>(n, v, BLACK);
				root = new_p;
				new_p->set_position(NULL);

				return ;
			}

			while (p && p->name != n) {
				p0 = p;
				if (n < p->name) {
					p = p->left;
				} else {
					p = p->right;
				}
			}
			if (p) {
				p->value = v;
				return ;
			}

			MyPair<t1, t2>* new_p = new MyPair<t1, t2>(n, v);
			if (n < p0->name) {
				p0->left = new_p;
			} else {
				p0->right = new_p;
			}
			new_p->set_position(p0);

			/*
			���������   �����ǳ�
			*/
			balance(new_p);
			return ;
		}

		int delete_MyPair(t1 n) {
			MyPair<t1, t2> *p0;
			MyPair<t1, t2> *p = find(n);
			if (!p) {
				return 0;
			}
			while (p) {
				if (p->left) {
					delete_MyPair(p->left);
				}
				p0 = p;
				p = p->right;
				free(p0);
			}

			return 1;
		}
		
		
		void in_order(){
			in_order_travesal(root);		
		}
		
		void in_order_travesal(MyPair<t1,t2>* r){
			if(r){
				in_order_travesal(r->left);
				r->print();
				in_order_travesal(r->right);
			}
		}

		~MyMap() {
			delete_MyPair(root->name);
		}



};
