#include "visitnexit.h"

void printVisitExitInfo(visitExitInfo vne, venueInfo venueTemp)
{
    printf("\n\n\t\t\t.---------------------------------------------------------.\n");
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t|   Visit date : %02d/%02d/%04d    Visit time : %02d:%02d:%02d      |\n", xd.day, xd.month, xd.year, xD.hour, xD.minit, xD.second);
    printf("\t\t\t|   Exit date  : %02d/%02d/%04d    Exit time  : %02d:%02d:%02d      |\n", xd.day, xd.month, xd.year, xD.hour, xD.minit, xD.second);
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t|   Venue ID   : %3d                                      |\n", vne.venueID);
    if (vne.venueID == -1)
        printf("\t\t\t|  Warning: Venue record not entered.                         |\n");
    else
        printf("\t\t\t|   Venue Name : %-25s                |\n", venueTemp.venueName);
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t|   Visitor IC  : %-12s                            |\n", vne.visitorIC);
    printf("\t\t\t|   Temperature : %2.2f                                   |\n", vne.temp);
    printf("\t\t\t|   Reason of visit  : %-15s                    |\n", vne.visitReason);
    printf("\t\t\t|   Health condition : %-17s                  |\n", vne.healthCon);
    printf("\t\t\t|   Number of person with visitor :%2d                     |\n", vne.noPerson);
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t'---------------------------------------------------------'\n\n\n\n");

}

// adds a new visit/exit record
// returns the visit/exit ID
int addVisitExitRecord(vnePass* vnePass, char* visitorIC, int temperature, vneMetaData* md)
{
    (md->numAdd)++;

    if (*vnePass->size == *vnePass->maxSize) // resize array if needed
    {
        void* temp = realloc(vnePass->vneArr, (*vnePass->size + 10) * sizeof(visitExitInfo));
        if (!temp)
        {
            free(temp);
            temp = NULL;
            printf("\t\t\t      Error with adding visit or exit record. Please save the data and try again.\n");
            return;
        }
        vnePass->vneArr = temp;
        *vnePass->maxSize = *vnePass->size + 10;
    }

    char ans = 'Y';
    visitExitInfo vneData;

    if (*vnePass->size == 0)
        vneData.vneRecord = 1;
    else
        vneData.vneRecord = vnePass->vneArr[*vnePass->size - 1].vneRecord + 1;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    vneData.enterDate.day = tm.tm_mday;
    vneData.enterDate.month = tm.tm_mon + 1;
    vneData.enterDate.year = tm.tm_year + 1900;
    vneData.enterTime.hour = tm.tm_hour;
    vneData.enterTime.minit = tm.tm_min;
    vneData.enterTime.second = tm.tm_sec;

    printf("\n\n\t\t\t ENTER year of exit : ");
    scanf("%d", &vneData.exitDate.year);

    while (vneData.exitDate.year < 0 || vneData.exitDate.year > 2021)
    {
        printf("\n\t\t\t      IMPROPER year. Re-enter year of exit  : ");
        scanf("%d", &vneData.exitDate.year);
    }


    printf("\n\t\t\t ENTER month of exit  (1-12) : ");
    scanf("%d", &vneData.exitDate.month);

    while (vneData.exitDate.month < 1 || vneData.exitDate.month > 12)
    {
        printf("\n\t\t\t      IMPROPER month. Re-enter month of exit  : ");
        scanf("%d", &vneData.exitDate.month);
    }


    printf("\n\t\t\t ENTER date of exit (1-31) : ");
    scanf("%d", &vneData.exitDate.day);

    while (vneData.exitDate.day < 1 || vneData.exitDate.day > 31)
    {
        printf("\n\t\t\t      IMPROPER date. Re-enter date of exit : ");
        scanf("%d", &vneData.exitDate.day);
    }
    printf("\n\t\t\t ________________________________________________");



    printf("\n\n\t\t\t ENTER time of exit in hour (0-23) : ");
    scanf("%d", &vneData.exitTime.hour);

    while (vneData.exitTime.hour < 1 || vneData.exitTime.hour > 23)
    {
        printf("\n\t\t\t      IMPROPER hour. Re-enter time of exit in hour : ");
        scanf("%d", &vneData.exitTime.hour);
    }



    printf("\n\t\t\t ENTER time of exit in minutes (0-59) : ");
    scanf("%d", &vneData.exitTime.minit);

    while (vneData.exitTime.minit < 1 || vneData.exitTime.minit > 59)
    {
        printf("\n\t\t\t      IMPROPER minutes. Re-enter time of exit in minutes : ");
        scanf("%d", &vneData.exitTime.minit);
    }


    printf("\n\t\t\t ENTER time of exit in seconds (0-59) : ");
    scanf("%d", &vneData.exitTime.second);

    while (vneData.exitTime.second < 1 || vneData.exitTime.second > 59)
    {
        printf("\n\t\t\t      IMPROPER seconds. Re-enter time of exit in seconds : ");
        scanf("%d", &vneData.exitTime.second);
    }
    printf("\n\t\t\t ________________________________________________");


    vneData.temp = temperature;
    strcpy(vneData.visitorIC, visitorIC);
    rewind(stdin);
    printf("\n\n\t\t\t ENTER your reason of visit: ");
    fgets(&vneData.visitReason, BUFFER_SIZE, stdin); rewind(stdin);
    vneData.visitReason[strcspn(vneData.visitReason, "\n")] = 0;

    printf("\n\t\t\t ENTER your health condition: ");
    fgets(&vneData.healthCon, BUFFER_SIZE, stdin); rewind(stdin);
    vneData.healthCon[strcspn(vneData.healthCon, "\n")] = 0;

    printf("\n\t\t\t ENTER the number of person you visited with : ");
    scanf("%d", &vneData.noPerson);

    while (vneData.noPerson < 0)
    {
        printf("\n\t\t\t      IMPROPER number. Re-enter the number of person you visited with : ");
        scanf("%d", &vneData.noPerson);
    }


    printf("\n\t\t\t ENTER the venue ID: ");
    scanf("%d", &vneData.venueID); rewind(stdin);

    vnePass->vneArr[(*vnePass->size)++] = vneData;

    return vneData.vneRecord;
}

