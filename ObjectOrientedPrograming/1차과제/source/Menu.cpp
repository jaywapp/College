//#Menu.cpp
//##########
//Class Menu
//##########
 
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include "My.h"
#include "stdlib.h"
 
using std::cout;
using std::cin;
using std::endl;
 
void Menu::gotoxy(int x, int y) 
{
   /*
   �޴� ��Ϻ��� ������ �Է��� �ޱ����� �Լ�
   */
    COORD Pos = { x-1, y-1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int Menu::Salelist()
{
   string select;
   //Ŀ����ġ�� ���� ����
   int x=23;
   int y=2;
   int z=8;
   cout << "�Է½�, �ش� ����� ��Ȯ�� ��ȣ�� �Է����ֽñ� �ٶ��ϴ�.\n";
   cout << "���� �� ������ �ϼ���.\n";
   cout << "1. ��ü��ǰ ��Ϻ���\n2. �ǸŻ�ǰ �Է��ϱ�\n3. �ǸŻ�ǰ �����ϱ�\n4. �ǸŻ�ǰ ��Ϻ���\n5. ����";
   gotoxy(x,y);
   cin >> select;
   gotoxy(y,z);
if(select=="1")
{return 1;}
else if(select=="2")
{return 2;}
else if(select=="3")
{return 3;}
else if(select=="4")
{return 4;}
else if(select=="5")
{return 5;}
else 
{return 0;}
};