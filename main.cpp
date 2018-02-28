#include "getnode.h"
#include <unistd.h>
#include <iostream>
using namespace std;

class GetNode;

int main(int argc, char *argv[])
{
  GetNode *getNode;
  getNode = new GetNode();
  getNode->OpenINA231();
  
  int updatePeriod = getNode->getUpdatePeriodMicroSec();
  while (1) {
    usleep(updatePeriod);
    // probe values
    getNode->GetINA231();
    
    cout << "probe" << "\n";
    cout << getNode->armuW << " W" << "\n";
    
    //
  }
  return 0;
}
