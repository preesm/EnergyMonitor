#include "getnode.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <csignal>

using namespace std;

class GetNode;


unsigned char running = 1;

void signalHandler( int signum ) {
  if (signum == 2) {
    running = 0;
  }
}

int main(int argc, char ** argv) {
  signal(SIGINT, signalHandler);
  
  string resultDirPath = ".";
  if (argc == 1) {
  } else if (argc == 2) {
    ostringstream oss;
    oss << argv[1];
    resultDirPath = oss.str();
  } else  {
    cerr << "too many args.\n";
    return 1;
  }

  cout << "output dir = " << resultDirPath << "/" << "\n";

  ofstream a15wFile;
  ostringstream ossa15;
  ossa15 << resultDirPath << "/" << "a15w.csv";
  const char* a15wPath = ossa15.str().c_str();
  a15wFile.open (a15wPath);

  ofstream a7wFile;
  ostringstream ossa7;
  ossa7 << resultDirPath << "/" << "a7w.csv";
  const char* a7wPath = ossa7.str().c_str();
  a7wFile.open (a7wPath);

  ofstream gpuwFile;
  ostringstream ossgpu;
  ossgpu << resultDirPath << "/" << "gpuw.csv";
  const char* gpuwPath = ossgpu.str().c_str();
  gpuwFile.open (gpuwPath);

  ofstream memwFile;
  ostringstream ossmem;
  ossmem << resultDirPath << "/" << "memw.csv";
  const char* memwPath = ossmem.str().c_str();
  memwFile.open (memwPath);

  GetNode *getNode;
  getNode = new GetNode();
  getNode->OpenINA231();

  int updatePeriod = 100000; //us
  usleep(updatePeriod);
  while (running) {
    // probe values every updatePeriod us
    getNode->GetINA231();
    
    // get values
    float A15W = getNode->armuW;
    float GPUW = getNode->g3duW;
    float A7W = getNode->kfcuW;
    float MEMW = getNode->memuW;

    cout << A15W << " " << A7W << " " << GPUW << " " << MEMW << "\n";

    // append values to the files
    a7wFile << A7W << " ";
    gpuwFile << GPUW << " ";
    a15wFile << A15W << " ";
    memwFile << MEMW << " ";

    usleep(updatePeriod);
  }
  a7wFile.close();
  gpuwFile.close();
  a15wFile.close();
  memwFile.close();
  return 0;
}
