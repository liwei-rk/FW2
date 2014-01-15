#include "parser.h"
Parser::Parser(string tmpfile){
	eof=false;
	this->tmpfile=tmpfile;
	in.open(tmpfile.c_str());
	if(!in){
		cout<<"open tmpfile error"<<endl;
		exit(0);
	}
}
string Parser::next(){
	//streamsize最大多大,4GB
	//读取JSON大小
	in.get();
	string gdJson;
	char* buffer=(char*)malloc(gdJsonSize);
	if(!buffer){
		return "wrong";
	}
	//读取gdJsonSize个字符;
	in.read(buffer,gdJsonSize);
	string a(buffer);
	free(buffer);
	return a;
}
bool removeFile(){
	return false;
}
bool Parser::hasNext(){
	in>>gdJsonSize;
	if(in){
		return true;
	}else{
		eof=true;
		return false;
	}
	return true;
}
void testParser(){
	ofstream output("test");
	Parser parser("tmpfile");
	int count=0;
	while(parser.hasNext()){
		count++;
		cout<<count<<endl;
		output<<parser.next();
	}
	cout<<"Total count is "<<count<<endl;
}
void stepTest(){
	ifstream in("tmpfile");
	unsigned int size;
	in>>size;
	in.get();
	char* buffer=(char*)malloc(size);
	in.read(buffer,size);
	string json(buffer);
	cout<<buffer;
	if(!in){
		if(in.eof()){
			cout<<"end"<<endl;
		}
		if(in.fail()){
			cout<<"fail"<<endl;
		}
		if(in.bad()){
			cout<<"bad"<<endl;
		}
	}
	in>>size;
	in.read(buffer,size);
}
