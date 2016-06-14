#ifndef TEST_1_HPP_INCLUDED
#define TEST_1_HPP_INCLUDED

#include <string>

class mesh
{
   /** Standardkonstruktor */
   mesh(const int m, const int n);

   /** Destruktor */
   ~mesh();

   /** @return Anzahl der Knoten */
   int getNumNodes() const
   {
       //return _VertexCoords.Size()/2;
        }

   /** @return Anzahl der Dreiecke im Mesh */
  // int getNumTriangles() const
   //{  return _NumTriangles;  }


   /** Meshinitialisierung durch einlesen von Binaer-File @p InFileName
   * @param [in] InFileName Name des Files, von dem gelesen wird
   */
   void ReadFromBinary(std::string const& InFileName);


   /** Mesh in Binaer-File @p OutFileName schreiben
   * @param [in] InFileName Name des Files, auf das geschrieben wird
   */
   void WriteToBinary(std::string const& OutFileName) const;



private:
   double* _VertexCoords;          /*!< Knotenkoordinaten */
      int _NumTriangles;               /*!< Anzahl der Dreiecke */
      int _NumVertices;               /*!< Anzahl der Dreiecke */
   int* _Topology;                  /*!< Netzaufbau: Je 3 Werte definieren ein Dreieck
                                         (Array mit 3*_NumTriangles Elementen) */


};

#endif // TEST_1_HPP_INCLUDED
