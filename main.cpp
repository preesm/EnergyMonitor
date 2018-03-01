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
  if (signum == 2 || signum == 9) {
    running = 0;
  }
}

int main(int argc, char ** argv) {
  signal(2, signalHandler);
  signal(9, signalHandler);
  
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

  ostringstream ossa15;
  ossa15 << resultDirPath << "/" << "a15_W.csv";
  string stra15 = ossa15.str();
  const char* a15wPath = stra15.c_str();
  ofstream a15wFile (a15wPath);

  ostringstream ossa7;
  ossa7 << resultDirPath << "/" << "a7_W.csv";
  string stra7 = ossa7.str();
  const char* a7wPath = stra7.c_str();
  ofstream a7wFile (a7wPath);

  ostringstream ossgpu;
  ossgpu << resultDirPath << "/" << "gpu_W.csv";
  string strgpu = ossgpu.str();
  const char* gpuwPath = strgpu.c_str();
  ofstream gpuwFile (gpuwPath);

  ostringstream ossmem;
  ossmem << resultDirPath << "/" << "mem_W.csv";
  string strmem = ossmem.str();
  const char* memwPath = strmem.c_str();
  ofstream memwFile (memwPath);

  cout << "a15wFile = " << a15wPath << " (open = " << a15wFile.is_open() << " )\n";
  cout << "a7wFile = " << a7wPath << " (open = " << a7wFile.is_open() << " )\n";
  cout << "gpuwFile = " << gpuwPath << " (open = " << gpuwFile.is_open() << " )\n";
  cout << "memwFile = " << memwPath << " (open = " << memwFile.is_open() << " )\n";
  
  
  
  
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

    a7wFile.flush();
    gpuwFile.flush();
    a15wFile.flush();
    memwFile.flush();
    usleep(updatePeriod);
  }
  
  a7wFile.close();
  gpuwFile.close();
  a15wFile.close();
  memwFile.close();
  return 0;
}
