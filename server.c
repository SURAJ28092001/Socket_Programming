#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

void write_file(int server_sock)
{
	int n;
	FILE *fp;
	char *filename = "receive.txt";
	char buffer[2000];

	fp = fopen(filename,"w");
	while(1)
	{
		n = recv(server_sock,buffer,2000,0);
		if(n <= 0)
		{
			break;
			return;
		}
		fprintf(fp,"%s",buffer);
		bzero(buffer,2000);
	}
	return;
}

int main()
{
	char *ip = "127.0.0.1";
	int port = 10000;

	int client_sock,server_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size;

	char buffer[2000];
	int n;
	
	server_sock = socket(AF_INET,SOCK_STREAM,0);
	if(server_sock < 0)
	{
		printf("[-]Not connected to socket.\n");
		exit(1);
	}
	printf("[+]Socket connected successfully.\n");

	memset(&server_addr,'\0',sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip);

	n = bind(server_sock, (struct sockaddr*)&server_addr,sizeof(server_addr));
	if(n < 0)
	{
		printf("[-]Error in binding to port.\n");
		exit(1);
	}
 
	printf("[+]Connected to port : %d \n",port);
	
	listen(server_sock,1);
	printf("Listening.....\n");

	addr_size = sizeof(client_addr);
	client_sock = accept(server_sock,(struct sockaddr*)&client_addr, &addr_size);

	bzero(buffer,2000);
	recv(client_sock,buffer,sizeof(buffer),0);
	printf("%s",buffer);

	bzero(buffer,2000);
	strcpy(buffer,"Server : Hi Client !!! \n");
	printf("%s",buffer);
	send(client_sock,buffer,strlen(buffer),0);

	char input[5];
	double a,b;
	double c;

	while(1)
	{
		bzero(buffer,2000);
		strcpy(buffer,"Enter the operation to be done. \n Enter + for addition, - subtraction and so on. \n Type 'e' to exit. \n");
		printf("%s",buffer);
		send(client_sock,buffer,strlen(buffer),0);

		bzero(input,5);
		read(client_sock,input,sizeof(input));
		printf("Client : %s \n",input);

		if(strcmp(input,"e") == 0)
			break;
		if(strcmp(input,"+") != 0 && strcmp(input,"-") != 0 && strcmp(input,"*") != 0 && strcmp(input,"/") != 0)
		{
			bzero(buffer,2000);
			strcpy(buffer,"Invalid operation !!! Please try again.");
			printf("%s",buffer);
			write(client_sock,buffer,sizeof(buffer));
			continue;
		}
		a = 0.0;
		b = 0.0;
		//printf("0");
		bzero(buffer,2000);
		//printf("1");
		strcpy(buffer,"Enter the value of a : \n");
		//printf("2");
		printf("%s",buffer);
		write(client_sock,buffer,strlen(buffer));

		//bzero(a,10);
		read(client_sock,&a,sizeof(a));
		printf("Client : %f \n",a);

		bzero(buffer,2000);
		strcpy(buffer,"Enter the value of b : \n");
		printf("%s",buffer);
		write(client_sock,buffer,strlen(buffer));

		//bzero(b,10);
		read(client_sock,&b,sizeof(b));
		
		printf("Client : %f \n",b);

		c = 0.0;
		if(strcmp(input,"+") == 0)
		{
			c = a + b;
			printf("%lf \n",c);
			write(client_sock,&c,sizeof(c));
		}
		else if(strcmp(input,"-") == 0)
		{
			c = a - b;
			printf("%lf \n",c);
			write(client_sock,&c,sizeof(c));
		}
		else if(strcmp(input,"*") == 0)
		{
			c = a * b;
			printf("%lf \n",c);
			write(client_sock,&c,sizeof(c));
		}
		else if(strcmp(input,"/") == 0)
		{
			c = a / b;
			printf("%lf \n",c);
			write(client_sock,&c,sizeof(c));
		}

	}
		write_file(client_sock);
		printf("[+]File saved successfully \n");

	

	return 0;
}
