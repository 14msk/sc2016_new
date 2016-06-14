#ifndef FILE_MYEXCEPTIONS
#define FILE_MYEXCEPTIONS

/**		Global new exception handler for "new".
 * 		requires the C++ call
 * 			set_new_handler( my_new_handler );
 * 		in the code to activate it.
 *
 *     \warning Function stop via std::exit .
**/
[[ noreturn ]] void my_new_handler(void);

/**	 Exception class in case of an invalid index @p i that is
*    not in interval [0,@p l-1].
**/
class OutOfRange
{
 public:
/** \brief Constructor that has to be used with "throw".
 *
 * \param[in] i  index with @p i < 0 or @p i >= l
 * \param[in] l  length of data array
 */
  OutOfRange(const long long int &i, const long long int &l);

/** \brief Allows the access to the index
 *
 * \return index that is responsible for exception
 */
  const long long int& Index() const
 	{ return index; }

/** \brief Allows the access to the array length
 *
 * \return array length
 */
  const long long int& Interval_End() const
 	{ return end_interval; }

 private:
  long long int index;       /**<  index */
  long long int end_interval;/**<  array length */
};


#endif


