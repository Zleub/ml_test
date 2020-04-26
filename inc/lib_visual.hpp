#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <lib.hpp>

GLFWwindow* init_glfw();
std::vector<float> get_circle_vertices(float x, float y, float r);
int vertex_shader(std::string filename);
int fragment_shader(std::string filename);
int gen_shader_program(int vertex_shader, int fragment_shader);
int vector_to_vbo(std::vector<float> vertices);
int vbo_to_vao(int VBO, std::vector<float> vertices);
