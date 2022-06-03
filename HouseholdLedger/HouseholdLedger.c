#define _CRT_SECURE_NO_WARNINGS
#define leapyear(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct ledgerData {
	int date;    // ��¥
	int food;    // �ķ�ǰ
	int housing;    // �ְź�
	int clothes;    // �Ƿ���
	int medical;    // �Ƿ��
	int transportaion;    // �����
	int cultural;    // ��ȭ��Ȱ��
	int communication;    // ��ź�
	int alco_ciga;    // �ַ�, ���
	int education;    // ������
	int housewares;    // ������ǰ
	int c_etc;    // ��Ÿ �Һ�
	int t_consume;    // �� �Һ�ݾ�
	int salary;    // ����
	int in_etc;    // ��Ÿ �ҵ�
	int t_income;    // �� �ҵ�
	struct ledgerData* next;
}LEDGERDATA;

typedef struct fixedex {
	char category[30];
	int amount;
	struct fixedex* next;
}FIXEDEX;

LEDGERDATA* openData(LEDGERDATA* list);
LEDGERDATA* insertList(LEDGERDATA* list, char* data);
int changeTime(char* data);
void addData(LEDGERDATA* list);
void writeText(LEDGERDATA* list);
void search();
void fixedExpenditure();
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
	char test[10] = { NULL };
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
				addData(list);
				system("pause");
			}
			else if (select2 == 2) {    // ��ȸ
				search();
				system("pause");
			}
			else if (select2 == 3) {    // �������� ���
				fixedExpenditure();
				system("pause");
			}
			else if (select2 == 4) {    // �޷�
				calendar(list);
				system("pause");
			}
			else if (select2 == 5) {    // �Һ� �м�
				
			}
			else if (select2 == 6) {    // �ڷΰ���

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
		exit(0);
	}

	while (!feof(fp)) {
		fgets(data, sizeof(data), fp);
		if (data == NULL) break;
		list = insertList(list, data);
	}

	return list;
}

