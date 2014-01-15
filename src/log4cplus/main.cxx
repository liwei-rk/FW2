#include "log4cplus/logger.h"
#include "log4cplus/configurator.h"


using namespace std;
using namespace log4cplus;






int main()
{
    cout << "Entering main()..." << endl;     
    Logger root = Logger::getRoot();
    PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("log4cplus.properties"));
								
    LOG4CPLUS_DEBUG(root, "printMsgs()");
    LOG4CPLUS_INFO(root, "printMsgs()");
    LOG4CPLUS_WARN(root, "printMsgs()");
    LOG4CPLUS_ERROR(root, "printMsgs()" << "stream");
			
    

    cout << "Exiting main()..." << endl;
    return 0;
}


