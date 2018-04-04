
#include <iostream>
#include <string>
#include <fstream>
#include "rc4_enc.c"
#include "rc4_skey.c"
using namespace std;
#define KEY "default_key"
#define KEY_LENGTH (sizeof(KEY)-1)

// Encrypt/decrypt function
void encryptDecrypt(int argc, char *argv[]); 

//Main
int main(int argc, char *argv[]){
	
	if(argc > 3){
		cerr << "Error! Too many file names given.";
		return 0;}
	else if(argc < 2){
		cerr << "Error!  You need to provide a file name.";
		return 0;
	}
	else{
		encryptDecrypt(argc, argv);
		return 0;
	}
}

void encryptDecrypt(int argc, char* argv[]){
	printf("Args: %d\n", argc);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	        //Input and output filestreams
	        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	        ifstream ifs(argv[1]);
	        string input((istreambuf_iterator<char>(ifs)),
	                (istreambuf_iterator<char>()));
	        ofstream output;
	        if(argc == 2){ //Single file for encrypt/decrypt
	                output.open(argv[1], ios::binary);}
	        else{ //Separate file to encrypt/decrypt to
	                output.open(argv[2], ios::binary);}
	        RC4_KEY key;
	        int length = input.size();
	        unsigned char *buffer = (unsigned char*)malloc(length + 1);
	        memset(buffer, 0, length + 1);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //Encryption
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                RC4_set_key(&key, KEY_LENGTH, (const unsigned char*)KEY);
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

