/* 10. Implement RSA algorithm using client-server concept. The program should support the following :
 * i. Client generates {PU, PR} and distributes PU to Server.
 * ii. Sever encrypts message M using client’s public key {PU}.
 * iii.	Client decrypts the message sent by server using its private key {PR}.
 *
 * Author: Shyam Gaurav Venkatesh.    
*/ 

//Server side code.

#include <iostream>
#include <cmath>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int myModulus(int a, int x, int n)
{
	int seed = a%n;
	int prev, next;
	prev = seed;
	for(int i = 2; i <= x; i++)
	{
		next = (seed * prev) % n;
		prev = next;
	}
	return next;
}

int main()
{
	//SETTING UP CONNECTION.
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[3];
	struct sockaddr_in serv_addr, cli_addr;
	portno = 3894;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		error("Error opening socket\n");
	}
	
	memset((char *) &serv_addr,'\0', sizeof(serv_addr));
	
	//Add details to the server address structure for binding.
	serv_addr.sin_family = AF_INET;  		   //IPv4 protocol.
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //Connect to localhost.
	serv_addr.sin_port = htons(portno);
	
	//bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
	//Bind maps the file descriptor fd to the given sockaddr for accepting connections.
	if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
	{
		error("Failed to bind socket\n");
	}
	
	listen(sockfd, 5);
	cout<<"LISTENING\n";
	clilen = sizeof(cli_addr);
	

	newsockfd = accept(sockfd,(struct sockaddr*) &cli_addr, &clilen);
	if(newsockfd < 0)
		error("Error accepting connection\n");
		
	cout<<"Client connected successfully\n";
	//ACCEPT PU.
	recv(newsockfd,buffer,3,0);
	int e,p,q,n;
	e = buffer[0];
	p = buffer[1];
	q = buffer[2];
	n = p*q;
	cout<<"e = "<<e<<endl;
	cout<<"n = "<<n<<endl;
	cout<<"Enter the message\n";
	int msg;
	cin>>msg;
	int eMsg = myModulus(msg,e,n);
	cout<<"emsg = "<<eMsg<<endl;
	//Send this message back to the client for decrpytion.
	char *sendBuffer = new char[1];
	sendBuffer[0] = eMsg;
	send(newsockfd,sendBuffer,1,0);
}