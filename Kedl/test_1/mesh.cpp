#include <fstream>
#include <iostream>
#include "mesh.h"
//#include "MyVector.h"

using namespace std;

void mesh::ReadFromBinary(string const& InFileName) {
	ifstream in_file(InFileName, ifstream::binary);
    uint32_t n,m;
	if (in_file){

    in_file.read(reinterpret_cast<char*>(&n), sizeof(uint32_t));
      _xCoords.ReadFromBinary(InFileName,sizeof(uint32_t));
      _yCoords.ReadFromBinary(InFileName,n*sizeof(double)+sizeof(uint32_t));
      in_file.seekg(2*(_xCoords.Size()*sizeof(double))+sizeof(uint32_t));
      in_file.read(reinterpret_cast<char*>(&m), sizeof(uint32_t));
      _Topology.resize(m*3);
      cout <<"-----------"<< _Topology.size();
    in_file.read(reinterpret_cast<char*>(_Topology.data()), _Topology.size()*sizeof(double));
	}
   return;
}

void mesh::WriteToBinary(string const& OutFileName) const
{
    uint32_t n = _Topology.size()/3;
    _xCoords.WriteToBinary(OutFileName);
    _yCoords.VectorToBinary(OutFileName);
    ofstream out_file(OutFileName, ofstream::binary | ofstream::app);

    out_file.write(reinterpret_cast<const char*>(&n), sizeof(uint32_t));
    out_file.write(reinterpret_cast<const char*>(&_Topology[0]), 3*n* sizeof(_Topology[0]));
    out_file.close();
}

