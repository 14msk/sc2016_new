#pragma once

class MyVector;
class MyMatrixCRS;

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
   uint32_t getNumNodes() const
   {  return _xCoords.Size()/2;  }

   /** @return Anzahl der Dreiecke im Mesh */
   uint32_t getNumTriangles() const
   {  return _Topology.size()/3;  }


   // MyVector

   /** Liefert Information &uuml;ber Knoten am Rand bzw. im Inneren des Gebiets.
   * @return Vektor @p v der L&auml;nge _getNumNodes(), mit
   * v[i] = true, wenn Knoten i im Inneren des Gebiets liegt.
   */
   vector<bool> getInteriourNodes() const;

   /** Liefert Informationen zu Knoten, die &uuml;ber Kanten zusammenh&auml;ngen.
   * @return Matrix M mit M(i,j) = 1, wenn Knoten i nicht am Rand ist und mit
   * Knoten j &uuml;ber eine Kante in Verbindung steht. Weiters ist M(i,i) = 0
   * f&uuml;r alle i.
   */
   MyMatrixCRS getConnectivityMatrix() const;

   /** Meshinitialisierung durch einlesen von Bin&auml;r-File @p InFileName
   * @param [in] InFileName Name des Files, von dem gelesen wird
   */
   void ReadFromBinary(string const& InFileName);

   /** Mesh in Bin&auml;r-File @p OutFileName schreiben
   * @param [in] InFileName Name des Files, auf das geschrieben wird
   */
   void WriteToBinary(string const& OutFileName) const;


private:
   MyVector _xCoords;               /*!< x Knotenkoordinaten */
   MyVector _yCoords;               /*!< y Knotenkoordinaten */
   vector<uint32_t> _Topology;      /*!< Netzaufbau: Je 3 Werte definieren ein Dreieck
                                         (Array mit 3*_NumTriangles Elementen) */
};
