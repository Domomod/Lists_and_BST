#pragma once

#include<assert.h>
#include<algorithm>

class node
{
public:
	node(int v = 0) {
		val = v;
		height = -1;
		F = nullptr;
		L = nullptr;
		R = nullptr;
	}
	~node() {
	}

	//utility
	int getBalanceFactor() {
		int l = -1, r = -1;
		if (this->nextR() != nullptr)
			r = this->nextR()->getHeight();
		if (this->nextL() != nullptr)
			l = this->nextL()->getHeight();
		//printf("%d - %d = %d\n", r, l, r - l);
		return r - l;
	}

	void setHeight() {
		int l, r;
		if (this->nextL() != nullptr) {
			l = this->nextL()->getHeight();
		}
		else l = -1;
		if (this->nextR() != nullptr) {
			r = this->nextR()->getHeight();
		}
		else r = -1;

		int newB = std::max(l, r) + 1;
		//if (height == newB)
		//	return;
		height = newB;
	}

	void updateHeight() {
		//printf("\t%d\n", val);

		int l, r;
		if (this->nextL() != nullptr) {
			l = this->nextL()->getHeight();
		}
		else l = -1;
		if (this->nextR() != nullptr) {
			r = this->nextR()->getHeight();
		}
		else r = -1;

		int newB = std::max(l, r) + 1;
		//if (height == newB)
		//	return;
		height = newB;

		if (this->prevF() != nullptr) {
			this->prevF()->updateHeight();
		}
	}


	//setters
	void setVal(int v) { val = v; }
	void setF(node* f) { 
		F = f;
	}
	void setL(node* l) { 
		L = l;
		if (l != nullptr)
			l->setF(this);
		if (l == nullptr && this->nextR() == nullptr) {
			this->height = 0;
		}
	}
	void setR(node* r) { 
		R = r; 
		if (R != nullptr)
			R->setF(this);
		if (r == nullptr && this->nextL() == nullptr) {
			this->height = 0;
		}
	}

	//getters
	int getVal() { return val; }
	int getHeight() { return height; }
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

	//operators
	bool operator <(int i) { return val < i; }
	bool operator >(int i) { return val > i; }
	bool operator <=(int i) { return val <= i; }
	bool operator >=(int i) { return val >= i; }
	bool operator ==(int i) { return val == i; }
	
	bool operator <(node i) { return val < i.getVal(); }
	bool operator >(node i) { return val >  i.getVal(); }
	bool operator <=(node i) { return val <= i.getVal(); }
	bool operator >=(node i) { return val >= i.getVal(); }
	bool operator ==(node i) { return val == i.getVal(); }
private:
	int val;
	int height;
	node* F;
	node* L;
	node* R;
};