/** @file mesh.cpp
*   @author Simon Pieber, Pia Kedl
*   @date SoSe 2016
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

#include "MyVector.h"
#include "MyMatrixCRS.h"
#include "mesh.h"


vector<bool> mesh::getInteriourNodes() const
{
   uint32_t const NumTriangles = this->getNumTriangles();
   vector<uint32_t> Edges;

   for (uint32_t i=0; i<NumTriangles; ++i)
   {
      for (uint32_t k=0; k<3; ++k)
      {
         uint32_t N0 = _Topology[3*i + k],
                  N1 = _Topology[3*i + (k+1)%3];

         // suche Kante (N0,N1) in Edges
         uint32_t pos(-1), j(0);
         while (j<Edges.size()/2 && pos == static_cast<uint32_t>(-1))
         {
            if (    (Edges[2*j] == N0 && Edges[2*j+1] == N1)
                 || (Edges[2*j] == N1 && Edges[2*j+1] == N0) ) // gefunden
            {
               pos = 2*j;
            }
            ++j;
         }

         if (pos != static_cast<uint32_t>(-1))
         {
            Edges.push_back(N0);
            Edges.push_back(N1);
         }
         else
         {
            Edges.erase(Edges.begin()+pos, Edges.begin()+pos+2);
         }
      }

   }

   vector<bool> int_nodes(this->getNumNodes(), true);
   for (auto n : Edges)
   {
      int_nodes[n] = false;
   }
   return int_nodes;
}


MyMatrixCRS mesh::getConnectivityMatrix() const
{
   uint32_t N = this->getNumTriangles();
   vector<bool> interiour_nodes = this->getInteriourNodes();

   MyMatrixCRS M(N, N);
   for (uint32_t i=0; i<N; ++i)
   {
      for (uint32_t k=0; k<3; ++k)
      {
         uint32_t  A = _Topology[3*i + k],
                   B = _Topology[3*i + (k+1)%3];

         if (interiour_nodes[A])
         {
            M.Set(A, B, 1);
         }
         if (interiour_nodes[B])
         {
            M.Set(B, A, 1);
         }
      }
   }
   return M;
}


void mesh::ReadFromBinary(string const& InFileName) {
	ifstream in_file(InFileName, ifstream::binary);
    uint32_t n;
	if (in_file){

    in_file.read(reinterpret_cast<char*>(&n), sizeof(uint32_t));
      _xCoords.ReadFromBinary(InFileName,sizeof(uint32_t));
      _yCoords.ReadFromBinary(InFileName,n*sizeof(double)+sizeof(uint32_t));
   }

   return;
}





