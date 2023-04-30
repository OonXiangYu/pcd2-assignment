#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include <time.h>
#include <windows.h>
#pragma warning(disable:4996)
#define FILE_NAME "stock.dat"
#define MAX_MEMBER 10000
#define SALESFILE "Sales.txt"
#define MAX 1000
#define MAX_STAFF 100

// STRUCTURE .................................................................................................................................
//Goo Yong Kang 
struct membershipDate {
	int day, month, year;
};

typedef struct {
	char name[31], id[9], gender, password[31], membershipType;
	struct membershipDate mExpiryDate;
}Member;

//Loke Kevin
typedef struct {
	int day;
	int month;
	int year;
}Date;

typedef struct {
	char id[5], code[6], memberId[8];
	int quantity;
	double price;
	Date date;
}Sales;

//Jerome Lu Zheng Yao
struct Staff {
	char id[7];
	char name[50];
	char password[20];
	char recovery[20];
	char position[20];
	char role[20];
};

//Oon Xiang Yu
struct date { //tagged struct
	int day, month, year;
};

typedef struct { //data fields
	char stockCode[6], stockName[21], status[15];
	int stockQuantity, stockMinimum, stockReorder;
	double stockPrice;
	struct date d;
}Stock;

//Oon Xiang Yu
//main function
void addStock();
void searchStock(Stock s[], int);
void modifyStock();
void displayStock(Stock s[], int);
void updateStock();
void reportStock(Stock s[], int);

//validation function
int validDate(int day, int month, int year);
int validRepeat(char name[21]);
int validNumber(int);
int validFormat(char);
int validLength(char);

//subs function
void getSize(Stock s[], int*);
void title();

//Jerome Lu Zheng Yao
void addStaff(struct Staff staffList[], int* numStaff);
void displayStaff(struct Staff staffList[], int numStaff);
void generateReport(struct Staff staffList[], int numStaff);
void editStaff(struct Staff staffList[], int numStaff);
void checkPassword(struct Staff staffList[], int numStaff);
void searchStaff(struct Staff staffList[], int numStaff);

//Loke Kevin
void backMenuAh();
void wantEditAh();
void stillWantEditAh();

void addSales();
int salesValid(char salesId[5]);
int itemValid(char itemCode[15]);
double setPrice(char itemCode[15]);
int memberValid(char memId[20]);

void displaySales();

void searchSales();

void searchSalesId();
int searchIdValid(char salesId[5]);

void searchItem();
int searchItemValid(char itemCode[15]);

void searchMem();
int searchMemValid(char memId[20]);

void modify();
int salesModifyValid(char salesId[5]);

void reportSales();
int totalSales();
double totalRevenue();
void revenue(int quantities, double prices);

void deleteMenu();
void deleteSales();
void displayDelete();

void set_today_date(Date* date);

//Goo Yong Kang
void addMember();
void searchMember();
void modifyMember();
void displayMember();
void renewMembership();
void resetPassword();

//Main function
void memberMain();
void salesMain();
int staffMain();
void stockMain();

void main() {
	int option;

	do {
		printf("\n\n");
		printf("-----------------------\n");
		printf(" YY     YY   YY     YY\n");
		printf("  YY   YY     YY   YY\n");
		printf("   YY YY       YY YY\n");
		printf("    YYY         YYY\n");
		printf("     Y           Y\n");
		printf("     Y           Y\n");
		printf("     Y           Y\n");
		printf("-----------------------\n");

		printf("1. Member Module\n");
		printf("2. Sales Module\n");
		printf("3. Staff Module\n");
		printf("4. Stock Module\n");
		printf("5. Exit\n");
		printf("Please enter your option > ");
		rewind(stdin);
		scanf("%d", &option);
		if (option == 1 || option == 2 || option == 3 || option == 4) {
			switch (option) {
			case 1:
				memberMain();
				break;
			case 2:
				salesMain();
				break;
			case 3:
				staffMain();
				break;
			case 4:
				stockMain();
				break;
			}
		}
		else if (option == 5) {
			printf("\nThank you so much.\n");
			return;
		}
		else {
			printf("\nInvalid Answer\n");
		}
	} while (option != 5);
}

//Goo Yong Kang
void memberMain() {
	int selection;

	do {
		printf("\n\n\nMember Module\n");
		printf("-------------\n");
		printf("1. Add Member\n");
		printf("2. Search Member\n");
		printf("3. Modify Member\n");
		printf("4. Display Member\n");
		printf("5. Renew Membership\n");
		printf("6. Reset Password\n");
		printf("7. Exit\n");
		printf("\nEnter your selection from the options above: ");
		rewind(stdin);
		scanf("%d", &selection);

		if (selection >= 1 && selection <= 7)
			switch (selection) {
			case 1:
				addMember();
				break;
			case 2:
				searchMember();
				break;
			case 3:
				modifyMember();
				break;
			case 4:
				displayMember();
				break;
			case 5:
				renewMembership();
				break;
			case 6:
				resetPassword();
				break;
			case 7:
				printf("Thank you for using our service, have a nice day!\n");
				return;
				break;
			}
		else
			printf("Invalid output.\n\n");
	} while (selection != 7);
}

// 1st function
void addMember() {
	FILE* fptr;
	fptr = fopen("MemberList.dat", "ab+");
	if (fptr == NULL) {
		printf("File open error.\n");
		exit(-1);
	}

	Member newMember, memberList[MAX_MEMBER];
	int count = 0, i, lengthCheck, idCheck = 0;

	while (count < MAX_MEMBER && fread(&memberList[count], sizeof(Member), 1, fptr) == 1) {
		count++;
	}

	printf("\nAdd Member\n");
	printf("----------\n");

	do {
		printf("Enter member name: ");
		rewind(stdin);
		gets(newMember.name);
		lengthCheck = strlen(newMember.name);
		if (lengthCheck == 0) {
			printf("Name cannot be empty.\n\n");
		}
	} while (lengthCheck == 0);

	do {
		printf("Enter member ID (Format-MEM00001): ");
		rewind(stdin);
		scanf("%s", &newMember.id);
		lengthCheck = strlen(newMember.id);
		if (lengthCheck != 8) {
			printf("Member ID must follow the format.\n\n");
		}
		for (i = 0; i < count; i++) {
			if (strcmp(newMember.id, memberList[i].id) == 0) {
				printf("Member ID already exists.\n\n");
				idCheck = 1;
			}
		}
	} while (lengthCheck != 8 || idCheck == 1);

	do {
		printf("Enter member gender (M-Male, F-Female): ");
		rewind(stdin);
		scanf("%c", &newMember.gender);
		if (newMember.gender != 'M' && newMember.gender != 'F') {
			printf("Gender must be M (Male) or F (Female) only.\n\n");
		}
	} while (newMember.gender != 'M' && newMember.gender != 'F');

	do {
		printf("Enter password (Min-8, Max-30): ");
		rewind(stdin);
		scanf("%s", &newMember.password);
		lengthCheck = strlen(newMember.password);
		if (lengthCheck < 8 || lengthCheck > 30) {
			printf("Password must be within 8 to 30 characters.\n\n");
		}
	} while (lengthCheck < 8 || lengthCheck > 30);

	do {
		printf("Enter membership type (N-Normal, P-Premium): ");
		rewind(stdin);
		scanf("%c", &newMember.membershipType);
		if (newMember.membershipType != 'N' && newMember.membershipType != 'P') {
			printf("Membership type can be N (Normal) or P (Premium) only.\n\n");
		}
	} while (newMember.membershipType != 'N' && newMember.membershipType != 'P');

	SYSTEMTIME t;
	GetLocalTime(&t);
	newMember.mExpiryDate.day = t.wDay;
	newMember.mExpiryDate.month = t.wMonth;
	newMember.mExpiryDate.year = t.wYear + 5;

	fwrite(&newMember, sizeof(Member), 1, fptr);

	printf("\nMember added successfully.\n\n\n");
	fclose(fptr);
	return;
}

