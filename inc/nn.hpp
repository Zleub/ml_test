#include <lib.hpp>
#include <ne.hpp>

class nn {
public:
	typedef ne<double, double> inputType;
	typedef ne<std::tuple<std::vector<double>, std::vector<double>>, double> layerType;

	typedef double(*hypothesisType)(nn, double);

	nn();
	~nn();

	void					setInputLayer(std::vector<inputType> l);
	void					setOutputLayer(std::vector<layerType> l);
	void					setHypothesis(hypothesisType f);

	std::vector<inputType>	getInputLayer(void);
	std::vector<layerType>	getOutputLayer(void);

	std::vector<double>		forward(double i);
	double					backward(double x, double y);

private:
	std::vector<inputType>	inputLayer;
	std::vector<layerType>	outputLayer;
	hypothesisType			hypothesis;
};