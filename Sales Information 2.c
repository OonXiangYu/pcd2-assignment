#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#pragma warning(disable:4996)
#define SALESFILE "Sales.txt"
#define MAX 1000

// STRUCTURE .................................................................................................................................
typedef struct {
	int day;
	int month;
	int year;
}Date;

struct membershipDate {
	int day, month, year;
};

typedef struct {
	char id[8];
}Member;

typedef struct {
	char stockCode[6];
	double stockPrice;
}Stock;

typedef struct {
	char id[5], code[6], memberId[8];
	int quantity;
	double price;
	Date date;
}Sales;

// FUNCTIONS ..................................................................................................................................
void salesMain();

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

// VOID MAIN...................................................................................................................................
void main() {
	salesMain();
}
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
			exit(0);
		default:
			printf("\bSorry Choice Unavailable :(\n");
		}
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7);
}


// ADD SALES AND VALIDATION FUNCTION............................................................................................................
void addSales(){
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

		fprintf(fptr, "%s|%s|%d|%.2lf|%s|%d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId,p.date.day,p.date.month,p.date.year);
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
		if(strcmp(itemCode, s.stockCode)==0){
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
		printf("%-15s %5s %18d %21.2lf %20s %12d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
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
					printf("%-15s %5s %18d %21.2lf %20s %12d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
					idFound = 1;
				}
			}
		}
		else if(searchIdValid(salesId)==0)
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
					printf("%-15s %5s %18d %21.2lf %20s %12d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
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
					printf("%-15s %5s %18d %21.2lf %20s %12d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
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
			printf("%-15s %5s %18d %21.2lf %20s %12d/%d/%d\n", p[i].id, p[i].code, p[i].quantity, p[i].price, p[i].memberId, p[i].date.day, p[i].date.month, p[i].date.year);

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
							if (itemValid(item)!= 1) {
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
			}while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
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
			printf("%-15s %5s %18d %21.2lf %20s %12d/%d/%d\n", p[i].id, p[i].code, p[i].quantity, p[i].price, p[i].memberId, p[i].date.day, p[i].date.month, p[i].date.year);
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
		printf("%-15s %5s %18d %21.2lf %20s %12d/%d/%d\n", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
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
		printf("%-15s %5s %18d %21.2lf %20s %12d/%d/%d", p.id, p.code, p.quantity, p.price, p.memberId, p.date.day, p.date.month, p.date.year);
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
		printf("\nDo you want to back to Main Menu ?\n");
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
