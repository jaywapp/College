#include <iostream>
using namespace std;
#include <string>
#include "VM_product.h"
using std::ostream;
void VM_product::set_quantity(int Q)
{
	quantity=Q;
}
int VM_product::get_quantity()
{
	return quantity;
}
void VM_product::decrease(int A)
{
	quantity=quantity-A;
}
void VM_product::add(int A)
{
	quantity=quantity+A;
}
