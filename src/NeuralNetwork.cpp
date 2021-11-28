/* This code has been developed with help from the following resources:
 * https://www.geeksforgeeks.org/ml-neural-network-implementation-in-c-from-scratch/
 * https://www.kdnuggets.com/2018/10/simple-neural-network-python.html
 * https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6 
 */

#include "NeuralNetwork.h"

//--------------------------------------------------------------
void genData(std::string filename)
{
    std::ofstream file1(filename + "-in");
    std::ofstream file2(filename + "-out");

    for(uint r = 0; r < 1000; r++)
    {
        Scalar x = rand() / Scalar(RAND_MAX);
        Scalar y = rand() / Scalar(RAND_MAX);
        file1 << x << ", " << y << std::endl;
        file2 << 2 * x + 10 + y << std::endl;
    }
    
    file1.close();
    file2.close();
}

//--------------------------------------------------------------
void ReadCSV(std::string filename, std::vector<RowVector*>& data)
{
    data.clear();

    std::ifstream file(filename);
    std::string line, word;

    // Determine number of columns in file
    std::getline(file, line, '\n');

    std::stringstream ss(line);
    std::vector<Scalar> parsed_vec;

    while(std::getline(ss, word, ', '))
    {
        parsed_vec.push_back(Scalar(std::stof(&word[0])));
    }

    uint cols = parsed_vec.size();
    data.push_back(new RowVector(cols));

    for(uint i = 0; i < cols; i++)
    {
        data.back()->coeffRef(1, i) = parsed_vec[i];
    }
 
    // read the file
    if(file.is_open())
    {
        while(std::getline(file, line, '\n'))
        {
            std::stringstream ss(line);

            data.push_back(new RowVector(1, cols));

            uint i = 0;
            while(std::getline(ss, word, ', '))
            {
                data.back()->coeffRef(i) = Scalar(std::stof(&word[0]));
                i++;
            }
        }
    }
}

//--------------------------------------------------------------
Scalar activationFunction(Scalar x)
{
    // Modify to specify your activation function of choice
    return tanhf(x);
}

//--------------------------------------------------------------
Scalar activationFunctionDerivative(Scalar x)
{
    // Modify to specify the derivative of your chosen activation function
    return 1 - tanhf(x) * tanhf(x);
}

//--------------------------------------------------------------
NeuralNetwork::NeuralNetwork(std::vector<uint> topology, Scalar learningRate)
{    
    this->topology = topology;
    this->learningRate = learningRate;

    // Initialise vecctors for each layer
    for(uint i = 0; i < topology.size(); i++)
    {    
        // Initialise neuron vector
        if(i == topology.size() - 1)
        {
            // Last layer does not include a bias neuron
            neuronLayers.push_back(new RowVector(topology[i]));
        }
        else
        {
            // All other layers require a bias neuron
            neuronLayers.push_back(new RowVector(topology[i] + 1));
        }
 
        // Initialise cache vector
        cacheLayers.push_back(new RowVector(neuronLayers.size()));

        // Initialise delta vector
        deltas.push_back(new RowVector(neuronLayers.size()));

        // Set value of bias neuron
        if(i != topology.size() - 1)
        {
            neuronLayers.back()->coeffRef(topology[i]) = 1.0;
            cacheLayers.back()->coeffRef(topology[i]) = 1.0;
        }
 
        // Initialise weights matrix
        if(i > 0)
        {
            if(i != topology.size() - 1)
            {
                // Row dimension of matrix is equal to size of previous layer (incl. bias neuron)
                // Column dimension of matrix is equal to size of current layer (incl. bias neuron)
                weights.push_back(new Matrix(topology[i - 1] + 1, topology[i] + 1));

                // Set weights to be random values
                weights.back()->setRandom();

                // Set final column of weights matrix to appropriate values such that bias neuron will not be altered during matrix multiplication
                // All elements of final column, bar last one, are set to 0
                // Last element of final column is set to 1
                weights.back()->col(topology[i]).setZero();
                weights.back()->coeffRef(topology[i - 1], topology[i]) = 1.0;
            }
            else
            {
                // Column dimension of final layer weights matrix does not include a bias neuron
                weights.push_back(new Matrix(topology[i - 1] + 1, topology[i]));
                
                // Set weights to be random values
                weights.back()->setRandom();
            }
        }
    }
}

