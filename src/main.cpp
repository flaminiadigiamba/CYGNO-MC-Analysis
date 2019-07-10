#include "CYGNOTree.h" 
#include "CYGNOAnalysis.h"

using namespace std;

int main (int argc, char* argv[]){
    
    std::string myconf = argv[1];
    CYGNOAnalysis * CYGNO = new CYGNOAnalysis();
    cout << "Reading config" << endl;
    CYGNO->Config(myconf);
    cout << "Now start Loop" << endl;
    CYGNO->Loop();
    
    return 1;
    
}
