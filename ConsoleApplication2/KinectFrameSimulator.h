#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

template <class T>
class KinectFrameSimulator
{
public:
	KinectFrameSimulator(int _With_nested, int height, string bufferFileAddress);
	~KinectFrameSimulator();
	void saveBufferToFile(T* bufferToSave, size_t size);
	void readBufferFromFile();
	void accessReadBuffer(T*& frameBuffer);
	void readAndAccessBuffer(T*& frameBuffer);
	void releaseBuffer(T*& frameBuffer);

private:
	void releaseBuffer();

	T* buffer;
	size_t    bufferSize;
	string    fileAddress;
	bool      deleteOnDestruction;
};

template <class T>
KinectFrameSimulator<T>::KinectFrameSimulator(int width, int height, string bufferFileAddress)
{
	if (bufferFileAddress.length() != 0)
		fileAddress = bufferFileAddress;
	else
		throw "File address to save the buffer is empty";

	bufferSize = width * height;

	try
	{
		buffer = new uint16_t[bufferSize];
	}
	catch (...)
	{
		throw "Failed to allocate memory";
	}
}

template <class T>
KinectFrameSimulator<T>::~KinectFrameSimulator()
{
	releaseBuffer();
}

template <class T>
void KinectFrameSimulator<T>::saveBufferToFile(T* bufferToSave, size_t size)
{
	if (size > bufferSize)
		throw "Indicated buffer size is bigger than the reserved one for the class";

	ofstream file(fileAddress);
	if (!file)
		throw "File could not be created or opened";

	if (file.is_open())
		for (size_t index = 0; index < size; index++)
			file << bufferToSave[index] << " ";
	else
		throw "Failed to open the '" + fileAddress + "' file";
	try
	{
		file.close();
	}
	catch (const std::exception&)
	{
		throw "Failed to close the file";
	}
}

template <class T>
void KinectFrameSimulator<T>::readBufferFromFile()
{
	ifstream file(fileAddress);
	if (!file)
		throw "File could not be created or opened";

	if (file.is_open())
		for (size_t index = 0; index < bufferSize; index++)
			file >> buffer[index];
	else
		throw "Failed to open the '" + fileAddress + "' file";

	try
	{
		file.close();
	}
	catch (const std::exception&)
	{
		throw "Failed to close the file";
	}
}

template <class T>
void KinectFrameSimulator<T>::accessReadBuffer(T*& frameBuffer)
{
	if (buffer)
		frameBuffer = buffer;
	else
		throw "Buffer is not read from the file";
}

template <class T>
void KinectFrameSimulator<T>::readAndAccessBuffer(T*& frameBuffer)
{
	readBufferFromFile();
	accessReadBuffer(frameBuffer);
}

template <class T>
void KinectFrameSimulator<T>::releaseBuffer()
{
	if (buffer)
		delete[] buffer;
	buffer = nullptr;
}

template <class T>
void KinectFrameSimulator<T>::releaseBuffer(T*& frameBuffer)
{
	if (frameBuffer)
		delete[] frameBuffer;
	frameBuffer = nullptr;
	buffer = nullptr;
}