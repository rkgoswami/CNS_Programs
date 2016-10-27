/*
    Problem : Generate the all 16 round key each of 48-bit from given 64-bit key of DES algorithm
    BY:
        Rishav Kumar Goswami
*/
#include <iostream>
#include "desHeader.h"      /* Self made header file to facilite the saving of 
                            static table and utility functions for DES encryption*/


using namespace std;

/* Please make sure the you have included user-defined header file named "desHeader.h" 
    which included following :
        - Permutation choice 1 table (in form of matrix "int PChoice1[8][7]")
        - Permutation choice 2 table (in form of matrix "int PChoice2[6][8]")
        - Shift Value Table (in form of array "int ShiftVal[16]") for shift operation to generate C[i] and D[i]
*/

//covert the hexadecimal to binary string
string hexToBinary(string hexa){

    int i=0;
    int len = hexa.length();
    cout<<"\nBinary equivalent: ";
    string binStr="";
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
             default:  cout<<"nInvalid hexadecimal digit "<<hexa[i];
         }
         i++;        
    }

    return binStr;
}

string generatePChoiceOneKey(string tempKey){

    string PChoiceOutput="";
    for(int i=0;i<8;++i){
        for(int j=0;j<7;++j){
            //int ch = PChoice1[i][j]-1;
            PChoiceOutput+=tempKey[PChoice1[i][j]-1];
        }
    }
    return PChoiceOutput;
}

string generatePChoiceTwoKey(string tempKey){

    string PChoiceOutput="";
    for(int i=0;i<6;++i){
        for(int j=0;j<8;++j){
            PChoiceOutput+=tempKey[PChoice2[i][j]-1];
        }
    }
    return PChoiceOutput;
}

void generateNthDesKey(string Key[2],int round){

    //Step 1 : Rotate Left both left and right subKey by given shift value

    //extract the shift value
    int shift = ShiftVal[round];

    //rotate right string
    string rotChar = Key[0].substr(0,shift);
    
    //delete the #shift characters from begining and append it to end
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

    //Take input both plainText and the key
	string key;
	cout<<"\nEnter the key :";
	cin>>key;
	//convert the key to binaryString
	string BinKeyStr = hexToBinary(key);
    cout<<"\nLength = "<<BinKeyStr.length();
	cout<<"\nBinkeyStr = "<<BinKeyStr;

    //Step 1 : Perform P-Choice 1 on 64-bit BinKeyStr and extract only 56-bit
    string bin56Key = generatePChoiceOneKey(BinKeyStr);

    //Step 2 :
    string KeyStr[2];
    KeyStr[0]=bin56Key.substr(0,28);
    KeyStr[1]=bin56Key.substr(28,28);

    string nthKeyValue;
    cout<<"\nGenerated key are :\n";
    //generate nth round key here i represent the rounds
    for(int i=0;i<16;++i){

        generateNthDesKey(KeyStr,i);
    
        //Perform PChoice2
        nthKeyValue=""+KeyStr[0]+KeyStr[1];
        nthKeyValue = generatePChoiceTwoKey(nthKeyValue);
        cout<<"\nKey "<<i+1<<":"<<nthKeyValue;
    }

    cout<<"\n";
    return 0;
}

