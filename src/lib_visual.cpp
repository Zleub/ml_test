#include <lib_visual.hpp>

GLFWwindow* init_glfw() {
	GLFWwindow *window;

	if (!glfwInit())
		throw new std::exception();

	window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw new std::exception();
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		throw new std::exception();
	}

	return window;
}

std::vector<float> get_circle_vertices(float x, float y, float r) {
	int nb_point = 8;
	float slice = (M_PI * 2) / nb_point;
	std::vector<float> vertices;

	for (float i = 0; i < nb_point; i += 1) {
		vertices.push_back(x + (r * cos(i * slice)));
		vertices.push_back(y + (r * sin(i * slice)));
		vertices.push_back(0.);
	}

	return vertices;
}

int vertex_shader(std::string filename) {
	std::string vertexShaderSource;
	std::vector<std::string> vertexFile = load<std::string>(filename, identity);
	for (std::string s : vertexFile)
		vertexShaderSource += s;

	const char *vertexSource = vertexShaderSource.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	return vertexShader;
}

int fragment_shader(std::string filename) {
	std::string fragmentShaderSource;
	std::vector<std::string> fragmentFile = load<std::string>(filename, identity);
	for (std::string s : fragmentFile)
		fragmentShaderSource += s;

	const char *fragmentSource = fragmentShaderSource.c_str();

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	return fragmentShader;
}

int gen_shader_program(int vertex_shader, int fragment_shader) {
	unsigned int shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);

	return shader_program;
}

int vector_to_vbo(std::vector<float> vertices) {
	unsigned int VBO;
	float * array = vertices.data();

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), array, GL_STATIC_DRAW);

	return VBO;
}

int vbo_to_vao(int VBO, std::vector<float> vertices) {
	unsigned int VAO;
	float * array = vertices.data();

	glGenVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), array, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(0);

	return VAO;
}