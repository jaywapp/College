#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int NumofLocal();//������ ��ȣ�� �Ұ����ִ� �Լ�.
void intro();//���ӼҰ��� ����ϴ� �Լ�
void inputplayer(int* c);//�ο��� �Է� �Լ�
void move_inNPI(int* NPI);//���ε��� ���Player���� �̵��Լ�
int move(int player,int* a,int* dic);//Player ���� �̵��Լ�
int dice();//�ֻ����Լ�
int money(int player);//1������������ ���������Լ�
int total_pass(int Build,int Pass);//�� ����� ����Լ�.
void turn(char *Nu,int i);//���� �˸��Լ�
void movingprint(int dic,int playerplace,int i);//�̵� ������ ����Լ�.
void infor_place(int a); //�ɸ�ĭ�� �����̳� ���Һ�����
void buyLocal(char YorN, int* playermoney,int* Localorder, int Localprice,int i);//������ �����Ҷ� ����ϴ� �Լ�
void Pay_Process(int* v_total_pass,int* Host_money,int* Guest_money,int* have_ticket,int Local_Pay,int Local_build);//ĭ�� �ɷ����� ����Ḧ ����ϴ� �Լ�.
void Pay_block(int Local_order,int Local_build,int Local_Pay);//�ɸ� ĭ�� �⺻������ �ǹ������� �˷��ִ� �Լ�
void build_selection(int* Local_build,int Local_Pay,int* playermoney);//�ǹ��Ǽ��Լ�
void board(int player[4][4], int c,int i,int* b);//��Ȳ�� �Լ�
int Expensive(int Local[40][4],int playernumber);//������ �����߿� ���� ��� ������ ��󳻴� �Լ�
void Cruze(int* playermoney);//�÷��̾  ũ���� ĭ�� ���������� �����ϴ� �Լ�
void Welfare(int* playermoney,int* Welfare_money);//�÷��̾  ��ȸ�������ĭ�� ���������� �����ϴ� �Լ�
void Space(int* playermoney,int* playerplace);
void ChanceSelection(int* playerplace, int* playermoney,int* Localorder,int* Localprice, int* playernumber,int* welfare,int* have_ticket,int* player_island);//Chance�Լ��� ���� �Լ�
void Chance1(int* playermoney,int* playernumber);//����������
void Chance2(int* playermoney,int* playernumber);//���Ǵ�÷
void Chance3(int* playerplace, int* playermoney,int* playernumber,int* player_island);//�����ΰ��ÿ�
void Chance4(int* playerplace,int* playermoney,int* playernumber);//��������<���ֵ�>
void Chance5(int* playermoney,int* playernumber);//���ӿ��� ����
void Chance6(int* playermoney);//�ؿ�����
void Chance7(int* playermoney);//��������
void Chance8(int* playerplace,int* playernumber);//�̻簡�ÿ�
void Chance9(int* playermoney,int* playerplace);//��ӵ���
void Chance10(int* playermoney);//���
void Chance11(int* playermoney,int* playerplace);//����������(������������ ������)
void Chance12(int* playerplace,int* playermoney);//��������<�λ�>
void Chance13(int* playermoney);//��������
void Chance14(int* playermoney);//���б�
void Chance15(int* playermoney);//�뺧��ȭ��
void Chance16(int* playerplace, int* playermoney,int* playernumber);//��������<����>
void Chance17(int* playermoney, int* Localorder, int* Localprice);//�ݾ״����
void Chance18(int* playerplace, int* playermoney,int* playernumber);//���ֿ��� ��û��
void Chance19(int* playermoney,int* welfare);//��ȸ������ݹ��
void Chance20(int* have_ticket);//����

//----------------------------------------Local
int Start();
int Uijeongbu();
int Anyang();
int Kangchon();
int Choonchune();
int Jeju();
int Deakwanryung();
int Jeeli();
int Hanra();
int KoreanAir();
int Koomi();
int Deagu();
int Welfare_infor();
int Andong();
int Pohang();
int Kyungjoo();
int Ulsan();
int Busan();
int Haeundae();
int Changwon();
int Deajun();
int Spacetravel();
int Mokpo();
int Naroho();
int Gwangju();
int Suwon();
int Incheon();
int Bakdoo();
int Seoul();
int Cruze_infor();
int Dokdo();
int Saemankm();
int Yungkwang();
int Boryung();
int Chunan();

