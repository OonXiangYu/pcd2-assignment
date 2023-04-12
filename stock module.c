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
void displayStock();

int validDate(int day, int month, int year);
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

	if (day < 1 || day > 31) {
		return 0;
	}

	if (month < 1 || month > 12) {
		return 0;
	}

	if (year < 1900 || year > 9999) {
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

void title() {
	printf("\n%10s  %20s  %10s  %10s  %10s  %10s  %10s\n", "STOCK CODE", "STOCK NAME", "QUANTITY", "MINIMUM", "REORDER", "PRICE", "DATE");
	printf("%10s  %20s  %10s  %10s  %10s  %10s  %10s\n", "==========", "====================", "==========", "==========", "==========", "==========", "==========");
}

void addStock() {
	FILE* fptr = fopen(FILE_NAME, "ab");

	Stock s;

	char continueAdd, sure;

	do {
		printf("\nPlease enter stock code :");
		rewind(stdin);
		gets(s.stockCode);
		printf("Please enter stock name :");
		rewind(stdin);
		gets(s.stockName);
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
			printf("Please enter the date added record(dd/mm/yyyy) :");
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

	do {
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
		else if (select == 3) {
			return;
		}
		else {
			printf("\nInvalid answer\n");
		}
	} while (select != 1 || select != 2 || select != 3);

	fclose(fptr);
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
		printf("%10s  %20s  %10d  %10d  %10d  %10.2lf  %02d/%02d/%04d\n", s.stockCode, s.stockName, s.stockQuantity, s.stockMinimum, s.stockReorder, s.stockPrice, s.d.day, s.d.month, s.d.year);
	}

	fclose(fptr);
}