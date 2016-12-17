/*
    Problem : Generate the 48-bit input to given to the S-Box Operation. 
    BY:
        Rishav Kumar Goswami
*/
#include <iostream>
#include "desHeader.h" /*Self made header file to facilite the saving of static 
						table and utility functions for DES encryption*/


using namespace std;

string generatePChoiceTwoKey(string tempKey){

    string PChoiceOutput="";
    for(int i=0;i<6;++i){
        for(int j=0;j<8;++j){
            PChoiceOutput+=tempKey[PChoice2[i][j]-1];
        }
    }
    return PChoiceOutput;
}

string ExpansionPermutationFunction(string RightStr){

	string temp="";
	for(int i=0;i<8;i++){
		for(int j=0;j<6;++j){
			temp+=RightStr[ExpansionBox[i][j]-1];
		}
	}
	return temp;
}

void generateNthDesKey(string Key[2],int round){

    //Step 1 : Rotate Left both left and right subKey by given shift value

    //extract the shift value
    int shift = ShiftVal[round];

    //rotate right string
    string rotChar = Key[0].substr(0,shift);
    //string temp=Key[0];
    for(int i=0;i<shift;++i)
        Key[0].erase(Key[0].begin());
    Key[0]+=rotChar;

    //rotate left string
    rotChar = Key[1].substr(0,shift);
    for(int i=0;i<shift;++i)
        Key[1].erase(Key[1].begin());
    Key[1]+=rotChar;
}



int main()
{
	
	/* Given Input:
		- i-th round 64-bit output of DES 
		- i-1 th round 56-bit key 
	   OutPut:
	   	- 48-bit input for S-Box operation	
	*/

	/* Algorithm:
	   =========
		Step 0: Apply Left Circular Shift and then PChoic2() on given 56 bit key 
		Step 1: Split the Input( i.e 64-bit i-th round Output of DES) into 2-half 
				each of 32-bit i.e LeftStr and RightStr
		Step 2: (i+1)-th LeftStr = RightStr i.e store it in output result 
		Step 3: Motivation: (i+1)-th RightStr = LeftStr (XOR) EncryptionFunction(RightStr[i],Key[i])
			Step 3.1: Perform Expansion on the 32-bit string to 48-bit string using 
					ExpansionPermutaionFunction()
			Step 3.2:Perform XOR on 48-bit OutPut of above(Step 3.2) expansion and 
					the 48-bit Key Input for i-th round.
		Step 4: Print the Xor Output, Since it is to be passed to the S-Box 
	*/

	int i;
	cout<<"\nEnter the round number(1-16): ";
	cin>>i;

	string binDesOutput;
	cout<<"\nEnter the i-th round output of DES(64-bit binary digit) : ";
	cin>>binDesOutput;

	string bin56Key;
	cout<<"\nEnter the (i-1)th round key(56-bit binary digit) : ";
	cin>>bin56Key;

	//Step 0: Apply Shift and PChoice2() to reduce the 56-bit to 48-bit key
	string KeyStr[2];

    //split the bin56Key into two half each of 28-bit i.e C[i] and D[i]
    KeyStr[0]=bin56Key.substr(0,28);
    KeyStr[1]=bin56Key.substr(28,28);

    //This function perform the shift operation
    generateNthDesKey(KeyStr,i-1);
    
    string ithRoundKey =""+KeyStr[0]+KeyStr[1];
	ithRoundKey = generatePChoiceTwoKey(ithRoundKey);

	//print the ith round key
	cout<<"\nKey "<<i<<": "<<ithRoundKey;
	
	//Step 1
	string LeftStr=binDesOutput.substr(0,32);
	string RightStr=binDesOutput.substr(32,32);

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
	cout<<"\nInput for S-Box :\n "<<XorResult<<"\n";


	return 0;
}