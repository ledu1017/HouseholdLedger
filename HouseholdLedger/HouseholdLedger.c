#define _CRT_SECURE_NO_WARNINGS
#define leapyear(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct ledgerData {
	int date;    //��¥
	int food;    //�ķ�ǰ
	int housing;    //�ְź�
	int clothes;    //�Ƿ���
	int medical;    //�Ƿ��
	int transportaion;    //�����
	int cultural;    //��ȭ��Ȱ��
	int communication;    //��ź�
	int alco_ciga;    //�ַ�, ���
	int education;    //������
	int housewares;    //������ǰ
	int etc;    //��Ÿ
	int salary;    //����
	struct ledgerData* next;
}LEDGERDATA;

LEDGERDATA* openData(LEDGERDATA* list);
LEDGERDATA* insertList(LEDGERDATA* list, char* data);
int changeTime(char* data);
void addData();
void calendar(LEDGERDATA *list);
void menu1();
void menu2();
void menu3();
void menu4();
void menu5();
void menu6();

int main() {
	int select1 = 0, select2 = 0, select3 = 0;
	LEDGERDATA* list = NULL;

	while (1) {
		list = NULL;    // ����ڰ� ���� �߰��ϸ� �ٷ� �ֽ�ȭ �ϱ� ����
		list = openData(list);
		system("CLS");
		menu1();
		printf("�޴� ���� : ");
		scanf("%d", &select1);

		if (select1 == 1) {    // ����� �޴�
			menu2();
			printf("�޴� ���� : ");
			scanf("%d", &select2);
			if (select2 == 1) {    // ���� �߰�
				addData();
				system("pause");
			}
			else if (select2 == 2) {    // �������� ���
				printf("222");
				system("pause");
			}
			else if (select2 == 3) {    // �޷�
				calendar(list);
				system("pause");
			}
			else if (select2 == 4) {    // �Һ� �м�
				printf("444");
				system("pause");
			}
			else if (select2 == 5) {    // �ڷΰ���
				
			}
			else {
				printf("�߸��� ��ȣ �Է�\n");
				system("pause");
			}
		}
		else if (select1 == 2) {    // �����÷� �޴�
			menu3();
			printf("�޴� ���� : ");
			scanf("%d", &select3);
			if (select3 == 1) {    // �÷� �����
				printf("111");
				system("pause");
			}
			else if (select3 == 2) {    // �÷� �ҷ�����
				printf("222");
				system("pause");
			}
			else if (select3 == 3) {    // �ڷΰ���
				printf("333");
				system("pause");
			}
			else {
				printf("4444");
				system("pause");
			}
		}
		else if (select1 == 3) {    // ����
			printf("�����մϴ�.\n");
			exit(1);
		}
		else {
			printf("�߸��� ��ȣ�Դϴ�.\n");
			system("pause");
		}
	}
	return 0;
}

LEDGERDATA* openData(LEDGERDATA* list) {
	char data[200];
	FILE* fp = NULL;
	int i = 0;
	fp = fopen("ledgerData.txt", "r");
	if (fp == NULL) {
		printf("ledgerData.txt open error");
		return NULL;
	}

	while (!feof(fp)) {
		fgets(data, sizeof(data), fp);
		list = insertList(list, data);
	}

	fclose(fp);
	return list;
}

LEDGERDATA* insertList(LEDGERDATA* list, char *data) {
	char* result;
	LEDGERDATA* newnode = NULL, * head = list;

	if ((newnode = (LEDGERDATA*)malloc(sizeof(LEDGERDATA))) == NULL) {
		printf("insertList memory allocation error");
		return NULL;
	}

	result = strtok(data, " :\t");
	while (result != NULL) {
		if (strcmp(result, "��¥") == 0) {
			result = strtok(NULL, " :\t");
			newnode->date = changeTime(result);
		}
		else if (strcmp(result, "�ķ�ǰ") == 0) {
			result = strtok(NULL, " :\t");
			newnode->food = atoi(result);
		}
		else if (strcmp(result, "�ְź�") == 0) {
			result = strtok(NULL, " :\t");
			newnode->housing = atoi(result);
		}
		else if (strcmp(result, "�Ƿ���") == 0) {
			result = strtok(NULL, " :\t");
			newnode->clothes = atoi(result);
		}
		else if (strcmp(result, "�����Ƿ��") == 0) {
			result = strtok(NULL, " :\t");
			newnode->medical = atoi(result);
		}
		else if (strcmp(result, "�����") == 0) {
			result = strtok(NULL, " :\t");
			newnode->transportaion = atoi(result);
		}
		else if (strcmp(result, "��ȭ��Ȱ��") == 0) {
			result = strtok(NULL, " :\t");
			newnode->cultural = atoi(result);
		}
		else if (strcmp(result, "��ź�") == 0) {
			result = strtok(NULL, " :\t");
			newnode->communication = atoi(result);
		}
		else if (strcmp(result, "�ַ�,���") == 0) {
			result = strtok(NULL, " :\t");
			newnode->alco_ciga = atoi(result);
		}
		else if (strcmp(result, "������") == 0) {
			result = strtok(NULL, " :\t");
			newnode->education = atoi(result);
		}
		else if (strcmp(result, "������ǰ") == 0) {
			result = strtok(NULL, " :\t");
			newnode->housewares = atoi(result);
		}
		else if (strcmp(result, "��Ÿ") == 0) {
			result = strtok(NULL, " :\t");
			newnode->etc = atoi(result);
		}
		else if (strcmp(result, "����") == 0) {
			result = strtok(NULL, " :\t");
			newnode->salary = atoi(result);
		}
		else {
			result = strtok(NULL, " :\t");
		}
	}

	newnode->next = NULL;
	if (list == NULL) list = newnode;
	else {
		while (head->next != NULL) head = head->next;
		head->next = newnode;
	}

	return list;
}