// 2nd function
void searchMember() {
	FILE* fptr;
	fptr = fopen("MemberList.dat", "rb");
	if (fptr == NULL) {
		printf("File open error.\n");
		exit(-1);
	}

	Member memberList[MAX_MEMBER];
	int count = 0, search, i, lengthCheck, index, nameCount = 0, idCount = 0, genderSearch, genderCount = 0, mtSearch, mtCount = 0;
	int  medCount = 0, minMedYear, maxMedYear;
	char nameSearch[31], idSearch[9];

	while (count < MAX_MEMBER && fread(&memberList[count], sizeof(Member), 1, fptr) == 1) {
		count++;
	}
	fclose(fptr);

	do {
		printf("\nSearch Member\n");
		printf("-------------\n");
		printf("\n1. Search by name\n");
		printf("2. Search by member ID\n");
		printf("3. Search by gender\n");
		printf("4. Search by membership type\n");
		printf("5. Search by membership expiry date\n");
		printf("99. Return\n");
		printf("\nEnter the number to search by: ");
		rewind(stdin);
		scanf("%d", &search);

		if (search >= 1 && search <= 5) {
			switch (search) {
			case 1:
				do {
					printf("Enter name to search (Enter 99 to return): ");
					rewind(stdin);
					gets(nameSearch);

					if (strcmp(nameSearch, "99") == 0) {
						printf("Returning...\n\n");
						break;
					}

					printf("\nMember list with name \"%s\"\n", nameSearch);
					printf("------------------------");
					lengthCheck = strlen(nameSearch);
					for (int i = 0; i < lengthCheck; i++) {
						putchar('-');
					}
					printf("\n\n");
					printf("\n%30s %9s %6s %16s %22s\n", "Member Name", "Member ID", "Gender", "Membership Type", "Membership Expiry date");
					printf("%30s %9s %6s %16s %22s\n", "------------------------------", "---------", "------", "---------------", "----------------------");
					for (i = 0; i < count; i++) {
						if (strcmp(nameSearch, memberList[i].name) == 0) {
							printf("%30s %9s %6c %16c %12s%02d/%02d/%04d\n",
								memberList[i].name, memberList[i].id, memberList[i].gender, memberList[i].membershipType, " ",
								memberList[i].mExpiryDate.day, memberList[i].mExpiryDate.month, memberList[i].mExpiryDate.year);
							nameCount++;
						}
					}
					printf("\nMember(s) in total: %d\n\n", nameCount);
					nameCount = 0;
					break;
				} while (nameSearch != 99);
				break;

			case 2:
				do {
					printf("Enter member ID to search (Enter 99 to return): ");
					rewind(stdin);
					scanf("%s", &idSearch);

					if (strcmp(idSearch, "99") == 0) {
						printf("Returning...\n\n");
						break;
					}

					for (i = 0; i < count; i++) {
						if (strcmp(idSearch, memberList[i].id) == 0) {
							idCount = 1;
							index = i;
						}
					}

					if (idCount) {
						printf("\nMember list with ID \"%8s\"\n", idSearch);
						printf("------------------------------\n\n");
						printf("\n%30s %9s %6s %16s %22s\n", "Member Name", "Member ID", "Gender", "Membership Type", "Membership Expiry date");
						printf("%30s %9s %6s %16s %22s\n", "------------------------------", "---------", "------", "---------------", "----------------------");
						printf("%30s %9s %6c %16c %12s%02d/%02d/%04d\n",
							memberList[index].name, memberList[index].id, memberList[index].gender, memberList[index].membershipType, " ",
							memberList[index].mExpiryDate.day, memberList[index].mExpiryDate.month, memberList[index].mExpiryDate.year);
						printf("\nMatch found.\n\n");
						idCount = 0;
						break;
					}
					else {
						printf("Match not found.\n\n");
						break;
					}
				} while (idSearch != 99);
				break;

			case 3:
				do {
					printf("\n1. Search Male (M)\n");
					printf("2. Search Female (F)\n");
					printf("99. Return\n");
					printf("\nEnter the number to search by: ");
					rewind(stdin);
					scanf("%d", &genderSearch);

					if (genderSearch == 1 || genderSearch == 2) {
						switch (genderSearch) {
						case 1:
							printf("\nMember list by Male\n");
							printf("-------------------\n\n");
							printf("%30s %9s %6s %16s %22s\n", "Member Name", "Member ID", "Gender", "Membership Type", "Membership Expiry date");
							printf("%30s %9s %6s %16s %22s\n", "------------------------------", "---------", "------", "---------------", "----------------------");
							for (i = 0; i < count; i++) {
								if (memberList[i].gender == 'M') {
									printf("%30s %9s %6c %16c %12s%02d/%02d/%04d\n",
										memberList[i].name, memberList[i].id, memberList[i].gender, memberList[i].membershipType, " ",
										memberList[i].mExpiryDate.day, memberList[i].mExpiryDate.month, memberList[i].mExpiryDate.year);
									genderCount++;
								}
							}
							break;

						case 2:
							printf("\nMember list by Female\n");
							printf("---------------------\n\n");
							printf("%30s %9s %6s %16s %22s\n", "Member Name", "Member ID", "Gender", "Membership Type", "Membership Expiry date");
							printf("%30s %9s %6s %16s %22s\n", "------------------------------", "---------", "------", "---------------", "----------------------");
							for (i = 0; i < count; i++) {
								if (memberList[i].gender == 'F') {
									printf("%30s %9s %6c %16c %12s%02d/%02d/%04d\n",
										memberList[i].name, memberList[i].id, memberList[i].gender, memberList[i].membershipType, " ",
										memberList[i].mExpiryDate.day, memberList[i].mExpiryDate.month, memberList[i].mExpiryDate.year);
									genderCount++;
								}
							}
							break;
						}
						printf("\nMember(s) in total: %d\n\n", genderCount);
						genderCount = 0;
						break;

					}
					else if (genderSearch == 99) {
						printf("Returning...\n\n");
						break;
					}

					else {
						printf("Invalid input.\n\n");
					}

				} while (genderSearch != 99);
				break;

			case 4:
				do {
					printf("\n1. Search member(s) with Normal membership (N)\n");
					printf("2. Search member(s) with Premium membership (P)\n");
					printf("99. Return\n");
					printf("\nEnter the number to search by: ");
					rewind(stdin);
					scanf("%d", &mtSearch);

					if (mtSearch == 1 || mtSearch == 2) {
						switch (mtSearch) {
						case 1:
							printf("\nMember list with Normal membership\n");
							printf("----------------------------------\n\n");
							printf("%30s %9s %6s %16s %22s\n", "Member Name", "Member ID", "Gender", "Membership Type", "Membership Expiry date");
							printf("%30s %9s %6s %16s %22s\n", "------------------------------", "---------", "------", "---------------", "----------------------");
							for (i = 0; i < count; i++) {
								if (memberList[i].membershipType == 'N') {
									printf("%30s %9s %6c %16c %12s%02d/%02d/%04d\n",
										memberList[i].name, memberList[i].id, memberList[i].gender, memberList[i].membershipType, " ",
										memberList[i].mExpiryDate.day, memberList[i].mExpiryDate.month, memberList[i].mExpiryDate.year);
									mtCount++;
								}
							}
							break;

						case 2:
							printf("\nMember list with Premium membership\n");
							printf("-----------------------------------\n\n");
							printf("%30s %9s %6s %16s %22s\n", "Member Name", "Member ID", "Gender", "Membership Type", "Membership Expiry date");
							printf("%30s %9s %6s %16s %22s\n", "------------------------------", "---------", "------", "---------------", "----------------------");
							for (i = 0; i < count; i++) {
								if (memberList[i].membershipType == 'P') {
									printf("%30s %9s %6c %16c %12s%02d/%02d/%04d\n",
										memberList[i].name, memberList[i].id, memberList[i].gender, memberList[i].membershipType, " ",
										memberList[i].mExpiryDate.day, memberList[i].mExpiryDate.month, memberList[i].mExpiryDate.year);
									mtCount++;
								}
							}
							break;
						}
						printf("\nMember(s) in total: %d\n\n", mtCount);
						mtCount = 0;
						break;

					}
					else if (mtSearch == 99) {
						printf("Returning...\n\n");
						break;

					}
					else {
						printf("Invalid input.\n\n");
					}

				} while (mtSearch != 99);
				break;

			case 5:
				do {
					printf("\nEnter oldest year to search (Enter 0 to return): ");
					rewind(stdin);
					scanf("%d", &minMedYear);

					if (minMedYear >= 1 && minMedYear <= 9999) {
						do {
							printf("\nEnter latest year to search (Enter 0 to return): ");
							rewind(stdin);
							scanf("%d", &maxMedYear);

							if (maxMedYear >= 1 && maxMedYear <= 9999) {
								printf("\nMember list with membership expiry date from %04d to %04d\n", minMedYear, maxMedYear);
								printf("---------------------------------------------------------\n\n");
								printf("%30s %9s %6s %16s %22s\n", "Member Name", "Member ID", "Gender", "Membership Type", "Membership Expiry date");
								printf("%30s %9s %6s %16s %22s\n", "------------------------------", "---------", "------", "---------------", "----------------------");
								for (i = 0; i < count; i++) {
									if (memberList[i].mExpiryDate.year >= minMedYear && memberList[i].mExpiryDate.year <= maxMedYear) {
										printf("%30s %9s %6c %16c %12s%02d/%02d/%04d\n",
											memberList[i].name, memberList[i].id, memberList[i].gender, memberList[i].membershipType, " ",
											memberList[i].mExpiryDate.day, memberList[i].mExpiryDate.month, memberList[i].mExpiryDate.year);
										medCount++;
									}
								}
								printf("\nMember(s) in total: %d\n\n", medCount);
								medCount = 0;
								break;
							}

							else if (maxMedYear == 0) {
								printf("Retruning...\n\n");
								break;
							}

							else {
								printf("Invalid input.\n\n");
							}
							break;
						} while (maxMedYear != 0);
					}

					else if (minMedYear == 0) {
						printf("Retruning...\n\n");
						break;
					}

					else {
						printf("Invalid input.\n\n");
					}
					break;

				} while (minMedYear != 0);
				break;
			}
		}

		else if (search == 99) {
			printf("Returning...\n\n");
			break;
		}

		else {
			printf("Invalid input.\n\n");
		}

	} while (search != 99);
}