LEDGERDATA* insertList(LEDGERDATA* list, char *data) {
	char* result;
	LEDGERDATA* newnode = NULL, * head = list;

	if ((newnode = (LEDGERDATA*)malloc(sizeof(LEDGERDATA))) == NULL) {
		printf("insertList memory allocation error");
		exit(0);
	}
	
	newnode->t_consume = 0;
	newnode->t_income = 0;
	result = strtok(data, " :\t");
	while (result != NULL) {
		if (strcmp(result, "��¥") == 0) {
			result = strtok(NULL, " :\t");
			newnode->date = atoi(result);
		}
		else if (strcmp(result, "�ķ�ǰ") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->food = atoi(result);
		}
		else if (strcmp(result, "�ְź�") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->housing = atoi(result);
		}
		else if (strcmp(result, "�Ƿ���") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->clothes = atoi(result);
		}
		else if (strcmp(result, "�����Ƿ��") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->medical = atoi(result);
		}
		else if (strcmp(result, "�����") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->transportaion = atoi(result);
		}
		else if (strcmp(result, "��ȭ��Ȱ��") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->cultural = atoi(result);
		}
		else if (strcmp(result, "��ź�") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->communication = atoi(result);
		}
		else if (strcmp(result, "�ַ�,���") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->alco_ciga = atoi(result);
		}
		else if (strcmp(result, "������") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->education = atoi(result);
		}
		else if (strcmp(result, "������ǰ") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->housewares = atoi(result);
		}
		else if (strcmp(result, "��Ÿ") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->c_etc = atoi(result);
		}
		else if (strcmp(result, "����") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_income += atoi(result);
			newnode->salary = atoi(result);
		}
		else if (strcmp(result, "��Ÿ�ҵ�") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_income += atoi(result);
			newnode->in_etc = atoi(result);
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

void addData(LEDGERDATA *list) {
	LEDGERDATA* head = NULL, * tail = NULL, *newnode = NULL;
	int select = 0, money = 0, already = 0;
	char c_date[11];
	int i_date;
	head = tail = list;

	if ((newnode = (LEDGERDATA*)malloc(sizeof(LEDGERDATA))) == NULL) {    // �߰��Ǵ� ������ ���Ḯ��Ʈ�� �����ϱ� ����
		printf("addData memory allocation error");
		exit(0);
	}

	printf("��¥ �Է� ex)2021.5.6 : ");
	scanf("%s", c_date);
	i_date = changeTime(c_date);
	
	while (head != NULL && head->date != i_date) {
		tail = head;
		head = head->next;
	}
	if (head->date == i_date) already = 1;
	newnode->next = head;
	
	if (already == 1) {    // �ش��ϴ� ��¥�� �ش��ϴ� �����Ͱ� �����Ѵٸ� head�� ����
		while (1) {
			menu4();    // 1.�ҵ� 2. �Һ�
			printf("�޴� ���� : ");
			scanf("%d", &select);

			if (select == 1) {
				menu5();    // 1. ���� 2. ��Ÿ
				printf("�޴� ���� : ");
				scanf("%d", &select);
				printf("�ݾ��� �Է��ϼ��� : ");
				if (select == 1) scanf("%d", &head->salary);
				else if (select == 2) scanf("%d", &head->in_etc);
				else {
					printf("�߸��� ��ȣ�Դϴ�.\n");
					continue;    // �ݺ��� �ٽ� ����
				}
			}
			else if (select == 2) {
				menu6();    // �Һ� ī�װ� 11��
				printf("�޴� ���� : ");
				scanf("%d", &select);
				printf("\n�ݾ��� �Է��ϼ��� : ");
				if (select == 1) scanf("%d", &head->food);
				else if (select == 2) scanf("%d", &head->housing);
				else if (select == 3) scanf("%d", &head->clothes);
				else if (select == 4) scanf("%d", &head->medical);
				else if (select == 5) scanf("%d", &head->transportaion);
				else if (select == 6) scanf("%d", &head->cultural);
				else if (select == 7) scanf("%d", &head->communication);
				else if (select == 8) scanf("%d", &head->alco_ciga);
				else if (select == 9) scanf("%d", &head->education);
				else if (select == 10) scanf("%d", &head->housewares);
				else if (select == 11) scanf("%d", &head->c_etc);
				else {
					printf("�߸��� ��ȣ�Դϴ�.\n");
					continue;
				}
			}
			break;    // �߸��� ��ȣ �Է� �����ٸ� �ݺ��� ����
		}
	}
	else {    // �ش��ϴ� ��¥�� �����Ͱ� ���ٸ� ��ġ�� �°� ���Ӱ� �߰�
		while (1) {
			menu4();    // 1.�ҵ� 2. �Һ�
			printf("�޴� ���� : ");
			scanf("%d", &select);

			if (select == 1) {
				menu5();    // 1. ���� 2. ��Ÿ
				printf("�޴� ���� : ");
				scanf("%d", &select);
				printf("�ݾ��� �Է��ϼ��� : ");
				if (select == 1) scanf("%d", &newnode->salary);
				else if (select == 2) scanf("%d", &newnode->in_etc);
				else {
					printf("�߸��� ��ȣ�Դϴ�.\n");
					continue;    // �ݺ��� �ٽ� ����
				}
			}
			else if (select == 2) {
				menu6();    // �Һ� ī�װ� 11��
				printf("�޴� ���� : ");
				scanf("%d", &select);
				printf("\n�ݾ��� �Է��ϼ��� : ");
				if (select == 1) scanf("%d", &newnode->food);
				else if (select == 2) scanf("%d", &newnode->housing);
				else if (select == 3) scanf("%d", &newnode->clothes);
				else if (select == 4) scanf("%d", &newnode->medical);
				else if (select == 5) scanf("%d", &newnode->transportaion);
				else if (select == 6) scanf("%d", &newnode->cultural);
				else if (select == 7) scanf("%d", &newnode->communication);
				else if (select == 8) scanf("%d", &newnode->alco_ciga);
				else if (select == 9) scanf("%d", &newnode->education);
				else if (select == 10) scanf("%d", &newnode->housewares);
				else if (select == 11) scanf("%d", &newnode->c_etc);
				else {
					printf("�߸��� ��ȣ�Դϴ�.\n");
					continue;
				}
			}
			break;    // �߸��� ��ȣ �Է� �����ٸ� �ݺ��� ����
		}

		if (list == head) list = newnode;
		else tail->next = newnode;
	}

	writeText(list);
}

void writeText(LEDGERDATA* list) {
	FILE* fp = NULL;
	char list_data[30] = { NULL };
	char food[20] = " �ķ�ǰ:";
	char housing[20] = " �ְź�:";
	char clothes[20] = " �Ƿ���:";
	char medical[20] = " �����Ƿ��:";
	char transportation[20] = " �����:";
	char cultural[20] = " ��ȭ��Ȱ��:";
	char communication[20] = " ��ź�";
	char alco_ciga[20] = " �ַ�,���:";
	char education[20] = " ������:";
	char housewares[20] = " ������ǰ:";
	char c_etc[20] = " ��Ÿ�Һ�:";
	char salary[20] = " ����:";
	char in_etc[20] = " ��Ÿ�ҵ�:";
	char consume[20] = "\t[�Һ�]";
	char income[20] = "\t[�ҵ�]";
	
	if ((fp = fopen("ledgerData.txt", "w")) == NULL) {
		printf("writeText file open error");
		exit(0);
	}
	
	while (list != NULL) {
		char data[200] = "��¥:";    // txt ���Ͽ� �������� ó���� ���� "��¥:"�� �ʱ�ȭ
		sprintf(list_data, "%d ", list->date);
		strcat(data, list_data);    // �ʱ�ȭ �� data�� list->date�� ���ڷ� �ٲ㼭 �̾���̱�
		if (list->food > 0 || list->housing > 0 || list->clothes > 0 || list->medical > 0 || list->transportaion > 0 || list->cultural > 0 || list->communication > 0 || list->alco_ciga > 0 || list->education > 0 || list->c_etc > 0) {
			// �Һ� ī�װ��� �ִ°� �� �ϳ��� ���� �����Ѵٸ� ���ڿ��� "[�Һ�]" �ֱ�
			strcat(data, consume);
		}
		if (list->food >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->food);
			strcat(data, food);
			strcat(data, list_data);
		}
		if (list->housing >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->housing);
			strcat(data, housing);
			strcat(data, list_data);
		}
		if (list->clothes >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->clothes);
			strcat(data, clothes);
			strcat(data, list_data);
		}
		if (list->medical >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->medical);
			strcat(data, medical);
			strcat(data, list_data);
		}
		if (list->transportaion >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->transportaion);
			strcat(data, transportation);
			strcat(data, list_data);
		}
		if (list->cultural >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->cultural);
			strcat(data, cultural);
			strcat(data, list_data);
		}
		if (list->communication >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->communication);
			strcat(data, communication);
			strcat(data, list_data);
		}
		if (list->alco_ciga >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->alco_ciga);
			strcat(data, alco_ciga);
			strcat(data, list_data);
		}
		if (list->education >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->education);
			strcat(data, education);
			strcat(data, list_data);
		}
		if (list->housewares >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->housewares);
			strcat(data, housewares);
			strcat(data, list_data);
		}
		if (list->c_etc >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->c_etc);
			strcat(data, c_etc);
			strcat(data, list_data);
		}
		if(list->salary >= 0 || list->in_etc >=0) strcat(data, income);
		if (list->salary >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->salary);
			strcat(data, salary);
			strcat(data, list_data);
		}
		if (list->in_etc >= 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->in_etc);
			strcat(data, in_etc);
			strcat(data, list_data);
		}
		fprintf(fp, "%s", data);
		list = list->next;
		if (list == NULL) break;
		fprintf(fp, "\n");
	}
	fclose(fp);
}