int main()
{
	int player[4][4];//�������� ��ġ�� ������
	// player[4][4] �迭
	// user  place(1)  money(2) ticket(3) Nopeople(4)
	// 1
	// 2
	// 3
	// 4
	int a=0,b=0,c=0,d=0,k,dic,j,select=0;
	int NPI=0;
	int welfare=0;
	//a,b,c,d,k�� �ݺ����� �����Ҷ� ���� ����,dic�� ������ �޴º���,select�� �ǹ��Ǽ����θ� ������ ���º���
	char Nu,YorN;//Nu�� ���͸� �޾Ƴ��� ����,YorN�� Y��N�� �޾Ƴ��º���
	int Local[40][4];
	int v_total_pass=0;//�⺻����ῡ �ǹ��� ������ ������ �ݾ�; �ѱݾ�
	//Local[4][0]=������ ��ȣ
	//Local[4][1]=�ǹ����� 1-�ܵ� 2-���� 3-ȣ�� 0-�ǹ�����
	//Local[4][2]=�����ǰ���
	//Local[4][3]=�⺻�����(�ǹ����ϳ���������)
	srand(time(NULL));//rand�Լ��� �������� �������ִ� �Լ�
	intro();//���ӿ����Ѽ���
	inputplayer(&c);//�Բ��� �ο��� ����
	scanf("%c",&Nu);//�����Է�
	// �ʱ�ȭ�κ� ------------------------------------------

	for(int i=0;i<c;i++)//player��ġ�� �ʱ�ȭ
	{
		player[i][0]=0;
		player[i][3]=0;
	}
	for(int i=0;i<c;i++)//player���� �ʱ�ȭ
	{
		player[i][1]=5000000;
	}
	for(int i=0;i<c;i++)//player�� ���� ���� ����
	{
		player[i][2]=0;
	}
	for(int i=0;i<40;i++)//Local; 
	{
		Local[i][0]=0;//������ �ʱ�ȭ
		Local[i][1]=0;//�ǹ����� �ʱ�ȭ
		Local[i][2]=(i+1)*5000;//�������� ����
		Local[i][3]=(i+1)*300;//�⺻����� ����
	}



	//���ۺκ�-------------------------------------------------------
	while(b==0)//
	{	
		for(int i=0;i<c;i++)//�÷��̾��� ����
		{
			turn(&Nu,i);
			if(player[i][3]!=0)
			{
				move_inNPI(&NPI);
				if(NPI==1)
				{
					player[i][3]=0;
				}
				else if(NPI==2)
				{
					player[i][3]=player[i][3]-1;

				}
			}
			else
			{
				player[i][0]=move(player[i][0],&a,&dic);
				movingprint(dic,player[i][0],i);
			}
			if(a==1)//a�� 1�̸� �ѹ��� ����ǥ��, ���޹ޱ�����
			{
				printf("\a�� ������ �����ϼ˽��ϴ�. 20������ ���޹����ʽÿ�\n");
				player[i][1]=money(player[i][1]);
				a=0;
			}//if
			for(a=0;a<40;a++)//���� ����, �Ǽ� ��Ʈ����
			{//���⼭ a�� �� ĭ�� �ǹ���
				//int placeCheck(in
				if(player[i][0]==a)//player i �� ��ġ�� a�� �ɶ�
				{
					if(Local[a][0]==0 && a%10!=5 && a!=11 && a!=8 && a!=29 && a!=20 && a!=31)//a��° Local�� �����ڰ� ������
					{
						while(1)//�߸��Է������� �ǹ����� ���� �ݺ�������
						{
							infor_place(a);

							printf("�����Ͻðڽ��ϱ�?(Y/N)");
							fflush(stdin);
							scanf("%c",&YorN);
							buyLocal(YorN,&player[i][1],&Local[a][0],Local[a][2],i);
							if(YorN=='N' || YorN=='n' || YorN=='Y' || YorN=='y')
							{
								fflush(stdin);
								break;//����δ�������� �ݺ������������������� break��
							}//else if(YorN)
						}//while(1)
					}//if(Local[a][0]==0)

					else if(Local[a][0]!=0 && Local[a][0]!=i+1 && a%10!=5 && a!=11 && a!=8 && a!=29 && a!=20 && a!=31)
					{//a��° Local�� �����ڰ� �ְ�, �� �����ڰ� ������ �ƴҶ�
						infor_place(a);
						Pay_block(Local[a][0],Local[a][1],Local[a][3]);
						k=Local[a][0]-1;
						Pay_Process(&v_total_pass,&player[k][1],&player[i][1],&player[i][2],Local[a][3],Local[a][1]);
						fflush(stdin);
						scanf("%c",&Nu);
					}//else if(Local[a][0]!=0 && Local[a][0]!=i+1)
					else if(Local[a][0]==i+1 && a%10!=5 && a!=11 && a!=8 && a!=29  && a!=20 && a!=31)//�׶��� ������ ���϶�.
					{
						infor_place(a);
						if(Local[a][1]!=0)//�׸��� �ǹ��� ���� ��.
						{
							build_selection(&Local[a][1],Local[a][2],&player[i][2]);
						}
					}//else if(Local[a][0]==i+1)
					else if(a%10==5)//���Һ� ĭ�� �ɷ�����.
					{
						j=Expensive(Local,i+1);
						ChanceSelection(&player[i][0],&player[i][1],&Local[j][0],&Local[j][3],&i,&welfare,&player[i][2],&player[i][3]);
					}
					else if(a==11)
					{
						infor_place(a);
						if(NPI==2)
						{
							player[i][3]-1;
						}
						else if(NPI==0)
						{
							player[i][3]=2;
						}
					}
					else if(a==8 || a==29)
					{
						infor_place(a);
						Cruze(&player[i][1]);
					}
					else if(a==20)
					{
						infor_place(a);
						Welfare(&player[i][1],&welfare);
					}
					else if(a==31)
					{
						infor_place(a);
						Space(&player[i][1],&player[i][0]);
					}
				}

			}

			board(player,c,i,&b);
		}
	}
}//main----------------------------------

