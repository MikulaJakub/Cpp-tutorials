#include <sys/ipc.h>
#include <sys//shm.h>
#include <iostream>

// client
// attach to the shared memory segment created by server and read from it

using namespace std;

int main()
{

	cout << "Client has started ..." << endl;

	// attch to shared memory
	int id;
	cout << "Enter shared memory id: " ;
	cin >> id;	
	

	int* shared_memory;
	shared_memory = (int*) shmat(id, NULL, 0666);

	// read from the shared memory

	cout << "*shared_memory = " << *shared_memory << endl;
	cout << "*(shared_memory+1) = " << *(shared_memory+1) << endl;
	cout << "*(shared_memory+2) = " << *(shared_memory+2) << endl;
	cout << "*(shared_memory+3) = " << *(shared_memory+3) << endl;

	// detach from shared memory
	shmdt(shared_memory);


	// destroy shared memory segment
	cout << "Destroying the shared memory segment ..." << endl;

	shmctl(id, IPC_RMID, NULL);	//IPC_RMID indicates this is a remove operation
	cout << "Shared memory segment destroyed!" << endl;
	
	cout << "Client has finished!" << endl;

}
