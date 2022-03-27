#include"AntoineEOS.hpp"

using std::string; using std::map; using std::pair; using std::domain_error;
using std::vector; using std::log10; using std::log; using std::pow;
using std::exp;

/*
	get():
	- Private method used to get coefficients associeted with species.
	- Arguments: 
		* species_name, used as key for coefficients associated with species.
		* index, if species name is found in map<string,vector<double>>, species name
			gets vector<double> containing species coefficients, from this vector, index
			gets the relavent coefficient. The indices coorespond to the coefficients as follows
			0:A, 1:B, 2:C, 3:"lower temperature limit", 4:"upper temperature limit"
	*/
double AntoineEOS::get(const string& species_name, const int& index) 
{
	if (this->coefficient_map.find(species_name) == this->coefficient_map.end())
		throw domain_error("Species name not in library.");
	else
		return this->coefficient_map[species_name][index];
}
/*
	Constructor
	Name should be a concise reference to the source of the data being kept in the object.
	- Arguments
		* source, citation for the source of the data stored in the object, object should contain data associated with
			a single source.
		* pressure units - units used for pressure (units cannot vary within an object).
		* temperature units - units used for temperature.
		* log10 - if true, indicates the data uses a log base 10 equation, otherwise, natural log is used.
	*/
AntoineEOS::AntoineEOS(const string& source, const string& pressure_units, const string& temperature_units,const bool& log10)
{
	this->source = source;
	this->pressure_units = pressure_units;
	this->temperatuter_units = temperature_units;
	this->longest_name_sz = 0;
	this->dec_sz_vec = vector<string::size_type>(5,0);
	this->log10 = log10;
}

bool AntoineEOS::check_key(const std::string& key)
{
	if (this->coefficient_map.find(key) != this->coefficient_map.end())
		return true;
	else
		return false;
}

/* edit_sourc()
	Replace source filed with new string.
	*/
void AntoineEOS::edit_source(const string& new_source) 
{
	this->source = new_source;
}

/** Get coefficients
	
	get_x() - x = a or b or c or t_lwr or t_uppr
	Get coefficient x, use private get() method to return
	coefficient x.
	- Arguments
		* species_name, name of species, if species is
			stored in object, returns coefficient.
	*/
double AntoineEOS::get_a(const string& species_name)
{
	return get(species_name,0);
}
double AntoineEOS::get_b(const string& species_name)
{
	return get(species_name,1);
}
double AntoineEOS::get_c(const string& species_name) 
{
	return get(species_name, 2);
}
double AntoineEOS::get_t_lwr(const string& species_name) 
{
	return get(species_name, 3);
}
double AntoineEOS::get_t_upr(const string& species_name) 
{
	return get(species_name, 4);
}
/* get_source()
	return string containing source associated with object data.
*/
string AntoineEOS::get_source() 
{
	return this->source;
}

string AntoineEOS::get_temperature_units()
{
	return this->temperatuter_units;
}
string AntoineEOS::get_pressure_units()
{
	return this->pressure_units;
}

/* add_species()
	- Add species and associated parameters to object. Species and data shoule be from 
		the same source as other species contained in object.
	- Arguments
		* species_name, name of species, used as key to get parameters.
		* a, b, c - antoine parameters associated with species.
		* t_lwr and t_upr - bounds of temperature range for data.
		*/
void AntoineEOS::add_species(const string& species_name, const double& a, const double& b,
	const double& c, const double& t_lwr, const double& t_upr) 
{

	vector<double> v = { a,b,c,t_lwr,t_upr };
	pair<string, vector<double>> item(species_name, v);
	this->coefficient_map.insert(item);

	if (species_name.size() > this->longest_name_sz)
		this->longest_name_sz = species_name.size();

	for (int i = 0; i != v.size(); ++i) 
	{
		if (std::to_string(v[i]).size() > this->dec_sz_vec[i])
			this->dec_sz_vec[i] = std::to_string(v[i]).size();
	}
}
/*  to_string()
	String, which if printed will print a table of the species in the object and their parameters
	*/
string AntoineEOS::to_string() 
{
	std::ostringstream convert;

	string longest_name_sz_len;

	if (this->longest_name_sz > 12)
		longest_name_sz_len = string(this->longest_name_sz - 10, ' ');
	else
		longest_name_sz_len = string(2, ' ');

	string t_upr_str("Upper Temperature Limit"), t_lwr_str("Lower Temperature Limit");
	string ret("\n");
	
	if (this->log10)
		ret += "\tLog_10(Psat) = A - B/(C + T)";
	else
		ret += "\tLn(Psat) = A - B/(C + T)";

	ret += "\tpressure units "+ this->pressure_units+", temperature units "+ this->temperatuter_units+".\n\n";
	
	ret += "Species Name" + longest_name_sz_len + "A" + string(this->dec_sz_vec[0] + 1, ' ') + "B" + string(this->dec_sz_vec[1] + 1, ' ') + "C" +
		string(this->dec_sz_vec[2] + 1, ' ') + t_lwr_str + string(4, ' ') + t_upr_str + "\n\n";
	
	string::size_type sz_1, sz_2;
	// Iterate through coefficient_map, appending parameters to ret.
	map<string, vector<double>>::iterator itr = this->coefficient_map.begin();
	for (itr; itr != this->coefficient_map.end(); ++itr) 
	{
		ret += itr->first + string(this->longest_name_sz-itr->first.size()+2,' ');

		for (int i = 0; i != 3; ++i) 
		{
			sz_1 = this->dec_sz_vec[i] + 2;
			sz_2 = std::to_string(itr->second[i]).size();
			ret += std::to_string(itr->second[i]) + string(sz_1 - sz_2, ' ');
		}

		sz_1 = t_lwr_str.size();
		sz_2 = std::to_string(itr->second[3]).size();
		ret += std::to_string(itr->second[3]) + string(sz_1 - sz_2 + 4, ' ');

		sz_1 = t_upr_str.size();
		sz_2 = std::to_string(itr->second[4]).size();

		ret += std::to_string(itr->second[4]) + string(sz_1 - sz_2 + 4, ' ');
		
		ret += "\n";
	}

	ret += "\nSource: " + this->source + "\n";

	return ret;
}

string AntoineEOS::list_species()
{
	string ret("");
	map<string, vector<double>>::iterator itr = this->coefficient_map.begin();
	for (itr; itr != this->coefficient_map.end(); ++itr)
	{
		ret += itr->first;
		ret += "\n";
	}
	return ret;
}

// EOS calculations

double AntoineEOS::get_p_sat(const string species_name, const double temperature)
{
	// P_sat = 10exp( A - B/(C+T) ); return P_sat
	double x = get_a(species_name) - get_b(species_name) / (get_c(species_name) + temperature);;

	if (log10)
		return pow(10, x);
	else
		return exp(x);
}