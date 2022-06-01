#define _CRT_SECURE_NO_WARNINGS
#define leapyear(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct ledgerData {
	int date;    //날짜
	int food;    //식료품
	int housing;    //주거비
	int clothes;    //의류비
	int medical;    //의료비
	int transportaion;    //교통비
	int cultural;    //문화생활비
	int communication;    //통신비
	int alco_ciga;    //주류, 담배
	int education;    //교육비
	int housewares;    //가정용품
	int etc;    //기타
	int salary;    //월급
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
				addData();
				system("pause");
			}
			else if (select2 == 2) {    // 고정지출 목록
				printf("222");
				system("pause");
			}
			else if (select2 == 3) {    // 달력
				calendar(list);
				system("pause");
			}
			else if (select2 == 4) {    // 소비 분석
				printf("444");
				system("pause");
			}
			else if (select2 == 5) {    // 뒤로가기
				
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
		if (strcmp(result, "날짜") == 0) {
			result = strtok(NULL, " :\t");
			newnode->date = changeTime(result);
		}
		else if (strcmp(result, "식료품") == 0) {
			result = strtok(NULL, " :\t");
			newnode->food = atoi(result);
		}
		else if (strcmp(result, "주거비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->housing = atoi(result);
		}
		else if (strcmp(result, "의류비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->clothes = atoi(result);
		}
		else if (strcmp(result, "보건의료비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->medical = atoi(result);
		}
		else if (strcmp(result, "교통비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->transportaion = atoi(result);
		}
		else if (strcmp(result, "문화생활비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->cultural = atoi(result);
		}
		else if (strcmp(result, "통신비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->communication = atoi(result);
		}
		else if (strcmp(result, "주류,담배") == 0) {
			result = strtok(NULL, " :\t");
			newnode->alco_ciga = atoi(result);
		}
		else if (strcmp(result, "교육비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->education = atoi(result);
		}
		else if (strcmp(result, "가정용품") == 0) {
			result = strtok(NULL, " :\t");
			newnode->housewares = atoi(result);
		}
		else if (strcmp(result, "기타") == 0) {
			result = strtok(NULL, " :\t");
			newnode->etc = atoi(result);
		}
		else if (strcmp(result, "월급") == 0) {
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

	sscanf(data, "%4d.%d.%d", &year, &month, &day);    // 문자열로 이루어진 시간 데이터에서 '.' 문자 없애고 나머지는 정수로 받기
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
	printf("메뉴 선택 : ");
	scanf("%d", &select);
	if (select == 1) {
		menu5();
		printf("메뉴 선택 : ");
		scanf("%d", &select);
	}
	else if (select == 2) {
		menu6();
		printf("메뉴 선택 : ");
		scanf("%d", &select);
	}
}

void calendar(LEDGERDATA* list) {
	int year, month, k, sum = 0, chk = 0;
	int basicyear[12] = { 31,28,30,31,30,31,31,30,31,30,31 };

	printf("찾고싶은 연도와 달을 입력해주세요 [ex)2022 6]: ");
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
	printf("│ 2. 고정 지출 목록                │\n");
	printf("│                                  │\n");
	printf("│ 3. 캘린더                        │\n");
	printf("│                                  │\n");
	printf("│ 4. 소비 분석                     │\n");
	printf("│                                  │\n");
	printf("│ 5. 뒤로가기                      │\n");
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
	printf("┌───────────── 내역 추가───────────┐\n");
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