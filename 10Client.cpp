/* 10. Implement RSA algorithm using client-server concept. The program should support the following :
 * i. Client generates {PU, PR} and distributes PU to Server.
 * ii. Sever encrypts message M using client’s public key {PU}.
 * iii.	Client decrypts the message sent by server using its private key {PR}.
 *
 * Author: Shyam Gaurav Venkatesh.    
*/ 


// Client side code.
#include <iostream>
#include <cmath>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

char* createPublicKey(int e, int p, int q)
{
	char *temp = new char[3];
	temp[0] = char(e);
	temp[1] = char(p);
	temp[2] = char(q);
	return temp;
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
	int p,q,n,e,d;
	cout<<"Enter 2 prime numbers p and q\n";
	cin>>p>>q;
	//TODO: Check if p and q are prime.
	n = p*q;
	cout<<"Enter value of e\n";
	cin>>e;
	//TODO: Check if e satisfies condition.
	//Calculate phi(n)
	int phi = (p-1) * (q-1);
	cout<<"phi = "<<phi<<endl;
	//Now, PU = {e,n} and PR = {d,n}
	int res = 0;
	d = 0;
	while(res != 1)
	{
		d++;
		res = (d * e) % phi; 
	}
	//SETTING UP CONNECTION.
	int sockfd,portno;
	char *buffer = new char[1];
	struct sockaddr_in serv_addr;
	socklen_t servlen;
	portno = 3894;
	//Create the socket for client.
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	//Add details for the server address structure.
	serv_addr.sin_family = AF_INET;  		   //IPv4 protocol.
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //Connect to localhost.
	serv_addr.sin_port = htons(portno);
	
	memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);
	
	servlen = sizeof(serv_addr);
	
	//Connect to the server.
	connect(sockfd, (struct sockaddr*) &serv_addr, servlen);

	//SEND PU TO SERVER.
	char *publicKey = createPublicKey(e,p,q);
	send(sockfd,publicKey,3,0);

	//TODO: Recieve encrypted message from server.
	cout<<"d = "<<d<<endl;
	//Now, use private key to decrypt the message.
	recv(sockfd,buffer,1,0);
	int msg = buffer[0];
	int dMsg = myModulus(msg,d,n);
	cout<<"After decryption, the message is\n";
	cout<<dMsg<<endl;
}
