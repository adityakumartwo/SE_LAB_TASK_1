#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "stu_header.h"

int read_Input(struct Student s[], int max_size){
    FILE *fp = fopen("input.txt", "r");
    if(fp==NULL){
        printf("Error: Make sure file exists.\n");
        return 0;
    }

    int count = 0;
    char tempID[20], tempName[50];
    float min[5], maj[5];

    while (fscanf(fp, "%s %s", tempID,tempName) == 2)
    {
        int valid = 1;

        if (valid_ID(tempID, s, count)==0)
        {
            printf("Skipping invalid or duplicate ID: %s\n",tempID);
            valid = 0;
        }

        if (valid_Name(tempName)==0)
        {
            printf("Skipping invalid Name : %s\n",tempName);
            valid = 0;
        }

        for(int i = 0; i<5; i++){
            fscanf(fp, "%f %f", &min[i], &maj[i]);
            if (valid_Marks(min[i],maj[i])==0)
            {
                printf("Skipping ID %s due to marks out of range.\n",tempID);
                valid = 0;
            }
        }

        if(valid == 1 && count < max_size){
            strcpy(s[count].id, tempID);
            strcpy(s[count].name, tempName);
            for (int i = 0; i < 5; i++)
            {
                s[count].subjects[i].minor = min[i];
                s[count].subjects[i].major = maj[i];
            }
            count++;
        }
    }
    fclose(fp);
    return count;
}

void calcu_Results(struct Student s[], int count){
    for (int i = 0; i < count; i++)
    {
        float grandSum = 0;
        int failFlag = 0;

        for (int j = 0; j < 5; j++)
        {
            float total = s[i].subjects[j].minor + s[i].subjects[j].major;
            s[i].subjects[j].total = total;
            grandSum += total;

            if(total<50) failFlag = 1;
        }

        s[i].grandTotal = grandSum;
        s[i].percentage = grandSum/5.0;
        s[i].isFail = failFlag;

        show_Grade(s[i].percentage, failFlag, s[i].grade, &s[i].cgpa);
    
    }
    
}

int valid_ID(char *id, struct Student s[], int count){
    for (int i = 0; i<strlen(id); i++)
    {
        if(!isalnum(id[i])) return 0;
    }
    for(int i = 0; i<count; i++)
    {
        if(strcmp(s[i].id, id) == 0) return 0;
    }
    return 1;
}

int valid_Name(char *name){
    for(int i = 0; i<strlen(name);i++)
    {
        if(!isalpha(name[i])) return 0;
    }
    return 1;
}

int valid_Marks(float minor, float major)
{
    if(minor < 0 || minor > 40) return 0;
    if(major < 0 || major > 60) return 0;
    return 1;
}

void show_Grade(float p, int fail, char *gradeStr, float *cgpa){
    if(fail){
        strcpy(gradeStr, "F");
        *cgpa = 0.0;
    }
    else if (p>=90) {strcpy(gradeStr,"O"); *cgpa = 10.0 ;}
    else if (p>=85) {strcpy(gradeStr,"A+"); *cgpa = 9.0 ;}
    else if (p>=75) {strcpy(gradeStr,"A"); *cgpa = 8.0 ;}
    else if (p>=65) {strcpy(gradeStr,"B+"); *cgpa = 7.0 ;}
    else if (p>=60) {strcpy(gradeStr,"B"); *cgpa = 6.0 ;}
    else if (p>=55) {strcpy(gradeStr,"C"); *cgpa = 5.0 ;}
    else if (p>=50) {strcpy(gradeStr,"D"); *cgpa = 4.0 ;}
    else {strcpy(gradeStr,"F"); *cgpa = 0.0;}
}

void show_Output(struct Student s[], int count){
    FILE *fp = fopen("results.txt", "w");
    if(fp==NULL){
        printf("Error in output file.\n");
        return;
    }

    float classTotal = 0, maxP = -1, minP = 101;
    int gradeCounts[8] = {0};

    printf("\n%-10s %-15s %-10s %-10s %-5s %-15s\n", "ID", "Name", "Total", "Perc", "Grd", "CGPA");
    fprintf(fp,"%-10s %-15s %-10s %-10s %-5s %-15s\n", "ID", "Name", "Total", "Perc", "Grd", "CGPA");

    printf("\n");
    fprintf(fp,"\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-10s %-15s %-10.2f %-10.2f %-5s %-5.2f\n",
        s[i].id, s[i].name, s[i].grandTotal, s[i].percentage, s[i].grade, s[i].cgpa);

        fprintf(fp, "%-10s %-15s %-10.2f %-10.2f %-5s %-5.2f\n",
        s[i].id, s[i].name, s[i].grandTotal, s[i].percentage, s[i].grade, s[i].cgpa);

        classTotal += s[i].percentage;
        if(s[i].percentage>maxP)maxP = s[i].percentage;
        if(s[i].percentage<minP)minP = s[i].percentage;

        if(strcmp(s[i].grade, "O")==0) gradeCounts[0]++;
        else if (strcmp(s[i].grade, "A+")==0) gradeCounts[1]++;
        else if (strcmp(s[i].grade, "A")==0) gradeCounts[2]++;
        else if (strcmp(s[i].grade, "B+")==0) gradeCounts[3]++;
        else if (strcmp(s[i].grade, "B")==0) gradeCounts[4]++;
        else if (strcmp(s[i].grade, "C")==0) gradeCounts[5]++;
        else if (strcmp(s[i].grade, "D")==0) gradeCounts[6]++;
        else gradeCounts[7]++;
    }

    printf("\nClass Average: %.2f%%\n", classTotal / count);
    fprintf(fp,"\nClass Average: %.2f%%\n", classTotal / count);

    printf("Highest Perc : %.2f%%\n", maxP);
    fprintf(fp,"Highest Perc : %.2f%%\n", maxP);

    printf("Lowest Perc : %.2f%%\n", minP);
    fprintf(fp,"Lowest Perc : %.2f%%\n", minP);

    printf("\nResults saved to results.txt\n");
    fclose(fp);
}