// 3rd function
void modifyMember() {
	FILE* fptr;
	fptr = fopen("MemberList.dat", "rb");
	if (fptr == NULL) {
		printf("File open error.\n");
		exit(-1);
	}

	Member  memberList[MAX_MEMBER];
	int i = 0, count = 0, found = 0, index, selection, mSelection;
	char idSearch[9], newName[31], newGender, newMS, modifyNameConfirm, modifyGenderConfirm, modifyMSConfirm;

	while (count < MAX_MEMBER && fread(&memberList[count], sizeof(Member), 1, fptr) == 1) {
		count++;
	}
	fclose(fptr);

	printf("Enter member ID to modify: ");
	rewind(stdin);
	scanf("%s", idSearch);

	for (i = 0; i < count; i++) {
		if (strcmp(idSearch, memberList[i].id) == 0) {
			found = 1;
			index = i;
		}
	}

	if (found) {
		do {
			printf("\nMember information: \n");
			printf("1. Name: %-31s\n", memberList[index].name);
			printf("2. Gender: %c\n", memberList[index].gender);
			printf("3. Membership status: %c\n", memberList[index].membershipType);
			printf("99. Return\n");
			printf("\nEnter number to modify: ");
			rewind(stdin);
			scanf("%d", &selection);

			if (selection >= 1 && selection <= 3)
				switch (selection) {
				case 1:
					printf("Enter new name: ");
					rewind(stdin);
					gets(newName);
					do {
						printf("Are you sure to change your name to %s (Y-Yes, N-No)? ", newName);
						rewind(stdin);
						scanf("%c", &modifyNameConfirm);

						if (modifyNameConfirm == 'Y') {
							strcpy(memberList[index].name, newName);
							fptr = fopen("MemberList.dat", "wb");
							if (fptr == NULL) {
								printf("File open error.\n");
								exit(-1);
							}
							fwrite(&memberList, sizeof(Member), count, fptr);
							fclose(fptr);
							printf("Name change successful.\n\n");
						}

						else if (modifyNameConfirm == 'N') {
							printf("Name change cancel.\n\n");
						}

						else {
							printf("Invalid input.\n\n");
						}

					} while (modifyNameConfirm != 'Y' && modifyNameConfirm != 'N');
					break;

				case 2:
					do {
						if (memberList[index].gender == 'M') {
							printf("Your current gender is male(M). Do you want to change to female(F) (Y-Yes, N-No)? ");
						}
						if (memberList[index].gender == 'F') {
							printf("Your current gender is female(F). Do you want to change to male(M) (Y-Yes, N-No)? ");
						}
						rewind(stdin);
						scanf("%c", &modifyGenderConfirm);

						if (modifyGenderConfirm == 'Y') {
							if (memberList[index].gender == 'M') {
								memberList[index].gender = 'F';
							}
							else if (memberList[index].gender == 'F') {
								memberList[index].gender = 'M';
							}
							fptr = fopen("MemberList.dat", "wb");
							if (fptr == NULL) {
								printf("File open error.\n");
								exit(-1);
							}
							fwrite(&memberList, sizeof(Member), count, fptr);
							fclose(fptr);
							printf("Gender change successful.\n\n");
						}

						else if (modifyGenderConfirm == 'N') {
							printf("Gender change cancel.\n\n");
						}

						else {
							printf("Invalid input.\n\n");
						}

					} while (modifyGenderConfirm != 'Y' && modifyGenderConfirm != 'N');
					break;

				case 3:
					do {
						printf("\nMembership type available:\n");
						printf("1. Normal Membership (N)\n");
						printf("2. Premium Membership (P)\n\n");
						printf("99. Return\n");
						printf("Enter your selection: ");
						rewind(stdin);
						scanf("%d", &mSelection);

						if (mSelection == 1 || mSelection == 2) {
							switch (mSelection) {
							case 1:
								do {
									printf("Are you sure to update the type to normal(N) (Y-Yes, N-No)? ");
									rewind(stdin);
									scanf("%c", &modifyMSConfirm);

									if (modifyMSConfirm == 'Y') {
										memberList[index].membershipType = 'N';
										fptr = fopen("MemberList.dat", "wb");
										if (fptr == NULL) {
											printf("File open error.\n");
											exit(-1);
										}
										fwrite(&memberList, sizeof(Member), count, fptr);
										fclose(fptr);
										printf("Membership type update successful.\n\n");
									}

									else if (modifyMSConfirm == 'N') {
										printf("Membership type update cancel.\n\n");
									}

									else {
										printf("Invalid input.\n\n");
									}

								} while (modifyMSConfirm != 'Y' && modifyMSConfirm != 'N');
								break;

							case 2:
								do {
									printf("Are you sure to update the status to premium(P) (Y-Yes, N-No)? ");
									rewind(stdin);
									scanf("%c", &modifyMSConfirm);

									if (modifyMSConfirm == 'Y') {
										memberList[index].membershipType = 'P';
										fptr = fopen("MemberList.dat", "wb");
										if (fptr == NULL) {
											printf("File open error.\n");
											exit(-1);
										}
										fwrite(&memberList, sizeof(Member), count, fptr);
										fclose(fptr);
										printf("Membership type update successful.\n\n");
									}

									else if (modifyMSConfirm == 'N') {
										printf("Membership type update cancel.\n\n");
									}

									else {
										printf("Invalid input.\n\n");
									}

								} while (modifyMSConfirm != 'Y' && modifyMSConfirm != 'N');
								break;
							}
						}
						else if (mSelection == 99) {
							printf("Returning...\n\n");
						}

						else {
							printf("Invalid input.\n\n");
						}

					} while (mSelection != 99);

				}

			else if (selection == 99) {
				printf("Returning...\n\n\n");
			}

			else {
				printf("Invalid input.\n\n");
			}

		} while (selection != 99);
	}
	else {
		printf("Match not found.\n\n\n");
	}
}

// 4th function
void displayMember() {
	FILE* fptr;
	fptr = fopen("MemberList.dat", "rb");
	if (fptr == NULL) {
		printf("File open error.\n");
		exit(-1);
	}

	Member memberList;

	printf("\nMember List\n");
	printf("-----------\n\n");
	printf("%30s %9s %6s %16s %22s %30s\n", "Member Name", "Member ID", "Gender", "Membership Type", "Membership Expiry date", "Password");
	printf("%30s %9s %6s %16s %22s %30s\n", "------------------------------", "---------", "------", "---------------", "----------------------", "------------------------------");
	while (fread(&memberList, sizeof(Member), 1, fptr) == 1) {
		printf("%30s %9s %6c %16c %12s%02d/%02d/%04d %30s\n",
			memberList.name, memberList.id, memberList.gender, memberList.membershipType, " ",
			memberList.mExpiryDate.day, memberList.mExpiryDate.month, memberList.mExpiryDate.year, memberList.password);
	}
	printf("\n\n\n");
	fclose(fptr);
	return;
}

