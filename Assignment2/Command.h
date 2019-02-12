#pragma once
#include<iostream>
#include<string>
using namespace std;
class Command
{
private:
	string inputCommand;		// Command line entered by user
	string interpretedCL;		// Command line interpreted
	int currentLine;			// Current line address in buffer 
	int lastLine;				// Last line in buffer
	int firstLine;				// First line in buffer
	int firstNumber;			// first line number in interpreted command line
	int secondNumber;			// first line number in interpreted command line

public:
	/*
	* A constructor .
	* Creates a command object to initialize its members 
	* specified by its arguments.
	* @param  currentLine  Current line in buffer 
	* @param  lastLine buffer size.
	*/
	Command(int currentLine, int lastLine);
	/*
	* parse "Command line entered" by user to Command line interpreted 
	* It translates the user input command into the corresponding interpreted command by compiler
	* specified by its arguments.
	* @param  input "Command line entered" by user.
	* @return  Command line interpreted 
	*         returns string.
	*/
	string parseInputCommand(string input);
	/*
	* gets the first line number in interpreted command line
	* @param  no parameter
	* @return int first line number in interpreted command line
	*/
	int getFirstNumber();
	/*
	* gets the second line number in interpreted command line
	* @param  no parameter
	* @return int second line number in interpreted command line
	*/
	int getSecondNumber();
	/*
	* gets the command from interpreted command line
	* @param  no parameter
	* @return command in interpreted command line
	*/
	char getCommand();
};

