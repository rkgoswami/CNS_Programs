/*
	Q 12:
    Problem : Implementation of RSA Processing of Multiple Block of 4-decimal digit or 2 alphabets
    BY:
        Rishav Kumar Goswami
*/

#include <bits/stdc++.h>

using namespace std;

long RSAEncryptAndDecrypt(int Pi,int e,long n){

	long val = Pi % n;
	long tVal=1;
	for (int i = 1; i <= e; ++i){
		tVal = (tVal*val)%n;
	}

	return tVal;

}

int gcd(int a,int b){
	if(b==0)
		return a;
	else
		gcd(b,a%b);
}

void displaySet(int Set[],int n){
	for (int i = 0; i < n; ++i){
		cout<<" "<<Set[i];
	}
	cout<<" ]\n";
}

int main(){

	/* 	RSA Algorithm :
		==============
		Step 1: Take input prime p and q
		Step 2: Calculate n = p*q
		Step 3: Calculate fi(n) = fi(p)*fi(q)=(p-1)*(q-1), 
				since both are prime and applying Euler Totient theorem 
		Step 4: Find e such that gcd(e,fi(n))=1
				Step 4.1: Iterate Step 4 until the condition satisfy 
				Step 4.2: Display Public Key as PU = {e,n}
		Step 5: Calculate the Private key
				Step 5.1: Find 'd' such that (d*e) mod fi(n) = 1
				Step 5.2: Display Private Key as PR = {d,n}
		Step 6: Encryption process:
				-------------------
				Step 6.1: Calculate C = M^e mod n 
				Step 6.2: Print the Cipher Text C
		Step 7: Decryption Process:
				-------------------
				Step 7.1: Calculate M = C^d mod n
				Step 7.2: Display the Decrypted text
	*/
	
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
		cout<<"\nReEnter the value of e ( gcd(e,fi(n)) = 1 ): ";
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
	getchar();

	string msg;
	cout<<"\nEnter the message to be encrypted( preferred: even length with only alphabets ) :\n";
	getline(cin,msg);

	/*	RSA Block Processing :
		=====================
		Step 1: Each message block consist of 4 decimal digits or 
				two alphanumeric character i.e a=00 and A=26 and so on
				Step 1.1: if message length is odd the append 'x' at last
		Step 2: For each message block call RSAEncrypt() to encrypt it
		Step 3: Store that in an Array i.e C[i] representing cipher text
		Step 4: For each element in C[], call RSADecrypt() to decrypt it
	*/

	//Step 1:	
	int len = msg.length();
	//Step 1.1:
	if(len%2!=0){
		len+=1;
		msg+='x';
	}
	int C[len/2 +1],P[len];
	int k=0;
	for (int i = 0; i < len;i+=2){
		int x[2];
		for (int j = 0; j < 2; ++j){
			if(isupper(msg[i+j])){
				x[j]=msg[i+j]-'A'+26;
			}
			else{
				x[j]=msg[i+j]-'a';
			}	
		}
		P[k]=(x[0])*100 + (x[1]);
		//Step 2 & 3:
		C[k]=RSAEncryptAndDecrypt(P[k],e,n);
		k++;	
	}
	
	cout<<"\nGenerated Decimal Plain Set : [";
	displaySet(P,k);
	
	cout<<"\nGenerated Encryption Set : [";
	displaySet(C,k);
		
	//Step 4:
	string DecMsg="";
	int D[k];
	for (int i = 0; i < k;i++){
		D[i]=RSAEncryptAndDecrypt(C[i],d,n);	
	}
	cout<<"\nRecovered Decimal Decrypted Set : [";
	displaySet(D,k);

	cout<<"\n";
	return 0;
}