void showVisitExitRecord(visitExitInfo* vneArr, int size, venuePass pass)
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
        printVisitExitInfo(vneArr[index], findRecord(pass.venArr, *(pass.size), vneArr[index].venueID));

        index++;
    }
    system("pause");
    system("cls");
}

// loop through the array and find the record
// returns visitExitInfo with vneRecord -1 if not found
visitExitInfo findVisitExitRecord(visitExitInfo* vneArr, int size, int findVnERec)
{
    visitExitInfo temp;
    temp.vneRecord = -1; // value if not found  (not sure is visitor or venue)

    if (size == 0)
    {
        printf("\n\t\t\t.--------------------.\n");
        printf("\t\t\t|  No Record Found!  |\n");
        printf("\t\t\t'--------------------'\n");
        return temp;
    }

    int min = 0, max = size - 1, mid;

    while (min <= max)
    {
        mid = (max + min) / 2;
        if (vneArr[mid].vneRecord == findVnERec)
            return vneArr[mid];

        if (vneArr[mid].vneRecord > findVnERec)
            max = mid - 1;

        if (vneArr[mid].vneRecord < findVnERec)
            min = mid + 1;
    }
    return temp;
}

// performs findRecord and displays the result if found 
void searchVisitExitRecord(visitExitInfo* vneArr, int size, venuePass pass)
{
    int findVnERec;
    printf("\n\n\t\t\t   Enter visit record number to search: ");
    scanf("%d", &findVnERec);

    visitExitInfo temp = findVisitExitRecord(vneArr, size, findVnERec);

    if (temp.vneRecord == -1)
    {
        printf("\n\t\t\t.--------------------------------------.\n");
        printf("\t\t\t|   No record found for record No.%2d   |\n", findVnERec);
        printf("\t\t\t'--------------------------------------'\n\n");
        return;
    }

    printVisitExitInfo(temp, findRecord(pass.venArr, *(pass.size), temp.venueID));
    system("pause");
    system("cls");
}

