#include<iostream>
#include<string>
#include<exception>
#include"AntoineEOS.hpp"
#include"get_x.hpp"

// Test1 - testing bash function being used to push to repo.

using std::string; using std::cout; using std::endl;
using std::cin; using std::stod; using std::invalid_argument;

const string ACETALDEHYDE("Acetaldehyde"), ACETIC_ACID("Acetic-acid"), ACETIC_ACID_AST(ACETIC_ACID+"*"),
ACETIC_ANHYDRIDE("Acetic-anhydride"), ACETONE("Acetone"), ACRYLIC_ACID("Acrylic-acid"), AMMONIA("Ammonia"),
ANILINE("Aniline"), BENZENE("Benzene"), N_BUTANE("n-Butane"), I_BUTANE("i-Butane"), _1_BUTANOL("1-Butanol"),
_2_BUTANOL("2-Butanol"),_1_BUTENE("1-Butene"),BUTYRIC_ACID("Butyric-acid"),CARBON_DISULFIDE("Carbon-disulfide"),
CARBON_TETRACHLORIDE("Carbon-tetrachloride"),CHLOROBENZENE("Chlorobenzene"),CHLOROBENZNE_AST(CHLOROBENZENE+"*"),

// Citation for Antoine coefficient data.
BOUBLIK_ET_HALA_CITE("T. Boublik, V. Fried, and E. Halla, "
"The Vapor Pressure of Pure Substances, Elisevier, Amsterdam, 1973"),

BYE("Fare thee well!");

// Function declarations
int menu(AntoineEOS&);

int main()
{
	AntoineEOS boublik_et_hala(BOUBLIK_ET_HALA_CITE, "mmHG", "C",true);
	boublik_et_hala.add_species(ACETALDEHYDE,8.00552,1600.017,291.809,-.2,34.4);
	boublik_et_hala.add_species(ACETIC_ACID, 7.38782, 1533.313, 22.309, 29.8, 126.5);
	boublik_et_hala.add_species(ACETIC_ACID_AST, 7.18807, 1416.7, 225, 0, 36);
	boublik_et_hala.add_species(ACETIC_ANHYDRIDE, 7.14948, 1444.718, 199.817, 62.8, 139.4);
	boublik_et_hala.add_species(ACETONE, 7.11714, 1210.595, 229.664,-12.9,55.3);
	boublik_et_hala.add_species(ACRYLIC_ACID, 5.65204, 648.629, 154.683,20.0,70.0);
	boublik_et_hala.add_species(AMMONIA, 7.55466, 1002.711, 247.885,-83,60);
	boublik_et_hala.add_species(ANILINE, 7.32010, 1731.515, 206.049, 102.6, 185.2);
	boublik_et_hala.add_species(BENZENE, 6.89272, 1203.531, 219.888, 14.5, 80.9);
	boublik_et_hala.add_species(N_BUTANE, 6.82485, 943.453, 239.711, -78.0, -0.3);
	boublik_et_hala.add_species(I_BUTANE, 6.7886, 899.617, 241.941, -85.1, -11.6);
	boublik_et_hala.add_species(_1_BUTANOL, 7.36366, 1305.198, 173.427, 89.2, 125.7);
	boublik_et_hala.add_species(_2_BUTANOL,7.20131,1157.000,168.279,72.4,107.1);
	boublik_et_hala.add_species(_1_BUTENE,6.53101,810.261,228.066,-77.5,-3.7);
	boublik_et_hala.add_species(BUTYRIC_ACID, 8.71019, 2433.014, 255.189, 20, 150);
	boublik_et_hala.add_species(CARBON_DISULFIDE, 6.94279, 1169.110, 241.593, 3.6, 79.9);
	boublik_et_hala.add_species(CARBON_TETRACHLORIDE, 6.87926, 1212.021, 226.409, 14.1, 76.0);
	boublik_et_hala.add_species(CHLOROBENZENE, 6.97808, 1431.053, 217.550, 62, 131.7);
	boublik_et_hala.add_species(CHLOROBENZNE_AST, 7.10690, 1500.0, 224.0, 0, 42);

	menu(boublik_et_hala);

	return 0;
}

