#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

void send_file(FILE *fp, int sock)
{
	int n;
	char data[2000] = {0};
	while(fgets(data,2000,fp) != NULL)
	{
		if(send(sock,data,sizeof(data),0) == -1)
		{
			printf("[-]Error in sending file. \n");
			exit(1);
		}
		bzero(data,2000);
	}
}

int main()
{
	char *ip = "127.0.0.1";
	int port = 10000;

	int sock;
	struct sockaddr_in addr, client_addr;
	socklen_t addr_size;

	char buffer[2000];
	int n;
	
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("[-]Not connected to socket.\n");
		exit(1);
	}
	printf("[+]Socket connected successfully.\n");

	memset(&addr,'\0',sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ip);

	connect(sock, (struct sockaddr*)&addr,sizeof(addr));

	printf("[+]Connected to port : %d \n",port);

	bzero(buffer,2000);
	strcpy(buffer,"Client : Hi Server !!! \n");
	printf("%s",buffer);
	send(sock,buffer,strlen(buffer),0);

	bzero(buffer,2000);
	recv(sock,buffer,sizeof(buffer),0);
	printf("%s",buffer);

	char input[5];
	double a,b;
	double c;

	while(1)
	{
		bzero(buffer,2000);
		read(sock,buffer,sizeof(buffer));
		printf("Server : %s",buffer);

		bzero(input,5);
		scanf("%s",input);
		write(sock,input,strlen(input));

		if(strcmp(input,"e") == 0)
			break;
		if(strcmp(input,"+") != 0 && strcmp(input,"-") != 0 && strcmp(input,"*") != 0 && strcmp(input,"/") != 0)
		{
			bzero(buffer,2000);
			read(sock,buffer,sizeof(buffer));
			printf("Server : %s \n",buffer);
			continue;
		}

		a = 0.0;
		b = 0.0;

		bzero(buffer,2000);
		read(sock,buffer,sizeof(buffer));
		printf("Server : %s",buffer);

		// //bzero(a,10);
		scanf("%lf",&a);
		write(sock,&a,sizeof(a));

		bzero(buffer,2000);
		read(sock,buffer,sizeof(buffer));
		printf("Server : %s",buffer);

		//bzero(b,10);
		scanf("%lf",&b);
		write(sock,&b,sizeof(b));
		
		c = 0.0;
		read(sock,&c,sizeof(c)); 
		printf("Server : The answer is : %lf \n",c);
	}

	FILE *fp;
	char *filename = "sample.txt";
	fp = fopen(filename,"r");
	if(fp == NULL)
	{
		printf("[-]Error in reading file. \n");
		exit(1);
	}
	send_file(fp,sock);
	printf("[+]File data sent successfully. \n");

	close(sock);



	return 0;
}
	