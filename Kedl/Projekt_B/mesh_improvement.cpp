/** @file mesh_improvement.cpp
*   @author Simon Pieber, Pia Kedl
*   @date SoSe 2016
*/


#include <iostream>
#include <vector>



using namespace std;

#include "MyVector.h"
#include "MyMatrixCRS.h"
#include "mesh.h"
#include "mesh_improvement.h"


void ImproveMesh(mesh& in_mesh)
{
   MyMatrixCRS M = in_mesh.getConnectivityMatrix();

   uint32_t const NumNodes = in_mesh.getNumNodes();
   MyVector NumNeighbours(NumNodes);
   for (uint32_t i=0; i<NumNodes; ++i)
   {
      NumNeighbours[i] = M.getNumNonZeros(i);
   }

   MyMatrixCRS& M_lhs = M; // M wird nicht mehr gebraucht
   MyMatrixCRS  M_rhs = M;

   for (uint32_t i=0; i<NumNodes; ++i)
   {
      for (uint32_t j=0; j<i; ++j)
      {
         M_rhs.Set(i,j,0);
      }
      for (uint32_t j=i+1; j<NumNodes; ++j)
      {
         M_lhs.Set(i,j,0);
      }
   }

   for (size_t i=0; i<NumNodes; ++i)
   {
      M_lhs.MultiplyRowWithScalar(i, -1.0/NumNeighbours[i] );
      M_rhs.MultiplyRowWithScalar(i,  1.0/NumNeighbours[i] );
      if (NumNeighbours[i] < 0.5) // <=> Knoten i ist am Rand
      {
         M_rhs.Set(i,i,1);
      }
   }

}
