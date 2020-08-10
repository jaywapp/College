#ifndef SHOPPING_H
#define SHOPPING_H

#include <iostream>
using namespace std;
#include <string>
#include "VM_product.h"

class shopping_cart : public VM_product
{
friend ostream& operator<<(ostream & out,shopping_cart & SC)
{
	out << SC.get_name() <<"\t"<<SC.get_price()<<"\t"<<SC.get_quantity()<<"\t"<<SC.get_total();
	return out;
};
public:
	shopping_cart()
	{
		total=0;
	}
	void shopping_decrease(int A);
	void shopping_add(int A);
	void set_total(int T);
	int get_total();
private:
	int total;
};
#endif SHOPPING_H