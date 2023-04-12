#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#pragma warning(disable:4996)
#define FILE_NAME "stock.dat"

struct Date {
	int day, month, year;
};

typedef struct {
	char stockCode[6], stockName[20];
	int stockQuantity, stockMinimum, stockReorder;
	double stockPrice;
	struct Date d;
}Stock;

void addStock();
void searchStock();
void modifyStock();
void displayStock();

//subs function
int validDate(int day,int month,int year);
int validRepeat(char name[20]);
void title();

void main() {
	int select;

	do {
		printf("\n1. Add Record\n");
		printf("2. Search Record\n");
		printf("3. Modify Record\n");
		printf("4. Display Record\n");
		printf("7. Exit\n");
		printf("Please enter your option :");
		rewind(stdin);
		scanf("%d", &select);
		if (select == 1 || select == 2 || select == 3 || select == 4) {
			switch (select) {
			case 1:
				addStock();
				break;
			case 2:
				searchStock();
				break;
			case 3:
				modifyStock();
				break;
			case 4:
				displayStock();
				break;
			}
		}
		else if (select == 7) {
			printf("\nThank you so much\n\n");
			system("pause");
		}
		else {
			printf("\nInvalid answer\n\n");
		}
	} while (select != 7);
}

int validDate(int day, int month, int year) {

	if ((day < 1 || day > 31) || (month < 1 || month > 12) || (year < 1900 || year > 9999)) {
		return 0;
	}

	if (month == 2) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			if (day > 29) {
				return 0;
			}
		}
		else {
			if (day > 28) {
				return 0;
			}
		}
	}

	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30) {
			return 0;
		}
	}

	return 1;
}

int validRepeat(char name[20]) {
	FILE* fptr = fopen(FILE_NAME, "rb");
	Stock s;

	if (fptr == NULL) {
		exit(-1);
	}

	while (fread(&s, sizeof(s), 1, fptr)) {
		if (strcmp(name, s.stockName) == 0 || strcmp(name, s.stockCode) == 0) {
			return 1;
		}
	}
	fclose(fptr);

	return 2;
}

void title() {

	printf("\n%10s  %20s  %10s  %10s  %10s  %10s  %10s\n", "STOCK CODE", "STOCK NAME", "QUANTITY", "MINIMUM", "REORDER", "PRICE", "DATE");
	printf("%10s  %20s  %10s  %10s  %10s  %10s  %10s\n", "==========", "====================", "==========", "==========", "==========", "==========", "==========");

};

void addStock() {
	FILE* fptr = fopen(FILE_NAME, "ab");

	Stock s;

	char continueAdd, sure;

	do {
		do {
			printf("\nPlease enter stock code :");
			rewind(stdin);
			gets(s.stockCode);
			if (validRepeat(s.stockCode) == 1) {
				printf("\nStock Code is exist\n");
			}
			else if (validRepeat(s.stockCode) == 2) {
				printf("\nStock Code valid\n");
			}
		} while (validRepeat(s.stockCode) == 1);

		do {
			printf("Please enter stock name :");
			rewind(stdin);
			gets(s.stockName);
			if (validRepeat(s.stockName) == 1) {
				printf("\nStock Name is exist\n");
			}
			else if (validRepeat(s.stockName) == 2) {
				printf("\nStock Name valid\n");
			}
		} while (validRepeat(s.stockName) == 1);

		printf("Please enter stock quantity order :");
		rewind(stdin);
		scanf("%d", &s.stockQuantity);
		printf("Please enter stock quantity minimum level to reorder :");
		rewind(stdin);
		scanf("%d", &s.stockMinimum);
		printf("Please enter reorder stock quantity :");
		rewind(stdin);
		scanf("%d", &s.stockReorder);
		printf("Please enter stock price :");
		rewind(stdin);
		scanf("%lf", &s.stockPrice);

		do {
			printf("Please enter the date added or update record(dd/mm/yyyy) :");
			rewind(stdin);
			scanf("%d/%d/%d", &s.d.day, &s.d.month, &s.d.year);
			if (validDate(s.d.day, s.d.month, s.d.year) == 1) {
				printf("\nValid date\n");
			}
			else {
				printf("\nInvalid date\n");
			}
		} while (validDate(s.d.day, s.d.month, s.d.year) != 1);

		do {
		printf("Do you sure your record added into file (y/n):");
		rewind(stdin);
		sure = tolower(getchar());

			if (sure == 'y') {
				fwrite(&s, sizeof(s), 1, fptr);
				printf("record added\n");
			}
			else if (sure == 'n') {
				printf("\nrecord not added\n");
			}
			else {
				printf("\nInvalid answer\n");
			}
		} while (sure != 'y' && sure != 'n');

		do {
			printf("Do you want to continue add record (y/n):");
			rewind(stdin);
			continueAdd = tolower(getchar());
			if (continueAdd != 'y' && continueAdd != 'n') {
				printf("\nInvalid answer\n");
			}
		} while (continueAdd != 'y' && continueAdd != 'n');

	} while (continueAdd == 'y');

	fclose(fptr);
}

