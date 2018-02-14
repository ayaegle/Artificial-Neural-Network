//Adam Yaegle
//Normalizer.C
#ifndef NORMALIZER
#define NORMALIZER

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;


typedef vector<float> Entry;
void Normalize(string inputFile, string outputFile, char delim, int NUMBER_OF_INPUTS);
Entry GetLineFromInputFile(ifstream & inputFile, char delim, int NUMBER_OF_INPUTS);
Entry Normalizer(Entry unNormalized, int numbersAmt);
void WriteLineToOutputFile(ofstream & outputFile, Entry entry);





void Normalize(string inFile, string outFile, char delim, int NUMBER_OF_INPUTS)
{
	//open inputFile and outputFile
	ifstream inputFile;
	ofstream outputFile;
	inputFile.open(inFile.c_str());
	outputFile.open(outFile.c_str());

	Entry entry;
	vector<Entry> data;
	string inputString;
	float target;


	cout << "NORMALIZING..." << endl;
	//skip the initial data in the file
	for (int i = 0; i < NUMBER_OF_INPUTS; i++)
	{
		getline(inputFile, inputString, '\n');
		inputString = "";
	}


	entry = GetLineFromInputFile(inputFile, delim, NUMBER_OF_INPUTS);
	target = entry.at(NUMBER_OF_INPUTS - 1);
	while (inputFile)
	{
		entry = Normalizer(entry, (NUMBER_OF_INPUTS));
		entry.at(NUMBER_OF_INPUTS - 1) = target;//probalby push_back
		data.push_back(entry);
		WriteLineToOutputFile(outputFile, entry);
		entry = GetLineFromInputFile(inputFile, delim, NUMBER_OF_INPUTS);
		target = entry.at(NUMBER_OF_INPUTS - 1);
	}
	inputFile.close();
	outputFile.close();
}

Entry GetLineFromInputFile(ifstream & inputFile, char delim, int NUMBER_OF_INPUTS)
{

	float input;
	string inputString;

	Entry entry;
	entry.clear();


	for (int i = 0; i < NUMBER_OF_INPUTS; i++)
	{
		getline(inputFile, inputString, delim);
		input = atof(inputString.c_str());
		entry.push_back(input);
	}

	return entry;
}

Entry Normalizer(Entry unNormalized, int numbersAmt)
{
	Entry normalized;
	float normalizedNum;
	float numsSquared = 0;
	float magnitude;


	for (int i = 0; i < numbersAmt; i++)
	{
		//cout << unNormalized.at(i) << " ";
		numsSquared += pow(unNormalized.at(i), 2);
	}
	//cout << endl;
	magnitude = sqrt(numsSquared);


	for (int i = 0; i < numbersAmt; i++)
	{
		if (magnitude != 0)
		{
			normalizedNum = unNormalized.at(i) / magnitude;
		}
		else if (magnitude == 0)
		{
			normalizedNum = 0.01;
		}

		//just to keep normalizedNum between 0.01 and .99
		if (normalizedNum >= 0.99)
		{
			normalizedNum = 0.99;
		}
		else if (normalizedNum <= 0.01)
		{
			normalizedNum = 0.01;
		}

		normalized.push_back(normalizedNum);
	}
	//normalized.push_back(unNormalized.at(numbersAmt)); //adds the unNormalized target into the entry

	return normalized;
}

void WriteLineToOutputFile(ofstream & outputFile, Entry entry)
{
	for (int i = 0; i < entry.size(); i++)
	{
		outputFile.precision(3);
		outputFile << fixed << entry.at(i) << " ";
	}
	outputFile << endl;
}
#endif






