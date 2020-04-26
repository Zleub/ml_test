#include <nn.hpp>

nn::nn() {};
nn::~nn() {};

void nn::setInputLayer(std::vector<inputType> l) {
	this->inputLayer = l;
	for (inputType &ne : this->inputLayer)
		ne.weights.push_back(((double)rand() / (RAND_MAX)));
}

std::vector<nn::inputType> nn::getInputLayer(void) {
	return this->inputLayer;
}

void nn::setOutputLayer(std::vector<layerType> l) {
	this->outputLayer = l;
	for (layerType &ne : this->outputLayer)
		for (size_t i = 0; i < this->inputLayer.size(); i++) {
			ne.weights.push_back(((double)rand() / (RAND_MAX)));
			// ne.weights.push_back( 0.5 );
		}
	// ne.weights.resize( this->inputLayer.size() );
}

std::vector<nn::layerType> nn::getOutputLayer(void) {
	return this->outputLayer;
}

void nn::setHypothesis(hypothesisType f) {
	this->hypothesis = f;
}

std::vector<double> nn::forward(double i) {
	std::vector<double> _res;
	for (inputType in : this->inputLayer) {
		_res.push_back(in.f(i));
	}

	std::vector<double> res;
	for (layerType out : this->outputLayer) {
		res.push_back(out.f(std::make_tuple(out.weights, _res)));
	}

	// for (double r : res)
	//   std::cout << r << std::endl;

	return res;
}

double nn::backward(double x, double y) {
	double alpha = -0.01;
	std::vector<double> r = this->forward(x);

	for (size_t i = 0; i < r.size(); i++) {
		double min = this->hypothesis(*this, x) - y;
		// double error = 1. / 2. * pow(min, 2);
		layerType &out = this->outputLayer[i];

		for (size_t j = 0; j < out.weights.size(); j++) {
			inputType &in = this->inputLayer[j];
			in.weights[0] += alpha * min;

			// w += alpha * error;
			out.weights[j] += alpha * min * x;
		}
	}
	return 0;
}