// 5th function
void renewMembership() {
	FILE* fptr;
	fptr = fopen("MemberList.dat", "rb");
	if (fptr == NULL) {
		printf("File open error.\n");
		exit(-1);
	}

	Member  memberList[MAX_MEMBER];
	int i = 0, count = 0, found = 0, index;
	char idSearch[9], renewConfirm;

	while (count < MAX_MEMBER && fread(&memberList[count], sizeof(Member), 1, fptr) == 1) {
		count++;
	}
	fclose(fptr);

	printf("Enter member ID to renew membership: ");
	rewind(stdin);
	scanf("%s", idSearch);

	for (i = 0; i < count; i++) {
		if (strcmp(idSearch, memberList[i].id) == 0) {
			found = 1;
			index = i;
		}
	}

	if (found) {
		printf("\nMembership expiry date               : %02d/%02d/%04d\n",
			memberList[index].mExpiryDate.day, memberList[index].mExpiryDate.month, memberList[index].mExpiryDate.year);
		printf("Membership expiry date after renewal : %02d/%02d/%04d\n",
			memberList[index].mExpiryDate.day, memberList[index].mExpiryDate.month, memberList[index].mExpiryDate.year + 5);

		do {
			printf("\nAre you sure to renew the membership (Y-Yes, N-No)? ");
			rewind(stdin);
			scanf("%c", &renewConfirm);

			if (renewConfirm == 'Y') {
				memberList[index].mExpiryDate.year += 5;
				fptr = fopen("MemberList.dat", "wb");
				if (fptr == NULL) {
					printf("File open error.\n");
					exit(-1);
				}
				fwrite(&memberList, sizeof(Member), count, fptr);
				fclose(fptr);
				printf("Membership renewal successful. New expiry date: %02d/%02d/%04d\n\n\n",
					memberList[index].mExpiryDate.day, memberList[index].mExpiryDate.month, memberList[index].mExpiryDate.year);
			}

			else if (renewConfirm == 'N') {
				printf("Membership renewal cancel.\n\n\n");
				break;
			}

			else {
				printf("Invalid input.\n\n");
			}

		} while (renewConfirm != 'Y' && renewConfirm != 'N');
	}

	else {
		printf("Match not found.\n\n\n");
	}
}

// 6th function
void resetPassword() {
	FILE* fptr;
	fptr = fopen("MemberList.dat", "rb");
	if (fptr == NULL) {
		printf("File open error.\n");
		exit(-1);
	}

	Member  memberList[MAX_MEMBER];
	int i = 0, count = 0, found = 0, index;
	char idSearch[9], passVerify[31], newPass[31], resetConfirm;

	while (count < MAX_MEMBER && fread(&memberList[count], sizeof(Member), 1, fptr) == 1) {
		count++;
	}
	fclose(fptr);

	printf("Enter member ID to reset password (Enter 99 to return): ");
	rewind(stdin);
	scanf("%s", idSearch);

	if (strcmp(idSearch, "99") == 0) {
		printf("Returning...\n\n");
		return;
	}

	for (i = 0; i < count; i++) {
		if (strcmp(idSearch, memberList[i].id) == 0) {
			found = 1;
			index = i;
		}
	}

	if (found) {
		do {
			printf("Enter password (Enter 99 to return): ");
			rewind(stdin);
			gets(passVerify);

			if (strcmp(passVerify, memberList[index].password) == 0) {
				printf("Enter new password: ");
				rewind(stdin);
				scanf("%[^\n]", newPass);
				do {
					printf("Are you sure to reset your password (Y-Yes, N-No)? ");
					rewind(stdin);
					scanf("%c", &resetConfirm);

					if (resetConfirm == 'Y') {
						strcpy(memberList[index].password, newPass);
						fptr = fopen("MemberList.dat", "wb");
						if (fptr == NULL) {
							printf("File open error.\n");
							exit(-1);
						}
						fwrite(&memberList, sizeof(Member), count, fptr);
						fclose(fptr);
						printf("Password reset successful.\n\n\n");
						break;
					}

					else if (resetConfirm == 'N') {
						printf("Password reset cancel.\n\n\n");
						break;
					}

					else {
						printf("Invalid input.\n\n");
					}

				} while (resetConfirm != 'Y' && resetConfirm != 'N');
			}

			else if (strcmp(passVerify, "99") == 0) {
				printf("Returning...\n\n\n");
				break;
			}

			else {
				printf("Password wrong. Please try again.\n\n");
			}

		} while (strcmp(passVerify, memberList[i].password) != 0 && strcmp(passVerify, "99") != 0);
	}

	else {
		printf("Match not found.\n\n\n");
	}
}

//Loke Kevin
void salesMain() {
	int choice;
	do {
		printf("\n-------- Welcome To Sales Information -----------\n\n");
		printf("Please Choose a field to enter >>>\n");
		printf("1. Add Sales Record\n");
		printf("2. Display Sales Record\n");
		printf("3. Search For Sales Record\n");
		printf("4. Edit Sales Record\n");
		printf("5. Delete Sales Record\n");
		printf("6. Sales Report\n");
		printf("7. Exit Program\n\n");
		printf("Please Choose your option : ");
		rewind(stdin);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			addSales();
			break;

		case 2:
			displaySales();
			break;

		case 3:
			searchSales();
			break;

		case 4:
			modify();

		case 5:
			deleteMenu();

		case 6:
			reportSales();

		case 7:
			return;
		default:
			printf("\bSorry Choice Unavailable :(\n");
		}
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7);
}


// ADD SALES AND VALIDATION FUNCTION............................................................................................................
void addSales() {
	Sales p;
	char yesno;


	do {
		FILE* fptr = fopen(SALESFILE, "a");
		if (fptr == NULL) {
			printf("FILE NOT FOUND !!\n");
			return;
		}

		do {
			printf("Please enter the Sales ID (S101)   > ");
			rewind(stdin);
			scanf("%[^\n]", p.id);
			if (salesValid(p.id) == 1) {
				printf("The Sales ID had been used !!\n");
			}
			else if (salesValid(p.id) == 2) {
				printf("The Sales ID is too long !!\n");
			}
		} while (salesValid(p.id) == 1 || salesValid(p.id) == 2);

		do {
			printf("Please enter the Item Code (a0001) > ");
			rewind(stdin);
			gets(p.code);
			if (itemValid(p.code) != 1) {
				printf("Item Code not found in the server !!\n");
			}
		} while (itemValid(p.code) != 1);

		do {
			printf("Please enter Member ID (MEM00001)   > ");
			rewind(stdin);
			gets(p.memberId);
			if (memberValid(p.memberId) != 1) {
				printf("Member ID not found in the server !!\n");
			}
		} while (memberValid(p.memberId) != 1);

		printf("Please enter Item Quantity         > ");
		rewind(stdin);
		scanf("%d", &p.quantity);

		p.price = setPrice(p.code);

		set_today_date(&p.date);

		fprintf(fptr, "%s|%s|%d|%.2lf|%s|%d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
		printf("\nData Insert Success !!\n\n");
		fclose(fptr);
		do {
			printf("Do you want to continue to add?\n");
			printf("y = yes , n = no > ");
			scanf(" %c", &yesno);
			if (toupper(yesno) != 'Y' && toupper(yesno) != 'N') {
				printf("Please enter (y/n) ONLY!!\n");
			}
			else if (toupper(yesno) == 'N') {
				backMenuAh();
			}
		} while (toupper(yesno) != 'Y' && toupper(yesno) != 'N');


	} while (toupper(yesno) == 'Y');

}




int salesValid(char salesId[5]) {
	Sales p;
	int userinput = strlen(salesId);
	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}
	while (!feof(fptr)) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);
		if (strcmp(salesId, p.id) == 0) {
			return 1;
		}
		else if (userinput > 4) {
			return 2;
		}
	}
	fclose(fptr);
}


int itemValid(char itemCode[15]) {
	Stock s;
	FILE* fptr = fopen("stock.dat", "rb");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}

	while (!feof(fptr)) {
		fread(&s, sizeof(s), 1, fptr);
		if (strcmp(itemCode, s.stockCode) == 0) {
			setPrice(itemCode);
			return 1;
		}
	}
	fclose(fptr);
}


