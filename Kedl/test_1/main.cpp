#include <iostream>
#include <fstream>
#include "mesh.h"

struct mmmmesh {
    uint32_t vertices;
    double x1;
    double y1;
    double x2;
    double y2;
    double x3;
    double y3;
    uint32_t triangles;
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
    uint32_t i;
};

mmmmesh tmp_mesh_1 = {
    6,
    0.5,
    0.5,
    1.5,
    1.5,
    2.5,
    2.5,
    3,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9
};




using namespace std;
int main() {
   // ofstream out_file("tmp_mesh_1.bin", ofstream::binary);
    //out_file.write((char*)&tmp_mesh_1, sizeof(mmmmesh));
   // out_file.close();
    //double a = 2;
//  MyVector a(6);
 // a.ReadFromBinary("mesh_out.bin");
  //a.WriteToBinary("vector.out");
    //cout << sizeof(a);
//    cout << a;
    mesh v;
    v.ReadFromBinary("mesh_out_v2.bin");
    cout << "#knoten  " << v.getNumNodes() << endl << endl;
    cout << "#Dreiecke   " << v.getNumTriangles() << endl;
    cout << v._xCoords << endl;
    cout << v._yCoords << endl << endl;
    for (int i = 0; i < 9; i++) cout << v._Topology[i] << endl;



    v.WriteToBinary("mesh_out_v3.bin");
    return 0;
}

//
//	//Groeße der Datei bestimmen
//	in_file.seekg (0, in_file.end);
//    	int length = in_file.tellg();
//    	in_file.seekg (0, in_file.beg);
//
//	//Speicher allokieren
//	char * buffer = new char [length];
//
//	//read data as a block
//	in_file.read(buffer,length);
//
//	in_file.close();
//
//	int offset = 0;
//	memcpy (&buffer[offset],m,sizeof(m));
//	offset+=sizeof(m);
//	offset+=m*sizeof(double);
//
//	memcpy (&buffer[offset],n,sizeof(n);
//
//	mesh rc(m,n);
//
//	offset = 0+sizeof(m);
//	memcpy (&buffer[offset])
//
//
//	delete [] buffer;
//
//	}
//
