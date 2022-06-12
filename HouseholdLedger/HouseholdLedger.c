#define _CRT_SECURE_NO_WARNINGS
//#define leapyear(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
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

typedef struct householdbalance {
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
	int t_income;    // �� �ҵ�
	int t_consume;
	struct householdbalance* next;
}HOUSEHOLDBALANCE;

typedef struct fixedex {
	char category[30];
	int amount;
	struct fixedex* next;
}FIXEDEX;

LEDGERDATA* openData(LEDGERDATA* list);
HOUSEHOLDBALANCE* h_openData(HOUSEHOLDBALANCE* list);
LEDGERDATA* insertList(LEDGERDATA* list, char* data);
HOUSEHOLDBALANCE* h_insertList(HOUSEHOLDBALANCE* list, char* data);
LEDGERDATA* reset(LEDGERDATA* list);
int changeTime(char* data);
void addData(LEDGERDATA* list);
void writeText(LEDGERDATA* list);
void search();
void fixedExpenditure();
void calendar(LEDGERDATA* list);
void consumeAnalysis(LEDGERDATA* list, HOUSEHOLDBALANCE* b_list);
void start();
void menu1();
void menu2();
void menu3();
void menu4();
void menu5();
void menu6();

int main() {
	LEDGERDATA* list = NULL;
	HOUSEHOLDBALANCE* b_list = NULL;
	FILE* fp = NULL;
	int select1 = 0, select2 = 0, select3 = 0;

	//start();
	//system("pause");
	b_list = h_openData(b_list);
	while (1) {
		list = NULL;    // ����ڰ� ���� �߰��ϸ� �ٷ� �ֽ�ȭ �ϱ� ����
		list = openData(list);
		list = reset(list);
		system("CLS");
		menu1();
		printf("�޴� ���� : ");
		scanf("%d", &select1);

		while (1) {
			system("CLS");
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
				}
				else if (select2 == 4) {    // �޷�
					calendar(list);
					system("pause");
				}
				else if (select2 == 5) {    // �Һ� �м�
					consumeAnalysis(list, b_list);
					system("pause");
				}
				else if (select2 == 6) break;    // �ڷΰ���
				else {
					printf("�߸��� ��ȣ �Է�\n");
					system("pause");
					break;
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
				else if (select3 == 3) break;    // �ڷΰ���
				else {
					printf("�߸��� ��ȣ �Է�\n");
					system("pause");
					break;
				}
			}
			else if (select1 == 3) {    // ����
				printf("�����մϴ�.\n");
				exit(1);
			}
			else {
				printf("�߸��� ��ȣ�Դϴ�.\n");
				system("pause");
				break;
			}
		}
	}
	return 0;
}

