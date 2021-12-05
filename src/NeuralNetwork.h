#pragma once

#include "ofMain.h"
#include <Eigen/Eigen>
#include <vector>

#define DEFAULT_LEARNING_RATE 0.005

typedef float Scalar;
typedef Eigen::MatrixXf Matrix;
typedef Eigen::RowVectorXf RowVector;
typedef Eigen::VectorXf ColVector;

void genData(std::string filename);									// Generate dummy data
void ReadCSV(std::string filename, std::vector<RowVector*>& data);	// Extract data from csv file
Scalar activationFunction(Scalar x);
Scalar activationFunctionDerivative(Scalar x);

class NeuralNetwork
{
	public:
		NeuralNetwork();
		NeuralNetwork(std::vector<uint> topology, Scalar learningRate = Scalar(DEFAULT_LEARNING_RATE));
		~NeuralNetwork();
		void propagateForward(RowVector& input);	// Performs forward propagation of data
		void propagateBackward(RowVector& output);	// Performs backward propagation of errors
		void calcErrors(RowVector& output);			// Calculates errors made by neurons
		void updateWeights();						// Updates weights of connections
		void train(std::vector<RowVector*> input_data, std::vector<RowVector*> output_data);	// Trains neural network given an array of data points

		// void setup(std::vector<uint> topology, Scalar learningRate = Scalar(DEFAULT_LEARNING_RATE));
		// void update();
		void draw();

	private:
		std::vector<uint> topology;					// Stores the layer sizes of the neural network
		std::vector<RowVector*> neuronLayers; 		// Stores the different layers of the network
		std::vector<RowVector*> cacheLayers; 		// Stores the weighted sum values of each layer pre-activation function
		std::vector<RowVector*> deltas; 			// Stores the error contribution of each neuron
		std::vector<Matrix*> weights; 				// Stores the connection weights
		Scalar learningRate;						// Stores the learning rate of the network
		
		// float xPosStart;
		// float yPosStart;
		// float xPosEnd;
		// float yPosEnd;
		// uint8_t colour;
};