//--------------------------------------------------------------
NeuralNetwork::~NeuralNetwork()
{

}

//--------------------------------------------------------------
void NeuralNetwork::propagateForward(RowVector& input)
{
    // Initialise input layer values to be equal to the input data (excl. the bias neuron)
    // Block returns part (a 'block') of a given vector or matrix 
    // The block returned is specified by the function arguments (startRow, startCol, blockRows, blockCols)
    neuronLayers.front()->block(0, 0, 1, neuronLayers.front()->size() - 1) = input;
 
    // Propagate the data forward
    for(uint i = 1; i < topology.size(); i++)
    {
        // Perform dot product of neuron layers with weights matrix
        (*neuronLayers[i]) = (*neuronLayers[i - 1]) * (*weights[i - 1]);
    }
 
    // Apply activation function to all neurons within each layer (excl. bias neuron)
    // Note: unaryExpr applies the given function to all elements of the vector
    for(uint i = 1; i < topology.size() - 1; i++)
    {
        neuronLayers[i]->block(0, 0, 1, topology[i]).unaryExpr(std::ptr_fun(activationFunction));
    }
}

//--------------------------------------------------------------
void NeuralNetwork::calcErrors(RowVector& output)
{
    // Calculate the errors made by neurons of last layer
    (*deltas.back()) = output - (*neuronLayers.back());
 
    // Calculate the errors made by neurons of hidden layers (working back from last layer to first layer)
    for(uint i = topology.size() - 2; i > 0; i--)
    {
        (*deltas[i]) = (*deltas[i + 1]) * (weights[i]->transpose());
    }
}

//--------------------------------------------------------------
void NeuralNetwork::updateWeights()
{
    for(uint i = 0; i < topology.size() - 1; i++)
    {
        // Iterate over the different layers (from first hidden to output layer)
        // For output layer, there is no bias neuron, therefor number of neurons specified = number of cols
        // For all other layers, there is a bias neuron, therefor number of neurons specified = number of cols -1
        if (i != topology.size() - 2)
        {
            for(uint c = 0; c < weights[i]->cols() - 1; c++)
            {
                for(uint r = 0; r < weights[i]->rows(); r++)
                {
                    weights[i]->coeffRef(r, c) += learningRate * deltas[i + 1]->coeffRef(c) * activationFunctionDerivative(cacheLayers[i + 1]->coeffRef(c)) * neuronLayers[i]->coeffRef(r);
                }
            }
        }
        else
        {
            for(uint c = 0; c < weights[i]->cols(); c++)
            {
                for(uint r = 0; r < weights[i]->rows(); r++)
                {
                    weights[i]->coeffRef(r, c) += learningRate * deltas[i + 1]->coeffRef(c) * activationFunctionDerivative(cacheLayers[i + 1]->coeffRef(c)) * neuronLayers[i]->coeffRef(r);
                }
            }
        }
    }
}

//--------------------------------------------------------------
void NeuralNetwork::propagateBackward(RowVector& output)
{
    calcErrors(output);
    updateWeights();
}

//--------------------------------------------------------------
void NeuralNetwork::train(std::vector<RowVector*> input_data, std::vector<RowVector*> output_data)
{
    for(uint i = 0; i < input_data.size(); i++)
    {
        std::cout << "Input to neural network is : " << *input_data[i] << std::endl;

        propagateForward(*input_data[i]);

        std::cout << "Expected output is : " << *output_data[i] << std::endl;
        std::cout << "Output produced is : " << *neuronLayers.back() << std::endl;

        propagateBackward(*output_data[i]);

        std::cout << "Mean Squared Error : " << std::sqrt((*deltas.back()).dot((*deltas.back())) / deltas.back()->size()) << std::endl;
    }
}

// //--------------------------------------------------------------
// void NeuralNetwork::setup(){

// }

// //--------------------------------------------------------------
// void NeuralNetwork::update(){

// }

// //--------------------------------------------------------------
// void NeuralNetwork::draw(){

// }
