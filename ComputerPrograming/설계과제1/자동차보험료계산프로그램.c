/*
2010�� 2�б� ��ǻ�����α׷���
		-�������1-
		2010. 9 28
		���¼�������
		20102020268
		������ǻ�Ͱ��к�
		���ؿ�
*/

#include<stdio.h>


int main(void)
{	
	//���� ����
	int YEAR_CAR;
	int YEAR_DRIVE;
	int INS;
	int INS_BEFORE;
	int INS_LAST;
	int CAR_NEW;
	int CAR_TRUE;
	char MODEL;
	float DC;
    float PER;
	
	//���û��� �Է�
	printf("<�ڵ�������������α׷�>\n");
	printf("�ؿ� ���õǴ� ������ �Է����ּ���\n");
	printf("�� : ");
	scanf("%c",&MODEL);//�� �Է�
	printf("���� : ");
	scanf("%d",&YEAR_CAR);//���� �Է�
	printf("������� : ");
	scanf("%d",&YEAR_DRIVE);//������� �Է�
	printf("�빰��� : ");
	scanf("%d",&INS);//�빰��� �Է�
	
	//����
	CAR_NEW = 50000000-(MODEL-65)*15000000; //�������ݰ��
	PER = 70-MODEL;							//�𵨰� ���Ŀ� ���� �޶����� ������
	DC = (CAR_NEW*PER*(2010-YEAR_CAR))/100; //�������� - ��������
	CAR_TRUE = CAR_NEW-DC;					//�������ݰ��
	INS_BEFORE = 90000+(INS*50000)+(CAR_TRUE*0.02);		//������ �������
	INS_LAST = INS_BEFORE-(INS_BEFORE*0.03*YEAR_DRIVE); //������¿� ���� ���ε� �����(����)
	//1000���̸� ���� 
	CAR_TRUE = (CAR_TRUE/1000)*1000;
	INS_BEFORE = (INS_BEFORE/1000)*1000;
	INS_LAST = (INS_LAST/1000)*1000;
	//��� ���
	printf("==================\n");
	printf("==���������==\n");
	printf("==================\n");
	printf("���� �����ݾ� : %d\n",CAR_NEW);//��������
	printf("���� �����ݾ� : %d\n",CAR_TRUE);//��������
	printf("������ ����� : %d\n",INS_BEFORE);//�����������
	printf("����   ����� : %d\n",INS_LAST);//���������

	return 0;
}