LEDGERDATA* openData(LEDGERDATA* list) {
	FILE* fp = NULL;
	char data[200];
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

HOUSEHOLDBALANCE* h_openData(HOUSEHOLDBALANCE* list) {
	FILE* fp = NULL;
	char data[200];
	int i = 0;

	fp = fopen("householdBalance.txt", "r");
	if (fp == NULL) {
		printf("householdBalance.txt open error");
		exit(0);
	}

	while (!feof(fp)) {
		fgets(data, sizeof(data), fp);
		if (data == NULL) break;
		list = h_insertList(list, data);
	}

	return list;
}

LEDGERDATA* insertList(LEDGERDATA* list, char* data) {
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

HOUSEHOLDBALANCE* h_insertList(HOUSEHOLDBALANCE* list, char* data) {
	char* result;
	HOUSEHOLDBALANCE* newnode = NULL, * head = list;

	if ((newnode = (HOUSEHOLDBALANCE*)malloc(sizeof(HOUSEHOLDBALANCE))) == NULL) {
		printf("insertList memory allocation error");
		exit(0);
	}

	newnode->t_consume = 0;
	result = strtok(data, " :\t");
	while (result != NULL) {
		if (strcmp(result, "�ķ�ǰ") == 0) {
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
		else if (strcmp(result, "��Ÿ�Һ�") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->c_etc = atoi(result);
		}
		else if (strcmp(result, "�ҵ�") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_income = atoi(result);
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

LEDGERDATA* reset(LEDGERDATA* list) {
	LEDGERDATA* node = list;

	while (node != NULL) {
		if (node->food < 0) node->food = 0;
		if (node->housing < 0) node->housing = 0;
		if (node->clothes < 0) node->clothes = 0;
		if (node->medical < 0) node->medical = 0;
		if (node->transportaion < 0) node->transportaion = 0;
		if (node->cultural < 0) node->cultural = 0;
		if (node->communication < 0) node->communication = 0;
		if (node->alco_ciga < 0) node->alco_ciga = 0;
		if (node->education < 0) node->education = 0;
		if (node->housewares < 0) node->housewares = 0;
		if (node->c_etc < 0) node->c_etc = 0;
		if (node->salary < 0) node->salary = 0;
		if (node->in_etc < 0) node->in_etc = 0;
		node = node->next;
	}

	return list;
}
int changeTime(char* data) {
	int time, year, month, day;

	sscanf(data, "%4d.%d.%d", &year, &month, &day);    // ���ڿ��� �̷���� �ð� �����Ϳ��� '.' ���� ���ְ� �������� ������ �ޱ�
	time = year * 10000 + month * 100 + day;

	return time;
}

void addData(LEDGERDATA* list) {
	LEDGERDATA* head = NULL, * tail = NULL, * newnode = NULL;
	int select = 0, money = 0, already = 0, date = 0;
	head = tail = list;

	if ((newnode = (LEDGERDATA*)malloc(sizeof(LEDGERDATA))) == NULL) {    // �߰��Ǵ� ������ ���Ḯ��Ʈ�� �����ϱ� ����
		printf("addData memory allocation error");
		exit(0);
	}

	printf("��¥ �Է� ex)20210506 : ");
	scanf("%d", &date);

	while (head->next != NULL && head->date != date) {    // �Է��� ��¥ ã��
		tail = head;
		head = head->next;
	}
	if (head->date == date) already = 1;    // �ش��ϴ� ���� �����Ѵٸ� already�� 1�� ����

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
			newnode->date = date;
			newnode->next = NULL;
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
		if (list == NULL) list = newnode;
		else head->next = newnode;
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
		if (list->food > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->food);
			strcat(data, food);
			strcat(data, list_data);
		}
		if (list->housing > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->housing);
			strcat(data, housing);
			strcat(data, list_data);
		}
		if (list->clothes > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->clothes);
			strcat(data, clothes);
			strcat(data, list_data);
		}
		if (list->medical > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->medical);
			strcat(data, medical);
			strcat(data, list_data);
		}
		if (list->transportaion > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->transportaion);
			strcat(data, transportation);
			strcat(data, list_data);
		}
		if (list->cultural > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->cultural);
			strcat(data, cultural);
			strcat(data, list_data);
		}
		if (list->communication > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->communication);
			strcat(data, communication);
			strcat(data, list_data);
		}
		if (list->alco_ciga > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->alco_ciga);
			strcat(data, alco_ciga);
			strcat(data, list_data);
		}
		if (list->education > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->education);
			strcat(data, education);
			strcat(data, list_data);
		}
		if (list->housewares > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->housewares);
			strcat(data, housewares);
			strcat(data, list_data);
		}
		if (list->c_etc > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->c_etc);
			strcat(data, c_etc);
			strcat(data, list_data);
		}
		if (list->salary > 0 || list->in_etc > 0) strcat(data, income);
		if (list->salary > 0) {
			list_data[0] = '\0';
			sprintf(list_data, "%d", list->salary);
			strcat(data, salary);
			strcat(data, list_data);
		}
		if (list->in_etc > 0) {
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
	int date, check = 0;    // check�� ������ Ȯ���ߴµ� �ش� ��¥�� ���� ���� Ȯ���ϱ� ����
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
		strcpy(print_data, data);    // ���پ� �о�� �����Ϳ��� ��¥�� �и�
		result = strtok(data, ":");
		result = strtok(NULL, "\t");
		if (date == atoi(result)) {    // �Է��� ��¥�� �и��� ��¥�� ���ٸ�
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

		printf("%s: %d\n", newnode->category, newnode->amount);
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
}

void calendar(LEDGERDATA* list) {
	int year, month, k, q, t, sum = 0, chk = 0, count = 0, check = 0;    // k = q = t�� ���� ������ ���� �������� Ȯ���ϱ� ����
	int day1 = 1, day2 = 1, i = 0;
	int basicyear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	LEDGERDATA* data[31] = { NULL, };
	printf("ã����� ������ ���� �Է����ּ��� [ex)2022 6]: ");
	scanf("%d %d", &year, &month);

	while (list != NULL) {
		if (list->date / 100 == year * 100 + month) {
			data[i] = list;
			i++;
		}
		list = list->next;
	}

	if ((year % 4 == 0) && !(year % 100 == 0) || (year % 400 == 0)) {    //�������� Ȯ��
		chk = 1;    // �����̶�� üũ
		basicyear[1]++;    // �����̶�� 2���� 29�Ϸ� ��ȯ
	}
	else chk = 0;

	sum = 365;
	for (int i = 1; i < year; i++) {    // ���ۺ��� �۳���� ����̾����� ���
		if ((i % 4 == 0) && !(i % 100 == 0) || (i % 400 == 0)) sum += 366;
		else sum += 365;
	}
	for (int i = 0; i < month - 1; i++) sum += basicyear[i];

	t = q = k = sum % 7;    // ���� ���� ���

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);    // �Ͽ��� ������
	printf("\n\t  SUN\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);    // ���� �����
	printf("  MON\t\t  TUS\t\t  WED\t\t  THU\t\t  FRI\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);    // ����� �Ķ���
	printf("  SAT\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);    // ǥ ���
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");

	for (int j = 0; j < k; j++) printf("\t\t");    // ���ۿ��� ���߱�
	for (int i = 1; i <= basicyear[month - 1]; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("\t   %d\t", i);    // ��¥ ���� ����
		//printf("%d\n", count1);
		count++;
		if (k == 6) {    // ��¥�� 1����ġ �� �����ٸ� �ٹٲٰ� �Һ� ���� ����
			k = -1;
			printf("\n");
			count = 0;
			for (int j = 0; j < q; j++) printf("\t\t");    // ���� ���Ͽ� �°� ĭ ���߱�
			for (q; q <= 6; q++) {    // ������ġ �ݺ�, ó���� ���ۿ����� q���� ����
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);    // ǥ ���
				for (int z = 0; data[z] != NULL; z++) {    
					chk = 0;
					if (data[z]->date == (year * 100 + month) * 100 + day1) {    // �ش� ��¥�� ���� �����Ͱ� data�迭�� �����ϴ��� Ȯ��
						if (check == 1) printf("- %d\t", data[z]->t_consume);    // ĭ ���߱� ����
						else printf("\t- %d\t", data[z]->t_consume);
						if (data[z]->t_consume >= 100000) check = 1;    // �����Ͱ� 6�ڸ��� �Ѵ´ٸ� ������ ���� ĭ�� ���߱� ���� ǥ��
						else check = 0;
						chk = 1;
						break;
					}
				}
				if (chk == 0 && check == 1) printf("- 0\t");    // �ش��ϴ� ��¥�� �����Ͱ� ���ٸ� -0
				else if (chk == 0 && check == 0) printf("\t- 0\t");
				if (q == 6) {    // 1����ġ �Һ� �� �����ٸ� �ٹٲٰ� �ҵ� ���� ����
					printf("\n");
					for (int j = 0; j < t; j++) printf("\t\t");    // ���� ���Ͽ� �°� ĭ ���߱�
					for (t; t <= 6; t++) {
						for (int z = 0; data[z] != NULL; z++) {
							chk = 0;
							if (data[z]->date == (year * 100 + month) * 100 + day2) {    // �ش� ��¥�� ���� �����Ͱ� data�迭�� �����ϴ��� Ȯ��
								if (check == 1) printf("+ %d\t", data[z]->t_income);    // ĭ ���߱� ����
								else printf("\t+ %d\t", data[z]->t_income);
								if (data[z]->t_income >= 100000) check = 1;    // �����Ͱ� 6�ڸ��� �Ѵ´ٸ� ������ ���� ĭ�� ���߱� ���� ǥ��
								else check = 0;
								chk = 1;    // �ش��ϴ� ��¥�� �����Ͱ� �ִٰ� ǥ��
								break;
							}
						}
						if (chk == 0 && check == 1) printf("+ 0\t");    // �ش��ϴ� ��¥�� �����Ͱ� ���ٸ� +0
						else if (chk == 0 && check == 0) printf("\t+ 0\t");
						day2++;    // data�迭�ȿ� ����ڰ� �Է��� ��¥�� �´� ������ �� �ִ��� Ȯ���ϱ� ����
					}
					t = 0;    // ������ġ �� �������� 0���� �ʱ�ȭ
					printf("\n");
				}
				day1++;    // data�迭�ȿ� ����ڰ� �Է��� ��¥�� �´� ������ �� �ִ��� Ȯ���ϱ� ����
			}
			q = 0;    // ������ġ �� �������� 0���� �ʱ�ȭ
			printf("\n");
		}
		k++;    // ������ Ȯ���ϱ� ����
	}
	printf("\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int j = 0; j < q; j++) printf("\t\t");    // ���� ���Ͽ� �°� ĭ ���߱�
	for (int i = 0; i < count; i++) {
		for (int z = 0; data[z] != NULL; z++) {
			chk = 0;
			if (data[z]->date == (year * 100 + month) * 100 + day1) {    // �ش� ��¥�� ���� �����Ͱ� data�迭�� �����ϴ��� Ȯ��
				if (check == 1) printf("- %d\t", data[z]->t_consume);    // ĭ ���߱� ����
				else printf("\t- %d\t", data[z]->t_consume);
				if (data[z]->t_consume >= 100000) check = 1;    // �����Ͱ� 6�ڸ��� �Ѵ´ٸ� ������ ���� ĭ�� ���߱� ���� ǥ��
				else check = 0;
				chk = 1;
				break;
			}
		}
		if (chk == 0 && check == 1) printf("- 0\t");    // �ش��ϴ� ��¥�� �����Ͱ� ���ٸ� -0
		else if (chk == 0 && check == 0) printf("\t- 0\t");
		day1++;
	}
	printf("\n");
	for (int j = 0; j < q; j++) printf("\t\t");    // ���� ���Ͽ� �°� ĭ ���߱�
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < t; j++) printf("\t\t");    // ���� ���Ͽ� �°� ĭ ���߱�
		for (int z = 0; data[z] != NULL; z++) {
			chk = 0;
			if (data[z]->date == (year * 100 + month) * 100 + day2) {    // �ش� ��¥�� ���� �����Ͱ� data�迭�� �����ϴ��� Ȯ��
				if (check == 1) printf("+ %d\t", data[z]->t_income);    // ĭ ���߱� ����
				else printf("\t+ %d\t", data[z]->t_income);
				if (data[z]->t_income >= 100000) check = 1;    // �����Ͱ� 6�ڸ��� �Ѵ´ٸ� ������ ���� ĭ�� ���߱� ���� ǥ��
				else check = 0;
				chk = 1;    // �ش��ϴ� ��¥�� �����Ͱ� �ִٰ� ǥ��
				break;
			}
		}
		if (chk == 0 && check == 1) printf("+ 0\t");    // �ش��ϴ� ��¥�� �����Ͱ� ���ٸ� +0
		else if (chk == 0 && check == 0) printf("\t+ 0\t");
		day2++;    // data�迭�ȿ� ����ڰ� �Է��� ��¥�� �´� ������ �� �ִ��� Ȯ���ϱ� ����
	}
	printf("\n\n\n\n");
}

void consumeAnalysis(LEDGERDATA* list, HOUSEHOLDBALANCE* b_list) {
	int year, month;
	// �Ѵ�ġ �ջ� �ۼ�Ʈ
	double t_food = 0;    // �ķ�ǰ
	double t_housing = 0;    // �ְź�
	double t_clothes = 0;    // �Ƿ���
	double t_medical = 0;    // �Ƿ��
	double t_transportaion = 0;    // �����
	double t_cultural = 0;    // ��ȭ��Ȱ��
	double t_communication = 0;    // ��ź�
	double t_alco_ciga = 0;    // �ַ�, ���
	double t_education = 0;    // ������
	double t_housewares = 0;    // ������ǰ
	double t_c_etc = 0;    // ��Ÿ �Һ�
	double t_consume = 0;    // �� �Һ��
	int t_income = 0;    // �� �ҵ�

	int index[3][2] = { 0, };
	int count = 1;    // ���û ������ ������� ��Ÿ�� �� �ҵ������ ��� ���ϱ� ���� �ҵ������ ������ ���� Ȯ��
	double b_num[11] = { 0, };    // ���û ������ ������� ��Ÿ����
	double t_num[11] = { 0, };  // ����� ������ ������� ��Ÿ����
	int b_t_list[12] = { 0, };    // ���û �Ѵ�ġ ������ ī�װ��� �ݾ� ����
	int t_list[12] = { 0, };    // ����� �Ѵ�ġ ������ ī�װ��� �� �ݾ� ����
	char category[12][11] = { "�ķ�ǰ", "�ְź�", "�Ƿ���", "�Ƿ��","�����", "��ȭ��Ȱ��", "��ź�", "�ַ�,���", "������", "������ǰ", "��Ÿ�Һ�" };

	printf("ã����� ������ ���� �Է����ּ��� [ex)2022 6]: ");
	scanf("%d %d", &year, &month);

	while (1) {    // �Է��� ������ ���� ���ö����� �ݺ�
		if (list->date / 100 == year * 100 + month) {
			break;
		}
		else if (list == NULL) {
			printf("111\n");
			break;
		}
		else list = list->next;
	}

	while (list->date / 100 == year * 100 + month) {
		t_list[0] += list->food;
		t_list[1] += list->housing;
		t_list[2] += list->clothes;
		t_list[3] += list->medical;
		t_list[4] += list->transportaion;
		t_list[5] += list->cultural;
		t_list[6] += list->communication;
		t_list[7] += list->alco_ciga;
		t_list[8] += list->education;
		t_list[9] += list->housewares;
		t_list[10] += list->c_etc;
		t_list[11] += list->t_consume;
		if (list->t_income != 0) t_income = list->t_income;
		list = list->next;
	}

	if (1000000 <= t_income && t_income < 2000000) {
		while (b_list != NULL) {
			if (1000000 < b_list->t_income && b_list->t_income < 2000000) {
				b_t_list[0] += b_list->food / count;
				b_t_list[1] += b_list->housing / count;
				b_t_list[2] += b_list->clothes / count;
				b_t_list[3] += b_list->medical / count;
				b_t_list[4] += b_list->transportaion / count;
				b_t_list[5] += b_list->cultural / count;
				b_t_list[6] += b_list->communication / count;
				b_t_list[7] += b_list->alco_ciga / count;
				b_t_list[8] += b_list->education / count;
				b_t_list[9] += b_list->housewares / count;
				b_t_list[10] += b_list->c_etc / count;
				b_t_list[11] += b_list->t_consume / count;
				count++;
			}
			b_list = b_list->next;
		}
	}
	else if (2000000 <= t_income && t_income < 3000000) {
		while (b_list != NULL) {
			if (2000000 <= b_list->t_income && b_list->t_income < 3000000) {
				b_t_list[0] += b_list->food / count;
				b_t_list[1] += b_list->housing / count;
				b_t_list[2] += b_list->clothes / count;
				b_t_list[3] += b_list->medical / count;
				b_t_list[4] += b_list->transportaion / count;
				b_t_list[5] += b_list->cultural / count;
				b_t_list[6] += b_list->communication / count;
				b_t_list[7] += b_list->alco_ciga / count;
				b_t_list[8] += b_list->education / count;
				b_t_list[9] += b_list->housewares / count;
				b_t_list[10] += b_list->c_etc / count;
				b_t_list[11] += b_list->t_consume / count;
				count++;
			}
			b_list = b_list->next;
		}
	}
	else if (3000000 <= t_income && t_income < 4000000) {
		while (b_list != NULL) {
			if (3000000 <= b_list->t_income && b_list->t_income < 4000000) {
				b_t_list[0] += b_list->food / count;
				b_t_list[1] += b_list->housing / count;
				b_t_list[2] += b_list->clothes / count;
				b_t_list[3] += b_list->medical / count;
				b_t_list[4] += b_list->transportaion / count;
				b_t_list[5] += b_list->cultural / count;
				b_t_list[6] += b_list->communication / count;
				b_t_list[7] += b_list->alco_ciga / count;
				b_t_list[8] += b_list->education / count;
				b_t_list[9] += b_list->housewares / count;
				b_t_list[10] += b_list->c_etc / count;
				b_t_list[11] += b_list->t_consume / count;
				count++;
			}
			b_list = b_list->next;
		}
	}
	printf("\n\n");
	for (int i = 100; i > 0; i -= 5) {
		if (i % 10 == 0) printf("%3d ��", i);  //3d �ڸ��� ���߱� �ִ� 100% ���ڸ��̹Ƿ� 3d
		else printf("    ��");
		for (int j = 0; j < 11; j++) {
			printf("        ");
			b_num[j] = (double)b_t_list[j] / (double)b_t_list[11] * 100;
			t_num[j] = (double)t_list[j] / (double)t_list[11] * 100;
			if ((int)t_num[j] >= i - 2) {  //���� 10���� ���� ���� i���� ũ�ų� ������
				if ((int)t_num[j] + 1 == i || (int)t_num[j] + 2 == i || (int)t_num[j] - 1 == i || (int)t_num[j] - 2 == i || (int)t_num[j] == i) printf("����");  //������ ������ ǥ���ϴ� ���� ��ȣ ���
				else printf("����");  //0���� ������ ������ ���� ��ȣ ���
			}
			else printf("  ");
			if ((int)b_num[j] >= i - 2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				if ((int)b_num[j] + 1 == i || (int)b_num[j] + 2 == i || (int)b_num[j] - 1 == i || (int)b_num[j] - 2 == i || (int)b_num[j] == i) printf(" ����");
				else printf(" ����");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else printf("   ");
		}
		printf("\n");
	}

	printf("%3d ����", 0);  //0�� ǥ��
	for (int i = 0; i < 11; i++) {
		printf("��������������");
		if (t_list != 0 && t_list[i] > 7) {  //0���� �ƴ� ������ �Էµ� �κп��� �������� ��ȣ�� ���
			printf("���� ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("����");
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (t_list[i] != 0 && t_list[i] < 8) {
			printf("���� ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("����");
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (t_list[i] == 0) {
			printf("���� ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("����");
			printf("��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}
	printf("\n");
	printf("      ");
	printf("       �ķ�ǰ       �ְź�       �Ƿ���       �Ƿ��       �����     ��ȭ��Ȱ��     ��ź�     �ַ�,���      ������      ������ǰ     ��Ÿ�Һ�");
	printf("\n");
	printf("==>     ");
	for (int i = 0; i < 11; i++) {
		if (t_list[i] >= 100000) printf("    %d��  ", t_list[i]);
		else if (10000 <= t_list[i] && t_list[i] < 100000) printf("    %d�� ", t_list[i]);
		else if (1000 <= t_list[i] && t_list < 10000) printf("      %d�� ", t_list[i]);
		else if (100 <= t_list[i] && t_list < 1000) printf("       %d�� ", t_list[i]);
		else if (10 <= t_list[i] && t_list < 100) printf("        %d�� ", t_list[i]);
		else printf("       %d��  ", t_list[i]);
	}
	printf("\n\n\n");

	for (int i = 0; i < 3; i++) {    // ���� ū 3���� ���� ã�� ����
		for (int j = 0; j < 11; j++) {
			if (index[i][1] < t_list[j]) {
				if (i == 0) count = 1;    // ó���� �ߺ� Ȯ���� ���� �ʾƵ� �Ǳ⿡ ī��Ʈ�� 1�� �ٲ��ش�
				for (int k = 0; k < i; k++) {    // ������ ���� index �迭�� �̹� ����ִ��� Ȯ��
					if (index[k][1] == t_list[j]) {    // �̹� index�迭�� ����ִٸ�
						count = 0;    // count�� 0���� �����ؼ� �̹� �ִٰ� ǥ��
						break;
					}
					else count = 1;    // index �迭�� �ش� ���� ���⿡ count�� 1�� �����ؼ� ���ٰ� ǥ��
				}
				if (count == 1) {    // index�迭�� �ش� ���� ���ٸ� �ش� ���� index�� ���� ����
					index[i][0] = j;
					index[i][1] = t_list[j];
				}
			}
		}
	}

	printf("���� ī�װ� TOP3\n");
	for (int i = 0; i < 3; i++) {
		if (t_num[index[i][0]] - b_num[index[i][0]] > 20) {
			printf("%d�� %s %d\t���� �ҵ��� ��տ� ���� %.1lf%% �� ���� ���� �־��. �� ����ؼ� ������? �׷��� �ٿ��� ^^\n\n", i + 1, category[index[i][0]], index[i][1], t_num[index[i][0]] - b_num[index[i][0]]);
		}
		else if (t_num[index[i][0]] - b_num[index[i][0]] > 10) {
			printf("%d�� %s %d\t���� �ҵ��� ��տ� ���� %.1lf%% �� ���� ���� �־��. �̰� ���� �ٿ��� �ھ��\n\n", i + 1, category[index[i][0]], index[i][1], t_num[index[i][0]] - b_num[index[i][0]]);
		}
		else if (t_num[index[i][0]] - b_num[index[i][0]] > 0) {
			printf("%d�� %s %d\t���� �ҵ��� ��տ� ���� %.1lf%% �� ���� ���� �־��. ���� �����ϳ׿�\n\n", i + 1, category[index[i][0]], index[i][1], t_num[index[i][0]] - b_num[index[i][0]]);
		}
		else if (t_num[index[i][0]] - b_num[index[i][0]] < 0) {
			printf("%d�� %s %d\t���� �ҵ��� ��տ� ���� %.1lf%% ���� �����־��. ���׿�\n\n", i + 1, category[index[i][0]], index[i][1], t_num[index[i][0]] - b_num[index[i][0]]);
		}
	}
	return 0;
}

void start() {
	printf("\n\n\n\n\t\t\t����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t\t��                                                                                                                                       ��\n");
	printf("\t\t\t��                                                                                                                                       ��\n");
	printf("\t\t\t��                                                                                                                                       ��\n");
	printf("\t\t\t��                                                                           ��                                                           ��\n");
	printf("\t\t\t��                                          ��                              �� ��                                                           ��\n");
	printf("\t\t\t��                         ��������������������������    ��          ��������������������������       �� ��          ��                ��                               ��\n");
	printf("\t\t\t��                                     ��    ��                      ��       �� ��          ��                ��                               ��\n");
	printf("\t\t\t��                                     ��    ��                      �� �������������� ��          ������������������������������������                               ��\n");
	printf("\t\t\t��                                     ��    ��                      ��       �� ��          ��                ��                               ��\n");
	printf("\t\t\t��                                     ��    ��������������                �� �������������� ��          ������������������������������������                               ��\n");
	printf("\t\t\t��                                     ��    ��                      ��       �� ��                                                           ��\n");
	printf("\t\t\t��                                     ��    ��                      ��       �� ��     ����������������������������������������������������������                         ��\n");
	printf("\t\t\t��                                          ��                              �� ��                  ��                                        ��\n");
	printf("\t\t\t��                                          ��                              �� ��                  ��                                        ��\n");
	printf("\t\t\t��                                          ��                              �� ��                  ��                                        ��\n");
	printf("\t\t\t��                                                                           ��                  ��                                        ��\n");
	printf("\t\t\t��                                                                                                                                       ��\n");
	printf("\t\t\t��                                                                                                                                       ��\n");
	printf("\t\t\t��                                                                                                                                       ��\n");
	printf("\t\t\t����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
}

void menu1() {
	printf("\n���������������������������� �޴�����������������������������������\n");
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
	printf("�� 1. ���� �߰� & ����              ��\n");
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
	printf("��                                   ��\n");
	printf("�� 1. ���ο� �÷�                    ��\n");
	printf("��                                   ��\n");
	printf("�� 2. �÷� �ҷ�����                  ��\n");
	printf("��                                   ��\n");
	printf("�� 3. �ڷΰ���                       ��\n");
	printf("��                                   ��\n");
	printf("��������������������������������������������������������������������������\n");
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