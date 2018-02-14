#include "OutputNeuron.h"



OutputNeuron::OutputNeuron(int NUMBER_OF_INPUTS) : Neuron( NUMBER_OF_INPUTS)
{
	
}

void OutputNeuron::CalculateError(float target)
{
	oerror = Gradient()*(target - prediction);
}

void OutputNeuron::UpdateWeights(int learningRate,float hSigmoid)
{
	for (int i = 0; i < weights.size(); i++)
	{
		weights.at(i) += oerror*hSigmoid*learningRate;
	}
	wbias += oerror *learningRate;
}

//
float OutputNeuron::Activation(vector<float> entry)
{
	float activationResult = Neuron::Activation(entry);
	prediction = activationResult >= GetThreshold() ? 1 : 0;

	return prediction;
}



int OutputNeuron::GetPrediction() const
{
	return prediction;
}

float OutputNeuron::GetError() const
{
	return oerror;
}

OutputNeuron::~OutputNeuron()
{
}
