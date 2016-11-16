/*
    Problem : Implementation of RSA Key Distribution
    BY:
        Rishav Kumar Goswami
*/

#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace std;

void connectionSetup(int &sockfd){

	struct sockaddr_in server,client;

	//Step 1: Intialize sockfd
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	bzero((char*)&server,sizeof(server));

	//Step 2: Intialize the struct member
	server.sin_family = AF_INET;
	server.sin_port = htons(4909);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Step 3: binding
	connect(sockfd,(struct sockaddr* )&server,sizeof(server));
	cout<<"\nUser B connected successfully with User A\n";
}

long RSAEncryptAndDecrypt(int Pi,int key[]){

	long val = Pi % key[1];
	long tVal=1;
	for (int i = 1; i <= key[0]; ++i){
		tVal = (tVal*val)%key[1];
	}
	return tVal;
}

int gcd(int a,int b){
	if(b==0)
		return a;
	else
		gcd(b,a%b);
}

int main(){

	cout<<"\n=====================";
	cout<<"\n\tUser B";
	cout<<"\n=====================";
	
	/* 	RSA Algorithm With Key Distribution Scheme:
		==========================================
		Step 0: Setup a TCP connection between User A and User B
		Step 1: Take input prime p and q
		Step 2: Calculate n = p*q
		Step 3: Calculate fi(n) = fi(p)*fi(q)=(p-1)*(q-1), 
				since both are prime and applying Euler Totient theorem 
		Step 4: Find e such that gcd(e,fi(n))=1
				Step 4.1: Iterate Step 4 until the condition satisfy 
				Step 4.2: Display Public Key as PU_b = {e,n} i.e PU_b = e
		Step 5: Calculate the Private key (PR_b)
				Step 5.1: Find 'd' such that (d*e) mod fi(n) = 1
				Step 5.2: Display Private Key as PR_b = {d,n}
	
		Step 6: Recieve the Public key (PU_a) from User A
		Step 7: Share its Public Key(PU_b) to User A
		Step 8: Recieve the message from User A
		Step 9: Decrypt the recieved message using its private key(PR_b) and Send
				-----------------------------------------------------------------
				Step 9.1: Calculate M = C^( PR_b ) mod n
				Step 9.2: Display the Decrypted text
		Step 10: Read message to be send to User B
		Step 11: Encrypt the message using the public key of User B(PU_a) and Send
				-----------------------------------------------------------------
				Step 11.1: Calculate C = M^( PU_a ) mod n 
				Step 11.2: Send the Cipher Text C to User A
		
		
	*/

	//Step 0:
	int sockfd;
	connectionSetup(sockfd);
	
	//Step 1:
	int p,q;
	cout<<"\nEnter the value of p and q (both must be prime): ";
	cin>>p>>q;

	//Step 2:
	long n = p*q;

	//Step 3:
	long fiN = (p-1)*(q-1);

	//Step 4:
	int e;
	cout<<"\nEnter a prime no. 'e' less than "<<fiN<<" : ";
	cin>>e;

	while(gcd(e,fiN)!=1){
		cout<<"\nReEnter the value of PU_b ( gcd(PU_b,fi(n)) = 1 ): ";
		cin>>e;
	}
	cout<<"\nPublic Key : {"<<e<<","<<n<<"}";
	//Step 5:
	int d=1;
	while(1){

		if( (e*d)%fiN == 1)
			break;
		d++;
	}
	cout<<"\nPrivate Key : {"<<d<<","<<n<<"}";

	//Step 6:
	int PU_a[2];
	int temp;
	recv(sockfd,&temp,sizeof(temp),0);
	PU_a[0]=ntohs(temp);
	recv(sockfd,&temp,sizeof(temp),0);
	PU_a[1]=ntohs(temp);

	cout<<"\nRecived Public Key of User A : {"<<PU_a[0]<<","<<PU_a[1]<<"}\n";

	//Step 7:
	int PU_b[] = {e,n};
	int PR_b[] = {d,n};

	temp = htons(e);
	send(sockfd,&temp,sizeof(temp),0);
	temp = htons(n);
	send(sockfd,&temp,sizeof(temp),0);
	cout<<"\nPublic Key is Sent..\n";

	//Step 8:
	long Ltemp;
	recv(sockfd,&Ltemp,sizeof(Ltemp),0);
	long enMsg = ntohl(Ltemp);
	cout<<"\nRecived message from User B : "<<enMsg;
	cout<<"\nDecryting the message....Wait.!!";
	//Step 9:
	cout<<"\nDecrypted Message : "<<RSAEncryptAndDecrypt(enMsg,PR_b);

	//Step 10:
	int msg;
	cout<<"\nEnter the message(a integer) to be sent to User A: ";
	cin>>msg;

	//Step 11:
	cout<<"\nEncrypting the message...";
	enMsg = RSAEncryptAndDecrypt(msg,PU_a);
	Ltemp = htonl(enMsg);
	send(sockfd,&Ltemp,sizeof(Ltemp),0);
	cout<<"\nEncrypted message ("<<enMsg<<") is sent..\n";

	return 0;
}