void search() {
	int date, check = 0;
	char data[200] = { NULL };
	char print_data[200] = { NULL };
	char* result;
	FILE* fp;

	if ((fp = fopen("ledgerData.txt", "r")) == NULL) {
		printf("search file open error");
		exit(0);
	}

	printf("\n��¥�� �Է��ϼ��� [ ex)20220601 ] : ");
	scanf("%d", &date);
	
	while (!feof(fp)) {
		fgets(data, sizeof(data), fp);
		strcpy(print_data, data);
		result = strtok(data, ":");
		result = strtok(NULL, "\t");
		if (date == atoi(result)) {
			printf("\n%s\n", print_data);
			check = 1;
		}
	}
	if (check == 0) printf("�ش��ϴ� ��¥�� �ҵ�, �Һ� �������ϴ�.\n");

	fclose(fp);
}

void fixedExpenditure() {
	FIXEDEX* list = NULL, * head = NULL, * tail = NULL, * newnode = NULL;
	FILE* fp = NULL;
	char* result;
	char select;
	char category[30] = { NULL };
	char data[100];
	int amount = 0;

	if ((fp = fopen("fixedExpenditure.txt", "r")) == NULL) {
		printf("fixedExpenditure file open error");
		exit(0);
	}

	while (!feof(fp)) {
		head = list;
		newnode = (FIXEDEX*)malloc(sizeof(FIXEDEX));
		newnode->next = NULL;

		fgets(data, sizeof(data), fp);
		result = strtok(data, ":");
		strcpy(newnode->category, result);
		result = strtok(NULL, "\n");
		newnode->amount = atoi(result);

		printf("%s: %d\n",newnode->category, newnode->amount);
		if (list == NULL) list = newnode;
		else {
			while (head->next != NULL) head = head->next;
			head->next = newnode;
		}
	}
	fclose(fp);

	printf("\n����� �����Ϸ��� 1, �ڷ� ������ �ƹ��ų� �����ּ��� : ");
	getchar();
	scanf("%c", &select);
	tail = head = list;

	if (select == '1') {
		fp = fopen("fixedExpenditure.txt", "w");
		newnode = (FIXEDEX*)malloc(sizeof(FIXEDEX));
		newnode->next = NULL;
		printf("�߰� �Ǵ� ������ �̸��� �����ϼ��� [ ex) ���� ] :");
		scanf("%s", newnode->category);
		printf("�ݾ��� �Է����ּ��� ( 0�� �Է½� �ش� �̸��� ���� ������ �����մϴ�.) : ");
		scanf("%d", &newnode->amount);

		if (list == NULL) list = newnode;
		else {
			while (head != NULL) {
				tail = head;
				if (strcmp(head->category, newnode->category) == 0) {
					head->amount = newnode->amount;
					break;
				}
				head = head->next;
				if (head == NULL) tail->next = newnode;
			}
			while (1) {
				tail = list;
				if (list->amount > 0) fprintf(fp, "%s: %d", list->category, list->amount);
				list = list->next;
				if (list == NULL) break;
				if (tail->amount > 0) fprintf(fp, "\n");
			}
		}
	}
	else {
		printf("Pass");
	}
}

