#include "staff.h"

void printStaffInfo(staffInfo staff)
{
    printf("\n\n\t\t\t.---------------------------------------------------------.\n");
    printf("\t\t\t|                                                         |\n", staff.staffID);
    printf("\t\t\t|  Staff ID     :%3d                                      |\n", staff.staffID);
    printf("\t\t\t|  Staff Name   : %-40s|\n", staff.staffName);
    printf("\t\t\t|                                                         |\n", staff.staffID);
    printf("\t\t\t|  Position     : %-32s        |\n", staff.position);
    printf("\t\t\t|  Faculty      : %-36s    |\n", staff.faculty);
    printf("\t\t\t|                                                         |\n", staff.staffID);
    printf("\t\t\t|  Password     : %-32s        |\n", staff.password);
    printf("\t\t\t|  Phone Number : %-11s                             |\n", staff.phoneNo);
    printf("\t\t\t|                                                         |\n", staff.staffID);
    printf("\t\t\t|  Gender       : %c                                       |\n", staff.gender);
    printf("\t\t\t|  Login Name   : %-32s        |\n", staff.loginName);
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t'---------------------------------------------------------'\n\n\n\n");
}

void addStaffRecord(staffInfo* staffArr, int* index, int* maxSize, staffMetaData* md)
{
    (md->numAdd)++;

    char ans = 'Y';
    staffInfo staffData;

    while (toupper(ans) == 'Y') {
        if (*index == maxSize) // resize array if needed
        {
            void* temp = realloc(staffArr, (*index + 10) * sizeof(staffInfo));
            if (!temp)
            {
                free(temp);
                temp = NULL;
                printf("\t\t\t      Error with adding staff record. Please save the data and try again.\n");
                return;
            }
            staffArr = temp;
            *maxSize = *index + 10;
        }

        if (*index == 0)
            staffData.staffID = 1;
        else
            staffData.staffID = staffArr[*index - 1].staffID + 1;
        rewind(stdin);
        printf("\n\n\t\t\t Please enter staff name: ");
        fgets(staffData.staffName, BUFFER_SIZE, stdin); rewind(stdin);
        staffData.staffName[strcspn(staffData.staffName, "\n")] = 0;

        printf("\n\t\t\t Please enter staff position: ");
        scanf("%s", &staffData.position); rewind(stdin);

        printf("\n\t\t\t Please enter faculty: ");
        fgets(&staffData.faculty, BUFFER_SIZE, stdin); rewind(stdin);
        staffData.faculty[strcspn(staffData.faculty, "\n")] = 0;
        printf("\n\t\t\t ________________________________________________");

        printf("\n\n\t\t\t Please enter staff login name: ");
        scanf("%s", &staffData.loginName); rewind(stdin);

        printf("\n\t\t\t Please enter password: ");
        scanf("%s", &staffData.password); rewind(stdin);

        printf("\n\t\t\t Please enter phone number: ");
        scanf("%s", &staffData.phoneNo); rewind(stdin);

        printf("\n\t\t\t Please enter gender (M or F): ");
        scanf("%c", &staffData.gender); rewind(stdin);

        while (toupper(staffData.gender) != 'M' && toupper(staffData.gender) != 'F')
        {
            printf("\n\t\t\t      Invalid input. Please enter again: ");
            scanf("%c", &staffData.gender); rewind(stdin);
        }

        staffArr[(*index)++] = staffData;
        printf("\n\t\t\t.-------------------------.\n");
        printf("\t\t\t|  Your staff ID is : %2d  |\n", staffData.staffID);
        printf("\t\t\t'-------------------------'\n");
        printf("\n\t\t\t ________________________________________________");
        printf("\n\n\t\t\t    More record (Y or N) >> ");
        scanf("%c", &ans);
        rewind(stdin);
    }
    system("pause");
    system("cls");
}

void showStaffRecord(staffInfo* staffArr, int size)
{
    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return;
    }
    int index = 0;
    while (index < size)
    {
        printStaffInfo(staffArr[index]);

        index++;
    }
    system("pause");
    system("cls");
}

// loop through the array and find the record
// returns staffInfo with stuffID -1 if not found
staffInfo findStaffRecord(staffInfo* staffArr, int size, int searchID)
{
    staffInfo temp;
    temp.staffID = -1; // value if not found 

    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return temp;
    }

    int min = 0, max = size - 1, mid;

    while (min <= max)                        //data need to be sorted
    {
        mid = (max + min) / 2;
        if (staffArr[mid].staffID == searchID)
            return staffArr[mid];

        if (staffArr[mid].staffID > searchID)
            max = mid - 1;

        if (staffArr[mid].staffID < searchID)
            min = mid + 1;
    }
    return temp;
}

