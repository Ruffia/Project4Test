#include <iostream>
using namespace std;

#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi
#include <sstream>
#include <algorithm>

int main ()
{
	std::string str_dec = "2001, A Space Odyssey";
	std::string str_hex = "40c3";
	std::string str_bin = "-10010110001";
	std::string str_auto = "0x7f";

	std::string::size_type sz;   // alias of size_t

	int i_dec = std::stoi (str_dec,&sz);
	int i_hex = std::stoi (str_hex,nullptr,16);
	int i_bin = std::stoi (str_bin,nullptr,2);
	int i_auto = std::stoi (str_auto,nullptr,0);

	std::cout << str_dec << ": " << i_dec << " and [" << str_dec.substr(sz) << "]\n";
	std::cout << str_hex << ": " << i_hex << '\n';
	std::cout << std::hex << ": " << i_hex << '\n';
	std::cout << str_bin << ": " << i_bin << '\n';
	std::cout << str_auto << ": " << i_auto << '\n';


	int x = 26 ;
	string out;
	stringstream ss;
	ss << std::hex <<x;
	ss >> out ;
	::transform(out.begin(), out.end(), out.begin(), ::toupper);
	int b = 0;
	sscanf(out.c_str(),"%X",b);
	int a = std::stoi (out,nullptr,16);
	cout << out <<endl;

	return 0;
}