void searchStock() {
	FILE* fptr = fopen(FILE_NAME, "rb");

	if (fptr == NULL) {
		printf("\nInvalid file\n");
		return;
	}

	Stock s;
	int select, day, month, year, count = 0;
	char code[6];

	do{
	printf("\n1. Search by Stock ID\n");
	printf("2. Search by Date\n");
	printf("3. Exit\n");

		printf("\nPlease enter your Option :");
		rewind(stdin);
		scanf("%d", &select);
		if (select == 1) {

			printf("\nPlease enter stock ID :");
			rewind(stdin);
			gets(code);

			title();

			while (fread(&s, sizeof(s), 1, fptr)) {
				if (strcmp(code, s.stockCode) == 0) {
					printf("%10s  %20s  %10d  %10d  %10d  %10.2lf  %02d/%02d/%04d\n", s.stockCode, s.stockName, s.stockQuantity, s.stockMinimum, s.stockReorder, s.stockPrice, s.d.day, s.d.month, s.d.year);
					count++;
				}
			}

			if (count == 0) {
				printf("\nNo record\n");
			}

		}
		else if (select == 2) {
			do {
				printf("\nPlease enter the date added record(dd/mm/yyyy) :");
				rewind(stdin);
				scanf("%d/%d/%d", &day, &month, &year);
				if (validDate(day, month, year) == 1) {
					printf("\nValid date\n");
				}
				else {
					printf("\nInvalid date\n");
				}
			} while (validDate(day, month, year) != 1);

			title();

			while (fread(&s, sizeof(s), 1, fptr)) {
				if (day == s.d.day && month == s.d.month && year == s.d.year) {
					printf("%10s  %20s  %10d  %10d  %10d  %10.2lf  %02d/%02d/%04d\n", s.stockCode, s.stockName, s.stockQuantity, s.stockMinimum, s.stockReorder, s.stockPrice, s.d.day, s.d.month, s.d.year);
					count++;
				}
			}

			if (count == 0) {
				printf("\nNo record\n");
			}
		}
		else if (select == 3){
			return;
		}
		else {
			printf("\nInvalid answer\n");
		}
	} while (select != 1 || select != 2 || select != 3);

	fclose(fptr);
}

