#include <fstream>
#include <iostream>
#include "mesh.h"
//#include "MyVector.h"

using namespace std;

void mesh::ReadFromBinary(string const& InFileName) {
	ifstream in_file(InFileName, ifstream::binary);
    uint32_t n;
	if (in_file){

    in_file.read(reinterpret_cast<char*>(&n), sizeof(uint32_t));
      _xCoords.ReadFromBinary(InFileName,sizeof(uint32_t));
      _yCoords.ReadFromBinary(InFileName,n*sizeof(double)+sizeof(uint32_t));
      cout << "       ### " << n;
      //in_file.seekg(2*(_xCoords.Size()*sizeof(double)+sizeof(uint32_t)));
 //     in_file.read(reinterpret_cast<char*>(n), sizeof(uint32_t));
//      in_file.read(reinterpret_cast<char*>(_Topology),n*izeof(uint32_t));
   }

   return;
}

void mesh::WriteToBinary(string const& OutFileName) const
{
    _xCoords.WriteToBinary(OutFileName);
    _yCoords.WriteToBinary(OutFileName);
   ofstream out_file(OutFileName, ofstream::binary | ofstream::app);
//   out_file.write(reinterpret_cast<const char*>(&_Topology.Size()), sizeof(uint32_t));
//   out_file.write(reinterpret_cast<const char*>(_Topology),_Topology.Size()*sizeof(uint32_t));
   out_file.close();
}

