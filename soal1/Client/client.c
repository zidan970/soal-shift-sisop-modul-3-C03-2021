#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

// Client Variables
struct sockaddr_in address;
int sock = 0;
struct sockaddr_in serv_addr;

// Other Variables
bool status;
bool logged_in;

void send_to_server(char *message)
{
	send(sock, message, strlen(message), 0);
}

void read_from_server(char buffer[])
{
	int r;
	r = read(sock, buffer, 1024);
}

int main(int argc, char const *argv[])
{

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("\n Invalid Address/ Address not Supported \n");
		return -1;
	}

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed\n");
		return -1;
	}
	
	// Read welcome message
	char welcome[1024]= {0};
	read_from_server(welcome);
	printf("%s\n", welcome);

	// Login or Register
	status = false;
	logged_in = false;
	while(!status)
	{
		char input[10];
		scanf("%s", input);
		send_to_server(input);

		char output[1024] = {0};
		read_from_server(output);
		printf("%s ", output);

		// Login
		if(strcmp(input, "1") == 0)
		{
			char id[1024];
			scanf("%s",id);
			send_to_server(id);

			char output0[1024] = {0};
			read_from_server(output0);
			printf("%s ", output0);

			char pass[1024];
			scanf("%s",pass);
			send_to_server(pass);

			char output1[1024] = {0};
			read_from_server(output1);
			printf("%s\n", output1);
			if(strcmp(output1, "You are logged in!") == 0)
			{
				status = true;
				logged_in = true;
			}
			else
			{
				// Invalid login
			}
		}

		// Register
		else if(strcmp(input, "2") == 0)
		{
			char id[1024];
			scanf("%s",id);
			send_to_server(id);

			char output0[1024] = {0};
			read_from_server(output0);
			printf("%s\n", output0);

			char pass[1024];
			scanf("%s",pass);
			send_to_server(pass);

			char output1[1024] = {0};
			read_from_server(output1);
			printf("%s ", output1);

			status = true;
			logged_in = true;
		}

		else
		{
			printf("\nYou are not supposed to be here\n");
		}
	}

	
	if(!logged_in)
	{
		printf("You are not allowed here!\n");
		exit(1);
	}

	status = false;
	while(!status)
	{

		// Read command list
		printf("Running the app\n");

		printf("Masukkan Command: ");
		char comm[1024];
		scanf("%s",comm);
		send_to_server(comm);

		if(strcmp(comm,"add") == 0)
		{
			// Publisher
			char pub[1024] = {0};
			read_from_server(pub);
			printf("%s ", pub);
			char publisher[1024];
			scanf("%s",publisher);
			send_to_server(publisher);

			// Tahun
			char year[1024] = {0};
			read_from_server(year);
			printf("%s ", year);
			char tahun[1024];
			scanf("%s",tahun);
			send_to_server(tahun);

			// Filepath
			char f[1024] = {0};
			read_from_server(f);
			printf("%s ", f);
			char filepath[1024];
			scanf("%s",filepath);
			send_to_server(filepath);

			// Read output
			char output[1024] = {0};
			read_from_server(output);
			printf("%s\n", output);
		}
		else if(strcmp(comm, "see") == 0)
		{
			printf("\n");
			char output[1024] = {0};
			read_from_server(output);
			printf("%s\n", output);
		}
		else
		{
			printf("Error\n");
		}
	}
	return 0;
}