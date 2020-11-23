#include <iostream>
#include <thread>
#include <unistd.h>

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAutoInit.h>

using namespace std;

void run();

int main()
{
	cout << "Main program has started ... " << endl; 

	thread myThread(run);	

	// Here, the main program needs to sleep for a while,
	// when the main program closes, it terminates the thread too ! 
	while(1)
	{
		sleep(1);
	}	

	// Terminate the program with Ctrl+C
	cout << "Main program has finished!" << endl;
	return 0;
}

void run()
{
	VTK_MODULE_INIT(vtkRenderingOpenGL2)
	// otherwise I received error: no override found for ... 
	VTK_MODULE_INIT(vtkInteractionStyle)
	VTK_MODULE_INIT(vtkRenderingFreeType)	

	cout << "Running on a separate thread ... " << endl;
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();	

	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->SetWindowName("Empty blue window");
	renderWindow->AddRenderer(renderer);

	renderer->SetBackground(0.1, 0.3, 0.7);
	
	renderWindow->Render();
	renderWindowInteractor->Start();

	cout << "Thread finished!" << endl;
	return;
}

