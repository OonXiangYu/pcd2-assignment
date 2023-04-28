#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include <time.h>
#include <windows.h>
#pragma warning(disable:4996)
#define FILE_NAME "stock.dat"

struct Date { //tagged struct
	int day, month, year;
};

typedef struct { //data fields
	char stockCode[6], stockName[21], status[15];
	int stockQuantity, stockMinimum, stockReorder;
	double stockPrice;
	struct Date d;
}Stock;

//main function
void addStock();
void searchStock(Stock s[],int);
void modifyStock();
void displayStock(Stock s[], int);
void updateStock();
void reportStock(Stock s[], int);

//validation function
int validDate(int day,int month,int year);
int validRepeat(char name[21]);
int validNumber(int);
int validFormat(char);
int validLength(char);

//subs function
void getSize(Stock s[], int*);
void title();

//validation functions
int validDate(int day, int month, int year) {

	if ((day < 1 || day > 31) || (month < 1 || month > 12) || (year < 1900 || year > 9999)) { //valid the range of date
		return 0;
	}

	if (month == 2) {  //check for the leap year
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

	if (month == 4 || month == 6 || month == 9 || month == 11) { //check the month which only have 30days
		if (day > 30) {
			return 0;
		}
	}

	return 1;
}

int validRepeat(char name[21]) { //check is there any name or code is repeated
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

int validNumber(int num) { //check the numbermust be greater than 0
	if (num <= 0) {
		return 2;
	}
	
	return 3;
}

int validFormat(char code[6]) { //check the format of code
	if (isalpha(code[0]) && isdigit(code[1]) && isdigit(code[2]) && isdigit(code[3]) && isdigit(code[4]) && (strlen(code) == 5) ) {
		return 1;
	}

	return 2;
}

int validLength(char name[21]) { //check the length of name
	if (strlen(name) > 20) {
		return 1;
	}

	return 2;
}

void title() { //display title
	printf("\n%10s  %20s  %10s  %10s  %10s  %10s  %10s  %15s\n", "STOCK CODE", "STOCK NAME", "QUANTITY", "MINIMUM", "REORDER", "PRICE", "DATE","STATUS");
	printf("%10s  %20s  %10s  %10s  %10s  %10s  %10s  %15s\n", "==========", "====================", "==========", "==========", "==========", "==========", "==========","===============");
};

//

void getSize(Stock s[], int* size) { //get the counts of record
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

void displayStock(Stock s[], int a) { //display record
		printf("%10s  %20s  %10d  %10d  %10d  %10.2lf  %02d/%02d/%04d  %15s\n", s[a].stockCode, s[a].stockName, s[a].stockQuantity, s[a].stockMinimum, s[a].stockReorder, s[a].stockPrice, s[a].d.day, s[a].d.month, s[a].d.year,s[a].status);
}

//
void main() {
	int select;

	do {
		Stock s[1000];
		int size;
		getSize(s, &size);

		//logo
		printf("\n\n");
		printf("  %5s  %5s  %5s  %5s  %s%3s%s\n", "=====", "=====", "=====", "=====", "=", "", "=");
		printf("  %s%4s  %2s%s%2s  %s%3s%s  %s%4s  %s%2s%s\n", "=", "", "", "=", "", "=", "", "=", "=", "", "=", "", "=");
		printf("  %5s  %2s%s%2s  %s%3s%s  %s%4s  %s%s%s\n", "=====", "", "=", "", "=", "", "=", "=", "", "=", "", "=");
		printf("  %4s%s  %2s%s%2s  %s%3s%s  %s%4s  %s%2s%s\n", "", "=", "", "=", "", "=", "", "=", "=", "", "=", "", "=");
		printf("  %5s  %2s%s%2s  %5s  %5s  %s%3s%s\n", "=====", "","=","", "=====", "=====", "=", "", "=");

		printf("\n1. Add Record\n");
		printf("2. Search Record\n");
		printf("3. Modify Record\n");
		printf("4. Display Record\n");
		printf("5. Update Status\n");
		printf("6. Report\n");
		printf("7. Exit\n");
		printf("Please enter your option :");
		rewind(stdin);
		scanf("%d", &select);
		if (select == 1 || select == 2 || select == 3 || select == 4 || select == 5 || select == 6) { 
			switch (select) { //go to subs function that user select
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
				//logo
				printf("\n%38s%30s\n", "", "==============================");
				printf("%38s%-2s%10s%6s%9s%2s\n", "", "||", "", "DISPLAY", "", "||");
				printf("%38s%30s\n", "", "==============================");
				title();
				for (int i = 0; i < size; i++) {
					displayStock(s, i);
				}
				break;
			case 5:
				updateStock();
				break;
			case 6:
				reportStock(s, size);
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
	} while (select != 7); //loop 
}

void addStock() {
	FILE* fptr = fopen(FILE_NAME, "ab");
	Stock s;
	char continueAdd, sure, code[6], yesno;
	double price;

	//logo
	printf("\n%20s%30s\n", "", "==============================");
	printf("%20s%-2s%12s%3s%11s%2s\n", "", "||", "", "ADD", "", "||");
	printf("%20s%30s\n", "", "==============================");

	do {
		do {
			printf("\nPlease enter stock code (A0001):");
			rewind(stdin);
			gets(s.stockCode);
			if (validFormat(s.stockCode) == 1) { //validation
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
		} while (validRepeat(s.stockCode) == 1 || validFormat(s.stockCode) == 2); //loop when code didnt pass the validation

		do {
			printf("Please enter stock name :");
			rewind(stdin);
			gets(s.stockName);
			if (validLength(s.stockName) == 2) { //validation
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
		} while (validRepeat(s.stockName) == 1 || validLength(s.stockName) == 1);  //loop when name didnt pass the validation

		do {
			printf("Please enter stock quantity order :");
			rewind(stdin);
			if (scanf("%d", &s.stockQuantity) != 1) { //validation
				printf("\nAlphabet and Symbol are not allow\n");
			}
			else if (validNumber(s.stockQuantity) == 2) {
				printf("\nQuantity must greater than 0\n");
			}
			else if (validNumber(s.stockQuantity) == 3) {
				printf("\nValid answer\n");
			}
		} while (validNumber(s.stockQuantity) != 3);  //loop when stockQuantity didnt pass the validation

		do {
			printf("Please enter stock quantity minimum level to reorder :");
			rewind(stdin);
			if (scanf("%d", &s.stockMinimum) != 1) { //validation
				printf("\nAlphabet and Symbol are not allow\n");
			}
			else if (validNumber(s.stockMinimum) == 2) {
				printf("\nQuantity must greater than 0\n");
			}
			else if (validNumber(s.stockMinimum) == 3) {
				printf("\nValid answer\n");
			}
		} while (validNumber(s.stockMinimum) != 3); //loop when sotckMinimum didnt pass the validation

		do {
			printf("Please enter reorder stock quantity :");
			rewind(stdin);
			if (scanf("%d", &s.stockReorder) != 1) { //validation
				printf("\nAlphabet and Symbol are not allow\n");
			}
			else if (validNumber(s.stockReorder) == 2) {
				printf("\nQuantity must greater than 0\n");
			}
			else if (validNumber(s.stockReorder) == 3) {
				printf("\nValid answer\n");
			}
		} while (validNumber(s.stockReorder) != 3); //loop when stockReorder didnt pass the validation

		do {
			printf("Please enter stock price :");
			rewind(stdin);
			scanf("%lf",&price);
			printf("Price = %.2lf\n", price); //filter out the alphabet
			printf("Are you sure? (y/n) >");
			rewind(stdin);
			yesno = tolower(getchar());
			if (yesno == 'y') { 
				if (price <= 0) { //validation
					printf("\nPrice must greater than 0\n");
				}
				else {
					s.stockPrice = price;
					printf("\nPrice is added\n");
				}
			}
			else if (yesno == 'n') {
				printf("\nPrice not added\n");
			}
			else {
				printf("\nOnly y and n is accepted\n");
			}
		} while (yesno != 'y' || price <= 0); //loop when system didnt get the accepted price

		do {
			printf("Please enter the date added or update record(dd/mm/yyyy) :");
			rewind(stdin);
			scanf("%d/%d/%d", &s.d.day, &s.d.month, &s.d.year);
			if (validDate(s.d.day,s.d.month, s.d.year) == 1) { //validation
				printf("\nValid date\n");
			}
			else {
				printf("\nInvalid date\n");
			}
		} while (validDate(s.d.day, s.d.month, s.d.year) != 1); //loop when date didnt pass the validation

		strcpy(s.status, "-");

		do {
		printf("Do you sure your record added into file (y/n):");
		rewind(stdin);
		sure = tolower(getchar());

			if (sure == 'y') {
				fwrite(&s, sizeof(s), 1, fptr); //add record to binary file
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
			printf("Do you want to continue add record (y/n):"); // ask user to continue add
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

	//logo
	printf("\n%20s%30s\n", "", "==============================");
	printf("%20s%-2s%10s%6s%10s%2s\n", "", "||", "", "SEARCH", "", "||");
	printf("%20s%30s\n", "", "==============================");

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
				if (validFormat(code) == 1) { //validation
					printf("\nValid code\n");
				}
				else if (validFormat(code) == 2) {
					printf("\nInvalid format\n");
				}
			} while (validFormat(code) == 2); //loop when code format incorrect

			title();

			for (int i = 0; i < size; i++) { //check whether the code same wif the code inside binary file,then display
				if (strcmp(code, s[i].stockCode) == 0) {
					displayStock(s, i);
					count++;
				}
			}
			if (count == 0) { //show when there is no code
				printf("\nNo record\n");
			}
		}
		else if (select == 2) {
			do {
				printf("\nPlease enter the date added record(dd/mm/yyyy) :");
				rewind(stdin);
				if (scanf("%d/%d/%d", &day, &month, &year) == 1) {
					if (validDate(day, month, year) == 1) { //validation
						printf("\nValid date\n");
					}
					else {
						printf("\nInvalid date\n");
					}
				}
				else {
					printf("\nInvalid format\n");
				}
			} while (validDate(day, month, year) != 1); //loop when didnt pass the validation

			title();

			for (int i = 0; i < size; i++) { //display when the date is same
				if (day == s[i].d.day && month == s[i].d.month && year == s[i].d.year) {
					displayStock(s, i);
					count++;
				}
			}
			if (count == 0) { //show when there is no code
				printf("\nNo record\n");
			}
		}
		else if (select == 3) {
			printf("Please enter the price range\n");

			do {
				printf("min >");
				rewind(stdin);
				scanf("%lf", &price);
				printf("Price = %.2lf\n", price); //filter out alphabet
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
			} while (yesno != 'y'); //loop when user didnt give accepted price

			do {
				printf("max >");
				rewind(stdin);
				scanf("%lf", &price);
				printf("Price = %.2lf\n", price); //filter out alphabet
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

				if (hprice < lprice) { //validation
					printf("\nmax cant lower than min\n");
				}
			} while (yesno != 'y' || hprice < lprice); //loop when user didnt giv accepted price

			title();
			for (int i = 0; i < size; i++) { //display the record in the range
				if (s[i].stockPrice >= lprice && s[i].stockPrice <= hprice) {
					displayStock(s, i);
					count++;
				}
			}

			if (count == 0) { //show when there is no code
				printf("\nNo record\n");
			}
		}

		else if (select == 4) { //exit
			return;
		}
		else {
			printf("\nInvalid answer\n");
		}
	} while (select != 1 || select != 2 || select != 3 || select != 4); //loop when select isnt accepted answer
	fclose(fptr);
}

void modifyStock() {

					char  nname[20],code[6], yesno;
					int day, month, year, min, reorder, option, size, con = 0, a = 0;
					double price;
					Stock s[1000];
					getSize(s, &size);

					//logo
					printf("\n%20s%30s\n", "", "==============================");
					printf("%20s%-2s%10s%6s%10s%2s\n", "", "||", "", "MODIFY", "", "||");
					printf("%20s%30s\n", "", "==============================");

					do {
						con = 0;
						a = 0;
						printf("\nPlease enter the stock code (stop) :");
						rewind(stdin);
						gets(code);
						if (strcmp(code,"stop") == 0) { //if user type stop then function will exit
							return;
						}
						else if (validFormat(code) == 1) { //valid format
							for (int i = 0; i < size; i++) { 
								if (strcmp(code, s[i].stockCode) == 0) { //compare code
									if (strcmp(s[i].status, "available") == 0) { //compare status
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

											if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6) {
												switch (option) {
												case 1:
													do {
														printf("Please enter the new name :");
														rewind(stdin);
														gets(nname);
														if (validLength(nname) == 2) { //validation
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
													} while (validRepeat(nname) == 1 || validLength(nname) == 1); //loop when didnt pass the validation

													do {
														printf("Are you confirm to modify (y/n) ?");
														rewind(stdin);
														yesno = tolower(getchar());

														if (yesno == 'y') {
															strcpy(s[i].stockName, nname);
															printf("\nRecord change\n");
															FILE* wptr = fopen(FILE_NAME, "wb"); //edit the reocrd in binary file
															fwrite(&s, sizeof(Stock), size, wptr);
															fclose(wptr);
														}
														else if (yesno == 'n') {
															printf("\nRecord no changes\n");
														}
														else {
															printf("\nInvalid answer\n");
														}
													} while (yesno != 'y' && yesno != 'n'); //loop
													break;

												case 2:
													do {
														printf("Please enter new minimum quantity :");
														rewind(stdin);
														if (scanf("%d", &min) != 1) { //validation
															printf("\nAlphabet is not allow\n");
														}
														else if (validNumber(min) == 2) {
															printf("\nQuantity must greater then 0\n");
														}
														else if (validNumber(min) == 3) {
															printf("\nValid answer\n");
														}
													} while (validNumber(min) != 3); //loop when didnt pass the validation


													do {
														printf("Are you confirm to modify (y/n) ?");
														rewind(stdin);
														yesno = tolower(getchar());

														if (yesno == 'y') {
															s[i].stockMinimum = min;
															printf("\nRecord change\n");
															FILE* wptr = fopen(FILE_NAME, "wb"); //edit the record in file
															fwrite(&s, sizeof(Stock), size, wptr);
															fclose(wptr);
														}
														else if (yesno == 'n') {
															printf("\nRecord no changes\n");
														}
														else {
															printf("\nInvalid answer\n");
														}
													} while (yesno != 'y' && yesno != 'n'); //loop
													break;
												case 3:
													do {
														printf("Please enter new reorder quantity :");
														rewind(stdin);
														if (scanf("%d", &reorder) != 1) { //validation
															printf("\nAlphabet is not allow\n");
														}
														else if (validNumber(reorder) == 2) {
															printf("\nQuantity must greater then 0\n");
														}
														else if (validNumber(reorder) == 3) {
															printf("\nValid answer\n");
														}
													} while (validNumber(reorder) != 3); //loop when didnt pass the validation

													do {
														printf("Are you confirm to modify (y/n) ?");
														rewind(stdin);
														yesno = tolower(getchar());

														if (yesno == 'y') {
															s[i].stockReorder = reorder;
															printf("\nRecord change\n");
															FILE* wptr = fopen(FILE_NAME, "wb"); //edit the record in file
															fwrite(&s, sizeof(Stock), size, wptr);
															fclose(wptr);
														}
														else if (yesno == 'n') {
															printf("\nRecord no changes\n");
														}
														else {
															printf("\nInvalid answer\n");
														}
													} while (yesno != 'y' && yesno != 'n'); //loop
													break;
												case 4:
													do {
														printf("Please enter new stock price :");
														rewind(stdin);
														scanf("%lf", &price);
														printf("Price = %.2lf\n", price); //filter out alphabet
														printf("Are you sure? (y/n) >");
														rewind(stdin);
														yesno = tolower(getchar());
														if (yesno == 'y') {
															if (price <= 0) { //validation
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
													} while (yesno != 'y' || price <= 0); //loop when didnt pass the validation

													do {
														printf("Are you confirm to modify (y/n) ?");
														rewind(stdin);
														yesno = tolower(getchar());

														if (yesno == 'y') {
															s[i].stockPrice = price;
															printf("\nRecord change\n");
															FILE* wptr = fopen(FILE_NAME, "wb"); //edit the record in file
															fwrite(&s, sizeof(Stock), size, wptr);
															fclose(wptr);
														}
														else if (yesno == 'n') {
															printf("\nRecord no changes\n");
														}
														else {
															printf("\nInvalid answer\n");
														}
													} while (yesno != 'y' && yesno != 'n'); //loop
													break;
												case 5:
													do {
														printf("Please enter lastest date modify reocrd :");
														rewind(stdin);
														scanf("%d/%d/%d", &day, &month, &year);
														if (validDate(day, month, year) == 1) { //validation
															printf("\nValid date\n");
														}
														else {
															printf("\nInvalid date\n");
														}
													} while (validDate(day, month, year) != 1); //loop when didnt pass then validation

													do {
														printf("Are you confirm to modify (y/n) ?");
														rewind(stdin);
														yesno = tolower(getchar());

														if (yesno == 'y') {
															s[i].d.day = day;
															s[i].d.month = month;
															s[i].d.year = year;
															printf("\nRecord change\n");
															FILE* wptr = fopen(FILE_NAME, "wb"); //edit the record in binary file
															fwrite(&s, sizeof(Stock), size, wptr);
															fclose(wptr);
														}
														else if (yesno == 'n') {
															printf("\nRecord no changes\n");
														}
														else {
															printf("\nInvalid answer\n");
														}
													} while (yesno != 'y' && yesno != 'n'); //loop
													break;
												case 6:
													return;
													break;
												}
											}
											else {
											printf("\nInvalid answer\n");
											}
										} while (option != 6); //loop
									}
									else{
									printf("\nOnly stock that is available allow to modify\n");
									a++; //add when status is unavaliable or -
									}
								}
								else {
									con++; //add when code isnt exist
								}
							}
							if (con != 0) {
								printf("\nCode not exist\n");
							}
						}
						else {
						printf("\nInvalid format\n");
						}
					}while (con != 0 || a != 0 || validFormat(code) == 2); //loop
}

void updateStock() {
	Stock s[1000];
	int option, select, yesno, size, chose, quantity, decrease, con = 0, b = 0;
	char code[6], status[15];
	getSize(s, &size);

	//logo
	printf("\n%20s%30s\n", "", "==============================");
	printf("%20s%-2s%10s%6s%10s%2s\n", "", "||", "", "UPDATE", "", "||");
	printf("%20s%30s\n", "", "==============================");

	do {
		con = 0;
		b = 0;
		printf("\nPlease enter the stock code (stop):");
		rewind(stdin);
		gets(code);
		if (strcmp(code, "stop") == 0) { //exit when type stop
			return;
		}
		else if (validFormat(code) == 1) { //valid format
			for (int i = 0; i < size; i++) {
				if (strcmp(code, s[i].stockCode) == 0) { //compare whether the code is same
					do {
						title();
						displayStock(s, i);
						printf("\n1. Update Status\n");
						printf("2. Update Stock Quantity\n");
						printf("3. Exit\n");
						printf("Please select the data you want to update >");
						rewind(stdin);
						scanf("%d", &option);
						if (option == 1 || option == 2 || option == 3) {
							switch (option) {
							case 1:
								do {
									printf("\n1. available\n");
									printf("2. unavailable\n");
									printf("Please update the new status >");
									rewind(stdin);
									scanf("%d", &select);
									if (select == 1) {
										strcpy(status, "available"); //change status
										printf("\nStatus change\n");
									}
									else if (select == 2) {
										strcpy(status, "unavailable"); //change status
										printf("\nStatus change\n");
									}
									else {
										printf("\nInvalid answer\n");
									}
								} while (select != 1 && select != 2);

								do {
									printf("Are you confirm to update (y/n) ?");
									rewind(stdin);
									yesno = tolower(getchar());

									if (yesno == 'y') {
										strcpy(s[i].status, status);
										printf("\nRecord change\n");
										FILE* wptr = fopen(FILE_NAME, "wb"); //update status to file
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
									printf("\n1. Stock reorder\n");
									printf("2. Stock deducted\n");
									printf("3. Exit\n");
									printf("please select >");
									rewind(stdin);
									scanf("%d", &chose);
									if (chose == 1 || chose == 2 || chose == 3) {
										switch (chose) {
										case 1:
											title();
											displayStock(s, i);
											quantity = s[i].stockQuantity;
											quantity += s[i].stockReorder; //quantity + reorder
											printf("Are you confirm to reorder (y/n) >");
											rewind(stdin);
											yesno = tolower(getchar());
											if (yesno == 'y') {
												s[i].stockQuantity = quantity;
												printf("Reorder success\n");
												FILE* wptr = fopen(FILE_NAME, "wb"); //edit reocrd in file
												fwrite(&s, sizeof(Stock), size, wptr);
												fclose(wptr);
											}
											else if (yesno == 'n') {
												printf("Quantity no changes\n");
											}
											break;
										case 2:
											do {
												title();
												displayStock(s, i);
												quantity = s[i].stockQuantity;
												printf("\nPlease enter the quantity that we have sold >");
												rewind(stdin);
												if (scanf("%d", &decrease) != 1) { //validation
													printf("\nAlphabet and Symbol are not allow\n");
												}
												else if (validNumber(decrease) == 2) {
													printf("\nQuantity must greater than 0\n");
												}
												else if (validNumber(decrease) == 3) {
													printf("\nValid answer\n");
												}
											} while (validNumber(decrease) != 3); //loop

											do {
												printf("\nAre you confirm to update (y/n) >");
												rewind(stdin);
												yesno = tolower(getchar());
												if (yesno == 'y') {
													quantity -= decrease;
													if (quantity < 0) {
														printf("\nStock is not enough for sold\n");
													}
													else {
														s[i].stockQuantity = quantity;
														printf("\nStock Updated\n");
														FILE* wptr = fopen(FILE_NAME, "wb"); //edit record in file
														fwrite(&s, sizeof(Stock), size, wptr);
														fclose(wptr);
													}
												}
												else if (yesno == 'n') {
													printf("Quantity no changes\n");
												}
											} while (yesno != 'y' && yesno != 'n'); //loop
											break;
										case 3:
											return;
											break;
										}
									}
									else {
										printf("\nInvalid answer\n");
									}
								} while (chose != 3); //loop
							case 3:
								return;
								break;
							}
						}
						else {
							printf("\nInvalid answer\n");
						}
					} while (option != 3); //loop
				}
				else {
				con++; //add when code isnt exist
				}
			}
			if (con != 0) {
				printf("\nCode not exist\n");
			}
		}
		else {
			printf("\nInvalid format\n");
			b++; //add when code format is wrong
		}
	}while (con != 0 || b != 0); //loop
}

void reportStock(Stock s[], int size) {
	time_t t = time(NULL);
	struct tm* local_time = localtime(&t);
	char timeStr[100];

	//logo
	printf("\n%38s%30s\n","", "==============================");
	printf("%38s%-2s%10s%6s%10s%2s\n","", "||", "", "REPORT","", "||");
	printf("%38s%30s\n","", "==============================");
	
	printf("\n%48s%8s\n","","LowStock");
	printf("-------------------------------------------------------------------------------------------------------------");
	title();
	for (int i = 0; i < size; i++) {
		if (s[i].stockQuantity < s[i].stockMinimum) { //display stock that is low
			displayStock(s, i);
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");

	printf("\n%50s%5s\n","","Stock");
	printf("-------------------------------------------------------------------------------------------------------------");
	title();
	for (int i = 0; i < size; i++) {
		if (s[i].stockQuantity >= s[i].stockMinimum) { //display stock that is enough
			displayStock(s, i);
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");

	printf("\n%47s%11s\n","","Unavailable");
	printf("-------------------------------------------------------------------------------------------------------------");
	title();
	for (int i = 0; i < size; i++) {
		if (strcmp(s[i].status, "unavailable") == 0) { //display stock that is unavaliable
			displayStock(s, i);
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");

	printf("\n%48s%9s\n","","Available");
	printf("-------------------------------------------------------------------------------------------------------------");
	title();
	for (int i = 0; i < size; i++) { //display stock that is avaliable
		if (strcmp(s[i].status, "available") == 0) {
			displayStock(s, i);
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");

	printf("\n%42s%18s\n","","Status havent update");
	printf("-------------------------------------------------------------------------------------------------------------");
	title();
	for (int i = 0; i < size; i++) { //display stock that forget to update status
		if (strcmp(s[i].status, "-") == 0) {
			displayStock(s, i);
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");

	printf("\nTotal Stock Record = %d\n", size); //total record

	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", local_time);
	printf("\nReport generate at %s\n", timeStr); //current local time
	printf("\n\n");
	system("pause");
}
