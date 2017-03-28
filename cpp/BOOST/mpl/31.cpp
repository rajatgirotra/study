/* Variadic sequence
 * A variadic sequence is a member of sequence classes which has both variadic and numbered forms.
 *
 * 1] 
 * Let say Seq denotes the name of a generic sequence, then the variadic form allows us to specify a sequence of
 * n elements t1, t2, ..., tn where n is a predefined configurable limit BOOST_MPL_LIMIT_seq_SIZE allows us to specify a
 * sequence of
 * n elements t1, t2, ..., tn where n is a predefined configurable limit BOOST_MPL_LIMIT_seq_SIZE
 *
 * You had used BOOST_MPL_LIMIT_VECTOR_SIZE 40 in ebbs_deal_server in SCB when writin the transition table in boost MSM.
 *
 * 2] The numbered form also allows to specify a sequence of n elements where n is specified at the time of creation.
 * There is no maximum limit on the size of n except that dictated by the compiler
 *
 * Seqn < t1, t2, ... tn>
 *
 * The BOOST MPL provides vector, map and list  and many other as variadic sequences; so we have
 *
 * boost::mpl::vector<>
 * boost::mpl::vectorn<>
 *
 * boost::mpl::list<>
 * boost::mpl::listn<>
 *
 * and many more.
 *
 * So let us now continue with defining our dimensions using boost::mpl
 */

#include <iostream>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>

using namespace std;
namespace mpl = boost::mpl;

//Define our dimensions.

typedef mpl::vector< mpl::int_<1>,
                     mpl::int_<0>, 
                     mpl::int_<0>, 
                     mpl::int_<0>, 
                     mpl::int_<0>, 
                     mpl::int_<0>, 
                     mpl::int_<0> > mass;

typedef mpl::vector< mpl::int_<0>,
                     mpl::int_<1>, 
                     mpl::int_<0>, 
                     mpl::int_<0>, 
                     mpl::int_<0>, 
                     mpl::int_<0>, 
                     mpl::int_<0> > length;

// Instead of the verbose definition above, we can use vector_c class which is nothing but a wrapper to create a
// variadic sequence of integral constants like int_, bool_ etc.
typedef mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> Time;
typedef mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;
typedef mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperatur;
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> angle;


//Complex types
typedef mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity; // l/t
typedef mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0> accelaration; // l/(t2)
typedef mpl::vector_c<int, 1, 1, -1, 0, 0, 0, 0> momentum; // ml/t
typedef mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0> force; // ml/t2

//Scalar type. ie no dimension like Pi, e, etc..
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 0> scalar; // scalar

// Now we need a way to represent a quantity in these types. Let say mass of 49.5, or length of 2.3.
// For this we create a class called quantity which takes two template parameters, one for value and one for dimension.
template <typename T, typename Dimension>
struct quantity
{
    private:
        T m_value;

    public:
        explicit quantity(const T& roT) : m_value(roT)
        {
        }

        T value() const { return m_value; }
};

//Addition and subtraction should be easy to define now.
template <typename T, typename D>
quantity<T, D> operator + (const quantity<T, D>& lhs, const quantity<T, D>& rhs)
{
    return quantity<T,D>(lhs.value() + rhs.value());
}

template <typename T, typename D>
quantity<T, D> operator - (const quantity<T, D>& lhs, const quantity<T, D>& rhs)
{
    return quantity<T,D>(lhs.value() - rhs.value());
}


int main()
{
    quantity<int, length> l(10);
    quantity<int, length> l2(30);
    quantity<double, mass> m(72.2);

     //m = l; //compiler error coz quantity<int, length> is not compatible with quantity<double, mass>
     l = l + l2;
     cout << l.value() << endl; 
}

//Multiplication and division is slightly more difficult, because you can multiply different dimensions.
//Eg: Force = mass * accelaration, so the resultant dimension should be force.
//So basically during multiplication we have to add the corresponding types in the two dimension sequences.
//We'll use the transform algorithm of mpl.
//template <typename Sequence1, typename Sequence2, typename BinaryOperation>
//struct transform;
//The result is a sequence.
template <typename T, typename D1, typename D2>
quantity<T, typename mpl::transform<D1, D2, mpl::plus>::type >
operator * (const quantity<T, D1>& lhs, const quantity<T, D2>& rhs)
{
 // This will not compile. Because everyone knows that template arguments of metafunctions must be types.
 // But here we are passing, mpl::plus which is not a type but a class template.
 //
 // Eg:
 // template <typename T>
 // struct B{};
 //
 // so B is not a type but a class template, and B<double> is a type.
}

