//HELLO, this is a BASIC AI that will follow commands based on voice(soon)
//
#include <iostream>
#include "user.h"
#include "festival.h"
#include <EST_String.h>
#include <fstream> //not needed now, but maybe later
using namespace std;

int main()
{
	ifstream inFile;
	inFile.open("txtFiles/userInfo.txt");
	cout << inFile << endl;
	EST_Wave wave;
	int heapsize = 21000000;
	int load_init_size = 1;
	festival_initialize(load_init_size, heapsize);
	festival_eval_command("(voice_kal_diphone)");
	if(!inFile)
	{
		festival_say_text("Hello User. I am JARVIS. What is your name?");
		char* tempname = new char[20];
		char* age = new char[3];
		cout << "Type your name: "; cin >> tempname;
		cout << "Type your age: "; cin >> age; 
		cout << "your name is " << tempname << endl;
		user newUser(tempname, age);
		newUser.storeInformation(tempname, age);
		EST_String name = EST_String(tempname);
		festival_say_text("Hello " + name + ". How can I assist you?");
	}
	else
	{ 
		string name;
		std::getline(inFile, name);
		char* tempName = new char[35];
		std::strcpy(tempName, name.c_str());
		EST_String realName = EST_String(tempName);
		cout << realName << endl;
		festival_say_text("Welcome back " + realName + ". What do you need?");
	}
	cout<<"Hello world. This is a test" <<endl;
	char question[100];
	char* ans = new char[1];
	cout <<"Ask me a Question: ";cin.getline(question,sizeof(question));
	EST_String newQuestion = EST_String(question);
	festival_say_text("I do not understand your question:. " + newQuestion + ". Would you like me to google it?");
	cout << "y/n?"; cin >> ans;
	ifstream inFile2;
	inFile2.open("network/infoFiles/cURL.txt");	
	std::string information;
	std::getline(inFile2,information);
	std::cout << information << std::endl;
	EST_String realInfo = EST_String(information.c_str());
	festival_say_text(realInfo);
	//make it so when you ask a question and they don't answer, ask them if they would like to google it.
	//if yes, google and use the first question for an answer.
	//also, look for keywords when they ask something and store them with the answer in a text file somehow.
	//e.g. ([weather,day] - current temperature and date);
	inFile.close();
	return 123;
}
