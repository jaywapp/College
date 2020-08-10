#include <iostream>
using namespace std;
#include <string>
#include "product.h"

string product::get_name()
{
	return name;
}
int product::get_price()
{
	return price;
}
void product::set_name_price(string N,int P)
{
	name=N;
	price=P;
}
