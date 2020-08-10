//#SaleProduct.cpp
//#############
//Class SaleProduct
//#############
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
# pragma warning(disable : 4996)
using namespace std;

#include "My.h"

void SaleProduct::deleteSaleProduct(string name)
{
	int a;

	for(int i=0;i<MAX;i++)
	{
		if(name==List.salename[i])
		{
			for(int k=i;k<MAX;k++)
			{	
				List.salename[k]=List.salename[k+1];
				List.saleP_Q[0][k]=List.saleP_Q[0][k+1];
				List.saleP_Q[1][k]=List.saleP_Q[1][k+1];
				List.salename[k+1]="nothing";
			}
			cout<<"판매목록에서 해당상품을 제거하였습니다."<<endl;
			return;
		}
		a=1;
	}
	if(a==1)
	{
		cout<<"판매목록에 상품이 없습니다"<<endl;
		return;
	}
}//판매목록에서 사용자가 입력한 상품을 찾아 제거하는 함수.
void SaleProduct::enterSaleProduct(string name,int quantity,int price)
{
	
	for(int i=0;i<MAX;i++)
	{
		if(List.salename[i]==name)
		{
			List.saleP_Q[1][i]=List.saleP_Q[1][i]+quantity;
			return;
		}
		else
		{
			if(List.salename[i]=="nothing")
			{
				List.salename[i]=name;
				List.saleP_Q[1][i]=List.saleP_Q[1][i]+quantity;
				List.saleP_Q[0][i]=price;
				cout<"판매목록에서 해당상품을 추가하였습니다.\n";
				return;
			} 
			else if(i==MAX-1)
			{
				cout<"판매목록에 공간이 없습니다.\n";
			}
		}	
	}
}//사용자에게 입력받은 상품을 판매목록에 추가하는 함수
void SaleProduct::display(int i)
{
	int total=0;
	int tax=0;
	int pro_price=0;
	
	for(int i=0;i<MAX;i++)
	{	
		if(List.salename[i]=="nothing")
		{
			break;
		}
		total=total+(List.saleP_Q[0][i]*List.saleP_Q[1][0]);
	}
	pro_price=total/(1.1);
	tax=pro_price*(0.1);
	if(List.salename[0]=="nothing" && i==1)
	{
		cout<<"판매목록에 상품이 없습니다.\n해당 프로그램을 종료합니다.\n";
		return;
	}
	else if(List.salename[0]=="nothing")
	{
		cout<<"판매목록에 상품이 없습니다.\n다시 시도해주세요.\n";
		return;
	}
	cout<<"상품명	가격	수량"<<endl;
	for(int i=0;i<MAX;i++)
	{
		if(List.salename[i]=="nothing")
		{
			break;
		}
		else
		{
		cout<<List.salename[i]<<"	"<<List.saleP_Q[0][i]<<"	"<<List.saleP_Q[1][i]<<endl;
		}
	}
	if(i==1)
	{
	cout<<"소계 :"<<pro_price<<"원"<<endl;
	cout<<"부가세 :"<<tax<<"원"<<endl;
	cout<<"총액 :"<<total<<"원"<<endl;
	}	
}//판매목록을 출력함. 종료시에는 소계,부가세,총액도 함께 출력함