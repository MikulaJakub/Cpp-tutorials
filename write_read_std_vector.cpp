//(c) 2020
// 
// PURPOSE: This example writes a standard vector of a higher dimension into a binary file
//			Writting the following vector:
//
//			1
//			2 3
// 			4 5 6
//			7 8 9 10
// 			...
//
//			N ... N(N+1)/2
//
// COMPILE: g++ write_read_std_vector.cpp
//

#include <fstream>
#include <iostream>
#include <vector>

#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET   "\033[0m"

using namespace std;
int main(int argc, char *argv[])
{
	cout << ' ' << endl;
	cout <<BOLDYELLOW<< "Program has started ... " <<RESET<<endl;

	// read command line arguments (if any)
	int N = 10;
	char* p;
	if (argc > 1)	
		N = strtol(argv[1], &p, 10); 
	cout << "N = " << N << endl;


	// initialize a std vector:
	std::vector<std::vector<double>> vec_out;
	int k = 0;
	for (int i=0; i<N; i++)
	{
		std::vector<double> thisVec;
		for (int j=0; j<=i; j++)
		{
			thisVec.push_back((double)k);
			k++;
		}
		vec_out.push_back(thisVec);
	}	

	
	// write std vector into a binary file
	cout << "Writing std vector into a binary file ..." << endl;
	ofstream out_file("vec.bin", ios::out | ios::binary);
	int mainSize = vec_out.size();
	out_file.write(reinterpret_cast<const char *>(&mainSize), sizeof(int));
	for (auto& v : vec_out)
	{
		int thisSize = v.size();
		out_file.write(reinterpret_cast<const char *>(&thisSize), sizeof(int));
		out_file.write(reinterpret_cast<const char *>(&v[0]), v.size()*sizeof(double));
	}
	out_file.close();
	cout <<BOLDGREEN<< "Vector has been successfully written into a binary file!" <<RESET<<endl;

	// read the file and print the result into terminal
	cout << "Reading the binary file ..." << endl;
	ifstream in_file("vec.bin", ios::in | ios::binary);
	in_file.read((char*) &mainSize, sizeof(int));

	std::vector<std::vector<double>> vec_in;
	for (int i=0; i<mainSize; i++)
	{
		int thisSize;
		in_file.read((char*) &thisSize, sizeof(int));
		
		std::vector<double> thisVec;
		for (int j=0; j<thisSize; j++)
		{
			double thisValue;
			in_file.read((char*) &thisValue, sizeof(double));
			thisVec.push_back(thisValue);
		}
		vec_in.push_back(thisVec);
	}
	
	cout << "Printing the vector ... " << endl;
	for (int i=0; i<vec_in.size(); i++)
	{
		for (int j=0; j<vec_in[i].size(); j++)
			cout << vec_in[i][j] << ' ';

		cout << ' ' << endl;
	}


	cout <<BOLDGREEN<< "Program has finished!" <<RESET<<endl;
	cout << ' ' << endl;
	return 0;
}
