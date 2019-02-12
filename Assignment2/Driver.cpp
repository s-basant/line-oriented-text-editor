#include <iostream >
#include  <string >
#include "Led.h"
//using  std::cout;
//using  std::endl;
//using  std::string;

using namespace std;
int  main(int argc, char * argv[])
{
	string  filename;      // an  empty  filename
						   //Led Led;
	switch (argc) {      //  determine  the  filename
	case 1: // no file  name
		break;
	case 2:  filename = argv[1]; //  initialize  filename  from  argument
		break;
	default: cout << ("too  many  arguments  - all  discarded") << endl;
		break;
	}
	Led  editor(filename); //  create a Led  named  editor
	editor.run();          // run  our  editor

	return  0;             //  report  success
}
