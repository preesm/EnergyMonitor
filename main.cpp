#include "getnode.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class GetNode;

int main(int argc, char ** argv) {

  string resultDirPath = ".";
  if (argc == 0) {
  } else if (argc == 1) {
    cout << "using current dir for outputting results\n";
  } else if (argc == 2) {
    cout << "using '" << argv[1] << "' for outputting results\n";
    std::ostringstream oss;
    oss << argv[1];
    resultDirPath = oss.str();
  } else  {
    cerr << "too many args.\n";
    return 1;
  }

  ofstream a7wFile;
  ofstream a15wFile;
  ofstream gpuwFile;
  ofstream memwFile;

  a7wFile.open ("a7w.csv");
  a15wFile.open ("a15w.csv");
  gpuwFile.open ("gpuw.csv");
  memwFile.open ("memw.csv");

  GetNode *getNode;
  getNode = new GetNode();
  getNode->OpenINA231();

  int updatePeriod = 100000; //us
  while (1) {
    // probe values every updatePeriod us
    usleep(updatePeriod);
    getNode->GetINA231();
    
    // outptu values
    float A15W = getNode->armuW;
    float GPUW = getNode->g3duW;
    float A7W = getNode->kfcuW;
    float MEMW = getNode->memuW;
  }
  return 0;
}
