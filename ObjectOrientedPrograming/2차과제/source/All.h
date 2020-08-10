#ifndef ALL_H
#define ALL_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <string>
#include "product.h"
#include "shopping_cart.h"
#include "VM_product.h"
#define MAX_PRODUCT 20
#define MAX_VM_PRODUCT 10
#define MAX_SHOPPING_CART 10

using namespace std;

class All
{
public:
	All(string A);

	//*****Product -> VM_Product******
	bool search_name(string str);
	int search_name_VM(string str);
	int search_price(string str);
	void print_VM();
	void add_product();
	//********************************
	void insert_SC();
	void delete_SC();
	int search_name_shopping(string str);
	void print_SC();
	void reset_SC();
	void reset_SC2();
	void payment();
	void reset_Array();
	void insert_list(string M,int A);
	void delete_list(string M,int A);
private:
	product P[MAX_PRODUCT];
	VM_product VM[MAX_VM_PRODUCT];
	shopping_cart SC[MAX_SHOPPING_CART];
};
#endif ALL_H