//----------------------------------------------------
int move(int player,int* a,int* dic)//�÷��̾��� �̵��� ������ִ� �Լ�
{

	int temp;

	temp=dice();
	*dic=temp;
	player=player+temp;
	if(player>40)
	{
		player=player-40;//���� �� ���Һ� ĭ�� �Ѽ�
		*a=1;
	}
	return player;
}
void move_inNPI(int* NPI)
{
	int dice_NPI1,dice_NPI2;
	dice_NPI1=(rand()%6)+1;
	dice_NPI2=(rand()%6)+1;

	printf("�ֻ����� �����ڽ��ϴ�.!!\n");
	printf("ù��° �ֻ����� %d �ι�° �ֻ����� %d��\n",dice_NPI1,dice_NPI2);
	if(dice_NPI1==dice_NPI2)
	{
		
		printf("���� ���ڰ� ���Խ��ϴ�. Ż���ϼ���!\n");	
		*NPI=1;
	}
	else if(dice_NPI1!=dice_NPI2)
	{
		printf("�ٸ� ���ڰ� ���Խ��ϴ�. ���� �Ͽ� �ٽõ����ϼ���\n");
		*NPI=2;

	}
}


int money(int player)
{
	player=player+200000; //�ѹ��� ��������, ���� 20����
	return player;
}
int dice() //�ΰ��� ������ ������ ������ ����ϴ�
{
	int a,b;
	int result;
	char Nu;
	a=(rand()%6)+1;
	b=(rand()%6)+1;
	if(a!=b)
		printf("�ֻ��� A : %d, �ֻ��� B : %d\n",a,b);
	result = a+b;
	if(a==b)
	{

		printf("�ֻ��� A : %d, �ֻ��� B : %d\n�ֻ����� %d�� %d�� ���ڰ� �����ϴ�. �ѹ��� ��������",a,b,a,b);
		scanf("%c",&Nu);
		return result+dice();
	}
	return result;
	//return 11;
}
void inputplayer(int *c)
{
	int b;
	while(1)
	{
		printf("�Բ��Ͻ� �ο����� �Է��ϼ���(2��~4��) :");
		scanf("%d",c);
		b=*c;
		if(b==2 || b==4 || b==3)
		{
			printf("%d���̼� ������ �����ϰڽ��ϴ�.\n",b); 
			break;
		}
		else
		{
			printf("�߸��Է��ϼ̽��ϴ�.\n\n");
			*c=0;
		}
	}
}
void intro()
{
	printf("================================\n");
	printf("===========Korean Root==========\n");
	printf("=====================by.K G G===\n");
	printf("�� ������ ���۱��� KGG�� ������ �����մϴ�.\n");
	printf("�� ������ �ѱ��� �˸������� ���۵Ǿ�����,\n");
	printf("��� �� ��Ÿ�뵵�� ������ ������ �˸��ϴ�.\n");
	printf("��Ȱ�� ������ ���Ͽ� �ִ�ȭ��ư�� �����ּ���.\n");
	printf("\n\n");
}

