#include "get_x.hpp"

using std::string; using std::cin; using std::cout;
using std::endl;  using std::invalid_argument;



double get_double()
{
	string str;
	double ret;
	bool exit = false;

	while (!exit)
	{
		try
		{
			cin >> (str);
			ret = stod(str);
			exit = true;
		}
		catch (invalid_argument ex)
		{
			cout << "Must enter number" << endl;
			exit = false;
		}
	}

	return ret;
}

int get_int()
{
	return (int)get_double();
}