double setPrice(char itemCode[15]) {
	Stock s;
	FILE* fPtr = fopen("stock.dat", "rb");
	if (fPtr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}

	while (fread(&s, sizeof(s), 1, fPtr) != EOF) {
		if (strcmp(itemCode, s.stockCode) == 0) {
			return s.stockPrice;
		}
	}
	fclose(fPtr);
}


int memberValid(char memId[20]) {
	Member m;
	FILE* fptr = fopen("MemberList.dat", "rb");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}

	while (!feof(fptr)) {
		fread(&m, sizeof(m), 1, fptr);
		if (strcmp(memId, m.id) == 0) {
			return 1;
		}
	}
	fclose(fptr);
}


// DISPLAY SALES FUNCTION.......................................................................................................................
void displaySales() {
	Sales p;
	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}

	printf("%-15s %5s %20s %19s %17s %13s\n", "Sales Id", "Item Code", "Quantity", "Price(RM)", "Member ID", "Date");
	printf("-------------------------------------------------------------------------------------------------------\n");
	while (!feof(fptr)) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);
		printf("%-15s %5s %18d %24.2lf %17s %12d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
	}
	fclose(fptr);

	wantEditAh();
}


// SEARCH RESULT FUNCTION.......................................................................................................................
void searchSales() {
	int choice;

	do {
		printf("\nChoose one catogory to search >>>>\n");
		printf("1. Sales ID\n");
		printf("2. Item Code\n");
		printf("3. Member ID\n");
		printf("4. Back to Main Menu\n");
		printf("\nPlease enter your choice > ");
		rewind(stdin);
		scanf("%d", &choice);


		switch (choice) {
		case 1:
			searchSalesId();
			break;
		case 2:
			searchItem();
			break;
		case 3:
			searchMem();
			break;
		case 4:
			salesMain();
			break;
		default:
			printf("\nSorry Choice Unavailable :( \n");
		}
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

}

// SEARCH SALES ID AND VALIDATION................
void searchSalesId() {
	Sales p;
	char salesId[5];

	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}

	int idFound = 0;
	do {
		printf("\nPlease enter Sales ID to search (S101)  > ");
		rewind(stdin);
		gets(salesId);

		if (searchIdValid(salesId) == 1) {
			printf("%50s", "\n...........SEARCH RESULT...........");
			printf("\n%-15s %5s %20s %19s %17s %13s\n", "Sales Id", "Item Code", "Quantity", "Price(RM)", "Member ID", "Date");
			rewind(fptr);
			while (!feof(fptr)) {
				fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);
				if (strcmp(p.id, salesId) == 0) {
					printf("%-15s %5s %18d %24.2lf %17s %12d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
					idFound = 1;
				}
			}
		}
		else if (searchIdValid(salesId) == 0)
		{
			printf("\nSALES ID NOT FOUND IN THE FILE\n");
		}

	} while (!idFound);

	fclose(fptr);

	wantEditAh();
}



int searchIdValid(char salesId[5]) {
	Sales p;
	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}
	while (!feof(fptr)) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);
		if (strcmp(salesId, p.id) == 0) {
			fclose(fptr);
			return 1;
		}
	}
	fclose(fptr);
	return 0;
}


// SEARCH ITEM ID AND VALIDATION.................
void searchItem() {
	Sales p;
	char itemCode[15];

	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}

	int idFound = 0;
	do {
		printf("\nPlease enter Item Code to search (a0001)  > ");
		rewind(stdin);
		gets(itemCode);

		if (searchItemValid(itemCode) == 1) {
			printf("%50s", "\n...........SEARCH RESULT...........");
			printf("\n%-15s %5s %20s %19s %17s %13s\n", "Sales Id", "Item Code", "Quantity", "Price(RM)", "Member ID", "Date");
			rewind(fptr);
			while (!feof(fptr)) {
				fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);
				if (strcmp(p.code, itemCode) == 0) {
					printf("%-15s %5s %18d %24.2lf %17s %12d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
					idFound = 1;
				}
			}
		}
		else if (searchItemValid(itemCode) == 0)
		{
			printf("\nITEM CODE NOT FOUND IN THE FILE\n");
		}

	} while (!idFound);

	fclose(fptr);

	wantEditAh();
}


int searchItemValid(char itemCode[15]) {
	Sales p;
	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}
	while (!feof(fptr)) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);
		if (strcmp(itemCode, p.code) == 0) {
			fclose(fptr);
			return 1;
		}
	}
	fclose(fptr);
	return 0;
}


// SEARCH MEMBER ID AND VALIDATION................
void searchMem() {
	Sales p;
	char memId[20];

	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}

	int idFound = 0;
	do {
		printf("\nPlease enter Member ID to search (MEM00001)  > ");
		rewind(stdin);
		gets(memId);

		if (searchMemValid(memId) == 1) {
			printf("%50s", "\n...........SEARCH RESULT...........");
			printf("\n%-15s %5s %20s %19s %17s %13s\n", "Sales Id", "Item Code", "Quantity", "Price(RM)", "Member ID", "Date");
			rewind(fptr);
			while (!feof(fptr)) {
				fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);
				if (strcmp(p.memberId, memId) == 0) {
					printf("%-15s %5s %18d %24.2lf %17s %12d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
					idFound = 1;
				}
			}
		}
		else if (searchMemValid(memId) == 0)
		{
			printf("MEMBER ID NOT FOUND IN THE FILE\n");
		}

	} while (!idFound);

	fclose(fptr);

	wantEditAh();
}

int searchMemValid(char memId[20]) {
	Sales p;
	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}
	while (!feof(fptr)) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);
		if (strcmp(memId, p.memberId) == 0) {
			fclose(fptr);
			return 1;
		}
	}
	fclose(fptr);
	return 0;
}


// MODIFY ..................................................................................................
void modify() {
	Stock s;
	Sales p[MAX];
	int line = 0;

	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}
	while (!feof(fptr) && line < MAX) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p[line].id, &p[line].code, &p[line].quantity, &p[line].price, &p[line].memberId, &p[line].date.day, &p[line].date.month, &p[line].date.year);
		line++;
	}

	fclose(fptr);

	char salesId[5];
	do {
		printf("\nPlease enter the Sales ID (S101) to get the Data > ");
		rewind(stdin);
		gets(salesId);
		if (salesModifyValid(salesId) != 1) {
			printf("\nSales Id not found in the server !!\n");
		}
	} while (salesModifyValid(salesId) != 1);

	int amount, choice;
	char item[6];
	char member[8];
	char confirm;

	for (int i = 0; i < line; i++) {
		if (strcmp(salesId, p[i].id) == 0) {
			printf("%50s", "\n\n...........DATA RETRIEVED...........");
			printf("\n%-15s %5s %20s %19s %17s %13s\n", "Sales Id", "Item Code", "Quantity", "Price(RM)", "Member ID", "Date");
			printf("%-15s %5s %18d %24.2lf %17s %12d/%d/%d\n", p[i].id, p[i].code, p[i].quantity, p[i].price, p[i].memberId, p[i].date.day, p[i].date.month, p[i].date.year);

			do {
				printf("\n......Please choose the field you want to edit.......\n");
				printf("1. Item Code \n");
				printf("2. Quantity  \n");
				printf("3. Member ID \n");
				printf("4. Return to Main Menu\n\n");
				printf("Please enter your choice >>> ");
				rewind(stdin);
				scanf("%d", &choice);

				switch (choice) {
				case 1:
					while (1) {
						do {
							printf("\nPlease enter the new Item Code (a0001) >>> ");
							rewind(stdin);
							gets(item);
							if (itemValid(item) != 1) {
								printf("\nItem Code not found in the server !! \n");
							}
						} while (itemValid(item) != 1);
						printf("Confirm Change? (y/n) : ");
						rewind(stdin);
						confirm = tolower(getchar());
						if (confirm == 'y') {
							strcpy(p[i].code, item);
							p[i].price = setPrice(p[i].code);
							break;
						}
						else if (confirm == 'n') {
							stillWantEditAh();
						}
						else {
							printf("Please enter (y/n) ONLY!!\n");
						}
					}
					break;

				case 2:
					while (2) {
						printf("\nPlease enter the new Quantity >>> ");
						rewind(stdin);
						scanf("%d", &amount);
						printf("Confirm Change? (y/n) : ");
						rewind(stdin);
						confirm = tolower(getchar());
						if (confirm == 'y') {
							p[i].quantity = amount;
							break;
						}
						else if (confirm == 'n') {
							stillWantEditAh();
						}
						else {
							printf("Please enter (y/n) ONLY!!\n");
						}
					}
					break;

				case 3:
					while (3) {
						do {
							printf("\nPlease enter the new Member ID (MEM00001) >>> ");
							rewind(stdin);
							gets(member);
							if (memberValid(member) != 1) {
								printf("\nMember Code not found in the server !!\n");
							}
						} while (memberValid(member) != 1);
						printf("Confirm Change? (y/n) : ");
						rewind(stdin);
						confirm = tolower(getchar());
						if (confirm == 'y') {
							strcpy(p[i].memberId, member);
							break;
						}
						else if (confirm == 'n') {
							stillWantEditAh();
						}
						else {
							printf("Please enter (y/n) ONLY!!\n");
						}
					}
					break;
				case 4:
					salesMain();
					break;
				default:
					printf("\nSorry Choice Unavailable :(\n");
				}
			} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
		}
	}
	FILE* fPtr = fopen(SALESFILE, "w");
	for (int i = 0; i < line; i++) {
		fprintf(fPtr, "%s|%s|%d|%.2lf|%s|%d/%d/%d\n", p[i].id, p[i].code, p[i].quantity, p[i].price, p[i].memberId, p[i].date.day, p[i].date.month, p[i].date.year);
	}
	fclose(fPtr);

	printf("\nData Changed Success !!\n");

	stillWantEditAh();
}