// performs findRecord and displays the result if found 
void searchStaffRecord(staffInfo* staffArr, int size)
{
    int searchID;
    printf("\n\n\t\t\t   Enter staff ID to search: ");
    scanf("%d", &searchID);

    staffInfo temp = findStaffRecord(staffArr, size, searchID);

    if (temp.staffID == -1)
    {
        printf("\n\t\t\t.--------------------------------------.\n");
        printf("\t\t\t|   No record found for record No.%2d   |\n", searchID);
        printf("\t\t\t'--------------------------------------'\n\n");
        return;
    }

    printStaffInfo(temp);
    system("pause");
    system("cls");
}

void modifyStaffRecord(staffInfo* staffArr, int size, staffMetaData* md)
{
    (md->numModify)++;
    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return;
    }
    int usrInput;
    printf("\t\t\t ______________________________________________________________________\n");
    printf("\t\t\t|              |                  |                                    |\n");
    printf("\t\t\t|    Staff     |       Staff      |               Staff                |\n");
    printf("\t\t\t|  Record No.  |        ID.       |               Name.                |\n");
    printf("\t\t\t|______________|__________________|____________________________________|\n");

    for (int index = 0; index < size; index++)
    {
        printf("\t\t\t|              |                  |                                    |\n");
        printf("\t\t\t|      %2d      |       %3d        |     %-30s |\n", index + 1, staffArr[index].staffID, staffArr[index].staffName); //not sure what to print
        printf("\t\t\t|______________|__________________|____________________________________|\n");
    }
    printf("\n\t\t\t Select record number to modify : ");
    scanf("%d", &usrInput);
    rewind(stdin);

    while (usrInput > size)
    {
        printf("\n\t\t\t'```````````````````````````````````````````````````````````````````````'\n");
        printf("\t\t\t'      Record number not found. Please choose number shown in above.    '\n");
        printf("\t\t\t'                                                                       '\n");
        printf("\t\t\t`````````````````````````````````````````````````````````````````````````\n\n");

        printf("\t\t\t Select record number to modify : ");
        scanf("%d", &usrInput);
        rewind(stdin);
    }
    usrInput--;
    system("cls");

    printf("\n\n\t\t\t Please enter staff name: ");
    fgets(&staffArr[usrInput].staffName, BUFFER_SIZE, stdin); rewind(stdin);
    staffArr[usrInput].staffName[strcspn(staffArr[usrInput].staffName, "\n")] = 0;

    printf("\n\t\t\t Please enter staff position: ");
    scanf("%s", &staffArr[usrInput].position); rewind(stdin);

    printf("\n\t\t\t Please enter faculty: ");
    fgets(&staffArr[usrInput].faculty, BUFFER_SIZE, stdin); rewind(stdin);
    staffArr[usrInput].faculty[strcspn(staffArr[usrInput].faculty, "\n")] = 0;
    printf("\n\t\t\t ________________________________________________");

    printf("\n\n\t\t\t Please enter staff login name: ");
    scanf("%s", &staffArr[usrInput].loginName); rewind(stdin);

    printf("\n\t\t\t Please enter password: ");
    scanf("%s", &staffArr[usrInput].password); rewind(stdin);

    printf("\n\t\t\t Please enter phone number: ");
    scanf("%s", &staffArr[usrInput].phoneNo); rewind(stdin);

    printf("\n\t\t\t Please enter gender (M or F): ");
    scanf("%c", &staffArr[usrInput].gender); rewind(stdin);

    while (toupper(staffArr[usrInput].gender) != 'M' && toupper(staffArr[usrInput].gender) != 'F')
    {
        printf("\n\t\t\t      Invalid input. Please enter again: ");
        scanf("%c", &staffArr[usrInput].gender); rewind(stdin);
    }
    printf("\n\t\t\t.---------------------.\n");
    printf("\t\t\t|    Data updated!    |\n");
    printf("\t\t\t'---------------------'\n");
    printf("\n\t\t\t ________________________________________________\n\n");

    system("pause");
    system("cls");
}

