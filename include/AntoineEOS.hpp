#ifndef ANTOINEEOS_HPP
#define ANTOINEEOS_HPP

#include<string>
#include<stdexcept>
#include<iostream>
#include<sstream>
#include<vector>
#include<map>
#include<cmath>

struct AntoineEOS
{
private:
	std::map<std::string, std::vector<double>> coefficient_map;
	std::string source, pressure_units, temperatuter_units;
	std::string::size_type longest_name_sz;
	// dec_sz_vec, vector of dec sizes for coefficients, used for 
	// formating in to_string() method.
	std::vector<std::string::size_type> dec_sz_vec;
	bool log10;

	// Get
	double get(const std::string&, const int&);

public:
	AntoineEOS(const std::string&,const std::string&,const std::string&,const bool&);

	// Check for key
	bool check_key(const std::string&);

	// Edit source
	void edit_source(const std::string&);

	// Getters
	double get_a(const std::string&), get_b(const std::string&), get_c(const std::string&),
		get_t_lwr(const std::string&), get_t_upr(const std::string&);
	std::string get_source();

	std::string get_temperature_units(), get_pressure_units();

	// Add species and associated parameters.
	void add_species(const std::string&, const double&, const double&, const double&,
		const double&, const double&);
	


	// to_string()
	std::string to_string();
	std::string list_species();

	// EOS calculations
	double get_p_sat(const std::string,const double);
};
// Test to see I succesfully pushed from new computer
#endif