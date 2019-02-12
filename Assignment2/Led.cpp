#include<iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include"Led.h"
#include "Command.h"

using std::ifstream;
using std::istringstream;
using std::list;
using std::for_each;
using std::istream_iterator;
using std::back_insert_iterator;

using namespace std;
// constructor 
Led::Led(string fileName)
{
	this->fileName = fileName;
	currentLine = 0;
	lastLine = 0;
	startLine = 0;
	bool isBufferSaved = false;
	// check if user has entered file name to be read from
	if (!fileName.empty())  
	{
		ifstream in(fileName);
		if (!in)
		{
			cerr << "Cannot open the File : " << fileName << std::endl;
		}
		string str;
		// Read the next line from File untill it reaches the end.
		lineCount = 0;
		while (std::getline(in, str))
		{
			// Line contains string of length > 0 then save it in List
			if (str.size() > 0) 
			{
				buffer.push_back(str);  // push to the the list (buffer)
				lineCount++;			// keep the count of the user input
				lastLine = lineCount;
				currentLine = lineCount; // keep the current line address 
			}
		}
		bufferSize = buffer.size();		// set the buffer size
		in.close();						//Close The File
	}
}
void Led::run()
{
	// format the display for user in editing mode
	if (!fileName.empty() && lineCount !=0)
	{
		cout << "\"" << fileName << "\"";
		cout << " " <<lineCount;
		cout << " "<<"lines";
	}
	else if (!fileName.empty() && lineCount == 0)
	{
		cout << "\"" << fileName << "\"";
		cout << " " <<"[New File]";
	}
	else {
		cout << "\"?\"" ;
		cout << " " << "[New File]";
	}
	cout << endl;
	cout << "Entering command mode." << endl;
	// Continue the eidting session till user terminates or it breaks based on give condition
	while (true)
	{
		cout << "?" << " ";
		string commadLine= "";
		string line ;
		int count = 0;
		int bufferSizeOld = 0;
		cin.clear(); cin.sync();				//	Discards all unread characters from the input buffer. 
		getline(cin, commadLine);				//	Extracts characters from is and stores them into str until the delimitation 
		Command cmd(currentLine, bufferSize);	//	Creates command object sets current line and buffer size
		if (commadLine == "Bye")  break;		//	Breaks the editing session when user enters Bye in command mode
		cmd.parseInputCommand(commadLine);		//	Parse user input Command Line(CL) to get interpreted command line
		startLine = cmd.getFirstNumber();		//	Parse interpreted input CL to get first number
		//cout << "n1 :" << startLine << endl;
		lastLine = cmd.getSecondNumber();		//	Parse interpreted input CL to get first number
		//cout << "n2 :" << lastLine << endl;
		char command = cmd.getCommand();		//	Parse interpreted input CL to get first number
		list<string>::iterator it1, it2, it3;	//	Defining Lst iterators
		it1 = it2 = it3 = buffer.begin();		//	Intitializing to the list begninging
		string clipboardStr;					//	Used to append the lines in clipboard when Join command is passed
		string toSearch;						//	The string to search in find and replace funciton 
		string replaceStr;						//	The string to replace with in find and replace function
		string response;
		switch (command)						//	Swith the based on the command
		{
		case 'a':								// x a : appends text into the buffer after line x. 
			clipboard.clear();					// clear vector
			if ((buffer.size() == 0) && (startLine != 0))  // check if buffer is empty and user has input first line
			{
				cout << "Invalid range" << endl;
				break;
			}
			this->currentLine = 0;				// set current line to 0
			while (getline(cin, line))			// takes user input
			{
				clipboard.push_back(line);		//	insert into the vector
			}
			it3 = buffer.begin();				// set the iterator to list begining
			advance(it3, startLine );			// advance the iterator to the given first line number
			buffer.insert(it3, clipboard.begin(), clipboard.end()); // insert the vector content into list between given line numbers
			bufferSize = buffer.size();			// set the buffer size
			currentLine = startLine + clipboard.size() ;  // set the current line
			break;
		case 'i':									// inserts text into the buffer before line x. The current address is set to the last line entered
			clipboard.clear();						// clear the vector
			if ((buffer.size() == 0)&& (startLine!=0))  // check if buffer is empty and user has input first line
			{
				cout << "Invalid range" << endl;
				break;
			}
			this->currentLine = 0;					// set current line to 0
			while (getline(cin, line))				//	Extracts characters from is and stores them into str until the delimitation 
			{
				clipboard.push_back(line);			// insert into the vector
			}
			it3 = buffer.begin();					// intiialize the list iterators to begning of the list
			if (startLine > 0)						// if start line is > 0
			{
				advance(it3, startLine-1);			// advances the list iterator to line before the first line number if line number is > 0
			}
			else
			{
				advance(it3, startLine);			// else advances the list iterator to the line start line
			}
			buffer.insert(it3, clipboard.begin(), clipboard.end()); // insert the vector content into list between given line numbers
			bufferSize = buffer.size();				// buffer size
			if (startLine > 0)						// The current address is set to the last line entered
			{
				currentLine = startLine + clipboard.size()-1; 
			}
			else currentLine = clipboard.size();
			//currentLine = bufferSize;
			break;	
		case 'v':									//x v: Pastes text from the clipboard into the buffer below line x
			it3 = buffer.begin();					// initialize iterator to begining of the list
			advance(it3, startLine );				// advance the iterator to the start line
			buffer.insert(it3, clipboard.begin(), clipboard.end()); // insert the vetor in the list between given lines
			bufferSize = buffer.size();				// set buffer size
			currentLine = startLine + clipboard.size() ; // set the current line
			break;
		case 'u':									//x u :Pastes text from the clipboard into the buffer above line x
 			it3 = buffer.begin();					// intialize iterator to beinging of the list
			advance(it3, startLine - 1);			// advance iterator to the line before start line
			buffer.insert(it3, clipboard.begin(), clipboard.end()); // insert the vetor in the list between given lines
			bufferSize = buffer.size();				// set the buffer size
			currentLine = startLine + clipboard.size() - 1; // set the current line
			break;
		case 'd':									// x,y d : Deletes the line range x through y from the buffer.
			advance(it1, startLine - 1);			// advance interator to the line before startline
			advance(it2, lastLine);					// advace another iterator to the last line
			buffer.erase(it1, it2);					// erase the content of list pointing between these iterators
			bufferSize = buffer.size();				// set the buffer size
			if (lastLine >= bufferSize) currentLine = startLine - 1; // set the current line
			else currentLine = startLine; 
			break;
		case 'x':									//x, y x : Cuts the line range x through y from the buffer into the clipboard.
			clipboard.clear();
			for (string item : buffer)				// iterate the list
			{
				count++;
				if ((count >= startLine) && (count <= lastLine)) // filter for the lines in between start line and last line number entered by user
				{
					clipboard.push_back(item);		// insert into vector
				}
			}
			bufferSizeOld = buffer.size();			// set the old List size
			advance(it1, startLine - 1);			// advances first iterator to line before the start line
			advance(it2, lastLine);					// advances the iterator to the last line
			buffer.erase(it1, it2);					// erase the content between the iterators 
			bufferSize = buffer.size();				// set the buffer size
			currentLine = bufferSizeOld - ( lastLine - startLine + 1); // set the current line
			break;
		case 'r':								//x,y r : Replaces the line range x through y with input text.	
			advance(it1, startLine - 1);		// advances the first iterator to the line before start line
			advance(it2, lastLine);				// advance the last iterator to the last line
			buffer.erase(it1, it2);				// delete the list between iterator 
			clipboard.clear();					// clear the vector
			while (getline(cin, line))			//	Extracts characters from is and stores them into str until the delimitation  
			{
				clipboard.push_back(line);		// insert into the vector
			}
			it3 = buffer.begin();				// intialize the list iterator to the begning of the list
			advance(it3, startLine - 1);		// advances the iterator to the line before the start line number
			buffer.insert(it3, clipboard.begin(), clipboard.end());  // insert the vetor in the list between given lines
			bufferSize = buffer.size();			// set the buffer size
			currentLine = startLine + clipboard.size()-1; // set the current line
			break;
		case 'j':									//x, y j : Joins the line range x through y together on one line at address x, such that each line in turn is appended to line x, separated by a single space.
			count = 0;							
			for (string item : buffer)				// loop through the list
			{
				count++;
				if ((count >= startLine) && (count <= lastLine)) // filter the item of list which are in between the first line and last line number entered by user
				{
					clipboardStr += item + " ";			// concatenate the items into a single string
				}
			}
			advance(it1, startLine - 1);			// advances the list iterator to the line before startline
			advance(it2, lastLine);					// advances the list iterator to the last line
			buffer.erase(it1, it2);					// erase the list between line 1 and line 2
			it3 = buffer.begin();
			for (int i = 0; i < startLine - 1; i++) it3++;	// advances the iterator 
			buffer.insert(it3, clipboardStr);		// insert the vector item into the list 
			currentLine = startLine;				// set the current line
			bufferSize = buffer.size();				// set the buffer size
			lastLine = bufferSize;
			break;
		case 'p':								// x,y p :  Prints the line range x through y without affecting the current line address
			if (buffer.size() == 0)				// if the buffer is empty
			{
				if(startLine==0)
				cout << "empty buffer"<< endl;
				else cout << "Invalid range" << endl;
			}
			else 
			{
				count = 0;
				lineCount = 0;
				for (string item : buffer)			// iterate throught the buffer 
				{
					count++;
					if((count>= startLine )&& (count <= lastLine)) // filter the item of list which are in between the first line and last line number entered by user
						{
							lineCount++;							
							cout << count;							// print the count
							cout << ((count == this->currentLine) ? ">" : ":");   // format the output as expected
							cout << item << endl;
						}
				}
			}
			break;
		case 'c':							//	Prompts for and reads the text to be changed, and then prompts for and reads the replacement text.Searches each line in the line range for an occurrence of the specified string and changesa ll matched strings to the replacement text
			replacements = 0;				
			clipboard.clear();				// clear the vector
			cout << "Change what ? " ;		
			getline(cin, toSearch);			// get the input string to search for 
			cout << "To what ? " ;
			getline(cin, replaceStr);		// get the replace string 
			count = 0;
			for (string items : buffer)		// iterate through list 
			{
				count++;
				if ((count >= startLine) && (count <= lastLine))	// filter the item within start line and last line
				{
					findAndReplaceAll(items, toSearch, replaceStr); // function invoked to search and replace the string
					clipboard.push_back(items); // insert the replaced item into vector 
				}
			}
			advance(it1, startLine - 1);		// advances list iterator to line before start line
			advance(it2, lastLine);				// advance list iterator to last line
			buffer.erase(it1, it2);				// erase the content of list in between the iterators
			it3 = buffer.begin();				// set the list iterator to begining of the clipboard
			advance(it3, startLine - 1);		// advances third itertor to the line before start line
			buffer.insert(it3, clipboard.begin(), clipboard.end()); //  insert the vector into the list
			currentLine = lastLine;				// set the current line
			cout << "Changed ";				
			cout << replacements;				// print the replacement
			cout << " occurrence(s)"<< endl;
			//cin.ignore();
			break;
		case '+':								//	Moves the current line down by x lines provided that there are x lines below the current line; otherwise, prints the message end of  le reached and sets the current line to last line in the buffer.If omitted, x = 1
			bufferSize = buffer.size();			
			if (this->currentLine + startLine >= bufferSize ) // if the current line exceeds the buffer size
			{
				cout << "end of file reached"<< endl;  // prints out the message
				this->currentLine = bufferSize;			// set the current line to the last line of buffer
			}
			else
			{
				count = startLine;
				while (count != bufferSize)
				{
					this->currentLine++;		// increments the current line
					count++;
				}
			}

			break;
		case '-':								//	Moves the current line up by x lines provided that there are x lines above the current line; otherwise, prints the messagetop of  le reached and sets the current line to  first line in the buffer.If omitted, x = 1.
			
			if (this->currentLine - startLine <= 0)  // if the difference between current line and startline is less than 0 
			{
				cout << "top of file reached" << endl ;  // set the message
				this->currentLine = 1;				// set the curent line to start of the buffer
			}
			else 
			{
				count = startLine;				
				while (count != 0) 
				{
					this->currentLine--;			// decrement the current line
					count--;
				}
			}
			break;
		case 'g':										// Goes to the specified line x, meaning that it sets the current line to x and prints it. Prints the message invalid range if x is invalid. If omitted, x= the currentline address
			if (buffer.size() < startLine)				// if buffer size is less than the start line
				cout << "Invalid range" << endl;		// set message
			else
			{
				currentLine = startLine;
				int count = 0;
				lineCount = 0;

				for (string item : buffer)				// iterate through the list
				{
					count++;
					if (count == currentLine)			// filter for the item which is current line
					{
						lineCount++;
						cout << lineCount;
						cout << ((lineCount == currentLine) ? ">" : ":");	// format the output
						cout << item << endl;
					}
				}
			}

			break;
		case 'w':									// Writes out entire buffer to its associated file. If the buffer is not associated with a user named  le, it prompts for and reads the name of the associated  file.
			if ((!fileName.empty()) && (!isBufferSaved)) // if the file is given and buffer has not been saved
			{
				const char * path = fileName.c_str();	// convert string to  char*
				write_to_file(buffer, path);			// invoke funciton to write the file
			}
			else 
			{
				 response= "";
				do
				{
					cout << "Save changes to a file(y / n) ? ";  // format the output to validate from user
					cin >> response;							// take user's responce
					if (!(response == "y" || response == "n"))	
						cout << "bad answer:" + response << endl;	// prompts message based on user response
				} while (!(response == "y" || response == "n"));	
				if ((!isBufferSaved) && (response == "y"))		// if the buffer is not saved and 
				{
					cout << "Enter a file name: ";				// prompts user for a file name
					cin >> fileName;							// take user input as string
					const char * path = fileName.c_str();		// converts path to  char* 
					write_to_file(buffer, path);				// writes to the file
					cout << buffer.size();
					cout << " lines written to file: ";			// prompts confirmation message
					cout << "\"" + fileName + "\"" << endl;
					isBufferSaved = true;
					cin.ignore();
				}
			}

			break;
		case 'q':								// Quits led. Before quitting, however, it gives the user a last chance to save the buffer. If the user takes the chance, it simulates the w command
			 response = "";
			do 
			{ 
				cout <<"Save changes to a file(y / n) ? ";   // prompts message for user confirmation
				cin >> response;							// takes user confirmation as string
				if (!(response == "y" || response == "n"))	
					cout <<"bad answer:" + response << endl; // prompts message based on the response
			} while (!(response == "y" || response =="n"));	
			if ((!isBufferSaved) && (response == "y"))		// if buffer is not saved and response is to save
			{
				if (fileName.empty())			
				{
					cout << "Enter a file name: ";			// gets the file name if it is not mentioend
					cin >> fileName;						// gets file name as input
				}	
				const char * path = fileName.c_str();		// converts int char *
				write_to_file(buffer, path);				// writes to file
				cout << buffer.size();
				cout << " lines written to file: ";			// formats the confirmation messages
				cout << "\"" + fileName + "\""<< endl;
				cin.ignore();
			}
			
			break;
		case 'f':
			cout << "Invalid Input command" << endl;
			break;
		}
	}
}

// function to write to the file from the list (buffer)
void Led::write_to_file(const list<string> seq, const char* path2file)
{
	std::ofstream file(path2file);									// declare and initalize the ofstream
	for (auto iterator = seq.begin(); iterator != seq.end(); ++iterator) // auto iterator on list
		file << *iterator << '\n';									// insert into file
	file.close();													// close file
}
// function to find and replace in the list
void Led::findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
	size_t pos = data.find(toSearch);					// Get the first occurrence
	while (pos != std::string::npos)					// Repeat till end is reached
	{
		data.replace(pos, toSearch.size(), replaceStr);	// Replace this occurrence of Sub String
		pos = data.find(toSearch, pos + toSearch.size());// Get the next occurrence from the current position
		replacements++;									// increament total number of replaced items
	}
}