int total_pass(int Build,int Pass)
{
	int result;
	result=(Build*50000)+Pass;
	return result;
}
void turn(char *Nu,int i)
{
	printf("\n�ڡڡ�Player%d���� ����!!�ڡڡ�\n",i+1);
	printf("player %d�� �ֻ����� �����ðڽ��ϱ�? �����÷��� EnterŰ�� �����ּ���",i+1);
	scanf("%c",Nu);
}
void movingprint(int dic,int playerplace,int i)
{
	printf("%dĭ �̵��ϰڽ��ϴ�.\n",dic);
	printf("player%d���� ������ġ : %d\n",i+1,playerplace);
}
void infor_place(int a)
{
	//printf("���� ������ ���� Local[%d]�Դϴ�. ���� ������ �ƹ��� �����ϴ�.\n",a);
	/* ĭ�� ����,Ȳ�ݿ��谡 �������� �� printf�� ���ְ� switch������ ĭ���Լ����.
	*/	
	printf("\n");
	switch(a)
	{
	case 0 : Start();
		break;
	case 1 : Uijeongbu();//������
		break;
	case 2 : Anyang();
		break;
	case 3 : Kangchon();
		break;
	case 4 : Choonchune();
		break;
		
	case 6 : Jeju();
		break;
	case 7 : Deakwanryung();
		break;
	case 8 : Cruze_infor();
		break;
	case 9 : Saemankm();
		break;
	case 10 : Jeeli();
		break;
	case 11 : Dokdo();
		break;
	case 12 : Yungkwang();
		break; 
	case 13 : Boryung();
		break;
	case 14 : Hanra();
		break;
	
	case 16 : KoreanAir();
		break;
	case 17 : Chunan();
		break;
	case 18 : Koomi();
		break;
	case 19 : Deagu();
		break;
	case 20 : Welfare_infor();
		break; 
	case 21 : Andong();
		break; 
	case 22 : Pohang();
		break; 
	case 23 : Kyungjoo();
		break; 
	case 24 : Ulsan();
		break; 
	
	case 26 : Busan();
		break;
	case 27 : Haeundae();
		break; 
	case 28 : Changwon();
		break;
	case 29 : Cruze_infor();
		break;
	case 30 : Deajun();
		break; 
	case 31 : Spacetravel();
		break;
	case 32 : Mokpo();
		break; 
	case 33 : Naroho();
		break; 
	case 34 : Gwangju();
		break; 
	case 36 : Suwon();
		break; 
	case 37 : Incheon();
		break; 
	case 38 : Bakdoo();
		break; 
	case 39 : Seoul();
		break; 
	}


}
void buyLocal(char YorN, int* playermoney,int* Localorder, int Localprice,int i)
{   
	if(YorN=='Y' || YorN=='y')
	{

		*playermoney=*playermoney-Localprice;
		*Localorder=i+1;
		fflush(stdin);
		printf("�� ������ ���� Player%d���� �����Դϴ�.\n",i+1);

	}//if(YorN)
	else if(YorN=='N' || YorN=='n')
	{
		fflush(stdin);
	}//else if(YorN)
	else
	{
		printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ֽʽÿ�.\n");
		//break�� �����Ƿ� �ٽ� �ݺ�
	}//else
}
void Pay_block(int Local_order,int Local_build,int Local_Pay)
{
	printf("�� ���� Player%d�� ���Դϴ�.\n",Local_order);
	printf("�⺻������ %d���̰�,",Local_Pay);
	switch(Local_build)//�ǹ������� �˷��ֱ�����
	{
	case 0 :printf("�ǹ��� �����ϴ�.\n");
		break;
	case 1 :printf("�ǹ��� �ܵ��� �ֽ��ϴ�.\n");
		break;
	case 2 :printf("�ǹ��� ������ �ֽ��ϴ�.\n");
		break;
	case 3 :printf("�ǹ��� ȣ���� �ֽ��ϴ�.\n");
		break;
	}//switch
}
void Pay_Process(int* v_total_pass,int* Host_money,int* Guest_money,int* have_ticket,int Local_Pay,int Local_build)
{
	char YorN;
	if(*have_ticket!=0)
	{
		printf("������ �����ʴϴ�. ����Ͻðڽ��ϱ�? (Y/N) : ");
		scanf("%c",&YorN);
		if(YorN=='Y' || YorN=='y')
		{
			printf("������ 1�� ����Ͽ� %d���� ���ҽ��ϴ�.\n",*have_ticket-1);
			*have_ticket=*have_ticket-1;

		}
		else if(YorN=='N' || YorN=='n')
		{
			*v_total_pass=total_pass(Local_build,Local_Pay);//���������� total_pass�Լ��� ����Լ�
			printf("�� ������ %d �Դϴ�.\n",*v_total_pass);
			*Guest_money=*Guest_money-*v_total_pass;//�������ɸ������ ����
			*Host_money=*Host_money+*v_total_pass;//�����������ε� ���
		}
	}
	else
	{
		*v_total_pass=total_pass(Local_build,Local_Pay);//���������� total_pass�Լ��� ����Լ�
		printf("�� ������ %d �Դϴ�.\n",*v_total_pass);
		*Guest_money=*Guest_money-*v_total_pass;//�������ɸ������ ����
		*Host_money=*Host_money+*v_total_pass;//�����������ε� ���
	}
}
void build_selection(int* Local_build,int Local_Pay,int* playermoney)
{
	char YorN,Nu;
	int select;

	printf("�ǹ��� �����ðڽ��ϱ�?(Y/N) : ");
	scanf("%c",&YorN);
	if(YorN=='Y'||YorN=='y')
	{
		printf("������ �ǹ��� �����ϼ���.\n 1.�ܵ� 2.���� 3.ȣ��  - > ");
		scanf("%d",&select);
		while(select==0)//�߸��Է������� �ٽù�������
		{
			switch(select)
			{
			case 1: 
				*Local_build=1;
				*playermoney=*playermoney-(Local_Pay*0.5);
				printf("�ܵ��� �����̽��ϴ�.\n");
				break;
			case 2: 
				*Local_build=2;
				printf("������ �����̽��ϴ�.\n");
				*playermoney=*playermoney-(Local_Pay*1);
				break;
			case 3:
				*Local_build=3;
				*playermoney=*playermoney-(Local_Pay*1.5);
				printf("ȣ�ڸ� �����̽��ϴ�.\n");
				break;
			default : 
				printf("�ٽ��Է����ּ���\n");
				select=0;//select�� �ٽ� 0�� �����Ƿ� �ݺ�
			}
		}
		if(YorN=='N'||YorN=='n')
		{
			printf("�ǹ��� ���� �ʰ� �Ѿ�ϴ�.\n");
			fflush(stdin);
			scanf("%c",&Nu);
		}//if(YorN=='N')
		else//����
		{

		}
	}
}
void board(int player[4][4], int c,int i,int* b)//��Ȳ�� �Լ�
{
	char Nu;
	printf("------------------------------------------------------------------------------\n");
	printf("### �����Ȳ ###\n");
	printf("User Place money\n");
	for(int i=0;i<c;i++)//ó���� �Է¹��� �ο��� ��ŭ ����
	{
		printf("player%d %d %d��\n",i+1,player[i][0],player[i][1]);
	}

	printf("------------------------------------------------------------------------------\n");
	scanf("%c",&Nu);
	system("cls");
	NumofLocal();
	for(int i=0;i<c;i++)//���� 10000000�� �Ѵ� �� Ȯ���ϱ����� ������ �ݺ���
	{
		if(player[i][1]>=10000000)  //10000000��� ���� ��ǥ �׼� ��������
		{
			*b=1;//b�� 1�� �Ǹ� �׶��� i+1��° �÷��̾ ���ڰ� ��.
			printf("�����մϴ�. Player%d���� �¸��ϼ˽��ϴ�.****\n",i+1);
		}
	} 
}
int Expensive(int Local[40][4],int playernumber)
{//Local[i][2]
	int res=0,i;

	for(i=39;i>=0;i--)
	{
		if(Local[i][3]==playernumber && i%8!=0)
		{
			res=i;
			break;
		}
	}
	return res;
}
//------------------------------------------------------------------
//chance �Լ�����
void ChanceSelection(int* playerplace, int* playermoney,int* Localorder,int* Localprice, int* playernumber,int* welfare,int* have_ticket,int* player_island)
{
	char Nu;
	int ran_num;


	printf("���Һ�!!!!!!!!!!!!!!ī�带 �������� �̰ڽ��ϴ�.\n �ƹ�Ű�� �����ּ���^^");
	scanf("%c",&Nu);
	//ran_num=(rand()%20)+1;
	ran_num=4;

	switch(ran_num)
	{
	case 1 :Chance1(*&playermoney,*&playernumber);
		break;
	case 2 :Chance2(*&playermoney,*&playernumber);
		break;
	case 3 :Chance3(*&playerplace,*&playermoney,*&playernumber,*&player_island);
		break;
	case 4 :Chance4(*&playerplace,*&playermoney,*&playernumber);
		break;
	case 5 :Chance5(*&playermoney,*&playernumber);
		break;
	case 6 :Chance6(*&playermoney);
		break;
	case 7 :Chance7(*&playermoney);
		break;
	case 8 :Chance8(*&playerplace,*&playernumber);
		break;
	case 9 :Chance9(*&playermoney,*&playerplace);
		break;
	case 10 :Chance10(*&playermoney);
		break;
	case 11 :Chance11(*&playermoney,*&playerplace);
		break;
	case 12 :Chance12(*&playerplace,*&playermoney);
		break; 
	case 13 :Chance13(*&playermoney);
		break;
	case 14 :Chance14(*&playermoney);
		break;
	case 15 :Chance15(*&playermoney);
		break;
	case 16 :Chance16(*&playerplace,*&playermoney,*&playernumber);
		break;
	case 17 :Chance17(*&playermoney,*&Localorder,*&Localprice);
		break;
	case 18 :Chance18(*&playerplace,*&playermoney,*&playernumber);
		break;
	case 19 :Chance19(*&playermoney,*&welfare);
		break;
	case 20 :Chance20(*&have_ticket);
		break;
	}
}

