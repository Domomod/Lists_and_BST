#pragma once

#include<assert.h>

class node
{
public:
	node(int v = 0) {
		val = v;
		F = nullptr;
		L = nullptr;
		R = nullptr;
	}
	~node() {
	}

	//setters
	void setVal(int v) { val = v; }
	void setF(node* f) { F = f; }
	void setL(node* l) { 
		L = l;
		if (l != nullptr)
			l->setF(this);
	}
	void setR(node* r) { 
		R = r; 
		if (R != nullptr)
			R->setF(this);
	}

	//getters
	int getVal() { return val; }
	node* prevF() { return F; }
	node* nextL() { return L; }
	node* nextR() { return R; }

	node* maxLeft(){
		node* temp = this;
		while (temp->nextL() != nullptr) {
			temp = temp->nextL();
		}
		return temp;
	}

	node* maxRight(){
		node* temp = this;
		while (temp->nextR() != nullptr) {
			temp = temp->nextR();
		}
		return temp;
	}

	//operatory
	//dla liczb
	bool operator <(int i) { return val < i; }
	bool operator >(int i) { return val > i; }
	bool operator <=(int i) { return val <= i; }
	bool operator >=(int i) { return val >= i; }
	bool operator ==(int i) { return val == i; }
	//dla tych samych klas
	bool operator <(node i) { return val < i.getVal(); }
	bool operator >(node i) { return val >  i.getVal(); }
	bool operator <=(node i) { return val <= i.getVal(); }
	bool operator >=(node i) { return val >= i.getVal(); }
	bool operator ==(node i) { return val == i.getVal(); }
private:
	int val;
	node* F;
	node* L;
	node* R;
};
