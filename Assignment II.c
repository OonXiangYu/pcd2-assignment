#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#pragma warning(disable:4996)
#define MAX_MEMBER 10000

/*
Member module
- addMember
- searchMember
- modifyMember
- displayMember
- renewMembership
- ResetPassword
*/

// Structures declaration
struct membershipDate {
	int day, month, year;
};

typedef struct {
	char name[31], id[9], gender, password[31], membershipType;
	struct membershipDate mExpiryDate;
}Member;

// Functions declaration
void addMember();
void searchMember();
void modifyMember();
void displayMember();
void renewMembership();
void resetPassword();

// Main Function
void main() {
	int selection;

	do {
		printf("Member Module\n");
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
				printf("Thank you for using our service, have a nice day!");
				Sleep(3000);
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
	printf("%30s %9s %6s %16s %22s\n", "Member Name", "Member ID", "Gender", "Membership Type", "Membership Expiry date");
	printf("%30s %9s %6s %16s %22s\n", "------------------------------", "---------", "------", "---------------", "----------------------");
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