void Chance1(int* playermoney,int* playernumber)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-������ ����-.\n");
	printf("����� ��ġ�̽��ϴ�.\n������ ���� ġ�Ḧ ��������.\n������� 5�����Դϴ�\n");
	*playermoney = *playermoney - 50000;
	printf("player %d���� ���� ���� ����� %d��.\n",*playernumber,*playermoney);

}
void Chance2(int* playermoney,int* playernumber)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-���Ǵ�÷(20����)-.\n");
	printf("����� ���ǿ� ��÷�Ǽ̽��ϴ�.\n20������ ��������.\n");
	*playermoney = *playermoney - 200000;
	printf("player %d���� ���� ���� ����� %d��.\n",*playernumber,*playermoney);

}
void Chance3(int* playerplace, int* playermoney,int* playernumber,int* player_island)
{
	int Nopeople=11;//���ε�
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-���ε�-.\n");
	printf("����� ���ε��� ������ ǥ���Ǽ̽��ϴ�.\n");
	if(*playerplace>=Nopeople)
	{
		printf("������� �����ż� ���� ȹ��!!\n");
		*playermoney=*playermoney+200000;
		printf("���ε��� �̵��Ͽ����ϴ�\n");
		*playerplace=Nopeople;
	}
	else if(*playerplace<Nopeople)
	{
		printf("���ε��� �̵��Ͽ����ϴ�\n");
		*playerplace=Nopeople;
	}
	printf("�ֻ��� ���ڰ� ���� ���� �����ų� 3ȸ�� ���� ��\nŻ���Ͻ� �� �ֽ��ϴ�.");
	*player_island=2;

}
void Chance4(int* playerplace,int* playermoney,int* playernumber)
{
	int jeju=6;//���ֵ���ġ
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-��������<���ֵ�>-.\n");
	printf("���� ������ �ִٸ� ����� �����Ͻÿ�.\n������� ���İ��� ��쿡�� ������ Ÿ�ÿ�.");
	if(*playerplace>=jeju)
	{
		printf("������� �����ż� ���� ȹ��!!\n");
		*playermoney=*playermoney+200000;
		printf("���ֵ��� �̵��Ͽ����ϴ�\n");
		*playerplace=jeju;
		printf("������ �����ϽǼ� �����ϴ�.\n");
	}
	else if(*playerplace<jeju)
	{
		printf("���ֵ��� �̵��Ͽ����ϴ�\n");
		*playerplace=jeju;
		printf("������ �����ϽǼ� �����ϴ�.\n");
	}
	;
}
void Chance5(int* playermoney,int* playernumber)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-���ӿ��� ����-.\n");
	printf("����� ���ӿ����ϴٰ� ���ߵǼ̽��ϴ�.\n");
	printf("���� 5�����Դϴ�.\n");

	*playermoney = *playermoney - 50000;
	printf("player %d���� ���� ���� ����� %d��\n",*playernumber,*playermoney);
}
void Chance6(int* playermoney)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-�ؿ����� �ڱ�-.\n");
	printf("����� �ؿ����� �ڱ����� 10������ �����̽��ϴ�\n");

	*playermoney = *playermoney + 100000;
	
}
void Chance7(int* playermoney)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-���� ����-.\n");
	printf("����� ���� �������� 5������ �����̽��ϴ�\n");

	*playermoney = *playermoney + 50000;

}
void Chance8(int* playerplace,int* playernumber)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-�̻�-.\n");
	printf("�ڷ� 3ĭ �̻簡�ÿ�\n");
	*playerplace = *playerplace - 3;
	printf("������ �����ϽǼ� �����ϴ�.\n");

}
void Chance9(int* playermoney,int* playerplace)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-��ӵ���-.\n");
	printf("��ӵ��θ� Ÿ�̽��ϴ�. ������� ���� ���� ��������\n");
	*playermoney = *playermoney + 200000;
	*playerplace = 0;

}
void Chance10(int* playermoney)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-�׶����� ���-.\n");
	printf("����� �׶������� ����ϼ̽��ϴ�. ����� 10������ ��������\n");
	*playermoney = *playermoney + 100000;

}
void Chance11(int* playermoney,int* playerplace)
{
	int temp_place;
	char Nu;

	temp_place=(rand()%39)+1;
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-������-.\n");
	printf("�������� Ÿ�� ������� �̵��Ͻÿ�. ������� ��ĥ��� ������ �޽��ϴ�.\n");
	printf("\n�̵��ϰڽ��ϴ�.\n");
	scanf("%c",&Nu);
	fflush(stdin);
	infor_place(temp_place);
	if(*playerplace > temp_place)
	{
		*playermoney = *playermoney + 200000;
		*playerplace = temp_place;
	}
	else
	{
		*playerplace = temp_place;
	}
	

}
void Chance12(int* playerplace,int* playermoney)
{
	int temp_place = 23;

	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-��������<�λ�>-.\n");
	printf("�λ����� ���������� ���ϴ�. ����� 10������ ����մϴ�.\n");
	printf("������ �����ϽǼ� �����ϴ�.\n");
	*playermoney = *playermoney - 100000;
	*playerplace = temp_place;
}
void Chance13(int* playermoney)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-����-.\n");
	printf("���� �����մϴ�. 1õ���� �޽��ϴ�\n");
	*playermoney += 1000;

}
void Chance14(int* playermoney)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-���б�-.\n");
	printf("����� �б����� ���� �� ���� ���б� 10������ ���ӿ��� �޽��ϴ�.\n");
	*playermoney += 100000;

}
void Chance15(int* playermoney)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-�뺧��ȭ��-.\n");
	printf("����� �뺧��ȭ���� �����Ͽ� 30������ �޽��ϴ�\n");
	*playermoney += 300000;

}

