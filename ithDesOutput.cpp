/*
    Problem : Generate the 32-bit output of RightStr of i-th round of DES. 
    BY:
        Rishav Kumar Goswami
*/
#include <bits/stdc++.h>
#include "desHeader.h" /*Self made header file to facilite the saving of static 
						table and utility functions for DES encryption*/

using namespace std;

/* Please make sure the you have included user-defined header file named "desHeader.h" 
    which included following :
        - S-Box Table (in form of 3D-matrix "int SBox[8][4][16]")
        - Permutation choice 2 table (in form of matrix "int PChoice2[6][8]")
        - Shift Value Table (in form of array "int ShiftVal[16]") for shift operation to generate C[i] and D[i]
*/

int conversionBinToInt(string s){

	int len = s.length();
	int val=0;
	for(int i=len-1,k=0;i>=0;--i,k++){
		val=val+(s[i]-'0')*pow(2,k);
	}

	return val;
}

string conversionIntToBin(int num){
	string binStr="0000";
	int i=3;
	while(num){
		binStr[i--]=(char)(num%2 +'0');
		num/=2;
	}
	return binStr;
}

//conversion of Binary string to hexadecimal
string BinToHexa(string binStr){

 	//first convert the binary string to decimal then convert it to hexadecimal
 	unsigned long result =0 ;
    for(size_t count = 0; count < binStr.length() ; ++count)
    {
        result *=2;
        result += binStr[count]=='1'? 1 :0;
    }

 	//stream buffer to convert the decimal to hex
    stringstream ss;
    ss <<hex<<result;
    string hexVal(ss.str());

    return hexVal;
}


string SBoxFunction(string temp){
	//perform the s-box operation
	
	string SBoxOutput = "";
	for(int i=0,k=0;i<8;++i,k+=6){
		//split the temp string into sub string of 6-bits
		string subTemp=temp.substr(k,k+6);
		//extract xyyyyyx 
		// r = 1st bit+last bit  ie xx and  c = yyyy and covert it to integer
		string r="";
        r+=subTemp[0];
		r+=subTemp[5];
		string c=subTemp.substr(1,4);
		//covert r and c to integer
		int rInt = conversionBinToInt(r); 
		int cInt = conversionBinToInt(c);
		//index the value from s box
		SBoxOutput+=conversionIntToBin(SBox[i][rInt][cInt]);
	}

    return SBoxOutput;
}

string PFunction(string temp){
	//perform the p function permutation
	string PfOutput = "";
	
	for(int i=0;i<4;++i){
		for(int j=0;j<8;++j){
			PfOutput+=temp[PFunTable[i][j]-1];
		}
	}

	return PfOutput;
}

int main()
{
	
	/* Given Input:
		- i-th round 48-bit input for S-Box 
		- i-th round 32-bit Left String  
	   OutPut:
	   	- 32-bit output of RightStr of i-th round of DES.
	*/

	/* 	Algorithm:
		=========
		Step 1: Perform S-Box operation on the 48-bit input given for S-Box operation
		Step 2: Perform Permutation of the output of the S-Box using PFunTable[4][8] defined in "desHeader.h" header file
		Step 3: Perform XOR on 32-bit OutPut of above(Step 2) permutation table and the 32-bit LeftStr Input of (i-1)th round.
		Step 4: Print the Xor Output, Since it is the RightStr of i-th round
	*/
	string str48Input;
	cout<<"\nEnter the 48-bit input for S-Box : ";
	cin>>str48Input;
	string LeftStr;
	cout<<"\nEnter the 32-bit Left String : ";
	cin>>LeftStr;

	//Step 1: Perform S-Box operation on the 48-bit input given for S-Box operation
	string SBoxOutput = SBoxFunction(str48Input);
	
	//Step 2 : Pass the output of S-box to Permutation function 'PFunction()'
	string PfOutput = PFunction(SBoxOutput);

	//Step 3 : Perform XOR with the LeftStr and PfOutput
	string tempRightStr="";
	unsigned short a;
	unsigned short b;
	for(int i=0;i<32;++i){
		a=(unsigned short)(LeftStr[i]-'0');
		b=(unsigned short) (PfOutput[i]-'0');
		tempRightStr+=((a^b)+'0');
	}
	//Step 4 : Print the Xor Output, Since it is the RightStr of i-th round
	cout<<"\nThe 32-bit output of RightStr of i-th round of DES : \n"<<tempRightStr<<"\n";
	
	return 0;
}