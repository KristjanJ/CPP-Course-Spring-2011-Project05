#ifndef DYNAMICLINE_H
#define DYNAMICLINE_H

/*!
\brief A dynamic line.
*/
template <class T>
class DynamicLine
{
public:
    /*!
    \details Starting point of this line.
    */
    T* p1;

    /*!
    \details Ending point of this line.
    */
    T* p2;

    /*!
    \details Default constructor.
    */
    DynamicLine(void);

    /*!
    \details Constructs a line of two vectors.
    \param v1 Starting point.
    \param v2 Ending point.
    */
    DynamicLine(T* v1, T* v2);

    /*!
    \details Constructs a line from another line.
    \param l another line.
    */
    DynamicLine(const DynamicLine& l);

    /*!
    \details Destructor. Destructs this line.
    */
    ~DynamicLine(void);

    /*!
    \details Assignment operator. Makes a copy of another line and assigns it to this line.
    \param l another line.
    \returns A reference to this line.
    */
    DynamicLine& operator = (const DynamicLine& l);
};

template <class T>
DynamicLine<T>::DynamicLine(void)
{
    p1 = 0;
    p2 = 0;
}

template <class T>
DynamicLine<T>::DynamicLine(T* v1, T* v2)
{
    p1 = v1;
    p2 = v2;
}

template <class T>
DynamicLine<T>::DynamicLine(const DynamicLine& l)
{
    p1 = l.p1;
    p2 = l.p2;
}

template <class T>
DynamicLine<T>::~DynamicLine(void)
{
    p1 = 0;
    p2 = 0;
}

template <class T>
DynamicLine<T>& DynamicLine<T>::operator = (const DynamicLine& l)
{
    if (&l != this)
    {
        p1 = l.p1;
        p2 = l.p2;
    }

    return *this;
}

#endif // DYNAMICLINE_H
