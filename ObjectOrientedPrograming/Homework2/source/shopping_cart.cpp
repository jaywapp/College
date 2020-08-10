#include <iostream>
using namespace std;
#include <string>
#include "shopping_cart.h"

void shopping_cart::shopping_decrease(int A)
{
	decrease(A);
}
void shopping_cart::shopping_add(int A)
{
	add(A);
}
void shopping_cart::set_total(int T)
{
	total=T;
}
int shopping_cart::get_total()
{
	return total;
}