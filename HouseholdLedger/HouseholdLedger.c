#define _CRT_SECURE_NO_WARNINGS
//#define leapyear(year) ((year)%4 == 0 && ((year)%100 != 0 || (year)%400 == 0))
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

typedef struct householdbalance {
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
	int t_income;    // 총 소득
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
		list = NULL;    // 사용자가 내역 추가하면 바로 최신화 하기 위함
		list = openData(list);
		list = reset(list);
		system("CLS");
		menu1();
		printf("메뉴 선택 : ");
		scanf("%d", &select1);

		while (1) {
			system("CLS");
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
				}
				else if (select2 == 4) {    // 달력
					calendar(list);
					system("pause");
				}
				else if (select2 == 5) {    // 소비 분석
					consumeAnalysis(list, b_list);
					system("pause");
				}
				else if (select2 == 6) break;    // 뒤로가기
				else {
					printf("잘못된 번호 입력\n");
					system("pause");
					break;
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
				else if (select3 == 3) break;    // 뒤로가기
				else {
					printf("잘못된 번호 입력\n");
					system("pause");
					break;
				}
			}
			else if (select1 == 3) {    // 종료
				printf("종료합니다.\n");
				exit(1);
			}
			else {
				printf("잘못된 번호입니다.\n");
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
		if (strcmp(result, "식료품") == 0) {
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
		else if (strcmp(result, "기타소비") == 0) {
			result = strtok(NULL, " :\t");
			newnode->t_consume += atoi(result);
			newnode->c_etc = atoi(result);
		}
		else if (strcmp(result, "소득") == 0) {
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

	sscanf(data, "%4d.%d.%d", &year, &month, &day);    // 문자열로 이루어진 시간 데이터에서 '.' 문자 없애고 나머지는 정수로 받기
	time = year * 10000 + month * 100 + day;

	return time;
}

void addData(LEDGERDATA* list) {
	LEDGERDATA* head = NULL, * tail = NULL, * newnode = NULL;
	int select = 0, money = 0, already = 0, date = 0;
	head = tail = list;

	if ((newnode = (LEDGERDATA*)malloc(sizeof(LEDGERDATA))) == NULL) {    // 추가되는 내역을 연결리스트에 연결하기 위함
		printf("addData memory allocation error");
		exit(0);
	}

	printf("날짜 입력 ex)20210506 : ");
	scanf("%d", &date);

	while (head->next != NULL && head->date != date) {    // 입력한 날짜 찾기
		tail = head;
		head = head->next;
	}
	if (head->date == date) already = 1;    // 해당하는 값이 존재한다면 already를 1로 수정

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
			newnode->date = date;
			newnode->next = NULL;
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
		if (list == NULL) list = newnode;
		else head->next = newnode;
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
	int date, check = 0;    // check는 끝까지 확인했는데 해당 날짜가 없을 때를 확인하기 위함
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
		strcpy(print_data, data);    // 한줄씩 읽어온 데이터에서 날짜만 분리
		result = strtok(data, ":");
		result = strtok(NULL, "\t");
		if (date == atoi(result)) {    // 입력한 날짜와 분리한 날짜가 같다면
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

		printf("%s: %d\n", newnode->category, newnode->amount);
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
}

void calendar(LEDGERDATA* list) {
	int year, month, k, q, t, sum = 0, chk = 0, count = 0, check = 0;    // k = q = t로 달의 시작이 무슨 요일인지 확인하기 위함
	int day1 = 1, day2 = 1, i = 0;
	int basicyear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	LEDGERDATA* data[31] = { NULL, };
	printf("찾고싶은 연도와 달을 입력해주세요 [ex)2022 6]: ");
	scanf("%d %d", &year, &month);

	while (list != NULL) {
		if (list->date / 100 == year * 100 + month) {
			data[i] = list;
			i++;
		}
		list = list->next;
	}

	if ((year % 4 == 0) && !(year % 100 == 0) || (year % 400 == 0)) {    //윤년인지 확인
		chk = 1;    // 윤년이라면 체크
		basicyear[1]++;    // 윤년이라면 2월을 29일로 변환
	}
	else chk = 0;

	sum = 365;
	for (int i = 1; i < year; i++) {    // 시작부터 작년까지 몇년이었는지 계산
		if ((i % 4 == 0) && !(i % 100 == 0) || (i % 400 == 0)) sum += 366;
		else sum += 365;
	}
	for (int i = 0; i < month - 1; i++) sum += basicyear[i];

	t = q = k = sum % 7;    // 시작 요일 계산

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);    // 일요일 빨간색
	printf("\n\t  SUN\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);    // 평일 노란색
	printf("  MON\t\t  TUS\t\t  WED\t\t  THU\t\t  FRI\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);    // 토요일 파란색
	printf("  SAT\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);    // 표 흰색
	printf("────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");

	for (int j = 0; j < k; j++) printf("\t\t");    // 시작요일 맞추기
	for (int i = 1; i <= basicyear[month - 1]; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("\t   %d\t", i);    // 날짜 쓰는 과정
		//printf("%d\n", count1);
		count++;
		if (k == 6) {    // 날짜를 1주일치 다 적었다면 줄바꾸고 소비 내역 쓰기
			k = -1;
			printf("\n");
			count = 0;
			for (int j = 0; j < q; j++) printf("\t\t");    // 시작 요일에 맞게 칸 맞추기
			for (q; q <= 6; q++) {    // 일주일치 반복, 처음은 시작요일인 q에서 시작
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);    // 표 흰색
				for (int z = 0; data[z] != NULL; z++) {    
					chk = 0;
					if (data[z]->date == (year * 100 + month) * 100 + day1) {    // 해당 날짜에 대한 데이터가 data배열에 존재하는지 확인
						if (check == 1) printf("- %d\t", data[z]->t_consume);    // 칸 맞추기 위함
						else printf("\t- %d\t", data[z]->t_consume);
						if (data[z]->t_consume >= 100000) check = 1;    // 데이터가 6자리를 넘는다면 탭으로 띄우는 칸을 맞추기 위해 표시
						else check = 0;
						chk = 1;
						break;
					}
				}
				if (chk == 0 && check == 1) printf("- 0\t");    // 해당하는 날짜에 데이터가 없다면 -0
				else if (chk == 0 && check == 0) printf("\t- 0\t");
				if (q == 6) {    // 1주일치 소비 다 적었다면 줄바꾸고 소득 내역 쓰기
					printf("\n");
					for (int j = 0; j < t; j++) printf("\t\t");    // 시작 요일에 맞게 칸 맞추기
					for (t; t <= 6; t++) {
						for (int z = 0; data[z] != NULL; z++) {
							chk = 0;
							if (data[z]->date == (year * 100 + month) * 100 + day2) {    // 해당 날짜에 대한 데이터가 data배열에 존재하는지 확인
								if (check == 1) printf("+ %d\t", data[z]->t_income);    // 칸 맞추기 위함
								else printf("\t+ %d\t", data[z]->t_income);
								if (data[z]->t_income >= 100000) check = 1;    // 데이터가 6자리를 넘는다면 탭으로 띄우는 칸을 맞추기 위해 표시
								else check = 0;
								chk = 1;    // 해당하는 날짜에 데이터가 있다고 표시
								break;
							}
						}
						if (chk == 0 && check == 1) printf("+ 0\t");    // 해당하는 날짜에 데이터가 없다면 +0
						else if (chk == 0 && check == 0) printf("\t+ 0\t");
						day2++;    // data배열안에 사용자가 입력한 날짜에 맞는 날들이 다 있는지 확인하기 위함
					}
					t = 0;    // 일주일치 다 적었으니 0으로 초기화
					printf("\n");
				}
				day1++;    // data배열안에 사용자가 입력한 날짜에 맞는 날들이 다 있는지 확인하기 위함
			}
			q = 0;    // 일주일치 다 적었으니 0으로 초기화
			printf("\n");
		}
		k++;    // 일주일 확인하기 위함
	}
	printf("\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int j = 0; j < q; j++) printf("\t\t");    // 시작 요일에 맞게 칸 맞추기
	for (int i = 0; i < count; i++) {
		for (int z = 0; data[z] != NULL; z++) {
			chk = 0;
			if (data[z]->date == (year * 100 + month) * 100 + day1) {    // 해당 날짜에 대한 데이터가 data배열에 존재하는지 확인
				if (check == 1) printf("- %d\t", data[z]->t_consume);    // 칸 맞추기 위함
				else printf("\t- %d\t", data[z]->t_consume);
				if (data[z]->t_consume >= 100000) check = 1;    // 데이터가 6자리를 넘는다면 탭으로 띄우는 칸을 맞추기 위해 표시
				else check = 0;
				chk = 1;
				break;
			}
		}
		if (chk == 0 && check == 1) printf("- 0\t");    // 해당하는 날짜에 데이터가 없다면 -0
		else if (chk == 0 && check == 0) printf("\t- 0\t");
		day1++;
	}
	printf("\n");
	for (int j = 0; j < q; j++) printf("\t\t");    // 시작 요일에 맞게 칸 맞추기
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < t; j++) printf("\t\t");    // 시작 요일에 맞게 칸 맞추기
		for (int z = 0; data[z] != NULL; z++) {
			chk = 0;
			if (data[z]->date == (year * 100 + month) * 100 + day2) {    // 해당 날짜에 대한 데이터가 data배열에 존재하는지 확인
				if (check == 1) printf("+ %d\t", data[z]->t_income);    // 칸 맞추기 위함
				else printf("\t+ %d\t", data[z]->t_income);
				if (data[z]->t_income >= 100000) check = 1;    // 데이터가 6자리를 넘는다면 탭으로 띄우는 칸을 맞추기 위해 표시
				else check = 0;
				chk = 1;    // 해당하는 날짜에 데이터가 있다고 표시
				break;
			}
		}
		if (chk == 0 && check == 1) printf("+ 0\t");    // 해당하는 날짜에 데이터가 없다면 +0
		else if (chk == 0 && check == 0) printf("\t+ 0\t");
		day2++;    // data배열안에 사용자가 입력한 날짜에 맞는 날들이 다 있는지 확인하기 위함
	}
	printf("\n\n\n\n");
}

void consumeAnalysis(LEDGERDATA* list, HOUSEHOLDBALANCE* b_list) {
	int year, month;
	// 한달치 합산 퍼센트
	double t_food = 0;    // 식료품
	double t_housing = 0;    // 주거비
	double t_clothes = 0;    // 의류비
	double t_medical = 0;    // 의료비
	double t_transportaion = 0;    // 교통비
	double t_cultural = 0;    // 문화생활비
	double t_communication = 0;    // 통신비
	double t_alco_ciga = 0;    // 주류, 담배
	double t_education = 0;    // 교육비
	double t_housewares = 0;    // 가정용품
	double t_c_etc = 0;    // 기타 소비
	double t_consume = 0;    // 총 소비금
	int t_income = 0;    // 총 소득

	int index[3][2] = { 0, };
	int count = 1;    // 통계청 데이터 백분율로 나타낼 때 소득분위별 평균 구하기 위해 소득분위별 데이터 갯수 확인
	double b_num[11] = { 0, };    // 통계청 데이터 백분율로 나타내기
	double t_num[11] = { 0, };  // 사용자 데이터 백분율로 나타내기
	int b_t_list[12] = { 0, };    // 통계청 한달치 데이터 카테고리별 금액 저장
	int t_list[12] = { 0, };    // 사용자 한달치 데이터 카테고리별 총 금액 저장
	char category[12][11] = { "식료품", "주거비", "의류비", "의료비","교통비", "문화생활비", "통신비", "주류,담배", "교육비", "가정용품", "기타소비" };

	printf("찾고싶은 연도와 달을 입력해주세요 [ex)2022 6]: ");
	scanf("%d %d", &year, &month);

	while (1) {    // 입력한 연도와 달이 나올때까지 반복
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
		if (i % 10 == 0) printf("%3d ┃", i);  //3d 자릿수 맞추기 최대 100% 세자리이므로 3d
		else printf("    ┃");
		for (int j = 0; j < 11; j++) {
			printf("        ");
			b_num[j] = (double)b_t_list[j] / (double)b_t_list[11] * 100;
			t_num[j] = (double)t_list[j] / (double)t_list[11] * 100;
			if ((int)t_num[j] >= i - 2) {  //값을 10으로 나눈 값이 i보다 크거나 같을때
				if ((int)t_num[j] + 1 == i || (int)t_num[j] + 2 == i || (int)t_num[j] - 1 == i || (int)t_num[j] - 2 == i || (int)t_num[j] == i) printf("┏┓");  //같으면 시작을 표시하는 ┌┐ 기호 출력
				else printf("┃┃");  //0점을 만나기 전까지 ││ 기호 출력
			}
			else printf("  ");
			if ((int)b_num[j] >= i - 2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				if ((int)b_num[j] + 1 == i || (int)b_num[j] + 2 == i || (int)b_num[j] - 1 == i || (int)b_num[j] - 2 == i || (int)b_num[j] == i) printf(" ┏┓");
				else printf(" ┃┃");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else printf("   ");
		}
		printf("\n");
	}

	printf("%3d ┗━", 0);  //0점 표시
	for (int i = 0; i < 11; i++) {
		printf("━━━━━━━");
		if (t_list != 0 && t_list[i] > 7) {  //0점이 아닌 점수가 입력된 부분에만 ─┴┴─ 기호로 출력
			printf("┛┗ ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("┛┗");
			printf("━");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (t_list[i] != 0 && t_list[i] < 8) {
			printf("┏┓ ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("┛┗");
			printf("━");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (t_list[i] == 0) {
			printf("━━ ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("┛┗");
			printf("━");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}
	printf("\n");
	printf("      ");
	printf("       식료품       주거비       의류비       의료비       교통비     문화생활비     통신비     주류,담배      교육비      가정용품     기타소비");
	printf("\n");
	printf("==>     ");
	for (int i = 0; i < 11; i++) {
		if (t_list[i] >= 100000) printf("    %d원  ", t_list[i]);
		else if (10000 <= t_list[i] && t_list[i] < 100000) printf("    %d원 ", t_list[i]);
		else if (1000 <= t_list[i] && t_list < 10000) printf("      %d원 ", t_list[i]);
		else if (100 <= t_list[i] && t_list < 1000) printf("       %d원 ", t_list[i]);
		else if (10 <= t_list[i] && t_list < 100) printf("        %d원 ", t_list[i]);
		else printf("       %d원  ", t_list[i]);
	}
	printf("\n\n\n");

	for (int i = 0; i < 3; i++) {    // 가장 큰 3개의 값을 찾기 위함
		for (int j = 0; j < 11; j++) {
			if (index[i][1] < t_list[j]) {
				if (i == 0) count = 1;    // 처음엔 중복 확인을 하지 않아도 되기에 카운트를 1로 바꿔준다
				for (int k = 0; k < i; k++) {    // 현재의 값이 index 배열에 이미 들어있는지 확인
					if (index[k][1] == t_list[j]) {    // 이미 index배열에 들어있다면
						count = 0;    // count를 0으로 설정해서 이미 있다고 표시
						break;
					}
					else count = 1;    // index 배열에 해당 값이 없기에 count를 1로 설정해서 없다고 표시
				}
				if (count == 1) {    // index배열에 해당 값이 없다면 해당 값의 index와 값을 저장
					index[i][0] = j;
					index[i][1] = t_list[j];
				}
			}
		}
	}

	printf("지출 카테고리 TOP3\n");
	for (int i = 0; i < 3; i++) {
		if (t_num[index[i][0]] - b_num[index[i][0]] > 20) {
			printf("%d위 %s %d\t동일 소득자 평균에 비해 %.1lf%% 더 많이 쓰고 있어요. 꼭 써야해서 쓴거죠? 그래도 줄여요 ^^\n\n", i + 1, category[index[i][0]], index[i][1], t_num[index[i][0]] - b_num[index[i][0]]);
		}
		else if (t_num[index[i][0]] - b_num[index[i][0]] > 10) {
			printf("%d위 %s %d\t동일 소득자 평균에 비해 %.1lf%% 더 많이 쓰고 있어요. 이건 조금 줄여야 겠어요\n\n", i + 1, category[index[i][0]], index[i][1], t_num[index[i][0]] - b_num[index[i][0]]);
		}
		else if (t_num[index[i][0]] - b_num[index[i][0]] > 0) {
			printf("%d위 %s %d\t동일 소득자 평균에 비해 %.1lf%% 더 많이 쓰고 있어요. 지금 적당하네요\n\n", i + 1, category[index[i][0]], index[i][1], t_num[index[i][0]] - b_num[index[i][0]]);
		}
		else if (t_num[index[i][0]] - b_num[index[i][0]] < 0) {
			printf("%d위 %s %d\t동일 소득자 평균에 비해 %.1lf%% 적게 쓰고있어요. 좋네요\n\n", i + 1, category[index[i][0]], index[i][1], t_num[index[i][0]] - b_num[index[i][0]]);
		}
	}
	return 0;
}

void start() {
	printf("\n\n\n\n\t\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t\t┃                                                                                                                                       ┃\n");
	printf("\t\t\t┃                                                                                                                                       ┃\n");
	printf("\t\t\t┃                                                                                                                                       ┃\n");
	printf("\t\t\t┃                                                                           ┃                                                           ┃\n");
	printf("\t\t\t┃                                          ┃                              ┃ ┃                                                           ┃\n");
	printf("\t\t\t┃                         ━━━━━━━━━━━━┓    ┃          ━━━━━━━━━━━━┓       ┃ ┃          ┃                ┃                               ┃\n");
	printf("\t\t\t┃                                     ┃    ┃                      ┃       ┃ ┃          ┃                ┃                               ┃\n");
	printf("\t\t\t┃                                     ┃    ┃                      ┃ ━━━━━━┫ ┃          ┣━━━━━━━━━━━━━━━━┫                               ┃\n");
	printf("\t\t\t┃                                     ┃    ┃                      ┃       ┃ ┃          ┃                ┃                               ┃\n");
	printf("\t\t\t┃                                     ┃    ┣━━━━━━                ┃ ━━━━━━┫ ┃          ┗━━━━━━━━━━━━━━━━┛                               ┃\n");
	printf("\t\t\t┃                                     ┃    ┃                      ┃       ┃ ┃                                                           ┃\n");
	printf("\t\t\t┃                                     ┃    ┃                      ┃       ┃ ┃     ━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━                         ┃\n");
	printf("\t\t\t┃                                          ┃                              ┃ ┃                  ┃                                        ┃\n");
	printf("\t\t\t┃                                          ┃                              ┃ ┃                  ┃                                        ┃\n");
	printf("\t\t\t┃                                          ┃                              ┃ ┃                  ┃                                        ┃\n");
	printf("\t\t\t┃                                                                           ┃                  ┃                                        ┃\n");
	printf("\t\t\t┃                                                                                                                                       ┃\n");
	printf("\t\t\t┃                                                                                                                                       ┃\n");
	printf("\t\t\t┃                                                                                                                                       ┃\n");
	printf("\t\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

void menu1() {
	printf("\n┌───────────── 메뉴────────────────┐\n");
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
	printf("│ 1. 내역 추가 & 수정              │\n");
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
	printf("│                                   │\n");
	printf("│ 1. 새로운 플랜                    │\n");
	printf("│                                   │\n");
	printf("│ 2. 플랜 불러오기                  │\n");
	printf("│                                   │\n");
	printf("│ 3. 뒤로가기                       │\n");
	printf("│                                   │\n");
	printf("└───────────────────────────────────┘\n");
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