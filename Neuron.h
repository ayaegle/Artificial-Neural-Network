//Adam Yaegle
//Neuron.h
#ifndef NEURON
#define NEURON

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <cmath>
#include <stdio.h>
#include <time.h>  

using namespace std;
typedef vector<float> Entry;

class Neuron
{
public:

	Neuron(int NUMBER_OF_INPUTS);//neuron with random weights

	//summation and then sigmoid
	virtual float Activation(vector<float> entry);
	virtual void UpdateWeights(Entry inputs,int learningRate);
	virtual void CalculateError(float outputNeuronError,float outputNeuronWeight);

	float Sigmoid();
	float Gradient();
	float GetWeight(int index) const;
	float GetThreshold() const;
	float GetBiasWeight() const;
	vector<float> GetWeights()const;
	void SetWeights(vector<float> newWeights);


protected:
	vector<float> weights;
	float wbias;

private:
	float sum;
	float threshold;
	float error;
};

#endif // !NEURON