void modifyVisitExitRecord(visitExitInfo* vneArr, int size, venuePass pass, vneMetaData* md)
{
    (md->numModify)++;

    int usrInput;
    printf("\t\t\t ______________________________________________________________________\n");
    printf("\t\t\t|                  |           |                                       |\n");
    printf("\t\t\t|   Visit & Exit   |   Venue   |               Name of                 |\n");
    printf("\t\t\t|    Record No.    |    ID.    |                Venue                  |\n");
    printf("\t\t\t|__________________|___________|_______________________________________|\n");
    for (int index = 0; index < size; index++)
    {
        printf("\t\t\t|                  |           |                                       |\n");
        printf("\t\t\t|        %2d        |    %3d    |       %-30s  |\n", vneArr[index].vneRecord, vneArr[index].venueID, findRecord(pass.venArr, *(pass.size), vneArr[index].venueID).venueName); //not sure what to print
        printf("\t\t\t|__________________|___________|_______________________________________|\n");
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
    printf("\n\n\t\t\t ENTER year of visit (e.g. 2021) : ");
    scanf("%d", &vneArr[usrInput].enterDate.year);
    rewind(stdin);

    while (vneArr[usrInput].enterDate.year < 0 || vneArr[usrInput].enterDate.year > 2021)
    {
        printf("\n\t\t\t      IMPROPER YEAR. Re-enter year of visit : ");
        scanf("%d", &vneArr[usrInput].enterDate.year);
        rewind(stdin);
    }


    printf("\n\t\t\t ENTER month of visit (1-12) : ");
    scanf("%d", &vneArr[usrInput].enterDate.month);
    rewind(stdin);

    while (vneArr[usrInput].enterDate.month < 1 || vneArr[usrInput].enterDate.month > 12)
    {
        printf("\n\t\t\t      IMPROPER MONTH. Re-enter month of visit : ");
        scanf("%d", &vneArr[usrInput].enterDate.month);
        rewind(stdin);
    }


    printf("\n\t\t\t ENTER date of visit (1-31) : ");
    scanf("%d", &vneArr[usrInput].enterDate.day);
    rewind(stdin);

    while (vneArr[usrInput].enterDate.day < 1 || vneArr[usrInput].enterDate.day > 31)
    {
        printf("\n\t\t\t      IMPROPER date. Re-enter date of visit : ");
        scanf("%d", &vneArr[usrInput].enterDate.day);
        rewind(stdin);
    }
    printf("\n\t\t\t ________________________________________________");


    printf("\n\n\t\t\t ENTER time of visit in hour (0-23) : ");
    scanf("%d", &vneArr[usrInput].enterTime.hour);
    rewind(stdin);

    while (vneArr[usrInput].enterTime.hour < 0 || vneArr[usrInput].enterTime.hour > 23)
    {
        printf("\n\t\t\t      IMPROPER hour. Re-enter time of visit in hour : ");
        scanf("%d", &vneArr[usrInput].enterTime.hour);
        rewind(stdin);
    }


    printf("\n\t\t\t ENTER time of visit in minutes (0-59) : ");
    scanf("%d", &vneArr[usrInput].enterTime.minit);
    rewind(stdin);

    while (vneArr[usrInput].enterTime.minit < 0 || vneArr[usrInput].enterTime.minit > 59)
    {
        printf("\n\t\t\t      IMPROPER minutes. Re-enter time of visit in minutes : ");
        scanf("%d", &vneArr[usrInput].enterTime.minit);
        rewind(stdin);
    }


    printf("\n\t\t\t ENTER time of visit in seconds (0-59) : ");
    scanf("%d", &vneArr[usrInput].enterTime.second);
    rewind(stdin);

    while (vneArr[usrInput].enterTime.second < 0 || vneArr[usrInput].enterTime.second > 59)
    {
        printf("\n\t\t\t      IMPROPER second. Re-enter time of visit in seconds : ");
        scanf("%d", &vneArr[usrInput].enterTime.second);
        rewind(stdin);
    }
    printf("\n\t\t\t ________________________________________________");

    printf("\n\n\t\t\t ENTER year of exit : ");
    scanf("%d", &vneArr[usrInput].exitDate.year);
    rewind(stdin);

    while (vneArr[usrInput].exitDate.year < 0 || vneArr[usrInput].exitDate.year > 2021)
    {
        printf("\n\t\t\t      IMPROPER year. Re-enter year of exit  : ");
        scanf("%d", &vneArr[usrInput].exitDate.year);
        rewind(stdin);
    }


    printf("\n\t\t\t ENTER month of exit  (1-12) : ");
    scanf("%d", &vneArr[usrInput].exitDate.month);
    rewind(stdin);

    while (vneArr[usrInput].exitDate.month < 1 || vneArr[usrInput].exitDate.month > 12)
    {
        printf("\n\t\t\t      IMPROPER month. Re-enter month of exit  : ");
        scanf("%d", &vneArr[usrInput].exitDate.month);
        rewind(stdin);
    }


    printf("\n\t\t\t ENTER date of exit (1-31) : ");
    scanf("%d", &vneArr[usrInput].exitDate.day);
    rewind(stdin);

    while (vneArr[usrInput].exitDate.day < 1 || vneArr[usrInput].exitDate.day > 31)
    {
        printf("\n\t\t\t      IMPROPER date. Re-enter date of exit : ");
        scanf("%d", &vneArr[usrInput].exitDate.day);
        rewind(stdin);
    }
    printf("\n\t\t\t ________________________________________________");

    printf("\n\n\t\t\t ENTER time of exit in hour (0-23) : ");
    scanf("%d", &vneArr[usrInput].exitTime.hour);
    rewind(stdin);

    while (vneArr[usrInput].exitTime.hour < 0 || vneArr[usrInput].exitTime.hour > 23)
    {
        printf("\n\t\t\t      IMPROPER hour. Re-enter time of exit in hour : ");
        scanf("%d", &vneArr[usrInput].exitTime.hour);
        rewind(stdin);
    }


    printf("\n\t\t\t ENTER time of exit in minutes (0-59) : ");
    scanf("%d", &vneArr[usrInput].enterTime.minit);
    rewind(stdin);

    while (vneArr[usrInput].enterTime.minit < 0 || vneArr[usrInput].enterTime.minit > 59)
    {
        printf("\n\t\t\t      IMPROPER minutes. Re-enter time of exit in minutes : ");
        scanf("%d", &vneArr[usrInput].enterTime.minit);
        rewind(stdin);
    }


    printf("\n\t\t\t ENTER time of exit in seconds (0-59) : ");
    scanf("%d", &vneArr[usrInput].enterTime.second);
    rewind(stdin);

    while (vneArr[usrInput].enterTime.second < 0 || vneArr[usrInput].enterTime.second > 59)
    {
        printf("\n\t\t\t      IMPROPER seconds. Re-enter time of exit in seconds : ");
        scanf("%d", &vneArr[usrInput].enterTime.second);
        rewind(stdin);
    }
    printf("\n\t\t\t ________________________________________________");

    printf("\n\n\t\t\t ENTER visitor IC : ");
    scanf("%s", &vneArr[usrInput].visitorIC);
    rewind(stdin);

    printf("\n\t\t\t ENTER your temperature : ");
    scanf("%f", &vneArr[usrInput].temp);
    rewind(stdin);

    while (vneArr[usrInput].temp < 0)
    {
        printf("\n\t\t\t      IMPROPER temperature. Re-enter temperature : ");
        scanf("%f", &vneArr[usrInput].temp);
        rewind(stdin);
    }
    rewind(stdin);
    printf("\n\t\t\t ENTER your reason of visit : ");
    fgets(&vneArr[usrInput].visitReason, BUFFER_SIZE, stdin);
    vneArr[usrInput].visitReason[strcspn(vneArr[usrInput].visitReason, "\n")] = 0;

    printf("\n\t\t\t ENTER your health condition : ");
    fgets(&vneArr[usrInput].healthCon, BUFFER_SIZE, stdin);
    vneArr[usrInput].healthCon[strcspn(vneArr[usrInput].healthCon, "\n")] = 0;

    printf("\n\t\t\t ENTER the number of person you visited with : ");
    scanf("%d", &vneArr[usrInput].noPerson);
    rewind(stdin);
    while (vneArr[usrInput].noPerson < 0)
    {
        printf("\n\t\t\t      IMPROPER number. Re-enter the number of person you visited with : ");
        scanf("%d", &vneArr[usrInput].noPerson);
        rewind(stdin);
    }
    printf("\n\t\t\t.---------------------.\n");
    printf("\t\t\t|    Data updated!    |\n");
    printf("\t\t\t'---------------------'\n");
    printf("\n\t\t\t ________________________________________________\n\n");

    system("pause");
    system("cls");
}

visitExitInfo* readVisitExitData(int* size)
{
    FILE* fp;
    fp = fopen("./Files/Vne.txt", "r");

    if (fp == NULL) {
        fp = fopen("./Files/Vne.txt", "w");
        fclose(fp);
        *size = 0;
        visitExitInfo* ok = malloc(10 * sizeof(visitExitInfo)); // allocate extra 10 slots for new data
        return ok;
    }

    int count = 0;
    char temp[BUFFER_SIZE];
    while (fgets(temp, sizeof(temp), fp) != NULL)
    {
        count++;
    };
    *size = count;
    visitExitInfo* vneArr = malloc((10 + count) * sizeof(visitExitInfo)); // allocate extra 10 slots for new data
    rewind(fp);
    int i = 0, a, b, c;
    while (fscanf(fp, "%d|%d:%d:%d|%d:%d:%d|%d:%d:%d|%d:%d:%d|%[^|]|%d|%f|%[^|]|%[^|]|%d\n", &vneArr[i].vneRecord, &vneArr[i].enterDate.year, &vneArr[i].enterDate.month, &vneArr[i].enterDate.day, &vneArr[i].enterTime.hour, &vneArr[i].enterTime.minit, &vneArr[i].enterTime.second, &vneArr[i].exitDate.year, &vneArr[i].exitDate.month, &vneArr[i].exitDate.day, &vneArr[i].exitTime.hour, &vneArr[i].exitTime.minit, &vneArr[i].exitTime.second, &vneArr[i].visitorIC, &vneArr[i].venueID, &vneArr[i].temp, &vneArr[i].visitReason, &vneArr[i].healthCon, &vneArr[i].noPerson) != EOF)
    {
        i++;
    }
    fclose(fp);
    return vneArr;
}

void writeVisitExitData(visitExitInfo* vneArr, int size)
{
    FILE* fp;
    fp = fopen("./Files/Vne.txt", "w");
    for (int i = 0; i < size; i++)
    {
        fprintf(fp, "%d|%d:%d:%d|%d:%d:%d|%d:%d:%d|%d:%d:%d|%s|%d|%f|%s|%s|%d\n",
            vneArr[i].vneRecord,
            vneArr[i].enterDate.year, vneArr[i].enterDate.month, vneArr[i].enterDate.day,
            vneArr[i].enterTime.hour, vneArr[i].enterTime.minit, vneArr[i].enterTime.second,
            vneArr[i].exitDate.year, vneArr[i].exitDate.month, vneArr[i].exitDate.day,
            vneArr[i].exitTime.hour, vneArr[i].exitTime.minit, vneArr[i].exitTime.second,
            vneArr[i].visitorIC, vneArr[i].venueID, vneArr[i].temp, vneArr[i].visitReason,
            vneArr[i].healthCon, vneArr[i].noPerson);
    }
    fclose(fp);
}

void deleteVisitExitData(visitExitInfo* vneArr, int* size, vneMetaData* md) //(not sure what to del)
{
    (md->numDelete)++;

    int vneRecord;
    printf("\n\n\t\t\t ENTER record number to delete: ");
    scanf("%d", &vneRecord);
    rewind(stdin);

    if (findVisitExitRecord(vneArr, *size, vneRecord).vneRecord == -1)
    {
        printf("\n\t\t\t    .--------------------------------.\n");
        printf("\t\t\t    |     Unknown record number!     |\n");
        printf("\t\t\t    '--------------------------------'\n");
        return;
    }

    for (int i = vneRecord - 1; i + 1 < *size; i++)
    {
        vneArr[i] = vneArr[i + 1];
    }
    (*size)--;
}

void reportVne(vneMetaData* md)
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

void visitnexit(vnePass vnePass, venuePass venPass, vneMetaData* md)
{
    int option = 0;

    do {
        printf("\n\n\n");
        printf("\n\t\t\t     +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
        printf("\t\t\t     !     Visits & Exits Menu     !\n");
        printf("\t\t\t     +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n\n");
        printf("\t\t\t.---------------------------------------.\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [1]  Search records              |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [2]  Modify record               |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [3]  Show all records            |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [4]  Delete record               |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [5]  Report actions done         |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|      [6]  Return to Main Menu         |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t|                                       |\n");
        printf("\t\t\t'---------------------------------------'\n");
        printf("\n\t\t\t Enter your choice :  ");
        scanf("%d", &option);

        if (option == 1)
        {
            system("cls");
            searchVisitExitRecord(vnePass.vneArr, *(vnePass.size), venPass);
        }
        else if (option == 2)
        {
            system("cls");
            modifyVisitExitRecord(vnePass.vneArr, *(vnePass.size), venPass, md);
        }
        else if (option == 3)
        {
            system("cls");
            showVisitExitRecord(vnePass.vneArr, *(vnePass.size), venPass);
        }
        else if (option == 4)
        {
            system("cls");
            deleteVisitExitData(vnePass.vneArr, vnePass.size, md);
        }
        else if (option == 5)
        {
            system("cls");
            reportVne(md);
        }
        else if (option == 6)
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
        else
        {
            system("cls");
            printf("\n\n\t\t==============================================================\n\n");
            printf("\t\t    Invalid choice! Please enter the NUMBER shown in menu.    \n\n");
            printf("\t\t==============================================================\n\n\n\n");
            system("pause");
            system("cls");
        }
    } while (option != 7);
}