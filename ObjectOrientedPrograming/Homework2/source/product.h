#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
using namespace std;
#include <string>

class product
{
public:
	product()
	{
		name="\0";
		price=0;
	};

	//product(string _name, int _price):name(_name),price(_price){};
	string get_name();
	int get_price();
	void set_name_price(string N,int P);
private:
	int price;
	string name;
};
#endif PRODUCT_H