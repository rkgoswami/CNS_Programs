#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

void connectionSetup(int &sockfd){

	struct sockaddr_in server,client;

	//intialize the socket file discriptor
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero((char*)&server,sizeof(server));

	//assign value to sockadd_in members
	server.sin_family = AF_INET;
	server.sin_port = htons(4912);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//binding 
	connect(sockfd,(struct sockaddr*)&server,sizeof(server));

	cout<<"\nUser B is connected to User A successfully..";

}

int gcd(int a,int b){
	if(b==0)
		return a;
	gcd(b,a%b);	
}

int RSA_EncryptAndDecrypt(long Pi,int key[]){

	long val = Pi % key[1];
	long temp = 1;

	for (int i = 1; i <= key[0]; ++i){
		temp=(temp *val)%key[1];
	}

	return temp;
}

int main(int argc, char const *argv[]){
	
	int sockfd;
	connectionSetup(sockfd);


	//generate the Public and Private keys {PU,PR}
	int p,q;
	cout<<"\nEnter the value of p and q (both must prime): ";
	cin>>p>>q;

	int n = p*q;

	//find phi(n)
	int phi_n = (p-1)*(q-1);

	//take input e such that gcd(e,phi_n)=1
	int e;
	cout<<"\nEnter the value of e (prime) relative to "<<phi_n<<" : ";
	cin>>e;

	while(gcd(e,phi_n)!=1){
		cout<<"\nRe-Enter the value of e (prime) relative to "<<phi_n<<" : ";
		cin>>e;
	}

	//calculate d 

	int d=1;
	while(1){
		if ((e*d)%phi_n ==1){
			break;
		}
		d++;
	}

	cout<<"\n{PU,PR} = { "<<e<<" , "<<d<<" }";

	int PU[] = {e,n};
	int PR[] = {d,n};
 	//send public key to server
	int temp = htons(PU[0]);
 	send(sockfd,&temp,sizeof(temp),0);

	temp = htons(PU[1]);
 	send(sockfd,&temp,sizeof(temp),0);
	

	//send and recieve
	long Ltemp;
	recv(sockfd,&Ltemp,sizeof(Ltemp),0);
	long enMsg = ntohl(Ltemp);
	//decrypt the enMsg
	cout<<"\nRecieved encrypted message : "<<enMsg;

	long msg = RSA_EncryptAndDecrypt(enMsg,PR);

	cout<<"\nRecieved decrypted message : "<<msg;



	cout<<"\n";
	return 0;
}