staffInfo* readStaffData(int* size)
{
    FILE* fp;
    fp = fopen("./Files/Staff.dat", "rb");

    if (fp == NULL) {
        fp = fopen("./Files/Staff.dat", "wb");
        fclose(fp);
        *size = 0;
        staffInfo* ok = malloc(10 * sizeof(staffInfo)); // allocate extra 10 slots for new data
        return ok;
    }

    fseek(fp, 0, SEEK_END);
    int lSize = ftell(fp);
    rewind(fp);
    *size = lSize / sizeof(staffInfo);
    staffInfo* ok = malloc(10 * sizeof(staffInfo) + lSize); // allocate extra 10 slots for new data
    int i = 0;
    while (fread(&ok[i++], sizeof(staffInfo), 1, fp) == 1);
    fclose(fp);
    return ok;
}

void writeStaffData(staffInfo* staffArr, int size)
{
    FILE* fp;
    fp = fopen("./Files/Staff.dat", "wb");
    for (int i = 0; i < size; i++)
    {
        fwrite(&staffArr[i], sizeof(staffInfo), 1, fp);
    }
    fclose(fp);
}

void deleteStaffData(staffInfo* staffArr, int* size, staffMetaData* md)
{
    (md->numDelete)++;
    int staffID;
    printf("\n\t\t\t   Enter staff ID to delete: ");
    scanf("%d", &staffID);

    if (findStaffRecord(staffArr, *size, staffID).staffID == -1)
    {
        printf("\n");
        printf("\t\t\t    .--------------------------------.\n");
        printf("\t\t\t    |  Target data not in database!  |\n");
        printf("\t\t\t    '--------------------------------'\n\n");
        return;
    }

    for (int i = staffID - 1; i + 1 < *size; i++)
    {
        staffArr[i] = staffArr[i + 1];
    }
    (*size)--;
}

void reportStaff(staffMetaData* md)
{
    printf("\n\n\t\t\t ________________________________________________\n");
    printf("\t\t\t|                                        |       |\n");
    printf("\t\t\t|    Number of visitor records added     |  %2d   |\n", (md->numAdd));
    printf("\t\t\t|________________________________________|_______|\n");
    printf("\t\t\t|                                        |       |\n");
    printf("\t\t\t|    Number of visitor records modified  |  %2d   |\n", (md->numModify));
    printf("\t\t\t|________________________________________|_______|\n");
    printf("\t\t\t|                                        |       |\n");
    printf("\t\t\t|    Number of visitor records deleted   |  %2d   |\n", (md->numDelete));
    printf("\t\t\t|________________________________________|_______|\n");
}

void staff(staffInfo* staffArr, int* size, int* maxSize, staffMetaData* md)
{
    int usrInput = 0;
    do {
        printf("\n\n\n");
        printf("\n\t\t\t     +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
        printf("\t\t\t     !         Staff Module        !\n");
        printf("\t\t\t     +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n\n");
        printf("\t\t\t.---------------------------------------.\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [1]  Add new record              |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [2]  Search record               |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [3]  Modify records              |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [4]  Show all records            |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [5]  Delete record               |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [6]  Reports                     |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [7]  Back to Main Menu           |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t'---------------------------------------'\n");
        printf("\n\t\t\t Enter your choice :  ");
        scanf("%d", &usrInput);

        if (usrInput == 1) {
            system("cls");
            addStaffRecord(staffArr, size, maxSize, md);
        }
        else if (usrInput == 2) {
            system("cls");
            searchStaffRecord(staffArr, *(size));
        }
        else if (usrInput == 3) {
            system("cls");
            modifyStaffRecord(staffArr, *(size), md);
        }
        else if (usrInput == 4) {
            system("cls");
            showStaffRecord(staffArr, *(size));
        }
        else if (usrInput == 5) {
            system("cls");
            deleteStaffData(staffArr, (size), md);
        }
        else if (usrInput == 6) {
            system("cls");
            reportStaff(md);
        }
        else if (usrInput == 7)
        {
            printf("\n\n\n");
            system("pause");
            system("cls");
            printf("\n\n\t\t_____________________________________\n\n");
            printf("\t\t      Returning to main menu...\n");
            printf("\t\t_____________________________________\n\n\n\n\n");
            system("pause");
            system("cls");
            return;
        }
        else {
            system("cls");
            printf("\n\n\t\t==============================================================\n\n");
            printf("\t\t    Invalid choice! Please enter the NUMBER shown in menu.    \n\n");
            printf("\t\t==============================================================\n\n\n\n");
            system("pause");
            system("cls");
        }
    } while (usrInput != 7);
}