void Chance16(int* playerplace, int* playermoney,int* playernumber)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-��������<����>-.\n");
	printf("����� ���ϴ�. �ø��ȱ������ 200������ �����մϴ�.\n");
	printf("������ �����ϽǼ� �����ϴ�.\n");
	*playermoney=*playermoney-2000000;
	*playerplace=39;
}
void Chance17(int* playermoney, int* Localorder, int* Localprice)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-�ݾ״����-.\n");
	printf("������ ������ �ִ� �� �� �ְ��� ���� �ݾ׿� �˴ϴ�.\n");
	//switch
	*playermoney=*playermoney-(*Localprice/2);
	*Localorder=0;
}
void Chance18(int* playerplace, int* playermoney,int* playernumber)
{
	int block=0;

	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-���ֿ�����û��-.\n");
	printf("�̵��ϰ� ���� �������� �̵��Ͻ� �� �ֽ��ϴ�.\n");
	printf("�̵��� ������� ������ ������ �޽��ϴ�\n");
	printf("�̵��Ͻð� ���� ������ ��ȣ�� �Է����ּ��� : ");
	scanf("%d",&block);
	if(*playerplace>=block)
	{
		printf("������� �����ż� ���� ȹ��!!\n");
		*playermoney=*playermoney+200000;
		printf("���Ͻô� �������� �̵��Ͽ����ϴ�\n");
		*playerplace=block;
		printf("������ �����ϽǼ� �����ϴ�.\n");
	}
	else if(*playerplace<block)
	{
		printf("���Ͻô� �������� �̵��Ͽ����ϴ�\n");
		*playerplace=block;
		printf("������ �����ϽǼ� �����ϴ�.\n");
	}
	
}
void Chance19(int* playermoney,int* welfare)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-��ȸ�������-.\n");
	printf("������� ���� ��ȸ��������� ���޽��ϴ�.\n");
	printf("���� ���� ��ȸ��������� %d���Դϴ�.\n",*welfare);
	*playermoney=*playermoney+*welfare;
	*welfare=0;

}
void Chance20(int* have_ticket)
{
	printf("###���Һ�! �����ƴϸ� ��!###\n");
	printf("-����-.\n");
	printf("��� ������ ���� ����Ḧ �����޴� �����Դϴ�.\n");
	printf("���ǻ��� �Ҹ�Ǹ� �Ÿ� �� �絵�� ���� �ʽ��ϴ�.\n");
	*have_ticket=*have_ticket+1;
	printf("���ϰ� ������ �ִ� ������ �� %d�� �Դϴ�.\n",*have_ticket);

}
void Cruze(int* playermoney)
{
		*playermoney=*playermoney-200000;
}
void Welfare(int* playermoney, int* Welfare_money)
{
	*playermoney=*playermoney-50000;
	*Welfare_money=*Welfare_money+50000;
}
void Space(int* playermoney,int* playerplace)
{
	int want=0;
	char Nu;
	printf("������� ������ �Է��ϼ��� : ");
	scanf("%d",&want);
	
	*playermoney=*playermoney-200000;
	*playerplace=want;
	printf("\n�̵��ϰڽ��ϴ�. \n");
	scanf("%c",&Nu);
}
int Start()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Start.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Uijeongbu()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("������.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Anyang()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Anyang.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Kangchon()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Kangchon.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Choonchune()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Choonchune.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Jeju()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Jeju.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Deakwanryung()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Deakwanryung.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Jeeli()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Jeeli.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Hanra()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Hanra.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int KoreanAir()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("KoreanAir.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Koomi()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Koomi.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Deagu()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Deagu.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Welfare_infor()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Welfare.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Andong()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Andong.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Pohang()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Pohang.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Kyungjoo()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Kyungjoo.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Ulsan()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Ulsan.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Busan()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Busan.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Haeundae()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Haeundae.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Changwon()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Changwon.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Deajun()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Deajun.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Spacetravel()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Spacetravel.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Mokpo()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Mokpo.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Naroho()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Naroho.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Gwangju()
{	int state;
char* pState;
char str[20];

FILE*file=fopen("Gwangju.txt","rt");
if(file==NULL)
{
	printf("file open error!\n");
	return 1;
}

while(1)
{
	pState=fgets(str,sizeof(str),file);
	if(pState==NULL)
		break;
	fputs(str,stdout);
}


state=fclose(file);
if(state!=0)
{
	printf("file close error!\n");
	return 1;
}
}
int Suwon()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Suwon.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Incheon()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Incheon.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Bakdoo()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Bakdoo.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Seoul()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("Seoul.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int NumofLocal()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("NumofLocal.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Dokdo()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("����.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Cruze_infor()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("ũ����.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Saemankm()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("������.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Yungkwang()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("����.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Boryung()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("����.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}
int Chunan()
{
	int state;
	char* pState;
	char str[20];

	FILE*file=fopen("õ��.txt","rt");
	if(file==NULL)
	{
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		pState=fgets(str,sizeof(str),file);
		if(pState==NULL)
			break;
		fputs(str,stdout);
	}


	state=fclose(file);
	if(state!=0)
	{
		printf("file close error!\n");
		return 1;
	}
}