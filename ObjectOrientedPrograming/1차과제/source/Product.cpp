//#Product.cpp
//#############
//Class Product
//#############
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "My.h"//��������� ��� ����

void Product::inputProduct(string STR,int PRICE,int i)
{
	name[i]=STR;
	price[i]=PRICE;
}//���ϳ����� ������ �Է�.
void Product::display()
{
	int a=0;
	string str;
	
	cout<<"��ǰ��		����"<<endl;
	while(1)
	{
		if(name[a]=="nothing")
		{break;}
		cout<<name[a]<<"		"<<price[a]<<endl;
		str=name[a];
		a++;
	};
}//Product���� ������ �о�� ����� �������� ���
int Product::Checking(string check_name)
{
	for(int i=0;i<MAX;i++)
	{
		if(check_name==name[i])
		{
			return 1;
		}
	}
	return 0;
}//����ڷκ��� �Է¹��� ��ǰ���� ��ǰ��Ͽ� �ִ��� Ȯ��
int Product::priceinfor(string searchname)
{	
	for(int i=0;i<MAX;i++)
	{
		if(searchname==name[i])
		{
			return price[i];
		}
	}
	return 0;
}//����ڰ� �Է��� ��ǰ�� �´� ���������� �ҷ����� �Լ�.