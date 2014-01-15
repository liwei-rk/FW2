#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <fstream>
using namespace std;
class Parser{
	//断点
public:
	Parser(string tmpfile);
	bool hasNext();
	string next();
	bool removeFile();
	unsigned int gdJsonSize;
private:
	bool eof;
	string tmpfile;
	ifstream in;
};
#endif //PARSER_H
