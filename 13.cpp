/* 13. Compute common secret key between client and server using Diffie-Hellman
 * key exchange technique. Perform encryption and decryption of message using
 * the shared secret key (Use simple XOR operation to encrypt and decrypt the  
 * message.)  
 *
 * Author: Shyam Gaurav Venkatesh.    
*/ 
 
#include <iostream> 
#include <cmath> 
#include <map> 
using namespace std;


int main()
{
	int alpha,Xa,Xb,q;
	cout<<"Enter values of alpha, Xa, Xb and q\n";
	cin>>alpha>>Xa>>Xb>>q;

	if(alpha >= q)
	{
		cout<<"Invalid input, alpha < q is a required condition\n";
		return -1;
	}

	long long Ya,Yb;
	Ya = pow(alpha,Xa);
	Ya = Ya % q;
	Yb = pow(alpha,Xb);
	Yb = Yb % q;

	long long Ka = pow(Yb,Xa);
	Ka = Ka % q;
	long long Kb = pow(Ya,Xb);
	Kb = Kb % q;

	cout<<"Given:\nalpha = "<<alpha<<endl;
	cout<<"Xa = "<<Xa<<endl;
	cout<<"Xb = "<<Xb<<endl;
	cout<<"We get\n";
	cout<<"Ya = "<<Ya<<endl;
	cout<<"Yb = "<<Yb<<endl;
	cout<<"Keys generated\n";
	cout<<"Ka = "<<Ka<<endl;
	cout<<"Kb = "<<Kb<<endl;

}