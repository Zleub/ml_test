#include <lib.hpp>
#include <ne.hpp>
#include <nn.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <lib_visual.hpp>

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


  GLFWwindow* window = init_glfw();
  std::vector<float> circle = get_circle_vertices(0, 0, 0.2);
  std::vector<float> circle2 = get_circle_vertices(0.2, 0.2, 0.2);

  for (float i : circle2) {
	  circle.push_back(i);
  }

  int VBO = vector_to_vbo(circle);
  int VAO = vbo_to_vao(VBO, circle);

  std::cout << circle.size() << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		//glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 0, circle.size() / 3);

		/* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

  return 0;
}
