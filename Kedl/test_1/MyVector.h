#include <string>
#include <vector>
using namespace std;
/** Eigene Vektorklasse mit teilweise intelligenter dynamischer
    Speicherallokierung */
class MyVector
{
public:

   /** Standardkonstruktor */
   MyVector();

   /** Parameterkonstruktor
   * @param [in] n Vektorl&auml;nge
   */
   MyVector(uint32_t n);

   /** Parameterkonstruktor mit Initialisierung @p init
   * @param [in] n Vektorl&auml;nge
   * @param [in] init
   */
   MyVector(uint32_t n, double init);

   /** Parameterkonstruktor mit Initializer-List
   * @param [in] init  initializer_list
   */
   MyVector(initializer_list<double> const & init);

   /** Kopierkonstruktor
   * @param [in] v
   */
   MyVector(MyVector const& v);

   /** Destruktor (gibt Speicherplatz wieder frei) */
   ~MyVector();

   /** Zuweisungsoperator
   * @param [in] v
   */
   MyVector& operator=(MyVector const& v);

   /** Zugriffsoperator f&uuml;r const-Vektoren
   * @param [in] i Index
   * @return Wert von @p v an der Stelle @p i
   */
   double operator[](uint32_t i) const
   {  return _val[i];  }

   /** Zugriffsoperator
   * @param [in] i Index
   * @return Referenz auf Wert von @p v an der Stelle @p i
   */
   double& operator[](uint32_t i)
   {  return _val[i];  }

   /** Gibt Wert von @p v an der Stelle @p i
     * mit &Uuml;berpr&uuml;fung, ob Index zul&auml;ssig ist
     * @param [in] n Index
     * @return Wert von @p v an der Stelle @p i
   */
   double  get(uint32_t n) const;

   /** Zugriff auf Wert von @p v an der Stelle @p i
     * mit &Uuml;berpr&uuml;fung, ob Index zul&auml;ssig ist
     * @param [in] n Index
     * @return Referenz auf Wert von @p v an der Stelle @p i
   */
   double& get(uint32_t n);

   /** &Uuml;berpr&uuml;fung, ob 0 <= i < @p _n */
   void IndexCheck(uint32_t i) const;

   void     operator+=(MyVector const& rhs);
   void     operator-=(MyVector const& rhs);

   /** Komponentenweise Multiplikation mit @p a
   * @param [in] a
   * @return Vektor multipliziert mit @p a
   */
   MyVector operator*(double a) const;

   /** Vektoraddition
   * @param [in] rhs rechte Seite
   * @return Vektor-Summe
   */
   MyVector operator+(MyVector const& rhs) const;

   /** Vektorsubtraktion
   * @param [in] rhs rechte Seite
   * @return Vektor-Differenz
   */
   MyVector operator-(MyVector const& rhs) const;


   /**
   * @return Anzahl der Elemente (@p _length)
   */
   uint32_t Size() const
   {
     return _length;
   }

   /**
   * @return Kapazit&auml;t (@p _capacity)
   */
   uint32_t Capacity() const
   {
     return _capacity;
   }

   /** Clear l&ouml;scht gesamten Vektor, auch den
   * reservierten Speicher.
   */
   void Clear();

   /** F&uuml;ge Element am Ende des Vektors hinzu
   * @param [in] x hinzuzuf&uuml;gendes Element
   */
   void PushBack(double x);

   /** Erh&ouml;ht den reservierten Speicherplatz, falls
   * @p n > @p _capacity
   * @param [in] n Zielkapazit&auml;t
   */
   void IncreaseCapacity(uint32_t n);

   /** Schreibe Vektor in ASCII_File @p OutFileName
   * @param [in] OutFileName Name des Files
   */
   void WriteToAscii(string const& OutFileName) const;

   /** Lies Vektor von ASCII-File @p InFileName ein
   * @param [in] InFileName Name des Files
   */
   void ReadFromAscii(string const& InFileName);

   /** Schreibe Vektor in Bin&auml;r-File @p OutFileName
   * @param [in] OutFileName Name des Files
   */
   void WriteToBinary(string const& OutFileName) const;

   /** Lies Vektor von Bin&auml;r-File @p InFileName ein
   * @param [in] OutFileName Name des Files
   */
   void ReadFromBinary(string const& InFileName, uint32_t offset);
   void VectorToBinary(string const& OutFileName) const;


private:
   uint32_t _length;      /*!< Vektorl&auml;nge */
   uint32_t _capacity;    /*!< Kapazit&auml;t (reservierter Speicher) */
   double*  _val;         /*!< Pointer auf das erste Vektorelement  */
};

MyVector operator*(double a, MyVector const& v);

ostream& operator<<(ostream& os, MyVector const& v);

double dot(MyVector const& a, MyVector const& b);

double norm(MyVector const& a);



