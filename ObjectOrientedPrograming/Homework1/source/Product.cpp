//#Product.cpp
//#############
//Class Product
//#############
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "My.h"//사용자정의 헤더 선언

void Product::inputProduct(string STR,int PRICE,int i)
{
	name[i]=STR;
	price[i]=PRICE;
}//파일내용을 변수에 입력.
void Product::display()
{
	int a=0;
	string str;
	
	cout<<"상품명		가격"<<endl;
	while(1)
	{
		if(name[a]=="nothing")
		{break;}
		cout<<name[a]<<"		"<<price[a]<<endl;
		str=name[a];
		a++;
	};
}//Product내에 파일을 읽어와 저장된 변수들을 출력
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
}//사용자로부터 입력받은 상품명이 상품목록에 있는지 확인
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
}//사용자가 입력한 상품명에 맞는 가격정보를 불러오는 함수.