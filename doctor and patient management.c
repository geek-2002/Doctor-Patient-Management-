/*continuing assignment 1 program and using patient information 
in this program we manage doctors information who are giving 
treatments to covid patients using one text file for 
database of doctors and another text file to 
relate doctor and patient.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure for doctor information
struct doc
{
	int docid, age;
	char fname[20], lname[20], gender, area[20];
};

//structure for appointment information(doctor and patient id)
struct doc_pa
{
	int docid, pid;
};

//struture for patient information
struct patient
{
	int pid, age, add, amm, ayy, ddd, dmm, dyy;
	char fname[20], lname[20], gender, area[20];
};

//operations
void addData(int);
void delData(int);
void display();
void pdoccount();
void listing(int);
void summary();
void leastdoc();

//main function
int main()
{
	int c, z, flag = 1, ch, ch1, ch2, ch3, ch4;
	while (flag != 0)
	{
		//Menu
		printf("enter a choice:\n1.adding records\n2.deleting records\n3.display\n4.Display list of doctors treating the number of patients\n5.Add a record in the patient-doctor file with a doctor having the least number of patients\n6.summary\n7.listing\n");
		scanf("%d", &c);
		switch (c)
		{
			case 1://adding records
				printf("Enter a choice:\n1.Add doctor records\n2.Add patient record\n3.Enter appointed doctor's patient id\n");
				scanf("%d", &ch2);
				addData(ch2);
				break;
			case 2://deleting records
				printf("Enter a choice:\n1.delete doctor records\n2.delete patient record\n3.delete Ids after appointment is over\n");
				scanf("%d", &ch3);
				delData(ch3);
				break;
			case 3://displaying records
				display();
				break;
			case 4://displaying doctors according to count of patients
				pdoccount();
				break;
			case 5://adding the record of doctor with least number of patients
				leastdoc();
				break;
			case 6://count summary of all the doctors
				summary();
				break;
			case 7://listing
				printf("Enter a choice: \n1.Admitted on same date\n2.Discharged on same date\n3.Patients treated under the doctor\n4.Patients treated under the male doctor\n5.Patients treated under the female doctor area wise\n");
				scanf("%d", &ch);
				listing(ch);
				break;
		}
        //yes or no
		printf("\nContinue?(1/0)-->");
		scanf("%d", &z);
		if (z == 0)
		{
			flag = 0;
		}
	}
}

//adding records
void addData(int ch2)
{
	int i, n;
	FILE * fp;
	FILE * fp1;
	FILE * fp2;
	struct doc obj;
	struct patient obj1;
	struct doc_pa obj2;
	switch (ch2)
	{
		case 1://adding doctor records
			fp = fopen("doctorfile.txt", "a+");
			if (fp == NULL)
			{
				printf("\ncannot open the file\n");
				exit(1);
			}
            //taking in information
			printf("\n*****ADDING DOCTOR DATA*****\n");
			printf("\nEnter Doctor ID : ");
			fflush(stdin);
			scanf("%d", &obj.docid);
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
			printf("enter area :");
			fflush(stdin);
			gets(obj.area);
			fwrite(&obj, sizeof(struct doc), 1, fp);
			fclose(fp);
			printf("\nrecords added\n");
			break;
		case 2://adding patient records
			fp1 = fopen("patient_doc.txt", "a+");
			if (fp1 == NULL)
			{
				printf("\ncannot open the file\n");
				exit(1);
			}
            //taking in information
			printf("\n*****ADDING PATIENT DATA*****\n");
			printf("\nEnter Patient ID : ");
			fflush(stdin);
			scanf("%d", &obj1.pid);
			printf("Enter first Name : ");
			fflush(stdin);
			gets(obj1.fname);
			printf("Enter last Name : ");
			fflush(stdin);
			gets(obj1.lname);
			printf("Enter age : ");
			fflush(stdin);
			scanf("%d", &obj1.age);
			printf("Enter gender : ");
			fflush(stdin);
			scanf("%c", &obj1.gender);
			printf("enter admission date : ");
			fflush(stdin);
			scanf("%d %d %d", &obj1.add, &obj1.amm, &obj1.ayy);
			printf("Enter discharge date : ");
			fflush(stdin);
			scanf("%d %d %d", &obj1.ddd, &obj1.dmm, &obj1.dyy);
			printf("enter area :");
			fflush(stdin);
			gets(obj1.area);
			fwrite(&obj1, sizeof(struct patient), 1, fp1);
			fclose(fp1);
			printf("\nrecords added\n");
			break;
		case 3://adding appointment records(patient id and doctor id)
			fp2 = fopen("doc_pa.txt", "a+");
			if (fp2 == NULL)
			{
				printf("\ncannot open the file\n");
				exit(1);
			}
            //taking in information
			printf("\n*****ADDING APPOINTMENT DATA*****\n");
			printf("\nEnter Patient ID : ");
			fflush(stdin);
			scanf("%d", &obj2.pid);
			printf("\nEnter doctor ID : ");
			fflush(stdin);
			scanf("%d", &obj2.docid);
			fwrite(&obj2, sizeof(struct doc_pa), 1, fp2);
			fclose(fp2);
			printf("\nrecords added\n");
			break;
	}
}

//deleting data
void delData(int ch3)
{
	struct doc obj;
	struct patient obj1;
	struct doc_pa obj2;
	FILE * fp;
	FILE * fp1;
	FILE * fp2;
	FILE * fp3;
	FILE * fp4;
	FILE * fp5;
	switch (ch3)
	{
		case 1://deleting doctor records
			fp = fopen("doctorfile.txt", "r+");
			fp1 = fopen("dbms.txt", "a+");
			if (fp == NULL)
				printf("Failed to load! ");
			else
			{
				int n;
				printf("\nEnter the doctor ID to be deleted : ");
				scanf("%d", &n);
				while (fread(&obj, sizeof(struct doc), 1, fp))
				{
					if (obj.docid != n)
					{
						fwrite(&obj, sizeof(struct doc), 1, fp1);
					}
				}
                //removing record
				fclose(fp);
				fclose(fp1);
				remove("doctorfile.txt");
				rename("dbms.txt", "doctorfile.txt");
				printf("\nrecord deleted\n");
			}

			break;
		case 2://deleting patient records
			fp2 = fopen("patient_doc.txt", "r+");
			fp3 = fopen("dbms.txt", "a+");
			if (fp2 == NULL)
				printf("Failed to load! ");
			else
			{
				int n;
				printf("\nEnter the Patient ID to be deleted : ");
				scanf("%d", &n);
				while (fread(&obj1, sizeof(struct patient), 1, fp2))
				{
					if (obj1.pid != n)
					{
						fwrite(&obj1, sizeof(struct patient), 1, fp3);
					}
				}
                //removing record
				fclose(fp2);
				fclose(fp3);
				remove("patient_doc.txt");
				rename("dbms.txt", "patient_doc.txt");
				printf("\nrecord deleted\n");
			}

			break;
		case 3://deleting appointment records
			fp4 = fopen("doc_pa.txt", "r+");
			fp5 = fopen("dbms.txt", "a+");
			if (fp4 == NULL)
				printf("Failed to load! ");
			else
			{
				int n;
				printf("\nEnter the Patient ID after appointment is over : ");
				scanf("%d", &n);
				while (fread(&obj1, sizeof(struct doc_pa), 1, fp4))
				{
					if (obj1.pid != n)
					{
						fwrite(&obj1, sizeof(struct doc_pa), 1, fp5);
					}
				}
                //removing record
				fclose(fp4);
				fclose(fp5);
				remove("doc_pa.txt");
				rename("dbms.txt", "doc_pa.txt");
				printf("\nrecord deleted\n");
			}
	}
}

//displaying records
void display()
{
	FILE * fp;
	FILE * fp1;
	FILE * fp2;
	int docids[100], pids[100], i, j;
	struct doc obj;
	struct patient obj1;
	struct doc_pa obj2;
	//displaying patient records
	printf("\nPATIENT RECORDS\n");
	fp1 = fopen("patient_doc.txt", "r+");
	if (fp1 == NULL)
	{
		printf("Failed to load!!!");
	}
	else
	{
		while (fread(&obj1, sizeof(struct patient), 1, fp1))
		{
			printf("\n");
			printf("* * * * * * * * * * * * * * * * * * * * * * * *");
			printf("\npatient number : %d\n", obj1.pid);
			printf("patient first name:");
			puts(obj1.fname);
			printf("\n");
			printf("patient last name:");
			puts(obj1.lname);
			printf("\n");
			printf("patient age: %d\n", obj1.age);
			printf("patient gender: %c\n", obj1.gender);
			printf("patient admission date: %d %d %d \n", obj1.add, obj1.amm, obj1.ayy);
			printf("patient discharge date : %d %d %d \n", obj1.ddd, obj1.dmm, obj1.dyy);
			printf("patient area :");
			puts(obj1.area);
			printf("\n");
			printf("* * * * * * * * * * * * * * * * * * * * * * * *");
			printf("\n");
		}
	}

	fclose(fp1);
	//displaying doctor records
	printf("\nDOCTOR RECORDS\n");
	fp = fopen("doctorfile.txt", "r+");
	if (fp == NULL)
	{
		printf("Failed to load!!!");
	}
	else
	{
		while (fread(&obj, sizeof(struct doc), 1, fp))
		{
			printf("\n");
			printf("* * * * * * * * * * * * * * * * * * ******");
			printf("\nDoctor number : %d\n", obj.docid);
			printf("Doctor first name:");
			puts(obj.fname);
			printf("\n");
			printf("Doctor last name:");
			puts(obj.lname);
			printf("\n");
			printf("Doctor age: %d\n", obj.age);
			printf("Doctor gender: %c\n", obj.gender);
			printf("Doctor area :");
			puts(obj.area);
			printf("\n");
			printf("* * * * * * * * * * * * * * * * * * ******");
			printf("\n");
		}
	}

	fclose(fp);
	//displaying appointment records
	printf("\nAppointment RECORDS\n");
	fp2 = fopen("doc_pa.txt", "r+");
	if (fp2 == NULL)
	{
		printf("Failed to load!!!");
	}
	else
	{
		while (fread(&obj2, sizeof(struct doc_pa), 1, fp2))
		{
			printf("\n");
			printf("* * * * * * * * * * * * * * * * * * * * * ***");
			printf("\nDoctor number : %d\n", obj2.docid);
			printf("\nPatient Number : %d\n", obj2.pid);
			printf("* * * * * * * * * * * * * * * * * * * * * ***");
			printf("\n");
		}
	}

	fclose(fp2);
}

//Displaying count of doctors
void pdoccount()
{
	FILE * fp;
	FILE * fp1;
	FILE * fp2;
	int countp[100] = { 0
	}, m = 0, docids[100], pids[100], l = 0, i, j, p = 0;
	struct doc obj;
	struct doc_pa obj1;
	fp1 = fopen("doc_pa.txt", "r+");
	if (fp1 == NULL)
	{
		printf("Failed to load!!!");
	}
	else
	{
		while (fread(&obj1, sizeof(struct doc_pa), 1, fp1))
		{
			pids[m] = obj1.docid;
			m++;
			printf("\n");
		}
	}

	fclose(fp1);
	fp = fopen("doctorfile.txt", "r+");
	if (fp == NULL)
	{
		printf("Failed to load!!!");
	}
	else
	{
		//count of patients
		while (fread(&obj, sizeof(struct doc), 1, fp))
		{
			docids[p] = obj.docid;
			p++;
			for (i = 0; i < m; i++)
			{
				if (pids[i] == obj.docid)
				{
					l++;
					countp[obj.docid] = l;
				}
			}

			l = 0;
		}
	}

	fclose(fp);
	fp2 = fopen("doctorfile.txt", "r+");
	if (fp2 == NULL)
	{
		printf("Failed to load!!!");
	}
	else
	{
		while (fread(&obj, sizeof(struct doc), 1, fp2))
		{
			for (i = 0; i <= m; i++)
			{
				if (countp[obj.docid] == i)
				{
					printf("\nThe doctor list for %d number of patients:\n", i);
					printf("\n");
					printf("* * * * * * * * * * * * * * * * * * * *****");
					printf("\nDoctor number : %d\n", obj.docid);
					printf("Doctor first name:");
					puts(obj.fname);
					printf("\n");
					printf("Doctor last name:");
					puts(obj.lname);
					printf("\n");
					printf("Doctor age: %d\n", obj.age);
					printf("Doctor gender: %c\n", obj.gender);
					printf("Doctor area :");
					puts(obj.area);
					printf("Total number of patients : %d", countp[obj.docid]);
					printf("\n");
					printf("* * * * * * * * * * * * * * * * * * * *****");
					printf("\n");
					break;
				}
				else
				{
					continue;
				}
			}
		}
	}

	fclose(fp2);
}

//adding least patient count doctor record
void leastdoc()
{
	struct doc_pa dp;
	struct doc d, d1[20];
	int count[20] = { 0}, i = 0, min[5] = { 0}, j;
	struct patient p;
	FILE *point, *fp;
	point = fopen("doctorfile.txt", "r+");
	while (fread(&d, sizeof(struct doc), 1, point))
	{
		fp = fopen("doc_pa.txt", "r+");
		//count of patients
		while (fread(&dp, sizeof(struct doc_pa), 1, fp))
		{
			if (dp.docid == d.docid)
			{
				count[i]++;
			}
		}

		fclose(fp);
		d1[i] = d;
		i++;
	}

	fclose(point);
	int l, flag, k, t;	//least count of doctor and least name alphabet record
	struct doc temp;
	for (k = 0; k < i - 1; k++)
	{
		flag = 0;
		for (l = 0; l < i - 1 - k; l++)
		{
			if (strcmp(d1[l].fname, d1[l + 1].fname) > 0)
			{
				temp = d1[l];
				d1[l] = d1[l + 1];
				d1[l + 1] = temp;
				t = count[l];
				count[l] = count[l + 1];
				count[l + 1] = t;
				flag = 1;
			}
		}

		if (flag == 0)
			break;
	}

	int mcnt = count[0];
	for (k = 0; k < i; k++)
	{
		if (count[k] < mcnt)
			mcnt = count[k];
	}

	for (k = 0, j = 0; k < i; k++)
	{
		if (count[k] == mcnt)
		{
			min[j] = k;
			j++;
		}
	}

	point = fopen("leastcount.txt", "a+");
	for (k = 0; k < j; k++)
	{
		fwrite(&d1[min[0]], sizeof(struct doc), 1, point);
	}

	printf("\nadded the least record\n");
	fclose(point);
}

//summary of doctorwise patient count on given fields
void summary()
{
	FILE * fp;
	FILE * fp1;
	FILE * fp2;
	int countp[100] = { 0}, agepto[100] = { 0}, Count = 1, m = 0, n = 0, age = 0, agep[100] = { 0}, countage[100] = { 0}, docids[100], pids[100], l = 0, i, j, countf = 0, countm = 0, countpl[100] = { 0}, p = 0, k = 0, FreqArr[100] = { 0 };
	char genp[100], genpto[100], areap[100][20], areapto[100][20], areapth[100][20], areacp[20];
	struct doc obj;
	struct doc_pa obj1;
	struct patient obj2;
	fp1 = fopen("doc_pa.txt", "r+");
	if (fp1 == NULL)
	{
		printf("Failed to load!!!");
	}
	else
	{
		while (fread(&obj1, sizeof(struct doc_pa), 1, fp1))
		{
			pids[m] = obj1.docid;
			m++;
			docids[obj1.pid] = obj1.docid;
		}
	}

	fclose(fp1);
	fp2 = fopen("patient_doc.txt", "r+");
	if (fp2 == NULL)
	{
		printf("Failed to load!!!");
	}
	else
	{
		while (fread(&obj2, sizeof(struct patient), 1, fp2))
		{
			genp[obj2.pid] = obj2.gender;
			agep[obj2.pid] = obj2.age;
			strcpy(areap[obj2.pid], obj2.area);

		}
	}

	fclose(fp2);
	printf("\nDOCTOR-PATIENT COUNT SUMMARY\n");
	fp = fopen("doctorfile.txt", "r+");
	if (fp == NULL)
	{
		printf("Failed to load!!!");
	}
	else
	{
		while (fread(&obj, sizeof(struct doc), 1, fp))
		{
			//counting total no. of patient
			for (i = 0; i <= m; i++)
			{
				if (pids[i] == obj.docid)
				{
					l++;
					countp[obj.docid] = l;
				}
			}

			for (i = 0; i < 20; i++)
			{
				if (docids[i] == obj.docid)
				{
					genpto[i] = genp[i];
					agepto[i] = agep[i];
					strcpy(areapto[i], areap[i]);
					FreqArr[i] = -1;
				}
				else
				{
					genpto[i] = 'n';
					agepto[i] = 0;
					strcpy(areapto[i], "Null");
					FreqArr[i] = -1;
				}
			}
            //genderwise count
			for (i = 0; i < 10; i++)
			{
				if (genpto[i] != 'n')
				{
					if (genpto[i] == 'm')
					{
						countm++;

					}
					else
					{
						countf++;
					}
				}
			}
            //agewise count
			for (i = 1; i < 100; i++)
			{
				if (agepto[i] != 0)
				{
					countage[agepto[i]]++;
				}
			}

			l = 0;
			printf("\n");
			printf("* * * * * * * * * * * * * * * * * * * * ****");
			printf("\nDoctor number : %d\n", obj.docid);
			printf("Doctor first name:");
			puts(obj.fname);
			printf("\n");
			printf("Doctor last name:");
			puts(obj.lname);
			printf("\n");
			printf("Doctor age: %d\n", obj.age);
			printf("Doctor gender: %c\n", obj.gender);
			printf("Doctor area :");
			puts(obj.area);
			printf("Total number of patients : %d\n", countp[obj.docid]);
			printf("Total number of male patients : %d\n", countm);
			printf("Total number of female patients : %d\n", countf);
			for (i = 0; i < 100; i++)
			{
				if (countage[i] != 0)
				{
					printf("\nNumber of patients of age %d : %d\n", i, countage[i]);
				}
			}
             //areawise count
			for (i = 0; i <= 10; i++)
			{
				Count = 1;
				for (j = i + 1; j <= 10; j++)
				{
					if (strcmp(areapto[i], areapto[j]) == 0)
					{
						Count++;
						FreqArr[j] = 0;
					}
				}

				if (FreqArr[i] != 0)
				{
					FreqArr[i] = Count;
				}
			}

			for (i = 0; i <= 10; i++)
			{
				if (FreqArr[i] != 0)
				{
					if (strcmp(areapto[i], "Null") != 0)
					{
						printf("Number of Patients from area %s are %d\n", areapto[i], FreqArr[i]);
					}
				}
			}

			printf("\n");
			printf("* * * * * * * * * * * * * * * * * * * * * ***");
			printf("\n");
			//initialising all the count variables for next doctor record
			countm = 0;
			countf = 0;
			for (i = 1; i < 100; i++)
			{
				if (agepto[i] != 0)
				{
					countage[agepto[i]] = 0;
				}
			}
		}
	}

	fclose(fp);
}

//listing patient records
void listing(int ch)
{
	struct patient obj1[100], obj, temp, p, pat[10];
	struct doc_pa pd;
	struct doc d;
	int i = 0, j, tcount = 0;
	FILE * fp;
	FILE * point;
	switch (ch)
	{
		case 1://listing records of same admission date and sorting of fname in ascending order
			printf("\nEnter the admission date:");
			scanf("%d %d %d", &p.add, &p.amm, &p.ayy);
			fp = fopen("patient_doc.txt", "r+");
			if (fp == NULL)
				printf("Failed to open file");
			else
			{
				while (fread(&obj, sizeof(struct patient), 1, fp))
				{
					if (obj.add == p.add && obj.amm == p.amm && obj.ayy == p.ayy)
					{
						obj1[tcount] = obj;
						tcount++;
					}
				}
			}

			fclose(fp);
			if (tcount == 0)
			{
				printf("\nNo such record found!!");
			}
			else
			{
				printf("\nASCENDING ORDER ACCORDING TO PATIENT NAME");
				for (i = 1; i < tcount; i++)	//Arranging in ascending order
				{
					int flag = 0;
					for (j = 0; j < tcount - i; j++)
					{
						if (strcmp(obj1[j + 1].fname, obj1[j].fname) < 0)
						{
							temp = obj1[j];
							obj1[j] = obj1[j + 1];
							obj1[j + 1] = temp;
							flag = 1;
						}
					}

					if (flag == 0)
						break;
				}

				for (i = 0; i < tcount; i++)
				{
					printf("\n");
					printf("* * * * * * * * * * * * * * * * * * * * * * * *");
					printf("\npatient number : %d\n", obj1[i].pid);
					printf("patient first name:");
					puts(obj1[i].fname);
					printf("\n");
					printf("patient last name:");
					puts(obj1[i].lname);
					printf("\n");
					printf("patient age: %d\n", obj1[i].age);
					printf("patient gender: %c\n", obj1[i].gender);
					printf("patient admission date: %d %d %d \n", obj1[i].add, obj1[i].amm, obj1[i].ayy);
					printf("patient discharge date : %d %d %d \n", obj1[i].ddd, obj1[i].dmm, obj1[i].dyy);
					printf("patient area :");
					puts(obj1[i].area);
					printf("\n");
					printf("* * * * * * * * * * * * * * * * * * * * * * **");
					printf("\n");
				}
			}

			break;
		case 2://listing records of same discharge date and sorting of fname in ascending order
			printf("\nEnter the discharge date:");
			scanf("%d %d %d", &p.ddd, &p.dmm, &p.dyy);
			fp = fopen("patient_doc.txt", "r+");
			if (fp == NULL)
				printf("Failed to open file");
			else
			{
				while (fread(&obj, sizeof(struct patient), 1, fp))
				{
					if (obj.ddd == p.ddd && obj.dmm == p.dmm && obj.dyy == p.dyy)
					{
						obj1[tcount] = obj;
						tcount++;
					}
				}
			}

			fclose(fp);
			if (tcount == 0)
			{
				printf("\nNo such record found!!");
			}
			else
			{
				printf("\nASCENDING ORDER ACCORDING TO PATIENT NAME");
				for (i = 1; i < tcount; i++)	//Arranging in ascending order
				{
					int flag = 0;
					for (j = 0; j < tcount - i; j++)
					{
						if (strcmp(obj1[j + 1].fname, obj1[j].fname) < 0)
						{
							temp = obj1[j];
							obj1[j] = obj1[j + 1];
							obj1[j + 1] = temp;
							flag = 1;
						}
					}

					if (flag == 0)
						break;
				}

				for (i = 0; i < tcount; i++)
				{
					printf("\n");
					printf("* * * * * * * * * * * * * * * * * * * * * * * *");
					printf("\npatient number : %d\n", obj1[i].pid);
					printf("patient first name:");
					puts(obj1[i].fname);
					printf("\n");
					printf("patient last name:");
					puts(obj1[i].lname);
					printf("\n");
					printf("patient age: %d\n", obj1[i].age);
					printf("patient gender: %c\n", obj1[i].gender);
					printf("patient admission date: %d %d %d \n", obj1[i].add, obj1[i].amm, obj1[i].ayy);
					printf("patient discharge date : %d %d %d \n", obj1[i].ddd, obj1[i].dmm, obj1[i].dyy);
					printf("patient area :");
					puts(obj1[i].area);
					printf("\n");
					printf("* * * * * * * * * * * * * * * * * * * * * ***");
					printf("\n");
				}
			}

			break;
		case 3://Patients treated under the doctor and sorting fname in ascending order
			point = fopen("doctorfile.txt", "r+");
			if (point == NULL)
				printf("Failed to open file");
			else
			{
				while (fread(&d, sizeof(struct doc), 1, point))
				{
					printf("\n\nDOCTOR NAME:%s %s", d.fname, d.lname);
					printf("\nDOCTOR ID:%d", d.docid);
					FILE * fp3;
					fp3 = fopen("doc_pa.txt", "r+");
					int P[10], cnt = 0, i, j = 0, flag;
					while (fread(&pd, sizeof(struct doc_pa), 1, fp3))
					{
						if (d.docid == pd.docid)
						{
							P[cnt] = pd.pid;
							cnt++;
						}
					}

					fclose(fp3);
					fp3 = fopen("patient_doc.txt", "r+");
					while (fread(&p, sizeof(struct patient), 1, fp3))
					{
						for (i = 0; i < cnt; i++)
						{
							if (P[i] == p.pid)
							{
								pat[j] = p;
								j++;
							}
						}
					}

					fclose(fp3);
					printf("\nPATIENTS TREATED UNDER DOCTOR:");
					for (i = 1; i < cnt; i++)
					{
						flag = 0;
						for (j = 0; j < cnt - i; j++)
						{
							if (strcmp(pat[j + 1].fname, pat[j].fname) < 0)
							{
								temp = pat[j];
								pat[j] = pat[j + 1];
								pat[j + 1] = temp;
								flag = 1;
							}
						}

						if (flag == 0)
							break;
					}

					for (i = 0; i < cnt; i++)
					{
						printf("\n");
						printf("* * * * * * * * * * * * * * * * * * * * * * * *");
						printf("\npatient number : %d\n", pat[i].pid);
						printf("patient first name:");
						puts(pat[i].fname);
						printf("\n");
						printf("patient last name:");
						puts(pat[i].lname);
						printf("\n");
						printf("patient age: %d\n", pat[i].age);
						printf("patient gender: %c\n", pat[i].gender);
						printf("patient admission date: %d %d %d \n", pat[i].add, pat[i].amm, pat[i].ayy);
						printf("patient discharge date : %d %d %d \n", pat[i].ddd, pat[i].dmm, pat[i].dyy);
						printf("patient area :");
						puts(pat[i].area);
						printf("\n");
						printf("* * * * * * * * * * * * * * * * * * * * * * * *");
						printf("\n");
					}
				}
			}

			break;
		case 4://Patients treated under the male doctor and sorting of fname in ascending order
			point = fopen("doctorfile.txt", "r+");
			if (point == NULL)
				printf("Failed to open file");
			else
			{
				while (fread(&d, sizeof(struct doc), 1, point))
				{
					if (d.gender == 'm')
					{
						printf("\n\nDOCTOR NAME:%s %s", d.fname, d.lname);
						printf("\nDOCTOR ID:%d", d.docid);
						FILE * fp;
						fp = fopen("doc_pa.txt", "r+");
						int P[10], cnt = 0, i, j = 0, flag;
						while (fread(&pd, sizeof(struct doc_pa), 1, fp))
						{
							if (d.docid == pd.docid)
							{
								P[cnt] = pd.pid;
								cnt++;
							}
						}

						fclose(fp);
						fp = fopen("patient_doc.txt", "r+");
						while (fread(&p, sizeof(struct patient), 1, fp))
						{
							for (i = 0; i <= cnt; i++)
							{
								if (P[i] == p.pid)
								{
									pat[j] = p;
									j++;
								}
							}
						}

						fclose(fp);
						printf("\nPATIENTS TREATED UNDER MALE DOCTOR:");
						for (i = 0; i <= cnt; i++)	//Arranging in ascending
						{
							flag = 0;
							for (j = 0; j < cnt - i; j++)
							{
								if (strcmp(pat[j + 1].fname, pat[j].fname) < 0)
								{
									temp = pat[j];
									pat[j] = pat[j + 1];
									pat[j + 1] = temp;
									flag = 1;
								}
							}

							if (flag == 0)
								break;
						}

						for (i = 1; i <= cnt; i++)
						{
							printf("\n");
							printf("* * * * * * * * * * * * * * * * * * * * * * * *");
							printf("\npatient number : %d\n", pat[i].pid);
							printf("patient first name:");
							puts(pat[i].fname);
							printf("\n");
							printf("patient last name:");
							puts(pat[i].lname);
							printf("\n");
							printf("patient age: %d\n", pat[i].age);
							printf("patient gender: %c\n", pat[i].gender);
							printf("patient admission date: %d %d %d \n", pat[i].add, pat[i].amm, pat[i].ayy);
							printf("patient discharge date : %d %d %d \n", pat[i].ddd, pat[i].dmm, pat[i].dyy);
							printf("patient area :");
							puts(pat[i].area);
							printf("\n");
							printf("* * * * * * * * * * * * * * * * * * * * * * * *");
							printf("\n");
						}
					}
				}
			}

			break;
		case 5://Patients treated under the female doctor area wise and sorting of area in ascending order
			point = fopen("doctorfile.txt", "r+");
			if (point == NULL)
				printf("Failed to open file");
			else
			{
				while (fread(&d, sizeof(struct doc), 1, point))
				{
					if (d.gender == 'f')
					{
						printf("\n\nDOCTOR NAME:%s %s", d.fname, d.lname);
						printf("\nDOCTOR ID:%d", d.docid);
						FILE * fp;
						fp = fopen("doc_pa.txt", "r+");
						int P[10], cnt = 0, i, j = 0, flag;
						while (fread(&pd, sizeof(struct doc_pa), 1, fp))
						{
							if (d.docid == pd.docid)
							{
								P[cnt] = pd.pid;
								cnt++;
							}
						}

						fclose(fp);
						fp = fopen("patient_doc.txt", "r+");
						while (fread(&p, sizeof(struct patient), 1, fp))
						{
							for (i = 0; i < cnt; i++)
							{
								if (P[i] == p.pid)
								{
									pat[j] = p;
									j++;
								}
							}
						}

						fclose(fp);
						printf("\nPATIENTS TREATED UNDER FEMALE DOCTOR AREAWISE:");
						for (i = 1; i < cnt; i++)
						{
							flag = 0;
							for (j = 0; j < cnt - i; j++)
							{
								if (strcmp(pat[j + 1].area, pat[j].area) < 0)
								{
									temp = pat[j];
									pat[j] = pat[j + 1];
									pat[j + 1] = temp;
									flag = 1;
								}
							}

							if (flag == 0)
								break;
						}

						for (i = 0; i < cnt; i++)
						{
							printf("\n");
							printf("* * * * * * * * * * * * * * * * * * * * * * * *");
							printf("\npatient number : %d\n", pat[i].pid);
							printf("patient first name:");
							puts(pat[i].fname);
							printf("\n");
							printf("patient last name:");
							puts(pat[i].lname);
							printf("\n");
							printf("patient age: %d\n", pat[i].age);
							printf("patient gender: %c\n", pat[i].gender);
							printf("patient admission date: %d %d %d \n", pat[i].add, pat[i].amm, pat[i].ayy);
							printf("patient discharge date : %d %d %d \n", pat[i].ddd, pat[i].dmm, pat[i].dyy);
							printf("patient area :");
							puts(pat[i].area);
							printf("\n");
							printf("* * * * * * * * * * * * * * * * * * * * * * * *");
							printf("\n");
						}
					}
				}
			}

			break;
	}
}
