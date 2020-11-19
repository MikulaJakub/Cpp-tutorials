//(c) 2020, mikula_jakub@centrum.sk
//
// PURPOSE: Read a binary file into a 2D std vector
//			The data in the file are written as:
//			(I) 
//			(I) (F) (F) (F) ...  ^ 
//			(I) (F) (F) (F) ...  | major size
//			(I) (F) (F) (F) ...  |
//			....
//		          minor size	
//			    |<----------->|
//
//
// 			The vector format is:
//
// 			(F) (F) (F) ...
// 			(F) (F) (F) ...
// 			(F) (F) (F) ...
// 			... 
//
// 			where (F) is the float (4 bytes), (I) is integer (4 bytes)
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

	// Write the file `square.bin` first
	int N = 0;
	char* p;
	if (argc > 1)
		N = strtol(argv[1], &p, 10);
	else
	{
		cout <<BOLDRED<< "Program requires one (int) command line argument" <<RESET<< endl;
		cout <<BOLDRED<< "Process halted!" <<RESET<< endl;
		exit(1);
	}
	cout << "N = " << N << endl;
	std::vector<std::vector<float>> vec_out;
	int k = 0;
	for (int i=0; i<N;i ++)
	{
		std::vector<float> thisVec;
		for (int j=0; j<N; j++)
		{
			thisVec.push_back((float)k);
			k++;
		}
		vec_out.push_back(thisVec);
	}
	
	ofstream out_file("square.bin", ios::out | ios::binary);
	int mainSize = vec_out.size();
	out_file.write(reinterpret_cast<const char *>(&mainSize), sizeof(int));
	for (auto& v : vec_out)
	{
		int thisSize = v.size();
		out_file.write(reinterpret_cast<const char *>(&thisSize), sizeof(int));
		out_file.write(reinterpret_cast<const char *>(&v[0]), v.size()*sizeof(float));
	}
	out_file.close();

	cout <<BOLDGREEN<< "File has been written!" <<RESET<< endl;

	cout << "Reading the binary file square.bin ..." << endl;
	ifstream in_file("square.bin", ios::in | ios::binary);

	int majorSize;
	int minorSize;
	in_file.read((char*) &majorSize, sizeof(int));
	in_file.read((char*) &minorSize, sizeof(int));

	std::vector<std::vector<float>> vec_in;

	#pragma omp parallel
	{
		cout << "hello world!" << endl;
	}

	vec_in.resize(majorSize);

	#pragma omp parallel for
	for (int i=0; i<majorSize; i++)
	{
		// each processor has to open the file independently 
		ifstream this_in_file("square.bin", ios::in | ios::binary);
	
		int position = 4+4*(i+1)+4*minorSize*i;
		cout << "position = " << position << endl;	
		this_in_file.seekg(position,ios::beg);
		
		std::vector<float> thisVec;
		thisVec.resize(minorSize);
		for (int j=0; j<minorSize; j++)
		{
			float thisValue;
			this_in_file.read((char*) &thisValue, sizeof(float));
			thisVec[j] = thisValue;
		}
		vec_in[i] = thisVec;
		this_in_file.close();
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
