/*The following program is written for program to 
manage covid patient data of Surat city using a 
single text file through the menu options. The 
database records the data of all the patients 
and performs the operations given*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//patient structure to record patient details
struct data
{
	int recno, age, add, amm, ayy, ddd, dmm, dyy;
	char fname[20], lname[20], gender, area[20];
};

//sub functions
void addData();
void delData();
void alterData();
void display();
void count();
void sortfnasc();
void sortfndesc();
void sortlnasc();
void sortlndesc();
void sortageasc();
void sortagedesc();
void sortadmasc();
void sortdisdesc();
void listing();
void sepfile();
int tcount = 0;

//main function
int main()
{
	int c, z, flag = 1, ch;
	while (flag != 0)
	{
		printf("enter a choice:\n1.adding\n2.deleting\n3.alter\n4.display\n5.Count\n6.sort first name in ascending order\n7.sort first name in descending order\n8.sort last name in ascending order\n9.sort last name in descending order\n10.sort age in ascending order\n11.sort age in descending order\n12.sort admission date in ascending order\n13.sort discharge date in descending order\n14.lisiting of Patient\n15.seperate male and female files\n \nEnter--->\n");
		scanf("%d", &c);
		switch (c)
		{
			case 1:
				addData();
				break;
			case 2:
				delData();
				break;
			case 3:
				alterData();
				break;
			case 4:
				display();
				break;
			case 5:
				count();
				break;
			case 6:
				sortfnasc();
				break;
			case 7:
				sortfndesc();
				break;
			case 8:
				sortlnasc();
				break;
			case 9:
				sortlndesc();
				break;
			case 10:
				sortageasc();
				break;
			case 11:
				sortagedesc();
				break;
			case 12:
				sortadmasc();
				break;
			case 13:
				sortdisdesc();
				break;
			case 14:
				printf("Enter a choice: \n1.Patient first name starts from your first name letter to next 10 letters\n2.Admission date from user given date to next 10 dates\n3.Admission month from user given month to next 5 months\n");
				scanf("%d", &ch);
				listing(ch);
				break;
			case 15:
				sepfile();
				break;
		}

		printf("\nContinue?(1/0)-->");
		scanf("%d", &z);
		if (z == 0)
		{
			flag = 0;
		}
	}
}

//addition of record
void addData()
{
	int i, n;
	FILE * fp;
	struct data obj;
	fp = fopen("suratcovid.txt", "a+");
	if (fp == NULL)
	{
		printf("\ncannot open the file\n");
		exit(1);
	}

	printf("\n*****ADDING DATA*****\n");
	printf("\nEnter Record No : ");
	fflush(stdin);
	scanf("%d", &obj.recno);
	printf("Enter first Name : ");
	fflush(stdin);
	gets(obj.fname);
	printf("Enter last Name : ");
	fflush(stdin);
	gets(obj.lname);
	printf("Enter age : ");
	fflush(stdin);
	scanf("%d", &obj.age);
	printf("Enter gender : ");
	fflush(stdin);
	scanf("%c", &obj.gender);
	printf("enter admission date : ");
	fflush(stdin);
	scanf("%d %d %d", &obj.add, &obj.amm, &obj.ayy);
	printf("Enter discharge date : ");
	fflush(stdin);
	scanf("%d %d %d", &obj.ddd, &obj.dmm, &obj.dyy);
	printf("enter area :");
	fflush(stdin);
	gets(obj.area);
	fwrite(&obj, sizeof(struct data), 1, fp);
	fclose(fp);
	printf("\nrecords added\n");
}

//deletion of record
void delData()
{
	struct data obj;
	FILE * fp;
	FILE * fp1;
	fp = fopen("suratcovid.txt", "r+");
	fp1 = fopen("dbms.txt", "a+");
	if (fp == NULL)
		printf("Failed to load! ");
	else
	{
		int n;
		printf("\nEnter the Patient Number to be deleted : ");
		scanf("%d", &n);
		while (fread(&obj, sizeof(struct data), 1, fp))
		{
			if (obj.recno != n)
			{
				fwrite(&obj, sizeof(struct data), 1, fp1);
			}
		}

		fclose(fp);
		fclose(fp1);
		remove("suratcovid.txt");
		rename("dbms.txt", "suratcovid.txt");
		printf("\nrecord deleted\n");

	}
}

//modifying data
void alterData()
{
	struct data obj;
	FILE * fp;
	FILE * fp1;
	FILE * fp2;
	fp = fopen("suratcovid.txt", "r+");
	fp1 = fopen("dbms1.txt", "a+");
	if (fp == NULL && fp1 == NULL)
		printf("Failed to load! ");
	else
	{
		int n;
		printf("\nEnter the Patient Number to be updated : ");
		scanf("%d", &n);
		while (fread(&obj, sizeof(struct data), 1, fp))
		{
			if (obj.recno != n)
			{
				fwrite(&obj, sizeof(struct data), 1, fp1);
			}
		}

		fclose(fp);
		fclose(fp1);
		remove("suratcovid.txt");
		rename("dbms1.txt", "suratcovid.txt");
		fp2 = fopen("suratcovid.txt", "a+");
		if (fp2 == NULL)
		{
			printf("\ncannot open the file\n");
			exit(1);
		}

		printf("\n*****ADDING DATA*****\n");
		printf("\nEnter Record No : ");
		fflush(stdin);
		scanf("%d", &obj.recno);
		printf("Enter first Name : ");
		fflush(stdin);
		gets(obj.fname);
		printf("Enter last Name : ");
		fflush(stdin);
		gets(obj.lname);
		printf("Enter age : ");
		fflush(stdin);
		scanf("%d", &obj.age);
		printf("Enter gender : ");
		fflush(stdin);
		scanf("%c", &obj.gender);
		printf("enter admission date : ");
		scanf("%d %d %d", &obj.add, &obj.amm, &obj.ayy);
		printf("Enter discharge date : ");
		scanf("%d %d %d", &obj.ddd, &obj.dmm, &obj.dyy);
		printf("enter area :");
		fflush(stdin);
		gets(obj.area);
		fwrite(&obj, sizeof(struct data), 1, fp2);
		fclose(fp2);
		printf("\nrecords updated\n");
	}
}

//displaying patient records
void display()
{
	FILE * fp;
	struct data obj;
	fp = fopen("suratcovid.txt", "r+");
	if (fp == NULL)
	{
		printf("Failed to load!!!");
	}
	else
	{
		while (fread(&obj, sizeof(struct data), 1, fp))
		{
			printf("\n");
			printf("* * * * * * * * * * * * * * * * * * * * * * **");
			printf("\npatient number : %d\n", obj.recno);
			printf("patient first name:");
			puts(obj.fname);
			printf("\n");
			printf("patient last name:");
			puts(obj.lname);
			printf("\n");
			printf("patient age: %d\n", obj.age);
			printf("patient gender: %c\n", obj.gender);
			printf("patient admission date: %d %d %d \n", obj.add, obj.amm, obj.ayy);
			printf("patient discharge date : %d %d %d \n", obj.ddd, obj.dmm, obj.dyy);
			printf("patient area :");
			puts(obj.area);
			printf("\n");
			printf("* * * * * * * * * * * * * * * * * * * * * * **");
			printf("\n");
		}
	}

	fclose(fp);
}

//counting patient information
void count()
{
	FILE * fp;
	int countp = 0, countf = 0, countm = 0, j, countage[100] = { 0}, acount, flag = 0, k = 0, i, m = 0, countpl[100] = { 0}, p;
	char place[100][20];
	struct data obj, obj1;
	fp = fopen("suratcovid.txt", "r+");
	if (fp == NULL)
	{
		printf("\nFailed to load!!!\n");
	}
	else
	{
		while (fread(&obj, sizeof(struct data), 1, fp))
		{
			countage[obj.age]++;
			if (obj.recno)
			{
				countp++;
				if (obj.gender == 'f')
				{
					countf++;
				}
				else
				{
					countm++;
				}
			}

			int i;
			strcpy(place[k], obj.area);
			k++;
		}
        	for (i = 0; i < 100; i++)

			{
				if (countage[i] != 0)
				{
					printf("\nNumber of people of age %d : %d",i, countage[i]);
				}
			}
		for (i = 0; i < k; i++, p++)
		{
			for (j = i - 1; j < k; j++)
			{
				if (strcmp(place[i], place[j]) == 0)
				{
					m++;
					countpl[p] = m;
				}
			}

			m = 0;
		}

		printf("\nTotal number of patients: %d\n", countp);
		printf("\nTotal number of female: %d\n", countf);
		printf("\nTotal number of male: %d\n", countm);
		for (i = 0; i < k; i++)
		{
			printf("\nNo. of people from place %s are : %d\n",place[i], countpl[i]);
		}
	}
}

//sorting of first name of patient in ascending order
void sortfnasc()
{
	struct data obj1[100], obj, temp;
	int i = 0, j, tcount = 0;
	FILE * fp;
	fp = fopen("suratcovid.txt", "r+");
	while (fread(&obj, sizeof(struct data), 1, fp))
	{
		obj1[tcount] = obj;
		tcount++;
	}
    //bubble sort
	for (i = 0; i < tcount - 1; i++)
	{
		for (j = 0; j < tcount - i - 1; j++)
		{
			if (strcmp(obj1[j].fname, obj1[j + 1].fname) > 0)
			{
				temp = obj1[j];
				obj1[j] = obj1[j + 1];
				obj1[j + 1] = temp;
			}
		}
	}

	FILE * fp1;
	fp1 = fopen("sorted.txt", "a+");
	for (i = 0; i < tcount; i++)
	{
		fwrite(&obj1[i], sizeof(struct data), 1, fp1);
	}

	fclose(fp);
	fclose(fp1);
	remove("suratcovid.txt");
	rename("sorted.txt", "suratcovid.txt");
	printf("\n\nSorted Record is : \n");
	display();
}

//sorting of first name of patient in descending order
void sortfndesc()
{
	struct data obj1[100], obj, temp;
	int i = 0, j, tcount = 0;
	FILE * fp;
	fp = fopen("suratcovid.txt", "r+");
	while (fread(&obj, sizeof(struct data), 1, fp))
	{
		obj1[tcount] = obj;
		tcount++;
	}

	for (i = 0; i < tcount - 1; i++)
	{
		for (j = 0; j < tcount - i - 1; j++)
		{
			if (strcmp(obj1[j].fname, obj1[j + 1].fname) < 0)
			{
				temp = obj1[j];
				obj1[j] = obj1[j + 1];
				obj1[j + 1] = temp;
			}
		}
	}

	FILE * fp1;
	fp1 = fopen("sorting.txt", "a+");
	for (i = 0; i < tcount; i++)
	{
		fwrite(&obj1[i], sizeof(struct data), 1, fp1);
	}

	fclose(fp);
	fclose(fp1);
	remove("suratcovid.txt");
	rename("sorting.txt", "suratcovid.txt");
	printf("\n\nSorted Record is : \n");
	display();
}

//sorting of last name of patient in ascending order
void sortlnasc()
{
	struct data obj1[100], obj, temp;
	int i = 0, j, tcount = 0;
	FILE * fp;
	fp = fopen("suratcovid.txt", "r+");
	while (fread(&obj, sizeof(struct data), 1, fp))
	{
		obj1[tcount] = obj;
		tcount++;
	}

	for (i = 0; i < tcount - 1; i++)
	{
		for (j = 0; j < tcount - i - 1; j++)
		{
			if (strcmp(obj1[j].lname, obj1[j + 1].lname) > 0)
			{
				temp = obj1[j];
				obj1[j] = obj1[j + 1];
				obj1[j + 1] = temp;
			}
		}
	}

	FILE * fp1;
	fp1 = fopen("sorted.txt", "a+");
	for (i = 0; i < tcount; i++)
	{
		fwrite(&obj1[i], sizeof(struct data), 1, fp1);
	}

	fclose(fp);
	fclose(fp1);
	remove("suratcovid.txt");
	rename("sorted.txt", "suratcovid.txt");
	printf("\n\nSorted Record is : \n");
	display();
}

//sorting of last name of patient in descending order
void sortlndesc()
{
	struct data obj1[100], obj, temp;
	int i = 0, j, tcount = 0;
	FILE * fp;
	fp = fopen("suratcovid.txt", "r+");
	while (fread(&obj, sizeof(struct data), 1, fp))
	{
		obj1[tcount] = obj;
		tcount++;
	}

	for (i = 0; i < tcount - 1; i++)
	{
		for (j = 0; j < tcount - i - 1; j++)
		{
			if (strcmp(obj1[j].lname, obj1[j + 1].lname) < 0)
			{
				temp = obj1[j];
				obj1[j] = obj1[j + 1];
				obj1[j + 1] = temp;
			}
		}
	}

	FILE * fp1;
	fp1 = fopen("sorted.txt", "a+");
	for (i = 0; i < tcount; i++)
	{
		fwrite(&obj1[i], sizeof(struct data), 1, fp1);
	}

	fclose(fp);
	fclose(fp1);
	remove("suratcovid.txt");
	rename("sorted.txt", "suratcovid.txt");
	printf("\n\nSorted Record is : \n");
	display();
}

//sorting of age of patient in ascending order
void sortageasc()
{
	struct data obj1[100], obj, temp;
	int i = 0, j, tcount = 0;
	FILE * fp;
	fp = fopen("suratcovid.txt", "r+");
	while (fread(&obj, sizeof(struct data), 1, fp))
	{
		obj1[tcount] = obj;
		tcount++;
	}

	for (i = 0; i < tcount - 1; i++)
	{
		for (j = 0; j < tcount - i - 1; j++)
		{
			if (obj1[j].age > obj1[j + 1].age)
			{
				temp = obj1[j];
				obj1[j] = obj1[j + 1];
				obj1[j + 1] = temp;
			}
		}
	}

	FILE * fp1;
	fp1 = fopen("sorted.txt", "a+");
	for (i = 0; i < tcount; i++)
	{
		fwrite(&obj1[i], sizeof(struct data), 1, fp1);
	}

	fclose(fp);
	fclose(fp1);
	remove("suratcovid.txt");
	rename("sorted.txt", "suratcovid.txt");
	printf("\n\nSorted Record is : \n");
	display();
}

//sorting of age of patient in descending order
void sortagedesc()
{
	struct data obj1[100], obj, temp;
	int i = 0, j, tcount = 0;
	FILE * fp;
	fp = fopen("suratcovid.txt", "r+");
	while (fread(&obj, sizeof(struct data), 1, fp))
	{
		obj1[tcount] = obj;
		tcount++;
	}

	for (i = 0; i < tcount - 1; i++)
	{
		for (j = 0; j < tcount - i - 1; j++)
		{
			if (obj1[j].age < obj1[j + 1].age)
			{
				temp = obj1[j];
				obj1[j] = obj1[j + 1];
				obj1[j + 1] = temp;
			}
		}
	}

	FILE * fp1;
	fp1 = fopen("sorted.txt", "a+");
	for (i = 0; i < tcount; i++)
	{
		fwrite(&obj1[i], sizeof(struct data), 1, fp1);
	}

	fclose(fp);
	fclose(fp1);
	remove("suratcovid.txt");
	rename("sorted.txt", "suratcovid.txt");
	printf("\n\nSorted Record is : \n");
	display();
}

//sorting of admission date of patient in ascending order
void sortadmasc()
{
	struct data obj1[100], obj, temp;
	int i = 0, j, tcount = 0;
	FILE * fp;
	fp = fopen("suratcovid.txt", "r+");
	while (fread(&obj, sizeof(struct data), 1, fp))
	{
		obj1[tcount] = obj;
		tcount++;
	}

	for (i = 0; i < tcount - 1; i++)
	{
		for (j = 0; j < tcount - i - 1; j++)
		{
			if (obj1[j].add > obj1[j + 1].add || obj1[j].amm > obj1[j + 1].amm || obj1[j].ayy > obj1[j + 1].ayy)
			{
				temp = obj1[j];
				obj1[j] = obj1[j + 1];
				obj1[j + 1] = temp;
			}
		}
	}

	FILE * fp1;
	fp1 = fopen("sorted.txt", "a+");
	for (i = 0; i < tcount; i++)
	{
		fwrite(&obj1[i], sizeof(struct data), 1, fp1);
	}

	fclose(fp);
	fclose(fp1);
	remove("suratcovid.txt");
	rename("sorted.txt", "suratcovid.txt");
	printf("\n\nSorted Record is : \n");
	display();
}

//sorting of discharge date of patient in ascending order
void sortdisdesc()
{
	struct data obj1[100], obj, temp;
	int i = 0, j, tcount = 0;
	FILE * fp;
	fp = fopen("suratcovid.txt", "r+");
	while (fread(&obj, sizeof(struct data), 1, fp))
	{
		obj1[tcount] = obj;
		tcount++;
	}

	for (i = 0; i < tcount - 1; i++)
	{
		for (j = 0; j < tcount - i - 1; j++)
		{
			if (obj1[j].ddd < obj1[j + 1].ddd || obj1[j].dmm < obj1[j + 1].dmm || obj1[j].dyy < obj1[j + 1].dyy)
			{
				temp = obj1[j];
				obj1[j] = obj1[j + 1];
				obj1[j + 1] = temp;
			}
		}
	}

	FILE * fp1;
	fp1 = fopen("sorted.txt", "a+");
	for (i = 0; i < tcount; i++)
	{
		fwrite(&obj1[i], sizeof(struct data), 1, fp1);
	}

	fclose(fp);
	fclose(fp1);
	remove("suratcovid.txt");
	rename("sorted.txt", "suratcovid.txt");
	printf("\n\nSorted Record is : \n");
	display();
}

//listing of patients according to given conditions
void listing(int ch)
{
	struct data obj, d[100];
	int mon, year, flag = 0;
	FILE * fp;
	fp = fopen("suratcovid.txt", "r+");
	if (fp == NULL)
	{
		printf("Failed to list! Records Empty ");
		fclose(fp);
		return;
	}

	switch (ch)
	{
		case 1:	//listing according to the first letter of my name
			while (fread(&obj, sizeof(struct data), 1, fp))
			{
				if ((obj.fname[0] >= 'S' && obj.fname[0] <= 'Z') || (obj.fname[0] >= 's' && obj.fname[0] <= 'z') || (obj.fname[0] >= 'A' && obj.fname[0] <= 'B') || (obj.fname[0] >= 'a' && obj.fname[0] <= 'b'))
				{
					printf("\n\n****************************************************\n");
					printf("\nPatient Number : %d", obj.recno);
					printf("\nFirst Name : %s", obj.fname);
					printf("\nLast Name : %s", obj.lname);
					printf("\nAge : %d", obj.age);
					printf("\nGender : %c", obj.gender);
					printf("\nArea : %s", obj.area);
					printf("\nAdmission Date : %d / %d / %d", obj.add, obj.amm, obj.ayy);
					printf("\nDischarge Date : %d / %d / %d", obj.ddd, obj.dmm, obj.dyy);
					printf("\n\n****************************************************\n");
					flag = 1;
				}
			}

			fclose(fp);
			if (flag == 0)
			{
				printf("\n\nNo desired record found!");
			}

			break;
		case 2:	//listing according to user given admission date
			printf("Enter given date (format : dd mm yyyy) : ");
			scanf("%d %d %d", &d[0].add, &d[0].amm, &d[0].ayy);
			int i = 1, m;
			while (i != 11)
			{
				if ((d[i - 1].amm % 2 != 0 && d[i - 1].amm <= 7) || (d[i - 1].amm % 2 == 0 && d[i - 1].amm <= 12))
				{
					m = 31;
				}
				else if (d[i - 1].amm == 2)
				{
					if (d[i - 1].ayy % 400 == 0)
						m = 29;
					else if (d[i - 1].ayy % 100 == 0)
						m = 28;
					else if (d[i - 1].ayy % 4 == 0)
						m = 29;
					else
					{
						m = 28;
					}
				}
				else
				{
					m = 30;
				}

				if (d[i - 1].add == m)
				{
					d[i].add = (d[i - 1].add + 1) % m;
					if (d[i - 1].amm == 12)
					{
						d[i].amm = 1;
						d[i].ayy = d[i - 1].ayy + 1;
					}
					else
					{
						d[i].amm = d[i - 1].amm + 1;
						d[i].ayy = d[i - 1].ayy;
					}
				}
				else
				{
					d[i].add = (d[i - 1].add + 1);
					d[i].amm = d[i - 1].amm;
					d[i].ayy = d[i - 1].ayy;
				}

				i++;
			}

			while (fread(&obj, sizeof(struct data), 1, fp))
			{
				i = 0;
				while (i < 11)
				{
					if (obj.amm == d[i].amm)
					{
						printf("\n\n****************************************************\n");
						printf("\nPatient Number : %d", obj.recno);
						printf("\nFirst Name : %s", obj.fname);
						printf("\nLast Name : %s", obj.lname);
						printf("\nAge : %d", obj.age);
						printf("\nGender : %c", obj.gender);
						printf("\nArea : %s", obj.area);
						printf("\nAdmission Date : %d / %d / %d", obj.add, obj.amm, obj.ayy);
						printf("\nDischarge Date : %d / %d / %d", obj.ddd, obj.dmm, obj.dyy);
						printf("\n\n****************************************************\n");
						flag = 1;
						break;
					}

					i++;
				}
			}

			fclose(fp);
			if (flag == 0)
			{
				printf("\n\nNo desired record found!");
			}

			break;
		case 3:	//listing according to user given month and year 
			printf("\nEnter Admission month &year (mm yyyy): ");
			scanf("%d %d", &mon, &year);
			while (fread(&obj, sizeof(struct data), 1, fp))
			{
				if (obj.ayy == year)
				{
					if (mon <= 7)
					{
						if (obj.amm >= mon && obj.amm <= mon + 5)
						{
							printf("\n\n****************************************************\n");
							printf("\nPatient Number : %d", obj.recno);
							printf("\nFirst Name : %s", obj.fname);
							printf("\nLast Name : %s", obj.lname);
							printf("\nAge : %d", obj.age);
							printf("\nGender : %c", obj.gender);
							printf("\nArea : %s", obj.area);
							printf("\nAdmission Date : %d / %d / %d", obj.add, obj.amm, obj.ayy);
							printf("\nDischarge Date : %d / %d / %d", obj.ddd, obj.dmm, obj.dyy);
							printf("\n\n****************************************************\n");
							flag = 1;
						}
					}
					else
					{
						if (obj.amm >= mon && obj.amm <= 12)
						{
							printf("\n\n****************************************************\n");
							printf("\nPatient Number : %d", obj.recno);
							printf("\nFirst Name : %s", obj.fname);
							printf("\nLast Name : %s", obj.lname);
							printf("\nAge : %d", obj.age);
							printf("\nGender : %c", obj.gender);
							printf("\nArea : %s", obj.area);
							printf("\nAdmission Date : %d / %d / %d", obj.add, obj.amm, obj.ayy);
							printf("\nDischarge Date : %d / %d / %d", obj.ddd, obj.dmm, obj.dyy);
							printf("\n\n****************************************************\n");
							flag = 1;
						}
					}
				}
				else if (obj.ayy == year + 1)
				{
					if (obj.amm <= mon - 7)
					{
						printf("\n\n****************************************************\n");
						printf("\nPatient Number : %d", obj.recno);
						printf("\nFirst Name : %s", obj.fname);
						printf("\nLast Name : %s", obj.lname);
						printf("\nAge : %d", obj.age);
						printf("\nGender : %c", obj.gender);
						printf("\nArea : %s", obj.area);
						printf("\nAdmission Date : %d / %d / %d", obj.add, obj.amm, obj.ayy);
						printf("\nDischarge Date : %d / %d / %d", obj.ddd, obj.dmm, obj.dyy);
						printf("\n\n****************************************************\n");
						flag = 1;
					}
				}
			}

			fclose(fp);
			if (flag == 0)
			{
				printf("\n\nNo desired record found!");
			}

			break;
		default:
			printf("\n\nInvalid Input!");
			fclose(fp);
			break;
	}
}

//seperating male and female records into different files
void sepfile()
{
	struct data obj;
	FILE * fp;
	FILE * fp1;
	FILE * fp2;
	fp = fopen("suratcovid.txt", "r+");
	if (fp == NULL)
	{
		printf("Failed to seperate! Records Empty ");
		fclose(fp);
		return;
	}

	fp1 = fopen("malerecord.txt", "a+");
	fp2 = fopen("femalerecord.txt", "a+");
	if (fp1 != NULL)
	{
		fclose(fp1);
		remove("malerecord.txt");
		fp1 = fopen("malerecord.txt", "a+");
	}

	if (fp2 != NULL)
	{
		fclose(fp2);
		remove("femalerecord.txt");
		fp2 = fopen("femalerecord.txt", "a+");
	}

	while (fread(&obj, sizeof(struct data), 1, fp))
	{
		if (obj.gender == 'm')
		{
			fwrite(&obj, sizeof(struct data), 1, fp1);
		}
		else if (obj.gender == 'f')
		{
			fwrite(&obj, sizeof(struct data), 1, fp2);
		}
	}

	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fp1 = fopen("malerecord.txt", "r+");
	fp2 = fopen("femalerecord.txt", "r+");
	int flag = 0;
	printf(" Only males records are : ");
	while (fread(&obj, sizeof(struct data), 1, fp1))
	{
		printf("\n\n***********************************************************\n");
		printf("\nPatient Number : %d", obj.recno);
		printf("\nFirst Name : %s", obj.fname);
		printf("\nLast Name : %s", obj.lname);
		printf("\nAge : %d", obj.age);
		printf("\nGender : %c", obj.gender);
		printf("\nArea : %s", obj.area);
		printf("\nAdmission Date : %d / %d / %d", obj.add, obj.amm, obj.ayy);
		printf("\nDischarge Date : %d / %d / %d", obj.ddd, obj.dmm, obj.dyy);
		printf("\n\n****************************************************\n");
		flag = 1;
	}

	if (flag == 0)
	{
		printf("\n\nNo male records found!");
	}

	flag = 0;
	fclose(fp1);
	printf("\n\nOnly females records are : ");
	while (fread(&obj, sizeof(struct data), 1, fp2))
	{
		printf("\n\n****************************************************\n");
		printf("\nPatient Number : %d", obj.recno);
		printf("\nFirst Name : %s", obj.fname);
		printf("\nLast Name : %s", obj.lname);
		printf("\nAge : %d", obj.age);
		printf("\nGender : %c", obj.gender);
		printf("\nArea : %s", obj.area);
		printf("\nAdmission Date : %d / %d / %d", obj.add, obj.amm, obj.ayy);
		printf("\nDischarge Date : %d / %d / %d", obj.ddd, obj.dmm, obj.dyy);
		printf("\n\n****************************************************\n");
		flag = 1;
	}

	if (flag == 0)
	{
		printf("\n\nNo female records found!");
	}

	fclose(fp2);
}
