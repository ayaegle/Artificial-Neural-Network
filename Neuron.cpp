//Adam Yaegle
//Neuron.C

#include "Neuron.h"
     

Neuron::Neuron(int NUMBER_OF_INPUTS) : sum(0.0f), threshold(0.5f), error(0.0f)
{
	//randomly initializes the weights of this neuron between 0 and 1
	srand(time(NULL));
	for (int i = 0; i < NUMBER_OF_INPUTS; i++)
	{
		float randomWeight = ((double)rand() / (RAND_MAX));
		weights.push_back(randomWeight);
	}
	wbias = ((double)rand() / (RAND_MAX));
}




//sums the input vector then squashes the sum with the sigmoid function
//returns a value between 0 and 1 (so it can be compared to the threshold to see if this neuron fires)
float Neuron::Activation(vector<float> entry)
{
	sum = 0.0f;
	cout.precision(3);
	for (int i = 0; i < (entry.size()); i++)
	{
		sum += entry.at(i) * weights.at(i);
	}
	sum += wbias;

	return Sigmoid();
}

//if the predictions made by the output neuron is incorrect the weights need to be updated
void Neuron::UpdateWeights(Entry inputs,int learningRate)
{
	for (int k = 0; k < weights.size(); k++)
	{ 
		weights.at(k) += error * inputs.at(k) *learningRate;
	}
	wbias = wbias + error * learningRate;
}

void Neuron::CalculateError(float outputNeuronError, float outputNeuronWeight)
{
	error = Gradient()*outputNeuronWeight*outputNeuronError;
}

float Neuron::Sigmoid()
{
	return 1.00f / (1.00f + exp(-sum));
}

float Neuron::Gradient()
{
	return Sigmoid()*(1.00f - Sigmoid());
}

float Neuron::GetWeight(int index) const
{
	return weights.at(index);
}

float Neuron::GetThreshold() const
{
	return threshold;
}

float Neuron::GetBiasWeight() const
{
	return wbias;
}

vector<float> Neuron::GetWeights() const
{
	return weights;
}

void Neuron::SetWeights(vector<float> newWeights)
{
	weights.clear();
	for (float weight:newWeights)
	{
		weights.push_back(weight);
	}
	
}




