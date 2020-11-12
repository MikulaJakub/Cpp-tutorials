//(c) 2020
//
// PURPOSE:: 	This example writes a standard vector of a higher dimension into a binary file,
// 				and adding a new line into it. The file is a binary file.
//
//
// 				The structure of the vector in this example is:
//				1
// 				2 3
// 				4 5 6
// 				7 8 9 10
// 				. . . . . . . 
//			
//				and is added line by line
//
// COMPILE: g++ add2std_vector.cpp
//

#include <fstream>
#include <iostream>
#include <vector>

#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define RESET   "\033[0m"

using namespace std;
int main(int argc, char *argv[])
{
	cout << ' ' << endl;
	cout <<BOLDYELLOW<< "Program has started ... " <<RESET<<endl;

	int N = 0;
	char* p;
	if (argc > 1)
		N = strtol(argv[1], &p, 10);
	else
	{
		cout <<BOLDRED<< "Program requires one input argument!" <<RESET<< endl;
		cout <<BOLDRED<< "Process terminated!" <<RESET<< endl;
		exit(1);
	}

	// Initialize a vector that is to be added
	vector<double> vec_out;
	for (int i=0; i<N; i++)
		vec_out.push_back((double)i);

	int majorSize = 1;

	// write std vector line by line into a file
	cout << "Writing std vector into a binary file ..." << endl;
	
	// (1) create a file if it does not exist
	ifstream check_file("vec.bin", ios:: binary | ios:: out);
	if (check_file.is_open())
	{
		cout << "File exists! Appending to the existing file!" << endl;

		// Here, we assume that the file exists and the structure of the file is correct 
	}
	else
	{
		cout <<BOLDRED<< "File does not exist!" <<RESET<< "A new file is created!" << endl;
		ofstream create_file("vec.bin", ios:: binary | ios:: out);
		create_file.write(reinterpret_cast<const char *>(&majorSize), sizeof(int));
		create_file.close();
		majorSize = 0;	// -1 because I just wrote the major size here.
	
		// Now, a binary file is created containing a single integer.

	}

	// Read the file to find out the current size of the array and modidfy it
	// First, check if the file is empty, if yes, write the major size int first !

	fstream modify_file("vec.bin", ios:: binary | ios:: in | ios:: out);
	if (modify_file.peek() == std::ifstream::traits_type::eof())
	{
		cout << "File is empty!" << endl;	
//		modify_file.close();		

//		ofstream start_file("vec.bin", ios:: binary | ios:: out);
//		start_file.write(reinterpret_cast<const char *>(&majorSize), sizeof(int));
//		start_file.close();
		cout <<BOLDRED<< "Something went wrong!" <<RESET<< endl;
		cout <<BOLDRED<< "Process terminated!" <<RESET<< endl;

		// The major size is writen above!
	}
	else
	{
		modify_file.seekp(0, ios::beg);	// the major size is written as the first integer

		int thisSize;
		modify_file.read((char*)&thisSize, sizeof(int));
		cout << "Current major size is " << thisSize << endl;
	
		majorSize += thisSize;
//		modify_file.close();
	}
	cout << "majorSize = " << majorSize << endl;	
	
//	modify_file.open("vec.bin", ios:: binary | ios:: in | ios:: out);

	// Set pointer to the end and add a new line
	modify_file.seekp(0, ios::end);
	int minorSize = vec_out.size();
	if (minorSize > 0)
	{
		modify_file.write(reinterpret_cast<const char *>(&minorSize), sizeof(int));
		modify_file.write(reinterpret_cast<const char *>(&vec_out[0]), vec_out.size()*sizeof(double));
	
		// Set the pointer back to the beginning to update the size
		modify_file.seekp(0, ios::beg);
		modify_file.write(reinterpret_cast<const char *>(&majorSize), sizeof(int));
	}
	// Close the file
	modify_file.close();


	// Read the file and print it:
	// ------------------------------------------------
	// read the file and print the result into terminal
	cout << "Reading the binary file ..." << endl;
	ifstream in_file("vec.bin", ios::in | ios::binary);
	in_file.read((char*) &majorSize, sizeof(int));

	std::vector<std::vector<double>> vec_in;
	for (int i=0; i<majorSize; i++)
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

