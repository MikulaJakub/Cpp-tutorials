#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>

// server
// create and write into a shared memory segment
// client will attach to the segment and read from it

using namespace std;

int main()
{
	cout << "Server has started ... " << endl;

	key_t key;
	size_t size;	
	int shmflg;

	// size of shared memory segment
	// creating a size of four integers
	size = 4*sizeof(int);

	// create a shared memory segment
	key = IPC_PRIVATE;		//let the kernel choose a new key
//	key = ftok("shmfile",65);	//ftok to generate unique key	

	shmflg = 0666|IPC_CREAT;

	cout << "Requesting shared memory ..." << endl;
	int id = shmget(key, size, shmflg);

	cout << "Shared memory segment created:" << endl;
	cout << "id = " << id << endl;
	cout << "key = " << key << endl;
	cout << "size = " << size << endl;
	cout << "shmflg = " << shmflg << endl;

	// attach to shared memory segment with the given id and write data
	cout << "Attaching to shared memory segment to write data ..." << endl;	
	
	int* shared_memory;
	shared_memory = (int*) shmat(id, NULL, 0666);

	cout << "Shared memory attached at address " << shared_memory << endl;
	struct shmid_ds shmbuffer;
	shmctl(id, IPC_STAT, &shmbuffer);
	int segment_size = shmbuffer.shm_segsz;
	cout << "Segment size = " << segment_size << endl;

	*shared_memory = 10;
	*(shared_memory+1) = 9;
	*(shared_memory+2) = 8;
	*(shared_memory+3) = 7;


	// detach from shared memory
	shmdt(shared_memory);

	cout << "Server has finished!" << endl;

	return(0);

}