int changeTime(char* data) {
	int time, year, month, day;

	sscanf(data, "%4d.%d.%d", &year, &month, &day);    // ���ڿ��� �̷���� �ð� �����Ϳ��� '.' ���� ���ְ� �������� ������ �ޱ�
	time = year * 10000 + month * 100 + day;
	
	return time;
}

void addData() {
	FILE* fp = NULL;
	int select = 0, money = 0;

	if ((fp = fopen("ledgerData.txt", "a") == NULL)) {
		printf("addData file open error");
		return;
	}

	menu4();
	printf("�޴� ���� : ");
	scanf("%d", &select);
	if (select == 1) {
		menu5();
		printf("�޴� ���� : ");
		scanf("%d", &select);
	}
	else if (select == 2) {
		menu6();
		printf("�޴� ���� : ");
		scanf("%d", &select);
	}
}

void calendar(LEDGERDATA* list) {
	int year, month, k, sum = 0, chk = 0;
	int basicyear[12] = { 31,28,30,31,30,31,31,30,31,30,31 };

	printf("ã����� ������ ���� �Է����ּ��� [ex)2022 6]: ");
	scanf("%d %d", &year, &month);

	if ((year % 4 == 0) && !(year % 100 == 0) || (year % 400 == 0)) {
		chk = 1;
		basicyear[1]++;
	}
	else chk = 0;

	sum = 365;
	for (int i = 1; i < year; i++) {
		if ((i % 4 == 0) && !(i % 100 == 0) || (i % 400 == 0)) sum += 365;
		else sum += 365;
	}

	for (int i = 0; i < month - 1; i++) sum += basicyear[i];

	k = sum % 7;

	printf("SUN\tMON\tTUS\tWED\tTHU\tFRI\tSAT\n");
	printf("==========================================\n");

	for (int j = 0; j < k; j++) printf("\t");
	for (int i = 1; i < basicyear[month - 1]; i++) {
		printf("%d\t", i);
		if (k == 6) {
			k = -1;
			printf("\n");
		}
		k++;
	}
	printf("\n");
}

void menu1() {
	printf("���������������������������� �޴�����������������������������������\n");
	printf("��                                  ��\n");
	printf("�� 1. �����                        ��\n");
	printf("��                                  ��\n");
	printf("�� 2. ���� �÷�                     ��\n");
	printf("��                                  ��\n");
	printf("�� 3. ����                          ��\n");
	printf("��                                  ��\n");
	printf("������������������������������������������������������������������������\n");
}

void menu2() {
	printf("���������������������������� ����Φ�����������������������������\n");
	printf("��                                  ��\n");
	printf("�� 1. ���� �߰�                     ��\n");
	printf("��                                  ��\n");
	printf("�� 2. ���� ���� ���                ��\n");
	printf("��                                  ��\n");
	printf("�� 3. Ķ����                        ��\n");
	printf("��                                  ��\n");
	printf("�� 4. �Һ� �м�                     ��\n");
	printf("��                                  ��\n");
	printf("�� 5. �ڷΰ���                      ��\n");
	printf("��                                  ��\n");
	printf("������������������������������������������������������������������������\n");
}

void menu3() {
	printf("���������������������������� ���� �÷���������������������������\n");
	printf("��                                  ��\n");
	printf("�� 1. ���ο� �÷�                   ��\n");
	printf("��                                  ��\n");
	printf("�� 2. �÷� �ҷ�����                 ��\n");
	printf("��                                  ��\n");
	printf("�� 3. �ڷΰ���                      ��\n");
	printf("��                                  ��\n");
	printf("������������������������������������������������������������������������\n");
}

void menu4() {
	printf("���������������������������� ���� �߰�������������������������\n");
	printf("��                                  ��\n");
	printf("�� 1. �ҵ�                          ��\n");
	printf("��                                  ��\n");
	printf("�� 2. �Һ�                          ��\n");
	printf("��                                  ��\n");
	printf("������������������������������������������������������������������������\n");
}

void menu5() {
	printf("�������������������� �ҵ� ī�װ�������������������������\n");
	printf("��                                  ��\n");
	printf("�� 1. ����                          ��\n");
	printf("��                                  ��\n");
	printf("�� 2. ��Ÿ                          ��\n");
	printf("��                                  ��\n");
	printf("������������������������������������������������������������������������\n");
}

void menu6() {
	printf("���������������������������������������������������������������� �Һ� ī�װ���������������������������������������������������������������������\n");
	printf("��                                                                              ��\n");
	printf("�� 1. �ķ�ǰ        2. �ְź�    3. �Ƿ���       4. ���� �Ƿ��    5. �����    ��\n");
	printf("��                                                                              ��\n");
	printf("�� 6. ��ȭ��Ȱ��    7. ��ź�    8. �ַ�, ���   9. ������         10. ������ǰ ��\n");
	printf("��                                                                              ��\n");
	printf("�� 11. ��Ÿ                                                                     ��\n");
	printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
}