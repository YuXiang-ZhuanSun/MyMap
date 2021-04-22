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
			
		

			//1,处理p的上层
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

			//2,处理p的下层
			if (p == parent->right ) {
				//左旋
				
				MyPair<t1, t2>* rot = p->left;
				p->left = parent;
				parent->parent=p;
				parent->right=rot;
				if(rot){
					rot->parent = parent;			
				}				
			} else if (p == parent->left) {
				//右旋
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
			//如果父亲是黑色，直接插入就ok
			if (p->parent->color == BLACK) {
				return ;
			}

			//父亲一定是红色，爷爷一定是黑色
			MyPair<t1, t2>* grandpa = p->parent->parent;
			
			//确定叔叔
			MyPair<t1, t2>* uncle;
			if (grandpa->left == p->parent) {
				uncle = grandpa->right;
			} else {
				uncle = grandpa->left;
			}
			
			//情况1：爸爸红，爷爷黑，叔叔红（有叔叔）   情况1需要继续平衡
			//把爷爷变成红色的，叔叔变成黑色的
			if (uncle && uncle->color == RED) {
				uncle->color = BLACK;
				grandpa->color = RED;
				p->parent->color = BLACK;
				balance(grandpa);//此时爷爷可能会变成红红相连，或者爷爷是根，（继续平衡）
				return ;
			}

			//情况2：爸爸红，爷爷黑，叔叔黑（或者没有叔叔）   情况2不需要继续平衡
			//爸爸是左儿子情形
			if (grandpa->left == p->parent) {

				if (p == p->parent->right) {
					//情况2.1  父亲在左，儿子在右
					rotate(p);
					p->color = BLACK;
					p->parent->color = RED;
					rotate(p);
				} else {
					//情况2.2  父亲在左，儿子在左
					p->parent->color = BLACK;
					grandpa->color = RED;
					rotate(p->parent);
				}
			} else {
				//爸爸是右儿子
				if (p == p->parent->left) {
					//情况2.1 父亲在右，儿子在左
					rotate(p);
					p->color = BLACK;
					p->parent->color = RED;
					rotate(p);
				} else {
					//情况2.2  父亲在右，儿子在右
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
			红黑树插入   闪亮登场
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
