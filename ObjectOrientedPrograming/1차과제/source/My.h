#include <iostream>
#include <string>

using namespace std;
#define MAX 100
class Product
{
public:
	Product()
	{
		for(int i=0;i<MAX;i++)
		{
			name[i]="nothing";
			price[i]=0;
		}
	};
	void inputProduct(string STR,int PRICE,int i);
	void display();
	int priceinfor(string searchname);
	int Checking(string check_name);

private:
	string name[MAX];
	int price[MAX];
};//Product

class Menu
{
public:
	int Salelist();
	void gotoxy(int x, int y);
};

class Sale
{
public:
	friend class SaleProduct;
	Sale()
	{
		for(int i=0; i<MAX;i++)
		{
			salename[i]="nothing";
			saleP_Q[0][i]=0;
			saleP_Q[1][i]=0;
		}
	}
private:
	string salename[MAX];
	int saleP_Q[2][MAX];	//price and quantity
	/*
	saleP_Q[0][i] 가격
	saleP_Q[1][i] 수량
	*/
};
class SaleProduct
{
public:
	void enterSaleProduct(string name,int quantity,int price);
	void deleteSaleProduct(string name);
	void display(int i);
	
private:
	Sale List;

};