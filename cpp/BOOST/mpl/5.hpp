/* TMP to calculate the binary to decimal */

#ifndef _MPL_4_HPP_
#define _MPL_4_HPP_ 

template <unsigned long N>
struct binary 
{
    enum {
        value = binary<N/10>::value << 1 | (N%10)
    };
};

template <>
struct binary<0>
{
    enum {
        value = 0
    };
};


#endif // _MPL_4_HPP_

