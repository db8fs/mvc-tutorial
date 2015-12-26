
#ifndef IVIEW_HH_
#define IVIEW_HH_

/**
 * @interface IView
 * @brief Implementers may observe an object
 * @tparam T the object type to be viewed
 */

template< class T >
class IView
{
public:

    //! non-finalized destructor for correct memory cleanup
    virtual ~IView() {}


    /**
     * @brief updates the view by receiving current status object
     */

    virtual void update( const T & ) = 0;

};


#endif // IVIEW_HH_
