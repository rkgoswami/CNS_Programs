/*
    Problem : Generate the 48-bit input to given to the S-Box Operation to generate the 32-bit output. 
    BY:
        Rishav Kumar Goswami
*/
#include <iostream>
#include "desHeader.h" /*Self made header file to facilite the saving of static 
						table and utility functions for DES encryption*/


using namespace std;

//covert the hexadecimal to binary string
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


//expand from 32-bit to 48-bit 
string ExpansionPermutationFunction(string RightStr){
	int ExpPT[8][6];
	int num=0;
	
	for(int i=0;i<8;i++){
		for(int j=1;j<5;++j){
			ExpPT[i][j]=RightStr[num];
			num++;
		}
	}
	//first column added to the table 
	int k=7;
	for(int i=0;i<8;++i){
		ExpPT[i][0]=ExpPT[k][4];
		k=(k+1)%8;
	}
		
	//last column added to the table 
	k=1;
	for(int i=0;i<8;++i){
		ExpPT[i][5]=ExpPT[k][1];
		k=(k+1)%8;
	}
	
	//extract string out of the 2d table
	string temp="";
	for(int i=0;i<8;++i){
		for(int j=0;j<6;++j){
			temp+=ExpPT[i][j];
		}
	}
	
	return temp;
}



int main()
{
	
	/* Given Input:
		- i-th round 64-bit output of DES 
		- i-th round 56-bit key 
	   OutPut:
	   	- 48-bit input for S-Box operation	
	*/

	/* 	Algorithm:
		=========
		Step 1: Split the Input( i.e 64-bit i-th round Output of DES) into 2-half each of 32-bit i.e LeftStr and RightStr
		Step 2: (i+1)-th LeftStr = RightStr i.e store it in output result 
		Step 3: Motivation: (i+1)-th RightStr = LeftStr (XOR) EncryptionFunction(RightStr[i],Key[i])
				Step 3.1: Perform Expansion on the 32-bit string to 48-bit string using ExpansionPermutaionFunction()
				Step 3.2: Perform XOR on 48-bit OutPut of above(Step 3.2) expansion and the 48-bit Key Input for i-th round.
		Step 4: Print the Xor Output, Since it is to be passed to the S-Box 
	*/

	string des64output;
	cout<<"\nEnter the i-th round output of DES( 16-hex digit ) : ";
	cin>>des64output;
	//convert the hexadecimal input to 64-bit binary string
	string binDesOutput =  hexToBinary(des64output);

	string RoundKey;
	cout<<"\nEnter the i-th round key( 16-hex digit ) : ";
	cin>>RoundKey;
	//convert the hexadecimal input to 64-bit binary string
	string ithRoundKey =  hexToBinary(RoundKey);


	//Step 1
	string LeftStr=binDesOutput.substr(0,32);
	string RightStr=binDesOutput.substr(32,32);

    //print the LeftStr and RightStr
    cout<<"\nL[i]="<<LeftStr;
    cout<<"\nR[i]="<<RightStr;

    //Step 2
    string result = ""+RightStr;
    
    //Step 3.1 
	string RightStr48 = ExpansionPermutationFunction(RightStr);

	//Step 3.2
	string XorResult="";

	unsigned short a;
	unsigned short b;
	for(int i=0;i<48;++i){
		a=(unsigned short)(RightStr48[i]-'0');
		b=(unsigned short)(ithRoundKey[i]-'0');
		XorResult+=((a^b)+'0');
	}

	//Step 4
	cout<<"\nOutput of XOR(RightStr,Key)which is Input to S-Box :\n "<<XorResult<<"\n";


	return 0;
}