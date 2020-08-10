#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
using namespace std;
#include <string>
#include "All.h"
string* StringSplit(string strOrigin, string strTok);

All::All(string A)
{
		string str,str1;
		int pr;
		ifstream Data;//파일 열기
		Data.open(A,ios::in); //파일 읽기
		
		for(int i=0;i<MAX_PRODUCT;i++)
		{
			Data>>str;
			if(str1==str)
			{
				const static int numofproduct=i;
				Data.close();
				break;
			}
		Data>>pr;
		str1=str;
		P[i].set_name_price(str,pr);
		}
};
int All::search_name_VM(string str)
{
	for(int i=0;i<MAX_VM_PRODUCT;i++)
	{
		if(str==VM[i].get_name())
			return i;
	}
	return -1;
}
bool All::search_name(string str)
{
	for(int i=0;i<MAX_PRODUCT;i++)
	{
		if(str==P[i].get_name())
			return true;
	}
	return false;
}
int All::search_name_shopping(string str)
{
	for(int i=0;i<MAX_SHOPPING_CART;i++)
	{
		if(str==SC[i].get_name())
			return i;
	}
	return -1;
}
int All::search_price(string str)
{
	for(int i=0;i<MAX_PRODUCT;i++)
	{
		if(str==P[i].get_name())
			return P[i].get_price();
	}
	return 0;
}
void All::add_product()
{
	string str;
	int index;
	int qun;
	int a=0;
	for(int i = 0; i<MAX_VM_PRODUCT;i++)
	{
		if(VM[i].get_quantity()!=0)
			a++;
	}
	while(1)
	{
		while(1)
		{
			cout<<"상품 입력 : ";
			cin>>str>>qun;
			if(qun<=50)
				break;
			else
				cout<<"수량이 너무 많습니다. 50개 이하로 입력해주세요."<<endl;
		}
		string *token = StringSplit(str,".");
		if(search_name(token[0])==true)
		{
			index=search_name_VM(token[0]);
			if(index==-1)
			{
				if(a==MAX_VM_PRODUCT)
				{
					cout<<"더 이상 상품을 추가할 수 없습니다.\n";
					return;
				}
				for(int i=0;i<MAX_VM_PRODUCT;i++)
				{
					if(VM[i].get_quantity()==0)
					{
						VM[i].set_name_price(token[0],search_price(token[0]));
						VM[i].set_quantity(qun);
						return;
					}
				}
			}
			else
			{
				VM[index].add(qun);
				if(VM[index].get_quantity()>50)
				{
					cout<<"최대 수량을 초과하였습니다. 다시 입력해주세요."<<endl;
					VM[index].decrease(qun);
				}
				else
					return;
			}
		}
		else
		{
			cout<<"catalog에 없는 상품입니다. 다시 입력해주세요."<<endl;
		}
	}
};
void All::print_VM()
{
	int a=0;
	for(int i = 0; i<MAX_VM_PRODUCT;i++)
	{
		if(VM[i].get_name()=="\0" && VM[i].get_price()==0)
			a++;
	}
	if(a==MAX_VM_PRODUCT)
	{
		cout<<"자판기에 상품이 없습니다.\n"<<endl;
		return;
	}
	cout<<"상품명\t단가\t수량"<<endl;
	for(int i = 0; i<MAX_VM_PRODUCT;i++)
	{
		if(VM[i].get_name()!="\0" && VM[i].get_price()!=0)
				cout<<VM[i]<<endl;
	}
}
void All::insert_SC()
{
	int n_=0;
	int q_=0;
	int temp=0;
	int check=0;
	for(int i = 0; i<MAX_VM_PRODUCT;i++)
	{		
		if(VM[i].get_quantity()!=0)
		{
				cout<<i+1<<". ";
				cout<<VM[i]<<endl;
		}
		else if(VM[i].get_name()=="\0" && VM[i].get_price()==0)
		{
			temp=i;
			break;
		}
	}
	for(int i=0;i<MAX_VM_PRODUCT;i++)
	{
		if(VM[i].get_quantity()!=0)
			check++;
	}
	if(check==0)
	{
		cout<<"자판기에 상품이 없습니다."<<endl;
		return;
	}
	while(1)
	{
		cout<<"상품을 선택하세요. : ";
		cin>>n_;
		if(n_<=temp && n_>=0)
			break;
		cout<<"잘못입력하셨습니다.\n상품목록내에서 다시 ";
	}
	while(1)
	{
		cout<<"수량을 입력하세요. : ";
		cin>>q_;
		if(q_<=VM[n_-1].get_quantity() && q_<=50)
			break;
		cout<<"자판기내의 수량을 초과하였습니다. \n다시 ";
	}
	temp=search_name_shopping(VM[n_-1].get_name());
	if(temp==-1)
	{
		for(int j=0;j<MAX_SHOPPING_CART;j++)
		{
			if(SC[j].get_name()=="\0" &&SC[j].get_price()==0)
			{
				SC[j].set_name_price(VM[n_-1].get_name(),VM[n_-1].get_price());
				SC[j].set_quantity(q_);
				SC[j].set_total(SC[j].get_quantity()*SC[j].get_price());
				VM[j].decrease(SC[j].get_quantity());
				break;
			}
		}
	}
	else
	{
		SC[temp].add(q_);
		SC[temp].set_total(SC[temp].get_quantity()*SC[temp].get_price());
		for(int j=0;j<MAX_SHOPPING_CART;j++)
		{
			if(SC[temp].get_name()==VM[j].get_name())
				VM[j].decrease(q_);
		}
	}
}
void All::delete_SC()
{
	int n_=0;
	int temp=0;
	for(int i = 0; i<MAX_SHOPPING_CART;i++)
	{		
		if(SC[i].get_name()!="\0" && SC[i].get_price()!=0 &&SC[i].get_quantity()!=0)
		{
				cout<<i+1<<". ";
				cout<<SC[i]<<endl;
		}
		else if(VM[i].get_name()=="\0" && VM[i].get_price()==0 && SC[i].get_quantity()==0 )
		{
			temp=i;
			break;
		}
	}
	if(temp==0)
	{
		cout<<"삭제할 목록이 없습니다. "<<endl;
		return;
	}
	while(1)
	{
		cout<<"삭제할 상품을 선택하세요. : ";
		cin>>n_;
		if(n_<=temp && n_>0)
			break;
		cout<<"잘못입력하셨습니다.\n상품목록내에서 다시 ";
	}
	insert_list(SC[n_-1].get_name(),SC[n_-1].get_quantity());
	for(int i=n_-1;i<MAX_SHOPPING_CART;i++)
	{

		if(SC[i].get_name()=="\0" && SC[i].get_price()==0 && SC[i].get_quantity()==0 && SC[i].get_total()==0)
			break;
		SC[i].set_name_price(SC[i+1].get_name(),SC[i+1].get_price());
		SC[i].set_quantity(SC[i+1].get_quantity());
		SC[i].set_total(SC[i+1].get_total());
	}
}
void All::payment()
{
	int pro_total=0;
	int total_pay=0;
	int tax=0;
	int money;
	print_SC();
	cout<<"---------------------------------------"<<endl;
	for(int i=0;i<MAX_SHOPPING_CART;i++)
	{
		total_pay=total_pay+SC[i].get_total();
	}
	pro_total=total_pay/(1.1);
	tax=pro_total*(0.1);
	cout<<"소계\t\t\t\t"<<pro_total<<"원"<<endl;
	cout<<"부가세\t\t\t\t"<<tax<<"원"<<endl;
	cout<<"총계\t\t\t\t"<<total_pay<<"원"<<endl;
	if(pro_total==0 && tax==0 &&total_pay==0)
		return;
	while(1)
	{
		cout<<"대금을 입력해 주십시오. : ";
		cin>>money;
		if(total_pay==money)
		{
			cout<<"결제가 완료되었습니다. "<<endl;
			reset_Array();
			reset_SC();
			return;
		}
		else if(total_pay<=money)
		{
			cout<<"거스름돈은 "<<money-total_pay<<"원입니다."<<endl;
			reset_Array();
			reset_SC();
			return;
		}
		else if(total_pay>=money)
		{
			cout<<"대금이 부족합니다. 다시 입력해주세요."<<endl;
		}
	}
}
void All::reset_SC()
{
	for(int i=0;i<MAX_SHOPPING_CART;i++)
	{
		SC[i].set_name_price("\0",0);
		SC[i].set_quantity(0);
		SC[i].set_total(0);
	}
}
void All::reset_SC2()
{
	for(int i=0;i<MAX_SHOPPING_CART;i++)
	{
		if(SC[i].get_name()!="\0")
			insert_list(SC[i].get_name(),SC[i].get_quantity());
		SC[i].set_name_price("\0",0);
		SC[i].set_quantity(0);
		SC[i].set_total(0);
	}
}
void All::print_SC()
{
	int a=0;
	for(int i = 0; i<MAX_SHOPPING_CART;i++)
	{
		if(SC[i].get_name()=="\0" && SC[i].get_price()==0)
			a++;
	}
	if(a==MAX_SHOPPING_CART)
	{
		cout<<"장바구니에 상품이 없습니다."<<endl;
		return;
	}
	cout<<"현재 장바구니 목록"<<endl;
	cout<<"상품명\t\t단가\t수량\t합계"<<endl;
	for(int i = 0; i<MAX_SHOPPING_CART;i++)
	{
		if(SC[i].get_name()!="\0" && SC[i].get_price()!=0)
		{
			cout<<i+1<<". ";
			cout<<SC[i]<<endl;
		}
	}
}
void All::delete_list(string M,int A)
{
	int index=search_name_VM(M);
	VM[index].decrease(A);
}
void All::insert_list(string M,int A)
{
	int index=search_name_VM(M);
	VM[index].add(A);
}

