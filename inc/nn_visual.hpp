#include <nn.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class nn_visual : public nn {
private:
    GLFWwindow*         window;
    std::vector<float>  v_vertices;

public:
    nn_visual ();
    ~nn_visual ();
};
