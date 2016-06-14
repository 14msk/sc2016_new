#include "MyVector.h"
class mesh
{
    public:
    /** Standardkonstruktor */
   mesh() : _xCoords(), _yCoords(), _Topology() {}

   /** Destruktor */
   ~mesh()
   {
   }
   /** @return Anzahl der Knoten */
   int getNumNodes() const
   {  return _xCoords.Size();  }

   /** @return Anzahl der Dreiecke im Mesh */
   uint32_t getNumTriangles() const
   {  return _Topology.size()/3;  }


   /** Meshinitialisierung durch einlesen von Binaer-File @p InFileName
   * @param [in] InFileName Name des Files, von dem gelesen wird
   */
   void ReadFromBinary(string const& InFileName);

   /** Mesh in Binaer-File @p OutFileName schreiben
   * @param [in] InFileName Name des Files, auf das geschrieben wird
   */
   void WriteToBinary(string const& OutFileName) const;


//private:
   MyVector _xCoords;               /*!< x Knotenkoordinaten */
   MyVector _yCoords;               /*!< y Knotenkoordinaten */
   vector<uint32_t> _Topology;

};
