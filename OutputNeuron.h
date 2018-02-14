
#ifndef OUTPUTNEURON
#define OUTPUTNEURON

#include "Neuron.h"

using namespace std;

class OutputNeuron : public Neuron
{
public:
	OutputNeuron(int NUMBER_OF_INPUTS);
	void CalculateError(float target);
	void UpdateWeights(int learningRate,float hSigmoid);
	float Activation(vector<float> entry) override;

	int GetPrediction() const;
	float GetError() const;
	~OutputNeuron();
private:

	float oerror;
	int prediction;
};
#endif

