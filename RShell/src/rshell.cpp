#include <unistd.h>
#include <string>
#include <vector> 
#include <stdio.h>
#include "Classes.h"

using namespace std;

int main () {
    
    string input;
    
    cout << "$ ";
    
    getline(cin, input);
    
    CommandLine v(input);
    
    bool passed = v.execute();
  
    return 0;
}

