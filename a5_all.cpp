
#include<string>
#include<iterator>
#include<list>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<functional>
using namespace std;
using namespace placeholders;

/*
Find whether the given string is palindrome
*@param phrase is the string
*@return true if palindrome or else false
*/
bool is_palindrome(const string &phrase)
{
	string temp;
	string::iterator it = temp.begin();

	//inserter since temp is empty

	remove_copy_if(phrase.begin(), phrase.end(), inserter(temp, it), [](char x) {return !isalpha(x); });
	transform(temp.begin(), temp.end(), temp.begin(), [](char x) {return toupper(x); });
	bool result = equal(temp.begin(), temp.begin() + temp.length() / 2, temp.rbegin());
	return result;

}
/*
Tests is_palindrome() function by providing strings
*/

void test_is_palindrome()
{
	string str_i = string("Was it a car or a cat i saw?");
	string str_u = string("Was it a car or a cat U saw?");
	cout << "The phrase \"" + str_i + "\" is " + (is_palindrome(str_i) ? "" : "not") + "a palindrome\n";
	cout << "The phrase \"" + str_u + "\" is " + (is_palindrome(str_u) ? "" : "not") + " a palindrome\n";
}


/*
*template class that finds the second largest element
*@param start, represents begining of container
*@param finish, represents end of container
*@return a pair of position of second largest element and bool if found
*/
template <class Iterator>
std::pair<Iterator, bool> second_max(Iterator start, Iterator finish)
{

	if (start == finish)
	{
		return make_pair(finish, false);
	}
	else
	{
		auto temp = *start;
		auto it1 = start;
		bool nsame = false;
		for (auto i = ++it1; i < finish; i++)
		{
			if (*i != temp)
			{
				nsame = true;
			}
		}
		if (nsame == false)
			return make_pair(start, false);
		else
		{

			auto l1 = *start;
			auto pos1 = start;
			auto it2 = start;
			auto l2 = *(++it2);
			auto pos2 = it2;

			if (l2 > l1)
			{
				auto temp = l2;
				l2 = l1;
				l1 = temp;
				pos2 = start;
				pos1 = it2;
			}
			it2++;
			while (it2 != finish)
			{
				if (*it2 > l1)
				{
					l1 = *it2;
					l2 = l1;
					pos2 = pos1;
					pos1 = it2;

				}
				else if (*it2 > l2 && *it2 < l1)
				{
					l2 = *it2;
					pos2 = it2;
				}
				it2++;
			}
			return make_pair(pos2, true);
		}
	}

}
/*
Function to test second_max function

*/
void test_second_max(vector<int> vec)
{
	auto retval = second_max(vec.begin(), vec.end());
	if (retval.second)
	{
		cout << "The second largest element in vec is " << *retval.first << endl;
	}
	else
	{
		if (retval.first == vec.end())
			cout << "List empty, no elements\n";
		else
			cout << "Container's elements are all equal to " << *retval.first << endl;
	}
}


/*
Lambda Function to calculate number of string of length n
@param vec- represents vector<string>, n- length of string
@return count of strings
*/

int countStringLambda(vector<string> vec, int n)
{
	return count_if(vec.begin(), vec.end(), [n](string l) {return l.length() == n; });
}

/*
class for overloaded comparator
overload operator() to return bool result comparing string with given length
*/


class stringlength
{
	int len;
public:
	stringlength(int n) :len{ n } {}
	bool operator()(string l) const
	{
		return l.length() == len;
	}
};

/*
counts the number of strings of length n using comparator class
*@param vec , represents vector<string>
*@param n ,length of string
*@return number of strings

*/
int countStringFunctor(vector<string> vec, int n)
{
	stringlength sl(n);
	return count_if(vec.begin(), vec.end(), sl);
}

/*
Free function that return bool result comparing string length with given length
*/

bool freeStringlength(string l, int n)
{
	return l.length() == n;
}


/*
counts the number of strings of length n using FreeFun
*@param vec , represents vector<string>
*@param n ,length of string
*@return number of strings

*/
int countStringFreeFun(vector<string> vec, int n)
{

	return count_if(vec.begin(), vec.end(), std::bind(&freeStringlength, _1, n));
}

/*
counts the frequency of letters using lambda and stores in a map
and outputs the map

*/

void charFrequency()
{

	cout << "Enter one or more lines of text.\n";
	cout << "To end input press Ctrl-X in Windows and Ctrl-D in Linux \n";
	map<char, int> freq;
	istream_iterator<char> istart(cin), fin;
	for_each(istart, fin, [&freq](char i) {if (i == ' ') {} else ++freq[i]; });
	for_each(freq.begin(), freq.end(), [](pair<char, int> a) {cout << a.first << " " << a.second << endl; });
}
/*
struct for overloaded comparator
overload operator() to return bool result comparing strings for desired results
*/

struct compare
{
	bool operator()(const string &a, const string &b)
	{
		if (a.length() < b.length())
		{
			return true;
		}
		else if (a.length() > b.length())
		{
			return false;
		}

		//lexically compares two strings
		return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}
};


/*
uses multiset with compare comparator to store string in desired order
and prints the multiset
*/
void multisetUsingMyComparator()
{
	multiset<string, compare>strSet;
	vector<string> vec = { "C","BB","A","CC","A","B","BB","A","D","CC","DDD","AAA" };
	copy(vec.begin(), vec.end(), inserter(strSet, strSet.begin()));
	ostream_iterator<string> out(cout, " ");
	copy(strSet.begin(), strSet.end(), out);
}

int main()
{
	//problem 1:
	test_is_palindrome();
	cout << "\n";

	//problem 2:
	vector<int> v1{ 1 };
	test_second_max(v1);
	vector<int> v2{ 1,1 };
	test_second_max(v2);
	vector<int> v3{ 1,1,3,3,7,7 };
	test_second_max(v3);
	cout << "\n";

	//problem 3:
	vector<string> vecstr{ "count_if", "Returns", "the", "number", "of", "elements", "in", "the","range", "[first", "last)", "for", "which", "pred", "is", "true." };
	cout << countStringLambda(vecstr, 5) << endl;
	cout << countStringFreeFun(vecstr, 5) << endl;
	cout << countStringFunctor(vecstr, 5) << endl;
	cout << "\n";

	//problem 4:
	charFrequency();
	cout << "\n";


	//problem 5:
	multisetUsingMyComparator();
	cout << "\n";
	return 0;
}
