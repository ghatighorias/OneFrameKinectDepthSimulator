// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "KinectFrameSimulator.h"

using namespace std;

void generateRandomArray(uint16_t*& frameBuffer, size_t size)
{
	if (frameBuffer)
		delete[] frameBuffer;

	frameBuffer = new uint16_t[size];

	for (size_t index = 0; index < size; index++)
		frameBuffer[index] = rand() % 8192;

}

int main()
{
	int width = 5;
	int heigth = 2;
	size_t arraySize = width * heigth;
	uint16_t* buffer = nullptr;
	uint16_t* Rbuffer = nullptr; 
	string fileAddress = "D:\\example.txt";
	KinectFrameSimulator<uint16_t>* simulator =  new KinectFrameSimulator<uint16_t>(width, heigth, fileAddress);
	
	
	generateRandomArray(buffer, arraySize);
	
	simulator->saveBufferToFile(buffer, arraySize);
	simulator->readAndAccessBuffer(Rbuffer);

	for (size_t i = 0; i < arraySize; i++)
	{
		cout << Rbuffer[i] << " ";
	}

	simulator->releaseBuffer(Rbuffer);
	delete simulator;
	getchar();
    return 0;
}



