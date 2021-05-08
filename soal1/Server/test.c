#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

void take_filename(char filepath[], char filename[])
{
	char *check, str[1024];
	check = strtok(filepath, "/");
	while(check != NULL)
	{
		strcpy(str, check);
		check = strtok(NULL, "/");
	}
	strcpy(filename, str);
}

void take_ekstensi(char filename[], char ekstensi[])
{
	char *check;
	check = strtok(filename, ".");
	check = strtok(NULL, ".");
	strcpy(ekstensi, check);
}


void get_deskripsi(char deskripsi[], char isi[])
{
	char *check, filepath[1024], publisher[1024], tahun[1024];
	check = strtok(isi, "\t");
	strcpy(filepath, check);
	printf("%s\n", filepath);
	check = strtok(NULL, "\t");
	strcpy(publisher, check);
	printf("%s\n", publisher);
	check = strtok(NULL, "\t");
	strcpy(tahun, check);
	printf("%s\n", tahun);



	// Nama file
	strcat(deskripsi, "Nama: ");
	char filename[1024], cf[1024];
	strcpy(cf, filepath);
	take_filename(cf, filename);
	strcat(deskripsi, filename);
	strcat(deskripsi, "\n");

	// Publisher
	strcat(deskripsi, "Publisher: ");
	strcat(deskripsi, publisher);
	strcat(deskripsi, "\n");

	// Tahun
	strcat(deskripsi, "Tahun Publishing: ");
	strcat(deskripsi, tahun);

	// Ekstensi File
	strcat(deskripsi, "Ekstensi File: ");
	char cn[1024], ekstensi[1024];
	strcpy(cn, filename);
	take_ekstensi(cn, ekstensi);
	strcat(deskripsi, ekstensi);
	strcat(deskripsi, "\n");

	// Filepath
	strcat(deskripsi, "Filepath :");
	strcat(deskripsi, filepath);
	strcat(deskripsi, "\n\n");
}

void see_file()
{
	FILE *fp = fopen("files.tsv", "r");
	char isi[1024], deskripsi_total[1024] = {0};
	while(fgets(isi, sizeof(isi), fp))
	{
		printf("Scanning\n");
		char deskripsi[1024] = {0};
		get_deskripsi(deskripsi, isi);
		strcat(deskripsi_total, deskripsi);
	}
	fclose(fp);

	printf("%s\n", deskripsi_total);
}

int main()
{
	printf("Mulai\n");
	see_file();
}