void All::reset_Array()
{
	string str[MAX_VM_PRODUCT];
	int pri[MAX_VM_PRODUCT], quan[MAX_VM_PRODUCT];
	int j=0;

	for(int i=0;i<MAX_VM_PRODUCT;i++)
	{
		if(VM[i].get_name()!="\0" && VM[i].get_price()!=0 && VM[i].get_quantity()!=0)
		{
			str[j]=VM[i].get_name();
			pri[j]=VM[i].get_price();
			quan[j]=VM[i].get_quantity();
			j++;
		}
	}
	for(int i=0;i<MAX_VM_PRODUCT;i++)
	{
		VM[i].set_name_price("\0",0);
		VM[i].set_quantity(0);
	}
	for(int i=0;i<j;i++)
	{
		VM[i].set_name_price(str[i],pri[i]);
		VM[i].set_quantity(quan[i]);
	}
}
#define MAX_TOK 10      // 토큰으로 분리된 string배열의 최대값
string* StringSplit(string strOrigin, string strTok)
{
	int     cutAt;                            //자르는위치
	int     index     = 0;                    //문자열인덱스
	string* strResult = new string[MAX_TOK];  //결과return 할변수
	//strTok을찾을때까지반복
	while ((cutAt = strOrigin.find_first_of(strTok)) != strOrigin.npos)
	{
		if (cutAt > 0)  //자르는위치가0보다크면(성공시)
		{
			strResult[index++] = strOrigin.substr(0, cutAt);  //결과배열에추가
		}
		strOrigin = strOrigin.substr(cutAt+1);  //원본은자른부분제외한나머지
	}
	if(strOrigin.length() > 0)  //원본이아직남았으면
	{
		strResult[index++] = strOrigin.substr(0, cutAt);  //나머지를결과배열에추가
	}
	return strResult;  //결과return
}
