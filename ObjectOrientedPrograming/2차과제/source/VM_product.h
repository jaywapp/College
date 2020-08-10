
#ifndef VM_H
#define VM_H
#include <iostream>
using namespace std;
#include <string>
#include "product.h"
class VM_product : public product 
{
	friend ostream& operator<<(ostream & out,VM_product & VM)
	{
	out << VM.get_name() <<"\t"<<VM.get_price()<<"\t"<<VM.quantity;
	return out;
	};
public:
	VM_product(){quantity=0;};
	void set_quantity(int Q);
	int get_quantity();
	void decrease(int A);
	void add(int A);
private:
	int quantity;
};

#endif VM_H