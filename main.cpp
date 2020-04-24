#include <lib.hpp>
#include <ne.hpp>

#include <GLFW/glfw3.h>

class nn {
public:
  typedef ne<double, double> inputType;
  typedef ne<std::tuple<std::vector<double>, std::vector<double>>, double> layerType;

  typedef double (*hypothesisType)(nn, double);

  nn() {};
  ~nn() {};

  hypothesisType hypothesis;

  void setInputLayer(std::vector<inputType> l) {
    this->inputLayer = l;
    for(inputType &ne : this->inputLayer)
      ne.weights.push_back( ((double) rand() / (RAND_MAX)) );
  }

  std::vector<inputType> getInputLayer(void) {
    return this->inputLayer;
  }

  void setOutputLayer(std::vector<layerType> l) {
    this->outputLayer = l;
    for(layerType &ne : this->outputLayer)
      for (size_t i = 0; i < this->inputLayer.size(); i++) {
        ne.weights.push_back( ((double) rand() / (RAND_MAX)) );
        // ne.weights.push_back( 0.5 );
      }
      // ne.weights.resize( this->inputLayer.size() );
  }

  std::vector<layerType> getOutputLayer(void) {
    return this->outputLayer;
  }

  void setHypothesis(hypothesisType f) {
    this->hypothesis = f;
  }

  std::vector<double> forward( double i ) {
    std::vector<double> _res;
    for( inputType in : this->inputLayer ) {
      _res.push_back( in.f(i) );
    }

    std::vector<double> res;
    for ( layerType out : this->outputLayer) {
      res.push_back( out.f( std::make_tuple(out.weights, _res) ) );
    }

    // for (double r : res)
    //   std::cout << r << std::endl;

    return res;
  }

  double backward( double x, double y ) {
    double alpha = -0.01;
    std::vector<double> r = forward(x);

    for (size_t i = 0; i < r.size(); i++) {
      double min = this->hypothesis(*this, x) - y;
      // double error = 1. / 2. * pow(min, 2);
      layerType &out = this->outputLayer[i];

      for (size_t j = 0; j < out.weights.size(); j++) {
        inputType &in = this->inputLayer[j];
        in.weights[0] += alpha * min;

        double &w = out.weights[j];
        // w += alpha * error;
        w += alpha * min * x;
      }
    }
    return 0;
  }

private:
  std::vector<inputType> inputLayer;
  std::vector<layerType> outputLayer;

};

double hypothesis(nn net, double i) {
  return net.getInputLayer()[0].weights[0] + i * net.getOutputLayer()[0].weights[0];
}

std::tuple<double, double> test_load(std::string line) {
  std::vector<std::string> s = split(line, ',');
  return std::make_tuple( std::stoi(s[0]), std::stoi(s[1]) );
}

int main() {
  std::vector<std::tuple<double, double>> v = load("data.csv", test_load);

  //
  // std::ifstream afile("data.csv", std::ios::in);
  // if (afile.is_open()) {
  //   std::string line;
  //   while (std::getline(afile, line)) {
  //     std::vector<std::string> s = split(line, ',');
  //     try {
  //       double x = std::stoi(s[0]);
  //       double y = std::stoi(s[1]);
  //       v.push_back( std::make_tuple(x, y) );
  //     } catch (std::exception e) {
  //       std::cerr << e.what() << std::endl;
  //     }
  //   }
  //   afile.close();
  // }
  // else {
  //   std::cerr << "Unable to open file" << std::endl;
  // }

  // for(std::tuple<double, double> t : v)
  //   std::cout << std::get<0>(t) << " | " << std::get<1>(t) << std::endl;

  // nn net;
  // net.setInputLayer( std::vector<nn::inputType>(1, identity) );
  // net.setOutputLayer( std::vector<nn::layerType>(1, dot) );
  //
  // net.setHypothesis( hypothesis );
  //
  // size_t iter = 1000;
  // for (size_t i = 0; i < iter; i++) {
  //   for(std::tuple<double, double> t : v)
  //     net.backward(std::get<0>(t) / 300000., std::get<1>(t) / 10000.);
  //
  //   net.backward(240000. / 300000., 3650. / 10000.);
  //   if (i % (iter / 10) == 0)
  //     std::cout << "." << std::flush;
  // }
  // std::cout << std::endl;
  //
  // std::fstream file;
  // file.open ("input.csv", std::ios::out );
  // for(std::tuple<double, double> t : v)
  //   file << std::get<0>(t) / 300000. << "," << std::get<1>(t) / 10000. << std::endl;
  // file.close();
  //
  // file.open ("test.csv", std::ios::out );
  // for (double i = 0; i < 1; i += 0.1) {
  //   file << i << "," << hypothesis(net, i) << std::endl;
  //   // file << i << "," << net.forward(i)[0] << std::endl;
  // }
  // file.close();

  GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

  return 0;
}
