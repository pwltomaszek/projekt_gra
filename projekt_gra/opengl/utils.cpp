#include <fstream>

#include "utils.h"

using namespace std;

string readTextFile(const std::string &fileName)
{
    ifstream in( fileName.c_str(), ifstream::in );

    string fileContents, line;
    while( getline( in, line ) ) {
        fileContents.append( line + "\n" );
    }

//    cout << endl << fileContents << endl;
    return fileContents;
}

float clamp(float value, float min, float max)
{
       if (value < min)
          return .0f;
       else if (value > max)
          return 1.0f;
       else
          return value;
}
