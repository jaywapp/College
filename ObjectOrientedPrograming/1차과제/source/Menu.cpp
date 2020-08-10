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
   메뉴 목록보다 위에서 입력을 받기위한 함수
   */
    COORD Pos = { x-1, y-1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int Menu::Salelist()
{
   string select;
   //커서위치를 위함 변수
   int x=23;
   int y=2;
   int z=8;
   cout << "입력시, 해당 목록의 정확한 번호를 입력해주시기 바랍니다.\n";
   cout << "다음 중 선택을 하세요.\n";
   cout << "1. 전체상품 목록보기\n2. 판매상품 입력하기\n3. 판매상품 삭제하기\n4. 판매상품 목록보기\n5. 종료";
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