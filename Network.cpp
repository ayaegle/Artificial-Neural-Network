#include "Network.h"



Network::Network(int hiddenCount, int learningRate,int numberOfInputs) : ONeuron(hiddenCount) , tries(0.0f), successes(0.0f)
{
	LEARNING_RATE = learningRate;
	HIDDEN_COUNT = hiddenCount;
	NUMBER_OF_INPUTS = numberOfInputs;

	for (int i = 0; i < HIDDEN_COUNT; i++)
	{
		Neuron hiddenNeuron = Neuron(NUMBER_OF_INPUTS - 1);
		HNeurons.push_back(hiddenNeuron);
	}
}

int Network::GetLearningRate() const
{
	return LEARNING_RATE;
}

int Network::GetHiddenCount() const
{
	return HIDDEN_COUNT;
}

int Network::GetNumberOfInputs() const
{
	return NUMBER_OF_INPUTS;
}

float Network::GetAccuracy() const
{
	return (successes / tries) * 100;
}

void Network::GoLive() 
{
	vector<float> inputs;
	vector<float> hiddenNeuronsOutput;
	cout << "Make a predicition? (y/n)" << endl;
	char choice;
	cin >> choice;
	while (choice == 'y')
	{ 
	inputs.clear();
	hiddenNeuronsOutput.clear();

	for (int i = 0; i < NUMBER_OF_INPUTS-1; i++)
	{
		float x;
		cout << prompts.at(i) << ": ";
		cin >> x;
		cout << endl;
		inputs.push_back(x);
	}

	for (int j = 0; j < HIDDEN_COUNT; j++)
	{
		//Calculate result activation (summation then sigmoid)
		float hiddenOutput = HNeurons.at(j).Activation(inputs);
		hiddenNeuronsOutput.push_back(hiddenOutput);
	}
	//Calculate result activation (summation then sigmoid)
	//determine prediction
	float prediction = ONeuron.Activation(hiddenNeuronsOutput);
	cout << prediction << endl;
	string outcome;
	outcome = prediction == 1 ? prompts.at(prompts.size() - 2) : prompts.at(prompts.size()-1);
	cout << "Prediction Result: " << outcome << endl<< endl;
	cout << "Make a predicition? (y/n)" << endl;
	cin >> choice;
	}
}

void Network::ReadInPrompts(string filename)
{
	//open inputFile and outputFile
	ifstream inputFile;
	inputFile.open(filename.c_str());

	string inputString;


	//skip number of inputs line
	//getline(inputFile, inputString, '\n');
	inputFile.ignore(256,'\n');

	//skip the initial data in the file
	for (int i = 0; i < NUMBER_OF_INPUTS + 1; i++)
	{
		getline(inputFile, inputString, '\n');
		prompts.push_back(inputString);
	}

}

void Network::Train(int trainingSessions, vector<Entry> data)
{
	Entry entry;
	Entry hiddenNeuronsOutPut;
	//for each cycle (number of training sessions)
	for (int i = 0; i < trainingSessions; i++)
	{
		
		//for all the entries in data
		for (int k = 0; k < data.size(); k++)
		{
			
			tries++;
			entry = data.at(k);
			float target = *(entry.end()-1);
			entry.erase(entry.end()-1);

			//for each hiddenNeuron
			for (int j = 0; j < HIDDEN_COUNT; j++)
			{
				//Calculate result activation (summation then sigmoid)
				float hiddenOutput = HNeurons.at(j).Activation(entry);
				hiddenNeuronsOutPut.push_back(hiddenOutput);
			}
			
			//Calculate result activation (summation then sigmoid)
			//determine prediction
			float prediction = ONeuron.Activation(hiddenNeuronsOutPut);
			//cout <<  "target:  " << target << "   prediction:  " << prediction << endl;
			//back propogate
			if (prediction != target)
			{
				//Calculate Error
				ONeuron.CalculateError(target);
				float OError = ONeuron.GetError();



				//Calculate Error
				for (int i = 0; i < HIDDEN_COUNT; i++)
				{
					float OWeight = ONeuron.GetWeight(i);
					HNeurons.at(i).CalculateError(OError,OWeight);
					HNeurons.at(i).UpdateWeights(entry,LEARNING_RATE);
					ONeuron.UpdateWeights(LEARNING_RATE,HNeurons.at(i).Sigmoid());
				}
				
			}
			else {
				successes++;
			}
			hiddenNeuronsOutPut.clear();
			
		} //end for all data
	}
}

Network::~Network()
{
}
