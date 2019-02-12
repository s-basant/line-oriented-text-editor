#include<iostream>
#include <regex>
#include <string>
#include "Command.h"

using namespace std;
// constructor 
Command::Command(int currentLine, int lastLine)
{
	this->currentLine = currentLine;
	this->lastLine = lastLine;
	firstNumber = 0;
	secondNumber = 0;
}
// function to get first line number
int Command::getFirstNumber()
{ 
	return firstNumber; 
}
// function to get second line number 
int Command::getSecondNumber() 
{
	return secondNumber;
}
// function to get command
char Command::getCommand() 
{
	if (interpretedCL != "Invalid") 
	{
		return (this->interpretedCL.back());
	}
	else return 'f';
}
// funciton to parse the input command line to interpreted command line , input is the interpreted command line
string Command::parseInputCommand(string input)
{
	// intial intialization and declaration
	string str(input);
	string comma = ",";
	string str1 = "";
	string str2 = "";
	//cin >> str;

	if (str == ".")					// if the command is "."
	{
		str = to_string(this->currentLine)+"p";  // interpreted command line
	}
	else if (str == "$")			// if the command is "$"
	{
		str = to_string(this->lastLine) + "p";	 // interpreted command line
	}
	else if (str == "p")			// if the command is "p"
	{
		str = to_string(this->currentLine) + "p";	 // interpreted command line
	}
	else if (str == "i")			// if the command is "i"
	{
		str = to_string(this->lastLine) + "i";	 // interpreted command line
	}
	else if (str == "*")			// if the command is "*"
	{
		str = to_string(1) +","+ to_string(this->lastLine) + "p";	 // interpreted command line
	}
	else if (str == "q")			// if the command is "q"
	{
		interpretedCL = "q";		 // interpreted command line
		return interpretedCL;
	}
	else if (str == "w")		// if the command is "w"
	{
		interpretedCL = "w";		 // interpreted command line
		return interpretedCL;
	}

	// regular expression created to record the user enterted command and convert it to interpreted command line
	regex e1("^[0-9$.]+[aivudxrjpc/-/-/+gwq/*]");
	regex e2("^,[0-9$.]+[aivudxrjpc/-/-/+gwq/*]");
	regex e3("[0-9$.]+,[aivudxrjpc/-/-/+gwq/*]");
	regex e4("[0-9$.]+,[0-9$.]+[aivudxrjpc/-/-/+gwq/*]");
	regex e5("[/+]");
	regex e6("[/-]");
	regex e7("^[0-9$.]+$");
	regex e8("^,[0-9$.]+$");
	regex e9("^[0-9$.]+,$");
	regex e10("^[0-9$.]+,[0-9$.]+$");
	regex e11(",");
	regex e12("[/*]");

	// matches user entered command with given possible type of user entered expression 

	bool match1 = regex_search(str, e1);
	bool match2 = regex_search(str, e2);
	bool match3 = regex_search(str, e3);
	bool match4 = regex_search(str, e4);
	bool match5 = regex_search(str, e5);
	bool match6 = regex_search(str, e6);
	bool match7 = regex_search(str, e7);
	bool match8 = regex_search(str, e8);
	bool match9 = regex_search(str, e9);
	bool match10 = regex_search(str, e10);
	bool match11 = (str.compare(comma) == 0);
	bool match12 = regex_search(str, e12);
	interpretedCL = "";
	int size;
	size = str.length();
	string one = "1";
	string dot = ".";
	if (regex_search(str, e1)) // xz	=> x,xz
	{
		interpretedCL =  + "," + str.substr(0, size - 1) + str.at(size - 1);
		str1 = str.substr(0, size - 1);
		str1 = ((str1 == "$") ? to_string(lastLine) : str1);
		str1 = ((str1 == ".") ? to_string(currentLine) : str1);
		firstNumber = stoi(str1);
		secondNumber= firstNumber;
		//cout << "firstLine :" + firstLine;
		//	cout << "e1 :" << interpretedCL;
	}
	else if (regex_search(str, e2))  // ,yz	=> 	.,yz
	{
		interpretedCL = "." "," + str.substr(1, size - 2) + str.at(size - 1);
		str2 = str.substr(1, size - 2);
		str2 = ((str2 == "$") ? to_string(lastLine) : str2);
		str2 = ((str2 == ".") ? to_string(currentLine) : str2);
		firstNumber = currentLine;
		secondNumber = stoi(str2);
		//	cout << "e2 :" << interpretedCL;
	}
	else if (regex_search(str, e3)) // x,z	=> 	x,.z
	{
		interpretedCL = str.substr(0, size - 2) + "," + "." + str.at(size - 1);
		str1 = str.substr(0, size - 2);
		str1 = ((str1 == "$") ? to_string(lastLine) : str1);
		str1 = ((str1 == ".") ? to_string(currentLine) : str1);
		firstNumber = stoi(str1);
		secondNumber = currentLine;
		//	cout << "e3 :" << interpretedCL;
	}
	else if (regex_search(str, e4))  // x,yz	=> x,yz
	{
		interpretedCL = str;
		string lineString = str.substr(0,size - 1);
		int pos = lineString.find(",");
		str1 = lineString.substr(0, pos);
		str2 = lineString.substr(pos + 1);
		str1 = ((str1 == "$") ? to_string(lastLine) : str1);
		str1 = ((str1 == ".") ? to_string(currentLine) : str1);
		str2 = ((str2 == "$") ? to_string(lastLine) : str2);
		str2 = ((str2 == ".") ? to_string(currentLine) : str2);
		firstNumber = stoi(str1);
		secondNumber = stoi(str2);
		//	cout << "e4 :" << interpretedCL;
	}
	else if (regex_search(str, e5)) // + => 	1,1+
	{
		interpretedCL = one + "," + one + str.at(size - 1);
		firstNumber = 1;
		secondNumber = 1;
		//	cout << "e5 :" << interpretedCL;
	}
	else if (regex_search(str, e6)) // – => 	1,1–
	{
		interpretedCL = one + "," + one + str.at(size - 1);
		firstNumber = 1;
		secondNumber = 1;
		//	cout << "e6 :" << interpretedCL;
	}
	else if (regex_search(str, e7)) // x	=>  x,xg
	{
		interpretedCL = str + "," + str + "g";
		firstNumber = stoi(str);
		secondNumber = firstNumber;
		//	cout << "e7 :" << interpretedCL;
	}
	else if (regex_search(str, e8)) // ,y	=>  .,yp
	{
		interpretedCL = dot + comma + str.substr(1) + "p";
		str2 = str.substr(1);
		str2 = ((str2 == "$") ? to_string(lastLine) : str2);
		str2 = ((str2 == ".") ? to_string(currentLine) : str2);
		firstNumber = currentLine;
		secondNumber = stoi(str2);
		//	cout << "e8 :" << interpretedCL;
	}
	else if (regex_search(str, e9)) // x,	=>  x,.p
	{
		interpretedCL = str + ".p";
		str1 = str.substr(0,1);
		str1 = ((str1 == "$") ? to_string(lastLine) : str1);
		str1 = ((str1 == ".") ? to_string(currentLine) : str1);
		firstNumber = stoi(str);
		secondNumber = currentLine;
		//	cout << "e9 :" << interpretedCL;
	}
	else if (regex_search(str, e10)) // x,y	=> 	x,yp
	{
		interpretedCL = str + "p";
		string lineString = str.substr(0, size);
		int pos = lineString.find(",");
		str1 = lineString.substr(0, pos);
		str2 = lineString.substr(pos + 1);
		str1 = ((str1 == "$") ? to_string(lastLine) : str1);
		str1 = ((str1 == ".") ? to_string(currentLine) : str1);
		str2 = ((str2 == "$") ? to_string(lastLine) : str2);
		str2 = ((str2 == ".") ? to_string(currentLine) : str2);
		firstNumber = stoi(str1);
		secondNumber = stoi(str2);

		//	cout << "e10 :" << interpretedCL;
	}
	else if (str.compare(comma) == 0) // , => 	.,.p
	{
		interpretedCL = ".,.p";
		firstNumber = currentLine;
		secondNumber = currentLine;
		//	cout << "e11 :" << interpretedCL;
	}
	else if (regex_search(str, e12)) // *  => 	1,$p
	{
		interpretedCL = "1,$p";
		firstNumber = 1;
		secondNumber = lastLine;
		//	cout << "e12 :" << interpretedCL;
	}
	else
	{
		interpretedCL = "Invalid";
	};
//	cout << "interpretedCL :" << interpretedCL;
	return interpretedCL;
}

