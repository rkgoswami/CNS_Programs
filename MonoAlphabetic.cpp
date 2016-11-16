/*
	Q 12:
    Problem : Implementation of MonoAlphabetic Encryption Scheme
    BY:
        Rishav Kumar Goswami
*/


#include <bits/stdc++.h>

using namespace std;

void encryptFileData(vector<char> randomAlpha){
	
   	// open input file in read mode.
   	ifstream infile; 
   	infile.open("input.txt");

   	//open the output file in write mode
   	ofstream outfile;
   	outfile.open("output.txt");
   	char x;
   	while (infile >> x){
   		int idx = x - 'a';
    	outfile << randomAlpha[idx];
	}
   	// close the opened file.
   	infile.close();
   	outfile.close();
}

void constructFrequencyTable(vector<char>randomAlpha){

	//opening both file in input mode
	ifstream infile1,infile2; 
   	infile1.open("input.txt");
   	infile2.open("output.txt");

   	//intializing the frequency with 0
   	int inFrequency[26];
   	memset(inFrequency,0,26*sizeof(int));

   	int outFrequency[26];
   	memset(outFrequency,0,26*sizeof(int))	;

	double cCount=0.0;
   	char x;
   	while (infile1 >> x){
   		int idx = x - 'a';
   		inFrequency[idx]++;
   		cCount++;
	}
	while (infile2 >> x){
   		int idx = x - 'A';
    	outFrequency[idx]++;
	}

	x='a';
	cout<<"\n===============================================";
	cout<<"\nFrequency\tPlain text\tCipher text";
	cout<<"\n===============================================";
	for (int i = 0; i < 26; ++i){
		cout<<"\n"<<(inFrequency[i]/cCount)<<"\t\t"<<char(x+i)<<"\t\t"<<randomAlpha[i];
	}
	cout<<"\n===============================================\n";

	infile1.close();
   	infile2.close();
}



int main(){

	/*
		Creaate it first in same directory:
		-----------------------------------
   		input file name - input.txt (create before hand with some alphabets in it say 'aasdfghjkdfghjkl......n letters')
   		output file name -  output.txt (empty)
   	*/

	/* 	MonoAlphabetic Cipher:
		======================
		Step 1: Declare a vector<char> and intialize with all 26 alphabets
		Step 2: Shuffle the vector element using built-in shuffle function of vector
		Step 3: Display the mapping table i.e original -> mapped letter
		Step 4: Call the function encryptFileData() which read the data from input file
				and map it according to the mapping table and store it in output file
		Step 5: Call the constructFrequencyTable which counts the frequency of letter in both file 
				and display it as desired form
	*/

	//Step 1:
	vector<char> randomAlpha;
  	char ch = 'A';
  	for (int i=0; i<26; ++i) 
  		randomAlpha.push_back(ch + i); 

  	//Using built-in random generator:
  	std::random_shuffle ( randomAlpha.begin(), randomAlpha.end() );

  	//Print out corresponding mapping table generated randomly
  	vector<char>::iterator itr;

  	cout<<"\n=========================";
  	cout<<"\nAlphabet Mapping Table:";
  	cout<<"\n=========================";
  	ch = 'a';
  	int i=0;
  	for (itr=randomAlpha.begin(); itr!=randomAlpha.end(); ++itr){
  		cout<<"\n"<<char(ch+i)<<" -> "<< *itr;
  		i++;
  	}
   	cout<<"\n=========================\n";

	encryptFileData(randomAlpha);
	constructFrequencyTable(randomAlpha);

	
	return 0;
}