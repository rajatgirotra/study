#include <algorithm>
#include <vector>
using namespace std;

struct Apple
{
	Apple(double weight, int age) :
		m_weight(weight),
		m_age(age)
	{}

	double m_weight; // The apple's weight, in kg
	int m_age; // The apple's age, in days
};

int main()
{
	vector<Apple> myApples;
	myApples.push_back(Apple(0.50, 35));
	myApples.push_back(Apple(0.75, 40));
	myApples.push_back(Apple(0.35, 37));

	// Sort the apples by their age
	sort(myApples.begin(),
		myApples.end(),
			[](const Apple &a, const Apple &b) -> bool
			{
				return (a.m_weight < b.m_weight);
			});

	return 0;
}
