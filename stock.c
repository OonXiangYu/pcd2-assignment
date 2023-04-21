#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#pragma warning(disable:4996)
#define FILE_NAME "stock.dat"

struct Date {
	int day, month, year;
};

typedef struct {
	char stockCode[6], stockName[21];
	int stockQuantity, stockMinimum, stockReorder;
	double stockPrice;
	struct Date d;
}Stock;

void addStock();
void searchStock(Stock s[],int);
void modifyStock();
void displayStock(Stock s[], int);

//subs function
int validDate(int day,int month,int year);
int validRepeat(char name[21]);
int validNumber(int);
int validFormat(char);
int validLength(char);

//
void getSize(Stock s[], int*);
void title();

//
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

int validRepeat(char name[21]) {
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

int validNumber(int num) {
	if (num <= 0) {
		return 2;
	}
	
	return 3;
}

int validFormat(char code[6]) {
	if (isalpha(code[0]) && isdigit(code[1]) && isdigit(code[2]) && isdigit(code[3]) && isdigit(code[4]) && (strlen(code) == 5) ) {
		return 1;
	}

	return 2;
}

int validLength(char name[21]) {
	if (strlen(name) > 20) {
		return 1;
	}

	return 2;
}

void title() {
	printf("\n%10s  %20s  %10s  %10s  %10s  %10s  %10s\n", "STOCK CODE", "STOCK NAME", "QUANTITY", "MINIMUM", "REORDER", "PRICE", "DATE");
	printf("%10s  %20s  %10s  %10s  %10s  %10s  %10s\n", "==========", "====================", "==========", "==========", "==========", "==========", "==========");
};

//

void getSize(Stock s[], int* size) {
	FILE* fptr = fopen(FILE_NAME, "rb");

	if (fptr == NULL) {
		printf("\nInvalid file\n");
		exit(-1);
	}

	int i = 0;

	while (fread(&s[i], sizeof(s[i]), 1, fptr)) {
		i++;
		*size = i;
	}

	fclose(fptr);
}

void displayStock(Stock s[], int a) {
		printf("%10s  %20s  %10d  %10d  %10d  %10.2lf  %02d/%02d/%04d\n", s[a].stockCode, s[a].stockName, s[a].stockQuantity, s[a].stockMinimum, s[a].stockReorder, s[a].stockPrice, s[a].d.day, s[a].d.month, s[a].d.year);
}

//
void main() {
	int select;

	do {
		Stock s[1000];
		int size;
		getSize(s, &size);

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
				searchStock(s, size);
				break;
			case 3:
				modifyStock();
				break;
			case 4:
				title();
				for (int i = 0; i < size; i++) {
					displayStock(s, i);
				}
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

void addStock() {
	FILE* fptr = fopen(FILE_NAME, "ab");
	Stock s;
	char continueAdd, sure, code[6], yesno;
	double price;
	
	do {
		do {
			printf("\nPlease enter stock code (A0001):");
			rewind(stdin);
			gets(code);
			strcpy(s.stockCode ,toupper(code));
			if (validFormat(s.stockCode) == 1) {
				if (validRepeat(s.stockCode) == 1) {
					printf("\nStock Code is exist\n");
				}
				else if (validRepeat(s.stockCode) == 2) {
					printf("\nStock Code valid\n");
				}
			}
			else if (validFormat(s.stockCode) == 2) {
				printf("\nInvalid format\n");
			}
		} while (validRepeat(s.stockCode) == 1 || validFormat(s.stockCode) == 2);

		do {
			printf("Please enter stock name :");
			rewind(stdin);
			gets(s.stockName);
			if (validLength(s.stockName) == 2) {
				if (validRepeat(s.stockName) == 1) {
					printf("\nStock Name is exist\n");
				}
				else if (validRepeat(s.stockName) == 2) {
					printf("\nStock Name valid\n");
				}
			}
			else if (validLength(s.stockName) == 1) {
				printf("\nOnly 20 spaces are allow\n");
			}
		} while (validRepeat(s.stockName) == 1 || validLength(s.stockName) == 1);

		do {
			printf("Please enter stock quantity order :");
			rewind(stdin);
			if (scanf("%d", &s.stockQuantity) != 1) {
				printf("\nAlphabet and Symbol are not allow\n");
			}
			else if (validNumber(s.stockQuantity) == 2) {
				printf("\nQuantity must greater than 0\n");
			}
			else if (validNumber(s.stockQuantity) == 3) {
				printf("\nValid answer\n");
			}
		} while (validNumber(s.stockQuantity) != 3);

		do {
			printf("Please enter stock quantity minimum level to reorder :");
			rewind(stdin);
			if (scanf("%d", &s.stockMinimum) != 1) {
				printf("\nAlphabet and Symbol are not allow\n");
			}
			else if (validNumber(s.stockMinimum) == 2) {
				printf("\nQuantity must greater than 0\n");
			}
			else if (validNumber(s.stockMinimum) == 3) {
				printf("\nValid answer\n");
			}
		} while (validNumber(s.stockMinimum) != 3);

		do {
			printf("Please enter reorder stock quantity :");
			rewind(stdin);
			if (scanf("%d", &s.stockReorder) != 1) {
				printf("\nAlphabet and Symbol are not allow\n");
			}
			else if (validNumber(s.stockReorder) == 2) {
				printf("\nQuantity must greater than 0\n");
			}
			else if (validNumber(s.stockReorder) == 3) {
				printf("\nValid answer\n");
			}
		} while (validNumber(s.stockReorder) != 3);

		do {
			printf("Please enter stock price :");
			rewind(stdin);
			scanf("%lf",&price);
			printf("Price = %.2lf\n", price);
			printf("Are you sure? (y/n) >");
			rewind(stdin);
			yesno = tolower(getchar());
			if (yesno == 'y') {
				if (price <= 0) {
					printf("\nPrice must greater than 0\n");
				}
				else {
					printf("\nPrice is added\n");
				}
			}
			else if (yesno == 'n') {
				printf("\nPrice not added\n");
			}
			else {
				printf("\nOnly y and n is accepted\n");
			}
		} while (yesno != 'y');

		do {
			printf("Please enter the date added or update record(dd/mm/yyyy) :");
			rewind(stdin);
			scanf("%d/%d/%d", &s.d.day, &s.d.month, &s.d.year);
			if (validDate(s.d.day,s.d.month, s.d.year) == 1) {
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

void searchStock(Stock s[], int size) {
	FILE* fptr = fopen(FILE_NAME, "rb");

	if (fptr == NULL) {
		printf("\nInvalid file\n");
		return;
	}

	int select, day, month, year, count = 0;
	char code[6], yesno;
	double lprice, hprice, price;

	do {
		printf("\n1. Search by Stock ID\n");
		printf("2. Search by Date\n");
		printf("3. Search by Price\n");
		printf("4. Exit\n");

		printf("\nPlease enter your Option :");
		rewind(stdin);
		scanf("%d", &select);
		if (select == 1) {

			do {
				printf("\nPlease enter stock ID :");
				rewind(stdin);
				gets(code);
				if (validFormat(code) == 1) {
					printf("\nValid code\n");
				}
				else if (validFormat(code) == 2) {
					printf("\nInvalid format\n");
				}
			} while (validFormat(code) == 2);

			title();

			for (int i = 0; i < size; i++) {
				if (strcmp(code, s[i].stockCode) == 0) {
					displayStock(s, i);
					count++;
				}
			}
			if (count = 0) {
				printf("\nNo record\n");
			}
		}
		else if (select == 2) {
			do {
				printf("\nPlease enter the date added record(dd/mm/yyyy) :");
				rewind(stdin);
				if (scanf("%d/%d/%d", &day, &month, &year) == 1) {
					if (validDate(day, month, year) == 1) {
						printf("\nValid date\n");
					}
					else {
						printf("\nInvalid date\n");
					}
				}
				else {
					printf("\nInvalid format\n");
				}
			} while (validDate(day, month, year) != 1);

			title();

			for (int i = 0; i < size; i++) {
				if (day == s[i].d.day && month == s[i].d.month && year == s[i].d.year) {
					displayStock(s, i);
					count++;
				}
			}
			if (count = 0) {
				printf("\nNo record\n");
			}
		}
		else if (select == 3) {
			printf("Please enter the price range\n");

			do {
				printf("min >");
				rewind(stdin);
				scanf("%lf", &price);
				printf("Price = %.2lf\n", price);
				printf("Are you sure? (y/n) >");
				rewind(stdin);
				yesno = tolower(getchar());
				if (yesno == 'y') {
					lprice = price;
					printf("\nPrice is added\n");
				}
				else if (yesno == 'n') {
					printf("\nPrice not added\n");
					price = 0;
				}
				else {
					printf("\nOnly y and n is accepted\n");
					price = 0;
				}
			} while (yesno != 'y');

			do {
				printf("max >");
				rewind(stdin);
				scanf("%lf", &price);
				printf("Price = %.2lf\n", price);
				printf("Are you sure? (y/n) >");
				rewind(stdin);
				yesno = tolower(getchar());
				if (yesno == 'y') {
					hprice = price;
					printf("\nPrice is added\n");
				}
				else if (yesno == 'n') {
					printf("\nPrice not added\n");
					price = 0;
				}
				else {
					printf("\nOnly y and n is accepted\n");
					price = 0;
				}
			} while (yesno != 'y');

			title();
			for (int i = 0; i < size; i++) {
				if (s[i].stockPrice >= lprice && s[i].stockPrice <= hprice) {
					displayStock(s, i);
					count++;
				}
			}

			if (count = 0) {
				printf("\nNo record\n");
			}
		}

		else if (select == 4) {
			return;
		}
		else {
			printf("\nInvalid answer\n");
		}
	} while (select != 1 || select != 2 || select != 3 || select != 4);
	fclose(fptr);
}

void modifyStock() {

					char  nname[20],code[6], yesno;
					int day, month, year, min, reorder, option, size, con = 0, a = 0;
					double price;
					Stock s[1000];
					getSize(s, &size);
					do {
						printf("Please enter the stock code :");
						rewind(stdin);
						gets(code);
						if (validFormat(code) == 1) {
							for (int i = 0; i < size; i++) {
								if (strcmp(code, s[i].stockCode) == 0) {
									do {
										title();
										displayStock(s, i);
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
												printf("Please enter the new name :");
												rewind(stdin);
												gets(nname);
												if (validLength(nname) == 2) {
													if (validRepeat(nname) == 1) {
														printf("\nStock Name is exist\n");
													}
													else if (validRepeat(nname) == 2) {
														printf("\nStock Name valid\n");
													}
												}
												else if (validLength(nname) == 1) {
													printf("\nOnly 20 spaces are allow\n");
												}
											} while (validRepeat(nname) == 1 || validLength(nname) == 1);

											do {
												printf("Are you confirm to modify (y/n) ?");
												rewind(stdin);
												yesno = tolower(getchar());

												if (yesno == 'y') {
													strcpy(s[i].stockName, nname);
													printf("\nRecord change\n");
													FILE* wptr = fopen(FILE_NAME, "wb");
													fwrite(&s, sizeof(Stock), size, wptr);
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
											do {
												printf("Please enter new minimum quantity :");
												rewind(stdin);
												scanf("%d", &min);
												if (validNumber(min) == 1) {
													printf("\nAlphabet is not allow\n");
												}
												else if (validNumber(min) == 2) {
													printf("\nQuantity must greater then 0\n");
												}
												else if (validNumber(min) == 3) {
													printf("\nValid answer\n");
												}
											} while (validNumber(min) != 3);


											do {
												printf("Are you confirm to modify (y/n) ?");
												rewind(stdin);
												yesno = tolower(getchar());

												if (yesno == 'y') {
													s[i].stockMinimum = min;
													printf("\nRecord change\n");
													FILE* wptr = fopen(FILE_NAME, "wb");
													fwrite(&s, sizeof(Stock), size, wptr);
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
											do {
												printf("Please enter new reorder quantity :");
												rewind(stdin);
												scanf("%d", &reorder);
												if (validNumber(reorder) == 1) {
													printf("\nAlphabet is not allow\n");
												}
												else if (validNumber(reorder) == 2) {
													printf("\nQuantity must greater then 0\n");
												}
												else if (validNumber(reorder) == 3) {
													printf("\nValid answer\n");
												}
											} while (validNumber(reorder) != 3);

											do {
												printf("Are you confirm to modify (y/n) ?");
												rewind(stdin);
												yesno = tolower(getchar());

												if (yesno == 'y') {
													s[i].stockReorder = reorder;
													printf("\nRecord change\n");
													FILE* wptr = fopen(FILE_NAME, "wb");
													fwrite(&s, sizeof(Stock), size, wptr);
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
											do {
												printf("Please enter new stock price :");
												rewind(stdin);
												scanf("%lf", &price);
												printf("Price = %.2lf\n", price);
												printf("Are you sure? (y/n) >");
												rewind(stdin);
												yesno = tolower(getchar());
												if (yesno == 'y') {
													if (price <= 0) {
														printf("\nPrice must be greater than 0\n");
													}
													else {
														printf("\nPrice is added\n");
													}
												}
												else if (yesno == 'n') {
													printf("\nPrice not added\n");
													price = 0;
												}
												else {
													printf("\nOnly y and n is accepted\n");
													price = 0;
												}
											} while (yesno != 'y');

											do {
												printf("Are you confirm to modify (y/n) ?");
												rewind(stdin);
												yesno = tolower(getchar());

												if (yesno == 'y') {
													s[i].stockPrice = price;
													printf("\nRecord change\n");
													FILE* wptr = fopen(FILE_NAME, "wb");
													fwrite(&s, sizeof(Stock), size, wptr);
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
													fwrite(&s, sizeof(Stock), size, wptr);
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
							if (con != 0) {
								printf("\nCode not exist\n");
							}
						}
						else {
						printf("\nInvalid format\n");
						}
					}while (con!=0);
}
