#pragma once
#include<iostream>
#include<string>
#include <list>
#include <vector>
using namespace std;
class Led
{
private:
	string fileName;				// file name to save the buffer
	list<string> buffer;			// List of type string to contain text lines to be inserted into text files
	vector<string> clipboard;		// Vector of type string for desired operations on the clipboard like reading and overwriting its entire contents.to 
	int currentLine;				// current line address in buffer 
	int lastLine;					// Last line address in buffer
	int startLine;					// Start line address in buffer
	bool isBufferSaved;				// boolean to indcate if buffer has been saved
	int lineCount;					// total line count
	int bufferSize;					// total buffer size
	int replacements;				// number of replacement by which id done by find and replace function
	/*
	* write buffer to file
	* insert and save entire buffer into file 
	* specified by its arguments.
	* @param  seq the list (buffer) to save.
	* @param  path2file file and path to save the buffer
	* @return returns void
	*/
	void write_to_file(const list<string> seq, const char* path2file);
	/*
	* find And ReplaceAll content in string.
	* Searches the string for the first occurrence of the sequence and replace the string with given
	* specified by its arguments.
	* @param  data the string line where the given string is to be searched and replaced by mentioned string in param
	* @param  toSearch the substring to search for.
	* @param  replaceStr the substring to replaced with.
	* @return the function returns void
	*/
	void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr);
public:
	/*
	* to run the editor
	* wapper funtion to create and invoke command object to validate and interpret user entered command
	* @param  no param
	* @return the function returns void
	*/
	void run();
	/*
	* A constructor .
	* Creates a Led object to initialize its members
	* specified by its arguments.
	* @param  input optional file name to opened by editor if given.
	* @return the function returns void
	*/
	Led(string input= nullptr);
};