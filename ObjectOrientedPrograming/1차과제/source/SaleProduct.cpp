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
			cout<<"�ǸŸ�Ͽ��� �ش��ǰ�� �����Ͽ����ϴ�."<<endl;
			return;
		}
		a=1;
	}
	if(a==1)
	{
		cout<<"�ǸŸ�Ͽ� ��ǰ�� �����ϴ�"<<endl;
		return;
	}
}//�ǸŸ�Ͽ��� ����ڰ� �Է��� ��ǰ�� ã�� �����ϴ� �Լ�.
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
				cout<"�ǸŸ�Ͽ��� �ش��ǰ�� �߰��Ͽ����ϴ�.\n";
				return;
			} 
			else if(i==MAX-1)
			{
				cout<"�ǸŸ�Ͽ� ������ �����ϴ�.\n";
			}
		}	
	}
}//����ڿ��� �Է¹��� ��ǰ�� �ǸŸ�Ͽ� �߰��ϴ� �Լ�
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
		cout<<"�ǸŸ�Ͽ� ��ǰ�� �����ϴ�.\n�ش� ���α׷��� �����մϴ�.\n";
		return;
	}
	else if(List.salename[0]=="nothing")
	{
		cout<<"�ǸŸ�Ͽ� ��ǰ�� �����ϴ�.\n�ٽ� �õ����ּ���.\n";
		return;
	}
	cout<<"��ǰ��	����	����"<<endl;
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
	cout<<"�Ұ� :"<<pro_price<<"��"<<endl;
	cout<<"�ΰ��� :"<<tax<<"��"<<endl;
	cout<<"�Ѿ� :"<<total<<"��"<<endl;
	}	
}//�ǸŸ���� �����. ����ÿ��� �Ұ�,�ΰ���,�Ѿ׵� �Բ� �����