int salesModifyValid(char salesId[5]) {
	Sales p;
	int userinput = strlen(salesId);
	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}
	while (!feof(fptr)) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);
		if (strcmp(salesId, p.id) == 0) {
			return 1;
		}
	}
	fclose(fptr);
}


// DELETE FUNCTION............................................................................................
void deleteMenu() {
	int choice;

	do {
		printf("\nDELETE SALES RECORD >>>>\n");
		printf("1. Show Record\n");
		printf("2. Delete Record\n");
		printf("3. Return to Main Menu\n\n");
		printf("\nPlease enter your choice > ");
		rewind(stdin);
		scanf("%d", &choice);


		switch (choice) {
		case 1:
			displayDelete();
			break;
		case 2:
			deleteSales();
			break;
		case 3:
			salesMain();
			break;
		default:
			printf("\nSorry Choice Unavailable :( \n");
		}
	} while (choice != 1 && choice != 2 && choice != 3);

}


void deleteSales() {
	Sales p[MAX];
	int lines = 0;

	FILE* fptr = fopen(SALESFILE, "r");

	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}
	while (!feof(fptr) && lines < MAX) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p[lines].id, &p[lines].code, &p[lines].quantity, &p[lines].price, &p[lines].memberId, &p[lines].date.day, &p[lines].date.month, &p[lines].date.year);
		lines++;
	}

	fclose(fptr);
	char salesId[5];
	do {
		printf("\nPlease enter the Sales ID (S101) that you want to delete > ");
		rewind(stdin);
		gets(salesId);
		if (salesModifyValid(salesId) != 1) {
			printf("\nSales ID not found !!\n");
		}
	} while (salesModifyValid(salesId) != 1);

	for (int i = 0; i < lines; i++) {
		if (strcmp(salesId, p[i].id) == 0) {
			printf("%50s", "\n\n...........DATA RETRIEVED...........");
			printf("\n%-15s %5s %20s %19s %17s %13s\n", "Sales Id", "Item Code", "Quantity", "Price(RM)", "Member ID", "Date");
			printf("%-15s %5s %18d %24.2lf %17s %12d/%d/%d\n", p[i].id, p[i].code, p[i].quantity, p[i].price, p[i].memberId, p[i].date.day, p[i].date.month, p[i].date.year);
		}
	}
	FILE* fPtr;
	char yesnos;
	char yesno1, yesno2;
	int y;
	do {
		printf("\nDo you confirm you want to delete?\n");
		printf("y = yes , n = no > ");
		rewind(stdin);
		yesnos = tolower(getchar());
		switch (yesnos) {
		case 'y':
			fPtr = fopen(SALESFILE, "w");
			for (int k = 0; k < lines; k++) {
				if (strcmp(salesId, p[k].id) == 0) {
					y = 0;
				}
				else {
					fprintf(fPtr, "%s|%s|%d|%.2lf|%s|%d/%d/%d\n", p[k].id, p[k].code, p[k].quantity, p[k].price, p[k].memberId, p[k].date.day, p[k].date.month, p[k].date.year);
				}
			}
			printf("\nSales Record Deleted !!\n");
			fclose(fPtr);
			break;
		case 'n':
			do {
				printf("\nDo you want to back to Delete Menu ?\n");
				printf("y = yes, n = no >  ");
				rewind(stdin);
				yesno1 = tolower(getchar());
				switch (yesno1) {
				case 'y':
					deleteMenu();
					break;
				case 'n':
					backMenuAh();
					break;
				default:
					printf("Please enter (y/n) ONLY!!\n");
				}
			} while (yesno1 != 'y' && yesno1 != 'n');
			break;
		default:
			printf("Please enter (y/n) ONLY!!\n");
		}
	} while (yesnos != 'y' && yesnos != 'n');

	char choose;
	do {
		printf("\nDo you still want continue to delete?\n");
		printf("y = yes , n = no > ");
		rewind(stdin);
		choose = tolower(getchar());
		switch (choose) {
		case 'y':
			deleteSales();
			break;
		case 'n':
			backMenuAh();

		}

	} while (choose != 'y' && choose != 'n');
}


void displayDelete() {
	Sales p;
	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}

	printf("%-15s %5s %20s %19s %17s %13s\n", "Sales Id", "Item Code", "Quantity", "Price(RM)", "Member ID", "Date");
	printf("-------------------------------------------------------------------------------------------------------\n");
	while (!feof(fptr)) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);
		printf("%-15s %5s %18d %24.2lf %17s %12d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
	}
	fclose(fptr);

	char yesno;
	do {
		printf("\nDo you want to Delete any Data?\n");
		printf("y = yes , n = no > ");
		rewind(stdin);
		yesno = tolower(getchar());
		switch (yesno) {
		case 'y':
			deleteSales();
			break;
		case 'n':
			backMenuAh();
			break;
		default:
			printf("Please enter (y/n) ONLY!!\n");
		}
	} while (yesno != 'y' && yesno != 'n');
}

// REPORT ..................................................................................................

void reportSales() {
	Sales p;
	int line = totalSales();
	double total = totalRevenue();

	FILE* fptr = fopen(SALESFILE, "r");
	printf("__________________________________________________SALES REPORT__________________________________________________________\n\n");
	printf("%-15s %5s %20s %19s %17s %13s %20s\n", "Sales Id", "Item Code", "Quantity", "Price(RM)", "Member ID", "Date", "Revenue");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	while (!feof(fptr)) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);
		printf("%-15s %5s %18d %24.2lf %17s %12d/%d/%d", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
		revenue(p.quantity, p.price);
	}
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%104s = %12.2lf\n", "Total Revenue", total);
	printf("%102s   = %9d\n", "Total Sales", line);

	printf("\n\n\n");
	backMenuAh();
}

int totalSales() {
	Sales p;
	int line = 0;

	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}

	while (!feof(fptr)) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p.id, &p.code, &p.quantity, &p.price, &p.memberId, &p.date.day, &p.date.month, &p.date.year);

		line++;
	}
	fclose(fptr);
	return line;
}

double totalRevenue() {
	Sales p[MAX];
	int line = 0;
	double revenue = 0;
	double total = 0;

	FILE* fptr = fopen(SALESFILE, "r");
	if (fptr == NULL) {
		printf("FILE NOT FOUND !!\n");
		return;
	}
	while (!feof(fptr) && line < MAX) {
		fscanf(fptr, "%[^|]|%[^|]|%d|%lf|%[^|]|%d/%d/%d\n", &p[line].id, &p[line].code, &p[line].quantity, &p[line].price, &p[line].memberId, &p[line].date.day, &p[line].date.month, &p[line].date.year);
		line++;
	}
	for (int i = 0; i < line; i++) {
		revenue = p[i].quantity * p[i].price;
		total += revenue;
	}
	fclose(fptr);

	return total;
}


void revenue(int quantities, double prices) {
	double revenue = 0;
	revenue = quantities * prices;
	printf(" %15.2lf\n", revenue);
}

