#include <sstream>
#include <stack>
#include <iostream>
#include "GString.h"
namespace ict{ namespace wde{ namespace gbasedata{ 
    using namespace std;
    string reverseUrl(string url){
        //trim head
        string::size_type head=url.find_first_of("://");
        if(head==string::npos){
            head=0;
        }else{
            head+=3;
        }
        url=url.substr(head);
        //trim tail
        string tail;
        string::size_type tail_index;
        if((tail_index=url.find_first_of("/"))!=string::npos){
            tail=url.substr(tail_index);
            url=url.substr(0,tail_index);
        }
        //reverse end
        stack<string> tokens;
        unsigned int begin=0;
        unsigned int found;
        while(url.find_first_of(".",begin)!=string::npos){
            found=url.find_first_of(".",begin);
            tokens.push(url.substr(begin,found-begin));
            begin=found+1;
        }
        tokens.push(url.substr(begin));
        stringstream destination;
        while(!tokens.empty()){
            destination<<tokens.top();
            tokens.pop();
            if(!tokens.empty()){
                destination<<".";
            }else{
                break;
            }
        }
        destination<<tail;
        return destination.str();
    }
}}}
