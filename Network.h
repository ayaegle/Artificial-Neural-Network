#ifndef NETWORK
#define NETWORK

#include <vector>
#include "Neuron.h"
#include <istream>
#include <fstream>
#include "OutputNeuron.h"

using namespace std;
typedef vector<float> Entry;


class Network
{
public:
	Network() = delete;
	Network(int hiddenCount,int LearningRate,int NumberOfInputs);
	
	void ReadInPrompts(string filename);
	void Train(int TrainingSessions,vector<Entry> data);

	int GetLearningRate() const;
	int GetHiddenCount() const;
	int GetNumberOfInputs()const;

	float GetAccuracy() const;

	void GoLive();

	~Network();
private:
	int LEARNING_RATE;
	int HIDDEN_COUNT;
	int NUMBER_OF_INPUTS;
	float tries;
	float successes;
	vector<Neuron> HNeurons;
	OutputNeuron ONeuron;
	vector<string> prompts;

};
#endif