//DATE FUNCTION................................................................................................
void set_today_date(Date* date) {
	time_t current_time;
	struct tm* local_time;

	time(&current_time);
	local_time = localtime(&current_time);

	date->day = local_time->tm_mday;
	date->month = local_time->tm_mon + 1;
	date->year = local_time->tm_year + 1900;
}

//LAZY FUNCTION.................................................................................................

void backMenuAh() {
	char yesno2;
	do {
		printf("\nDo you want to back to Sales Menu ?\n");
		printf("y = yes, n = no >  ");
		rewind(stdin);
		yesno2 = tolower(getchar());
		switch (yesno2) {
		case 'y':
			salesMain();
			break;
		case 'n':
			return;
			break;
		default:
			printf("Please enter (y/n) ONLY!!\n");
		}
	} while (yesno2 != 'y' && yesno2 != 'n');
}

void wantEditAh() {
	char yesno;
	do {
		printf("\nDo you want to Edit the Data?\n");
		printf("y = yes , n = no > ");
		rewind(stdin);
		yesno = tolower(getchar());
		switch (yesno) {
		case 'y':
			modify();
			break;
		case 'n':
			backMenuAh();
			break;
		default:
			printf("Please enter (y/n) ONLY!!\n");
		}
	} while (yesno != 'y' && yesno != 'n');
}

void stillWantEditAh() {
	char yesnos;
	do {
		printf("\nDo you still want to Edit the Data ?\n");
		printf("y = yes , n = no > ");
		rewind(stdin);
		yesnos = tolower(getchar());
		switch (yesnos) {
		case 'y':
			modify();
			break;
		case 'n':
			backMenuAh();
			break;
		default:
			printf("Please enter (y/n) ONLY!!\n");
		}
	} while (yesnos != 'y' && yesnos != 'n');

}

//Jerome Lu Zheng Yao
int staffMain() {
	struct Staff staffList[MAX_STAFF];
	int numStaff = 0;
	int choice;

	printf("=== YY Company Staff Information System ===\n");

	while (1) {
		printf("\nMenu:\n");
		printf("1. Add Staff\n");
		printf("2. Display Staff\n");
		printf("3. Generate Report\n");
		printf("4. Edit Staff Information\n");
		printf("5. Check Password Account\n");
		printf("6. Search Staff\n");
		printf("7. Exit\n");
		printf("Enter your choice (1-7): ");

		// Input validation
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 7) {
			printf("Invalid choice, please enter a number between 1 and 7: ");
			fflush(stdin);
		}

		fflush(stdin);

		switch (choice) {
		case 1:
			addStaff(staffList, &numStaff);
			break;
		case 2:
			displayStaff(staffList, numStaff);
			break;
		case 3:
			generateReport(staffList, numStaff);
			break;
		case 4:
			editStaff(staffList, numStaff);
			break;
		case 5:
			checkPassword(staffList, numStaff);
			break;
		case 6:
			searchStaff(staffList, numStaff);
			break;
		case 7:
			printf("Exiting program.\n");
			return;
			break;
		default:
			printf("Invalid choice, please try again.\n");
		}
	}

	return 0;
}




void addStaff(struct Staff staffList[], int* numStaff) {
	struct Staff newStaff;

	FILE* fp = fopen("stafftxt.txt", "a");
	printf("Enter id : ");
	scanf("%s", newStaff.id);

	// Check if ID already exists
	for (int i = 0; i < *numStaff; i++) {
		if (strcmp(staffList[i].id, newStaff.id) == 0) {
			printf("Error: Staff ID already exists.\n");
			return;
		}
	}
	fflush(stdin);

	printf("Enter Staff Name: ");
	scanf(" %[^\n]", newStaff.name);

	if (strcmp(newStaff.name, "xx") == 0) {
		return;
	}
	fflush(stdin);

	printf("Enter Password: ");
	scanf("%s", newStaff.password);
	fflush(stdin);


	printf("Enter Recovery Email: ");
	scanf("%s", newStaff.recovery);
	fflush(stdin);

	printf("Enter Position: ");
	scanf("%s", newStaff.position);
	fflush(stdin);


	printf("Enter Role: ");
	scanf("%s", newStaff.role);
	fflush(stdin);

	printf("%-10s %-20s %-20s %-20s %-20s %-20s\n", "ID", "Name", "Position", "Role", "Recovery Email", "Password");

	staffList[*numStaff] = newStaff;
	(*numStaff)++;


	for (int i = 0; i < *numStaff; i++) {
		fprintf(fp, "%s %s %s %s %s %s\n", staffList[i].id, staffList[i].name, staffList[i].position, staffList[i].role, staffList[i].recovery, staffList[i].password);
	}
	fclose(fp);
}

void displayStaff(struct Staff staffList[], int numStaff) {
	FILE* fp = fopen("stafftxt.txt", "r");
	printf("=== Staff List ===\n");

	if (fp == NULL) {
		printf("Error: Unable to open file.\n");
		return;
	}

	printf("%-10s %-20s %-20s %-20s %-20s\n", "ID", "Name", "Position", "Role", "Recovery Email");

	char line[100];
	while (fgets(line, sizeof(line), fp) != NULL) {
		char id[7], name[50], password[20], recovery[20], position[20], role[20];
		sscanf(line, "%s %s %s %s %s\n", id, name, position, role, recovery);
		printf("%-10s %-20s %-20s %-20s %-20s\n", id, name, position, role, recovery);
	}

	fclose(fp);
}

void generateReport(struct Staff staffList[], int numStaff) {
	FILE* fp = fopen("stafftxt.txt", "r");
	printf("==================================== Staff Report ====================================\n");

	if (fp == NULL) {
		printf("Error: Unable to open file.\n");
		return;
	}

	printf("+------+----------------------+----------------------+----------------------+----------------------+\n");
	printf("| %-4s | %-20s | %-20s | %-20s | %-20s |\n", "ID", "Name", "Position", "Role", "Recovery Email");
	printf("+------+----------------------+----------------------+----------------------+----------------------+\n");

	char line[100];
	while (fgets(line, sizeof(line), fp) != NULL) {
		char id[7], name[50], password[20], recovery[20], position[20], role[20];
		sscanf(line, "%s %s %s %s %s\n", id, name, position, role, recovery);
		printf("| %-4s | %-20s | %-20s | %-20s | %-20s |\n", id, name, position, role, recovery);
		printf("+------+----------------------+----------------------+----------------------+----------------------+\n");
	}

	fclose(fp);
	return;
}



void editStaff(struct Staff staffList[], int numStaff) {
	char id[7], name[21];
	int index = -1, choice, i = 0;

	printf("=== Edit Staff Information ===\n");

	printf("Enter Staff ID to edit: ");
	scanf("%s", id);

	FILE* fp = fopen("stafftxt.txt", "r");
	FILE* temp_fp = fopen("temp.txt", "w");

	if (fp == NULL || temp_fp == NULL) {
		printf("Error: Unable to open file.\n");
		return;
	}

	while (fscanf(fp, "%s %s %s %s %s\n", staffList[i].id, staffList[i].name, staffList[i].position, staffList[i].role, staffList[i].recovery) != EOF) {
		if (strcmp(staffList[i].id, id) == 0) {
			index = i;
			printf("\nWhat do you want to change?");
			printf("\n1. Name");
			printf("\n2. Password");
			printf("\n3. Recovery Email");
			printf("\n4. Position");
			printf("\n5. Role");
			printf("\n6. Exit");
			printf("\nEnter your choice: ");
			scanf("%d", &choice);
			if (choice == 1) {
				printf("Enter new Staff Name: ");
				scanf(" %[^\n]", name);
				strcpy(staffList[index].name, name);
			}
			else if (choice == 2) {
				printf("Enter new Password (current password is hidden): ");
				scanf("%s", staffList[index].password);
			}
			else if (choice == 3) {
				printf("Enter new Recovery Email (current recovery email is %s): ", staffList[index].recovery);
				scanf("%s", staffList[index].recovery);
			}
			else if (choice == 4) {
				printf("Enter new Position (current position is %s): ", staffList[index].position);
				scanf("%s", staffList[index].position);
			}
			else if (choice == 5) {
				printf("Enter new Role (current role is %s): ", staffList[index].role);
				scanf("%s", staffList[index].role);
			}
			else {
				fclose(fp);
				fclose(temp_fp);
				return;
			}
		}
		fprintf(temp_fp, "%s %s %s %s %s %s\n", staffList[i].id, staffList[i].name, staffList[i].password, staffList[i].position, staffList[i].role, staffList[i].recovery);
		i++;
	}

	fclose(fp);
	fclose(temp_fp);

	if (index == -1) {
		remove("temp.txt");
		printf("Error: Staff ID not found.\n");
	}
	else {
		remove("stafftxt.txt");
		rename("temp.txt", "stafftxt.txt");
		printf("Staff information updated successfully!\n");
	}
	return;
}

