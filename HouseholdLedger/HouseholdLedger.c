#define _CRT_SECURE_NO_WARNINGS
#define leapyear(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct ledgerData {
	int date;    // 날짜
	int food;    // 식료품
	int housing;    // 주거비
	int clothes;    // 의류비
	int medical;    // 의료비
	int transportaion;    // 교통비
	int cultural;    // 문화생활비
	int communication;    // 통신비
	int alco_ciga;    // 주류, 담배
	int education;    // 교육비
	int housewares;    // 가정용품
	int c_etc;    // 기타 소비
	int t_consume;    // 총 소비금액
	int salary;    // 월급
	int in_etc;    // 기타 소득
	int t_income;    // 총 소득
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
		list = NULL;    // 사용자가 내역 추가하면 바로 최신화 하기 위함
		list = openData(list);
		system("CLS");
		menu1();
		printf("메뉴 선택 : ");
		scanf("%d", &select1);

		if (select1 == 1) {    // 가계부 메뉴
			menu2();
			printf("메뉴 선택 : ");
			scanf("%d", &select2);
			if (select2 == 1) {    // 내역 추가
				addData(list);
				system("pause");
			}
			else if (select2 == 2) {    // 조회
				search();
				system("pause");
			}
			else if (select2 == 3) {    // 고정지출 목록
				fixedExpenditure();
				system("pause");
			}
			else if (select2 == 4) {    // 달력
				calendar(list);
				system("pause");
			}
			else if (select2 == 5) {    // 소비 분석
				
			}
			else if (select2 == 6) {    // 뒤로가기

			}
			else {
				printf("잘못된 번호 입력\n");
				system("pause");
			}
		}
		else if (select1 == 2) {    // 적금플랜 메뉴
			menu3();
			printf("메뉴 선택 : ");
			scanf("%d", &select3);
			if (select3 == 1) {    // 플랜 만들기
				printf("111");
				system("pause");
			}
			else if (select3 == 2) {    // 플랜 불러오기
				printf("222");
				system("pause");
			}
			else if (select3 == 3) {    // 뒤로가기
				printf("333");
				system("pause");
			}
			else {
				printf("4444");
				system("pause");
			}
		}
		else if (select1 == 3) {    // 종료
			printf("종료합니다.\n");
			exit(1);
		}
		else {
			printf("잘못된 번호입니다.\n");
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
		if (strcmp(result, "날짜") == 0) {
			result = strtok(NULL, " :\t");
			newnode->date = atoi(result);
		}
		else if (strcmp(result, "식료품") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->food = atoi(result);
		}
		else if (strcmp(result, "주거비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->housing = atoi(result);
		}
		else if (strcmp(result, "의류비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->clothes = atoi(result);
		}
		else if (strcmp(result, "보건의료비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->medical = atoi(result);
		}
		else if (strcmp(result, "교통비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->transportaion = atoi(result);
		}
		else if (strcmp(result, "문화생활비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->cultural = atoi(result);
		}
		else if (strcmp(result, "통신비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->communication = atoi(result);
		}
		else if (strcmp(result, "주류,담배") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->alco_ciga = atoi(result);
		}
		else if (strcmp(result, "교육비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->education = atoi(result);
		}
		else if (strcmp(result, "가정용품") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->housewares = atoi(result);
		}
		else if (strcmp(result, "기타") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->c_etc = atoi(result);
		}
		else if (strcmp(result, "월급") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_income += atoi(result);
			newnode->salary = atoi(result);
		}
		else if (strcmp(result, "기타소득") == 0) {
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

	sscanf(data, "%4d.%d.%d", &year, &month, &day);    // 문자열로 이루어진 시간 데이터에서 '.' 문자 없애고 나머지는 정수로 받기
	time = year * 10000 + month * 100 + day;
	
	return time;
}

void addData(LEDGERDATA *list) {
	LEDGERDATA* head = NULL, * tail = NULL, *newnode = NULL;
	int select = 0, money = 0, already = 0;
	char c_date[11];
	int i_date;
	head = tail = list;

	if ((newnode = (LEDGERDATA*)malloc(sizeof(LEDGERDATA))) == NULL) {    // 추가되는 내역을 연결리스트에 연결하기 위함
		printf("addData memory allocation error");
		exit(0);
	}

	printf("날짜 입력 ex)2021.5.6 : ");
	scanf("%s", c_date);
	i_date = changeTime(c_date);
	
	while (head != NULL && head->date != i_date) {
		tail = head;
		head = head->next;
	}
	if (head->date == i_date) already = 1;
	newnode->next = head;
	
	if (already == 1) {    // 해당하는 날짜에 해당하는 데이터가 존재한다면 head값 수정
		while (1) {
			menu4();    // 1.소득 2. 소비
			printf("메뉴 선택 : ");
			scanf("%d", &select);

			if (select == 1) {
				menu5();    // 1. 월급 2. 기타
				printf("메뉴 선택 : ");
				scanf("%d", &select);
				printf("금액을 입력하세요 : ");
				if (select == 1) scanf("%d", &head->salary);
				else if (select == 2) scanf("%d", &head->in_etc);
				else {
					printf("잘못된 번호입니다.\n");
					continue;    // 반복문 다시 실행
				}
			}
			else if (select == 2) {
				menu6();    // 소비 카테고리 11개
				printf("메뉴 선택 : ");
				scanf("%d", &select);
				printf("\n금액을 입력하세요 : ");
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
					printf("잘못된 번호입니다.\n");
					continue;
				}
			}
			break;    // 잘못된 번호 입력 없었다면 반복문 종료
		}
	}
	else {    // 해당하는 날짜에 데이터가 없다면 위치에 맞게 새롭게 추가
		while (1) {
			menu4();    // 1.소득 2. 소비
			printf("메뉴 선택 : ");
			scanf("%d", &select);

			if (select == 1) {
				menu5();    // 1. 월급 2. 기타
				printf("메뉴 선택 : ");
				scanf("%d", &select);
				printf("금액을 입력하세요 : ");
				if (select == 1) scanf("%d", &newnode->salary);
				else if (select == 2) scanf("%d", &newnode->in_etc);
				else {
					printf("잘못된 번호입니다.\n");
					continue;    // 반복문 다시 실행
				}
			}
			else if (select == 2) {
				menu6();    // 소비 카테고리 11개
				printf("메뉴 선택 : ");
				scanf("%d", &select);
				printf("\n금액을 입력하세요 : ");
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
					printf("잘못된 번호입니다.\n");
					continue;
				}
			}
			break;    // 잘못된 번호 입력 없었다면 반복문 종료
		}

		if (list == head) list = newnode;
		else tail->next = newnode;
	}

	writeText(list);
}

void writeText(LEDGERDATA* list) {
	FILE* fp = NULL;
	char list_data[30] = { NULL };
	char food[20] = " 식료품:";
	char housing[20] = " 주거비:";
	char clothes[20] = " 의류비:";
	char medical[20] = " 보건의료비:";
	char transportation[20] = " 교통비:";
	char cultural[20] = " 문화생활비:";
	char communication[20] = " 통신비";
	char alco_ciga[20] = " 주류,담배:";
	char education[20] = " 교육비:";
	char housewares[20] = " 가정용품:";
	char c_etc[20] = " 기타소비:";
	char salary[20] = " 월급:";
	char in_etc[20] = " 기타소득:";
	char consume[20] = "\t[소비]";
	char income[20] = "\t[소득]";
	
	if ((fp = fopen("ledgerData.txt", "w")) == NULL) {
		printf("writeText file open error");
		exit(0);
	}
	
	while (list != NULL) {
		char data[200] = "날짜:";    // txt 파일에 쓰기위해 처음에 들어가는 "날짜:"로 초기화
		sprintf(list_data, "%d ", list->date);
		strcat(data, list_data);    // 초기화 한 data에 list->date를 문자로 바꿔서 이어붙이기
		if (list->food > 0 || list->housing > 0 || list->clothes > 0 || list->medical > 0 || list->transportaion > 0 || list->cultural > 0 || list->communication > 0 || list->alco_ciga > 0 || list->education > 0 || list->c_etc > 0) {
			// 소비 카테고리에 있는것 중 하나라도 값이 존재한다면 문자열에 "[소비]" 넣기
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

	printf("\n날짜를 입력하세요 [ ex)20220601 ] : ");
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
	if (check == 0) printf("해당하는 날짜에 소득, 소비가 없었습니다.\n");

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

	printf("\n목록을 수정하려면 1, 뒤로 가려면 아무거나 눌러주세요 : ");
	getchar();
	scanf("%c", &select);
	tail = head = list;

	if (select == '1') {
		fp = fopen("fixedExpenditure.txt", "w");
		newnode = (FIXEDEX*)malloc(sizeof(FIXEDEX));
		newnode->next = NULL;
		printf("추가 또는 수정할 이름을 선택하세요 [ ex) 월세 ] :");
		scanf("%s", newnode->category);
		printf("금액을 입력해주세요 ( 0원 입력시 해당 이름에 대한 내용을 삭제합니다.) : ");
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

	printf("찾고싶은 연도와 달을 입력해주세요 [ex)2022 6]: ");
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
	printf("────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");

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
	printf("┌───────────── 메뉴────────────────┐\n");
	printf("│                                  │\n");
	printf("│ 1. 가계부                        │\n");
	printf("│                                  │\n");
	printf("│ 2. 적금 플랜                     │\n");
	printf("│                                  │\n");
	printf("│ 3. 종료                          │\n");
	printf("│                                  │\n");
	printf("└──────────────────────────────────┘\n");
}

void menu2() {
	printf("┌───────────── 가계부──────────────┐\n");
	printf("│                                  │\n");
	printf("│ 1. 내역 추가                     │\n");
	printf("│                                  │\n");
	printf("│ 2. 조회                          │\n");
	printf("│                                  │\n");
	printf("│ 3. 고정 지출 목록                │\n");
	printf("│                                  │\n");
	printf("│ 4. 캘린더                        │\n");
	printf("│                                  │\n");
	printf("│ 5. 소비 분석                     │\n");
	printf("│                                  │\n");
	printf("│ 6. 뒤로가기                      │\n");
	printf("│                                  │\n");
	printf("└──────────────────────────────────┘\n");
}

void menu3() {
	printf("┌───────────── 적금 플랜────────────┐\n");
	printf("│                                  │\n");
	printf("│ 1. 새로운 플랜                   │\n");
	printf("│                                  │\n");
	printf("│ 2. 플랜 불러오기                 │\n");
	printf("│                                  │\n");
	printf("│ 3. 뒤로가기                      │\n");
	printf("│                                  │\n");
	printf("└──────────────────────────────────┘\n");
}

void menu4() {
	printf("┌──────────  내역 추가 ────────────┐\n");
	printf("│                                  │\n");
	printf("│ 1. 소득                          │\n");
	printf("│                                  │\n");
	printf("│ 2. 소비                          │\n");
	printf("│                                  │\n");
	printf("└──────────────────────────────────┘\n");
}

void menu5() {
	printf("┌───────── 소득 카테고리───────────┐\n");
	printf("│                                  │\n");
	printf("│ 1. 월급                          │\n");
	printf("│                                  │\n");
	printf("│ 2. 기타                          │\n");
	printf("│                                  │\n");
	printf("└──────────────────────────────────┘\n");
}

void menu6() {
	printf("┌─────────────────────────────── 소비 카테고리─────────────────────────────────┐\n");
	printf("│                                                                              │\n");
	printf("│ 1. 식료품        2. 주거비    3. 의류비       4. 보건 의료비    5. 교통비    │\n");
	printf("│                                                                              │\n");
	printf("│ 6. 문화생활비    7. 통신비    8. 주류, 담배   9. 교육비         10. 가정용품 │\n");
	printf("│                                                                              │\n");
	printf("│ 11. 기타                                                                     │\n");
	printf("└──────────────────────────────────────────────────────────────────────────────┘\n");
}