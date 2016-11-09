#include <bits/stdc++.h>

using namespace std;

string hexToBinary(string hexa){
	
    int i=0;
    string binStr="";
	int len = hexa.length();
    while(i<len)
    {
        switch(hexa[i])
        {
       		case '0': binStr+="0000"; break;
            case '1': binStr+="0001"; break;
            case '2': binStr+="0010"; break;
            case '3': binStr+="0011"; break;
            case '4': binStr+="0100"; break;
            case '5': binStr+="0101"; break;
            case '6': binStr+="0110"; break;
            case '7': binStr+="0111"; break;
            case '8': binStr+="1000"; break;
    	    case '9': binStr+="1001"; break;
            case 'A': binStr+="1010"; break;
            case 'B': binStr+="1011"; break;
            case 'C': binStr+="1100"; break;
            case 'D': binStr+="1101"; break;
            case 'E': binStr+="1110"; break;
            case 'F': binStr+="1111"; break;
            case 'a': binStr+="1010"; break;
            case 'b': binStr+="1011"; break;
            case 'c': binStr+="1100"; break;
            case 'd': binStr+="1101"; break;
            case 'e': binStr+="1110"; break;
            case 'f': binStr+="1111"; break;
            default:  cout<<"\nInvalid hexadecimal digit "<<hexa[i];
        }
        i++;
    }
    
    return binStr;
}

int conversionBinToInt(string s){

	int len = s.length();
	int val=0;
	for(int i=len-1,k=0;i>=0;--i,k++){
		val=val+(s[i]-'0')*pow(2,k);
	}

	return val;
}

int SimpleHash(string text){
	/*	Step 1 : Convert the plain text into hex form
		Step 2 : Convert the hex to binary
		Step 3 : Calculate the hash using simple XOR method
		Step 4 : Convert the binStr into integer
		*/  

	//Step 1:
	stringstream ss;
	for(int i=0;i<text.length();++i){
		ss<<hex<<(int)text[i];
	}
	string hexText(ss.str());

	//Step 2:
	string binText = hexToBinary(hexText);

	//Step 3:
	string hashStr="";
	unsigned short a,b,c,d;
	for(int i=0;i<binText.length()-4;i+=4){
		a=(unsigned short)(binText[i]-'0');
		b=(unsigned short)(binText[i+1]-'0');
		c=(unsigned short)(binText[i+2]-'0');
		d=(unsigned short)(binText[i+3]-'0');
		hashStr+=((a^b^c^d)+'0');
	}

	//Step 4:
	int hashVal = conversionBinToInt(hashStr);

	return hashVal;

}

int findInvModQ(int k,int q){
	int invK = 1;
	while(1){
		if( ((k*invK)%q) == 1)
			break;
		invK++; 
	}

	return invK;
}

void signing(string text,int g,int p,int q,int k,int x,int signature[2]){

	/*	Step 1: Calculate r = (g^k mod p)mod q	
		Step 2: Calculate s = ( (k^-1) * (H(M)+xr) )mod q 
				Step 2.1 : Calculate k^-1 = a i.e ( k*a mod q = 1)
				Step 2.2 : Calculate H(M)
				Step 2.2 : Calculate s = ((k^-1)mod q )( (H(M))+xr) mod q)
	*/

	//Step 1:
	int r = ( int(pow(g,k))%p )%q;

	//Step 2.1:
	int invK = findInvModQ(k,q);

	//Step 2.2:
	int hashVal = SimpleHash(text);

	//Step 2.3:
	int s = ( (invK % q) * ((hashVal+(x*r))%q) %q );

	signature[0]=r;
	signature[1]=s;


}

int verify(string text,int signature[2],int p,int q,int g,int y){

	//signature(r,s) i.e r = signature[0] , s = signature[1]

	/*	Step 1: Calculate w = (s')^-1 mod q
		Step 2: Calculate v 
				Step 2.1 : Calculate u1 = [H(M')w]mod q
				Step 2.2 : Calculate u2 = r'w mod q
				Step 2.2 : Calculate v = ( ((g^u1)(y^u2)) mod p ) mod q
		Step 3: return v
	*/

	int w = findInvModQ(signature[1],q) % q;

	int u1 = (SimpleHash(text)*w )% q;
	int u2 = (signature[0]*w )% q;

	int v = ( int(pow(g,u1)*pow(y,u2)) %p ) %q;

	return v;
}

bool checkPrime(int p){

	for(int i=2;i<=sqrt(p);++i){
		if(p%i==0){
			return false;
		}
	}
	return true;
}

int main(){

	/*	Step 1: Input a prime number
		Step 2: Select prime no. (p) such that q divides p-1
		Step 3: Calculate value of g 
			Step 3.1: Randomly generate the h i.e 1 < h < (p-1)
			Step 3.2: Calculate g =  h^((p-1)/q) mod p  i.e g > 1 
		Step 4: Calculate User's Public key 
				- generate the value of x 
				- such that 0<x<q
		Step 5: Calculate User's Private Key
				- y = g^x mod p
		Step 6: Generate the User's Per Message secret key
				- randomly generate the k  

		Step 7: Signing function
		Step 8: Verifying function
		Step 9: if(v==r):
					"Authentic" 
				else:
					"Unauthentic"
	*/


	srand(time(NULL));
	
	//Step 1:
	int q ,p;
	cout<<"\nEnter the prime number i.e q : ";
	cin>>q;

	//Step 2:
	int i=1;
	while(1){
		p = q*i +1;
		if(checkPrime(p)){
			break;
		}
		else
			i++;	
	}
	
	//Step 3:
	int h = rand()%(p-1)+1;
	int g = int(pow(h,(p-1)/q)) % p;

	//Step 4:
	int x=rand()%q;

	//Step 5:
	int y = int(pow(g,x)) % p;

	//Step 6:
	int k = rand()%q;


	cout<<"\nq = "<<q;
	cout<<"\np = "<<p;
	cout<<"\ng = "<<g;
	cout<<"\nx = "<<x;
	cout<<"\ny = "<<y;
	cout<<"\nk = "<<k;

	string msg;
	cout<<"\nEnter the Message : ";
	cin>>msg;

	//Step 7:
	int signature[2];
	signing(msg,g,p,q,k,x,signature);
	cout<<"\nSignature(r,s): ( "<<signature[0]<<" , "<<signature[1]<<" )";

	//Step 8:

	int v = verify(msg,signature,p,q,g,y);

	cout<<"\nVerify(v): "<<v<<endl;

	if(v==signature[0]){
		cout<<"\nAuthentic";
	}
	else{
		cout<<"\nUnauthentic";
	}

	cout<<"\n";

	return 0;
} 