void checkPassword(struct Staff staffList[], int numStaff) {
	char id[7], recovery[20];

	printf("Enter ID: ");
	scanf("%s", id);
	printf("Enter recovery email: ");
	scanf("%s", recovery);

	FILE* fp = fopen("stafftxt.txt", "r");
	if (fp == NULL) {
		printf("Error: Unable to open file.\n");
		return;
	}

	char line[100];
	while (fgets(line, sizeof(line), fp) != NULL) {
		char file_id[7], name[50], password[20], file_recovery[20], position[20], role[20];
		sscanf(line, "%s %s %s %s %s %s\n", file_id, name, position, role, file_recovery, password);
		if (strcmp(file_id, id) == 0 && strcmp(file_recovery, recovery) == 0) {
			printf("Password: %s\n", password);
			fclose(fp);
			return;
		}
	}

	fclose(fp);
	printf("No staff member found with the given ID and recovery email.\n");
}

void searchStaff(struct Staff staffList[], int numStaff) {

	char searchId[7];
	int found = 0;

	printf("Enter staff ID to search: ");
	scanf("%s", searchId);

	FILE* fp = fopen("stafftxt.txt", "r");
	if (fp == NULL) {
		printf("Error: Unable to open file.\n");
		return;
	}

	printf("=== Search Results ===\n");
	printf("%-10s %-20s %-20s %-20s %-20s\n", "ID", "Name", "Position", "Role", "Recovery Email");

	char line[100];
	while (fgets(line, sizeof(line), fp) != NULL) {
		char id[7], name[50], password[20], recovery[20], position[20], role[20];
		sscanf(line, "%s %s %s %s %s\n", id, name, position, role, recovery);
		if (strcmp(id, searchId) == 0) {
			printf("%-10s %-20s %-20s %-20s %-20s\n", id, name, position, role, recovery);
			found = 1;
			break;
		}
	}

	if (!found) {
		printf("Staff ID '%s' not found.\n", searchId);
	}

	fclose(fp);

}

//Oon Xiang Yu
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
	if (isalpha(code[0]) && isdigit(code[1]) && isdigit(code[2]) && isdigit(code[3]) && isdigit(code[4]) && (strlen(code) == 5)) {
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
	printf("\n%10s  %20s  %10s  %10s  %10s  %10s  %10s  %15s\n", "STOCK CODE", "STOCK NAME", "QUANTITY", "MINIMUM", "REORDER", "PRICE", "DATE", "STATUS");
	printf("%10s  %20s  %10s  %10s  %10s  %10s  %10s  %15s\n", "==========", "====================", "==========", "==========", "==========", "==========", "==========", "===============");
};

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
	printf("%10s  %20s  %10d  %10d  %10d  %10.2lf  %02d/%02d/%04d  %15s\n", s[a].stockCode, s[a].stockName, s[a].stockQuantity, s[a].stockMinimum, s[a].stockReorder, s[a].stockPrice, s[a].d.day, s[a].d.month, s[a].d.year, s[a].status);
}

//Main function
void stockMain() {
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
		printf("  %5s  %2s%s%2s  %5s  %5s  %s%3s%s\n", "=====", "", "=", "", "=====", "=====", "=", "", "=");

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
			scanf("%lf", &price);
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
			if (validDate(s.d.day, s.d.month, s.d.year) == 1) { //validation
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

	char  nname[20], code[6], yesno;
	int day, month, year, min, reorder, option, size, con = 0, a = 0, b = 0;
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
		if (strcmp(code, "stop") == 0) { //if user type stop then function will exit
			return;
		}
		else if (validFormat(code) == 1) { //valid format
			for (int i = 0; i < size; i++) {
				if (strcmp(code, s[i].stockCode) == 0) { //compare code
					con = 0;
					if (strcmp(s[i].status, "avaliable") == 0) { //compare status
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
										scanf("%d", &min);
										if (validNumber(min) == 1) { //validation
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
										scanf("%d", &reorder);
										if (validNumber(reorder) == 1) { //validation
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
					else {
						printf("\nOnly stock that is avaliable allow to modify\n");
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
	} while (con != 0 || a != 0 || validFormat(code) == 2); //loop
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
		else if (validFormat(code) == 1) {
			for (int i = 0; i < size; i++) {
				if (strcmp(code, s[i].stockCode) == 0) {
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
									printf("\n1. avaliable\n");
									printf("2. unavaliable\n");
									printf("Please update the new status >");
									rewind(stdin);
									scanf("%d", &select);
									if (select == 1) {
										strcpy(status, "avaliable");
										printf("\nStatus change\n");
									}
									else if (select == 2) {
										strcpy(status, "unavaliable");
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
											quantity += s[i].stockReorder;
											printf("Are you confirm to reorder (y/n) >");
											rewind(stdin);
											yesno = tolower(getchar());
											if (yesno == 'y') {
												s[i].stockQuantity = quantity;
												printf("Reorder success\n");
												FILE* wptr = fopen(FILE_NAME, "wb");
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
												if (scanf("%d", &decrease) != 1) {
													printf("\nAlphabet and Symbol are not allow\n");
												}
												else if (validNumber(decrease) == 2) {
													printf("\nQuantity must greater than 0\n");
												}
												else if (validNumber(decrease) == 3) {
													printf("\nValid answer\n");
												}
											} while (validNumber(decrease) != 3);

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
														FILE* wptr = fopen(FILE_NAME, "wb");
														fwrite(&s, sizeof(Stock), size, wptr);
														fclose(wptr);
													}
												}
												else if (yesno == 'n') {
													printf("Quantity no changes\n");
												}
											} while (yesno != 'y' && yesno != 'n');
											break;
										case 3:
											return;
											break;
										}
									}
									else {
										printf("\nInvalid answer\n");
									}
								} while (chose != 3);
							case 3:
								return;
								break;
							}
						}
						else {
							printf("\nInvalid answer\n");
						}
					} while (option != 3);
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
			b++;
		}
	} while (con != 0 || b != 0);
}

void reportStock(Stock s[], int size) {
	time_t t = time(NULL);
	struct tm* local_time = localtime(&t);
	char timeStr[100];

	printf("\n%38s%30s\n", "", "==============================");
	printf("%38s%-2s%10s%6s%10s%2s\n", "", "||", "", "REPORT", "", "||");
	printf("%38s%30s\n", "", "==============================");

	printf("\n%48s%8s\n", "", "LowStock");
	printf("-------------------------------------------------------------------------------------------------------------");
	title();
	for (int i = 0; i < size; i++) {
		if (s[i].stockQuantity < s[i].stockMinimum) {
			displayStock(s, i);
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");

	printf("\n%50s%5s\n", "", "Stock");
	printf("-------------------------------------------------------------------------------------------------------------");
	title();
	for (int i = 0; i < size; i++) {
		if (s[i].stockQuantity >= s[i].stockMinimum) {
			displayStock(s, i);
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");

	printf("\n%47s%11s\n", "", "Unavaliable");
	printf("-------------------------------------------------------------------------------------------------------------");
	title();
	for (int i = 0; i < size; i++) {
		if (strcmp(s[i].status, "unavaliable") == 0) {
			displayStock(s, i);
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");

	printf("\n%48s%9s\n", "", "Avaliable");
	printf("-------------------------------------------------------------------------------------------------------------");
	title();
	for (int i = 0; i < size; i++) {
		if (strcmp(s[i].status, "avaliable") == 0) {
			displayStock(s, i);
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");

	printf("\n%42s%18s\n", "", "Status havent update");
	printf("-------------------------------------------------------------------------------------------------------------");
	title();
	for (int i = 0; i < size; i++) {
		if (strcmp(s[i].status, "-") == 0) {
			displayStock(s, i);
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");

	printf("\nTotal Stock Record = %d\n", size);

	strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", local_time);
	printf("\nReport generate at %s\n", timeStr);
}