// Give user option to leave program or return to menu.
int again(AntoineEOS& set) {
	cout << "\n\nSelect one of the two following options\n"
		"\t 1 - Return to main menu.\n"
		"\t 2 - Quit" << endl;

	int key = get_int();

	switch (key)
	{
	case 1:
		return menu(set);
	case 2:
		cout << BYE << endl;
		return 0;
	default:
		cout << "Invalid option" << endl;
		return again(set);
	}
}
// Give user 5 options, described in detail bellow. 
int menu(AntoineEOS& set)
{
	cout << " Choose from the following otpions\n"
		"\t1 - View full dataset.\n"
		"\t2 - View list of chemical species.\n"
		"\t3 - Get the saturation pressure for a species at a temperature.\n"
		"\t4 - Get range of saturation pressure values within temperature range \n"
		"\t5 - Quit" << endl;

	double high_temp, low_temp, inc, temp_d;
	int key = get_int();
	string str_key;

	switch (key)
	{
		// Otpion 1 - print whole dataset to consol
	case 1:
		cout << set.to_string() << endl;
		return again(set);

		// Option 2 - print the list of all chemical species in dataset to consol.
	case 2:
		cout << set.list_species() << endl;
		return again(set);

		// Option 3 - prompt user for name of chemical species, if the species is in the data set (must be spelled correctly and have the same case, may try to 
		// make program not case sensitive in the future), prompt display temperature range for species' Antoine parameters and prompt user for teperature (program will 
		// not stop user from puting in value outside of temperature range). Print the saturation pressure of the chemical species at the temperature given by the user, according 
		// to the Antoine coefficients in the dataset.
	case 3:
		cout << "Enter a chemical species." << endl;
		cin >> str_key;

		if (set.check_key(str_key))
		{
			cout << "Enter temperature in " << set.get_temperature_units() << "."
				"\nNote that for this data set, " << str_key << " has a temperature range between "
				<< set.get_t_lwr(str_key) << " and " << set.get_t_upr(str_key) << " " << set.get_temperature_units() << "." << endl;

			temp_d = get_double();

			cout << "At " << temp_d << " " << set.get_temperature_units() << ", " << str_key << " has a saturation pressure of "
				<< set.get_p_sat(str_key, temp_d) << " " << set.get_pressure_units() << "." << endl;
			return again(set);
		}
		else
		{
			cout << "Species not found, use second option in main menu to view list of species in library, be sure to enter species as it has been typed there." << endl;
			return again(set);
		}

		// Prompt user for name of chemical species, if chemical species is in dataset, print the coresponding temperature and saturation pressure values from the lower
		// temperature limit to the upper temperature limit in 50 increments.
	case 4:
		cout << "\nEnter chemical species." << endl;
		cin >> str_key;
		if (set.check_key(str_key))
		{
			low_temp = set.get_t_lwr(str_key);
			high_temp = set.get_t_upr(str_key);
			inc = (high_temp - low_temp) / 50;
			temp_d = low_temp;

			cout << "T(" << set.get_temperature_units() << ")\tP(" << set.get_pressure_units() << ")" << endl;
			for (int i = 0; i != 51; ++i)
			{
				cout << temp_d << "\t" << set.get_p_sat(str_key, temp_d) << endl;
				temp_d += inc;
			}
			return again(set);
		}
		else
		{
			cout << "Species not found, use second option in main menu to view list of species in library, be sure to enter species as it has been typed there." << endl;
			return again(set);
		}
		// Exit
	case 5:
		cout << BYE << endl;
		return 0;
	default:
		cout << "Invalid option, select option from menu." << endl;
		return again(set);
	}
}