void modifyStock() {

	Stock s[1000];
	int scount = 0;

	FILE* rptr = fopen(FILE_NAME, "rb");

	if (rptr == NULL) {
		printf("\nInvalid file\n");
		exit(-1);
	}

	while (fread(&s[scount], sizeof(s[scount]), 1, rptr) == 1) {
		scount++;
	}

	fclose(rptr);

	char code[6], nname[20], yesno;
	int day, month, year, min, reorder, option, con = 0;
	float price;

		printf("Please enter the stock code :");
		rewind(stdin);
		gets(code);

		do {
			for (int i = 0; i < scount; i++) {
				if (strcmp(code, s[i].stockCode) == 0) {
					title();
					printf("%10s  %20s  %10d  %10d  %10d  %10.2lf  %02d/%02d/%04d\n", s[i].stockCode, s[i].stockName, s[i].stockQuantity, s[i].stockMinimum, s[i].stockReorder, s[i].stockPrice, s[i].d.day, s[i].d.month, s[i].d.year);
					do {
						printf("\n1. Stock name\n");
						printf("2. Stock minimum quantity\n");
						printf("3. Stock quantity reorder\n");
						printf("4. Stock price\n");
						printf("5. Stock date added record\n");
						printf("6. Exit\n");
						printf("Please select the data you want to modify :");
						rewind(stdin);
						scanf("%d", &option);

						switch (option) {
						case 1:
							do {
								printf("Stock name : %s\n", s[i].stockName);
								printf("Please enter the new name :");
								rewind(stdin);
								gets(nname);
								if (validRepeat(nname) == 1) {
									printf("\nStock Name is exist\n");
								}
								else if (validRepeat(nname) == 2) {
									printf("\nStock Name valid\n");
								}
							} while (validRepeat(nname) == 1);

							do {
								printf("Are you confirm to modify (y/n) ?");
								rewind(stdin);
								yesno = tolower(getchar());

								if (yesno == 'y') {
									strcpy(s[i].stockName, nname);
									printf("\nRecord change\n");
									FILE* wptr = fopen(FILE_NAME, "wb");
									fwrite(&s, sizeof(Stock), scount, wptr);
									fclose(wptr);
								}
								else if (yesno == 'n') {
									printf("\nRecord no changes\n");
								}
								else {
									printf("\nInvalid answer\n");
								}
							} while (yesno != 'y' && yesno != 'n');
							break;

						case 2:
							printf("Stock minimum quantity : %d\n", s[i].stockMinimum);
							printf("Please enter new minimum quantity :");
							rewind(stdin);
							scanf("%d", &min);

							do {
								printf("Are you confirm to modify (y/n) ?");
								rewind(stdin);
								yesno = tolower(getchar());

								if (yesno == 'y') {
									s[i].stockMinimum = min;
									printf("\nRecord change\n");
									FILE* wptr = fopen(FILE_NAME, "wb");
									fwrite(&s, sizeof(Stock), scount, wptr);
									fclose(wptr);
								}
								else if (yesno == 'n') {
									printf("\nRecord no changes\n");
								}
								else {
									printf("\nInvalid answer\n");
								}
							} while (yesno != 'y' && yesno != 'n');
							break;
						case 3:
							printf("Stock reorder quantity : %d\n", s[i].stockReorder);
							printf("Please enter new reorder quantity :");
							rewind(stdin);
							scanf("%d", &reorder);
							do {
								printf("Are you confirm to modify (y/n) ?");
								rewind(stdin);
								yesno = tolower(getchar());

								if (yesno == 'y') {
									s[i].stockReorder = reorder;
									printf("\nRecord change\n");
									FILE* wptr = fopen(FILE_NAME, "wb");
									fwrite(&s, sizeof(Stock), scount, wptr);
									fclose(wptr);
								}
								else if (yesno == 'n') {
									printf("\nRecord no changes\n");
								}
								else {
									printf("\nInvalid answer\n");
								}
							} while (yesno != 'y' && yesno != 'n');
							break;
						case 4:
							printf("Stock price : %.2lf\n", s[i].stockPrice);
							printf("Please enter new price :");
							rewind(stdin);
							scanf("%f", &price);
							do {
								printf("Are you confirm to modify (y/n) ?");
								rewind(stdin);
								yesno = tolower(getchar());

								if (yesno == 'y') {
									s[i].stockPrice = price;
									printf("\nRecord change\n");
									FILE* wptr = fopen(FILE_NAME, "wb");
									fwrite(&s, sizeof(Stock), scount, wptr);
									fclose(wptr);
								}
								else if (yesno == 'n') {
									printf("\nRecord no changes\n");
								}
								else {
									printf("\nInvalid answer\n");
								}
							} while (yesno != 'y' && yesno != 'n');
							break;
						case 5:
							do {
								printf("Lastest record updated date : %02d/%02d/%04d\n", s[i].d.day, s[i].d.month, s[i].d.year);
								printf("Please enter lastest date modify reocrd :");
								rewind(stdin);
								scanf("%d/%d/%d", &day, &month, &year);
								if (validDate(day, month, year) == 1) {
									printf("\nValid date\n");
								}
								else {
									printf("\nInvalid date\n");
								}
							} while (validDate(day, month, year) != 1);

							do {
								printf("Are you confirm to modify (y/n) ?");
								rewind(stdin);
								yesno = tolower(getchar());

								if (yesno == 'y') {
									s[i].d.day = day;
									s[i].d.month = month;
									s[i].d.year = year;
									printf("\nRecord change\n");
									FILE* wptr = fopen(FILE_NAME, "wb");
									fwrite(&s, sizeof(Stock), scount, wptr);
									fclose(wptr);
								}
								else if (yesno == 'n') {
									printf("\nRecord no changes\n");
								}
								else {
									printf("\nInvalid answer\n");
								}
							} while (yesno != 'y' && yesno != 'n');
							break;
						case 6:
							return;
							break;
						}
					} while (option != 6);
				}
				else {
					con++;
				}
			}
		} while (con != 0);
}

void displayStock() {
	FILE* fptr = fopen(FILE_NAME, "rb");

	if (fptr == NULL) {
		printf("Invalid file\n");
		return;
	}

	Stock s;

	title();

	while (fread(&s, sizeof(s), 1, fptr)) {
		printf("%10s  %20s  %10d  %10d  %10d  %10.2lf  %02d/%02d/%04d\n", s.stockCode,s.stockName, s.stockQuantity, s.stockMinimum, s.stockReorder, s.stockPrice, s.d.day,s.d.month,s.d.year);
	}

	fclose(fptr);
}