void calendar(LEDGERDATA* list) {
	int year, month, k, q, t, sum = 0, chk = 0, count1 = 0, count2 = 0, check = 0;
	int basicyear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	LEDGERDATA* node = NULL;

	printf("ã����� ������ ���� �Է����ּ��� [ex)2022 6]: ");
	scanf("%d %d", &year, &month);

	while (1) {
		if (list->date / 100 == year * 100 + month) {
			break;
		}
		else if (list == NULL) {
			break;
		}
		list = list->next;
	}
	node = list;

	if ((year % 4 == 0) && !(year % 100 == 0) || (year % 400 == 0)) {
		chk = 1;
		basicyear[1]++;
	}
	else chk = 0;

	sum = 365;

	for (int i = 1; i < year; i++) {
		if ((i % 4 == 0) && !(i % 100 == 0) || (i % 400 == 0)) sum += 366;
		else sum += 365;
	}
	for (int i = 0; i < month - 1; i++) sum += basicyear[i];

	t = q = k = sum % 7;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("\n\t  SUN\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("  MON\t\t  TUS\t\t  WED\t\t  THU\t\t  FRI\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	printf("  SAT\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");

	for (int j = 0; j < k; j++) printf("\t\t");
	for (int i = 1; i <= basicyear[month - 1]; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("\t   %d\t", i);
		count1++;
		if (k == 6) {
			k = -1;
			printf("\n");
			count1 = 0;
			for (int j = 0; j < q; j++) printf("\t\t");
			while (1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				if (check == 1) printf("- %d\t", list->t_consume);
				else printf("\t- %d\t", list->t_consume);
				if (list->t_consume >= 100000) check = 1;
				else check = 0;
				list = list->next;
				if (q == 6) {
					q = 0;
					printf("\n");
					for (int j = 0; j < t; j++) printf("\t\t");
					while (1) {
						if (check == 1) printf("+ %d\t", node->t_income);
						else printf("\t+ %d\t", node->t_income);
						if (node->t_income >= 100000) check = 1;
						else check = 0;
						node = node->next;
						if (t == 6) {
							t = 0;
							printf("\n\n");
							break;
						}
						t++;
					}
					break;
				}
				q++;
			}
		}
		k++;
	}
	printf("\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 0; i < count1; i++) {
		if (check == 1) printf("- %d\t", list->t_consume);
		else printf("\t- %d\t", list->t_consume);
		if (list->t_consume >= 1000000) check = 1;
		else check = 0;
		list = list->next;
	}
	printf("\n");

	for (int i = 0; i < count1; i++) {
		if (check == 1) printf("+ %d\t", node->t_income);
		else printf("\t+ %d\t", node->t_income);
		if (node->t_income >= 1000000) check = 1;
		else check = 0;
		node = node->next;
	}
	printf("\n\n\n\n");
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
	printf("�� 2. ��ȸ                          ��\n");
	printf("��                                  ��\n");
	printf("�� 3. ���� ���� ���                ��\n");
	printf("��                                  ��\n");
	printf("�� 4. Ķ����                        ��\n");
	printf("��                                  ��\n");
	printf("�� 5. �Һ� �м�                     ��\n");
	printf("��                                  ��\n");
	printf("�� 6. �ڷΰ���                      ��\n");
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
	printf("����������������������  ���� �߰� ��������������������������\n");
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