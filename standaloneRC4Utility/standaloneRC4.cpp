#include <iostream>
#include <string>
#include <fstream>
#include "rc4_enc.c"
#include "rc4_skey.c"
using namespace std;


// Encrypt/decrypt function
void encryptDecrypt(int argc, char *argv[]); 

//Main
int main(int argc, char *argv[]){
	
	if(argc > 8){

		cerr << "Too many file names given: " << argc << endl;
		return 0;}
	else if(argc < 6){
		cerr << "You must provide a file name." << endl;
		return 0;
	}
	else if (strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-d") != 0)
	{
		cerr << "You must choose either -d or -e" << endl;
		return 0;
	}
	else if (strcmp(argv[2], "-k") != 0)
	{
		cerr << "You must provide a key value." << endl;
		return 0;
	}

	else if (strcmp(argv[4], "-in") != 0)
	{
		cerr << "Please provide an input file." << endl;
		return 0;
	}

	else{
		encryptDecrypt(argc, argv);
		return 0;
	}
}

void encryptDecrypt(int argc, char* argv[]){


	printf("Args: %d\n", argc);
	ifstream pass;
	pass.open("RC4_Key.txt"); 
		printf("Pass: yes\n");
		string password;
		getline(pass,password);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	        //Input and output filestreams
	        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	        ifstream ifs(argv[5]);
	        string input((istreambuf_iterator<char>(ifs)),
	                (istreambuf_iterator<char>()));
	        ofstream output;
	        if(argc == 6){ //Single file for encrypt/decrypt
	                output.open(argv[5], ios::binary);}
	        else{ //Separate file to encrypt/decrypt to
	                output.open(argv[7], ios::binary);}
	        RC4_KEY key;
	        int length = input.size();
	        unsigned char *buffer = (unsigned char*)malloc(length + 1);
	        memset(buffer, 0, length + 1);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //Encryption
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                RC4_set_key(&key, strlen(argv[3]) - 1, (const unsigned char*)argv[3]);
                RC4(&key, length, (const unsigned char*)input.c_str(), buffer);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //Write to file
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                string newData((char*)buffer, length);
                free(buffer);
                output.clear();
                output << newData;
                output.close();

            }