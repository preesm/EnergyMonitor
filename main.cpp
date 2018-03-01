#include "getnode.h"
#include <unistd.h>
#include <iostream>
using namespace std;

class GetNode;



int main() {
  GetNode *getNode;
  getNode = new GetNode();
  getNode->OpenINA231();
  
  int updatePeriod = 100000; //us
  while (1) {
    // probe values every updatePeriod us
    usleep(updatePeriod);
    getNode->GetINA231();
    
    // outptu values
    // todo ...
    
  }
  return 0;
}
