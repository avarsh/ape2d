#include <ape/graphics/graphics.h>

namespace ape {
    Graphics::Graphics(World& world) :
        world(world) {
        // Initialise glfw
        if(!glfwInit()) {
            std::cout << "GLFW failed to initalise.\n";
        }

        glfwSetErrorCallback(_errorCallback);
    }

    Graphics::~Graphics() {
        polygonBuffer.deleteBuffers();

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Graphics::createWindow(unsigned int width, unsigned int height, const std::string& title) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(0);

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);

        // Load polygon vertex and fragment shaders
        polygonShader.loadShaders("./data/shaders/polygon.vert", "./data/shaders/polygon.frag");

        glGenVertexArrays(1, &polygonVertexArray);

        glBindVertexArray(polygonVertexArray);

        polygonBuffer.initBuffers();

        // The position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // The colour attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        // Unbind everything
        glBindVertexArray(0);

        // Unbind these after unbinding vertex array
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Graphics::clearWindow(float red, float green, float blue, float alpha) {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Graphics::displayWindow() {

        polygonShader.useProgram();

        // Draw polygons
        if(polygonBuffer.vertexCount > 0 && polygonBuffer.elementCount > 0) {
            polygonBuffer.updateBuffer(world);

            glBindVertexArray(polygonVertexArray);
            glDrawElements(GL_TRIANGLES, polygonBuffer.elementCount, GL_UNSIGNED_SHORT, (GLvoid*)0);

            // Unbind everything
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        // Swap buffers
        glfwSwapBuffers(window);
    }

    bool Graphics::windowIsOpen() {
        return !glfwWindowShouldClose(window);
    }

    void Graphics::addVertex(entity_t entity, GLfloat x, GLfloat y, GLfloat red, GLfloat green, GLfloat blue) {
        auto& mesh = world.getComponent<Mesh>(entity);

        if(mesh.bufferIndex == -1) {
            mesh.bufferIndex = 0; // TODO: change this later
        }

        mesh.vertices.push_back(Vertex(x, y, red, green, blue));
        polygonBuffer.vertexCount++;

        // Append to indices, but only if we have enough vertices to
        // form a triangle or above
        if(mesh.vertices.size() >= 3) {
            mesh.indices.push_back(0);
            mesh.indices.push_back(mesh.vertices.size() - 2);
            mesh.indices.push_back(mesh.vertices.size() - 1);

            polygonBuffer.elementCount += 3;
        }
    }

    void Graphics::setVertexColour(entity_t entity, int vertex, GLfloat red, GLfloat blue, GLfloat green) {
        auto& mesh = world.getComponent<Mesh>(entity);

        assert(vertex < mesh.vertices.size());

        mesh.vertices[vertex].colors.red = red;
        mesh.vertices[vertex].colors.blue = blue;
        mesh.vertices[vertex].colors.green = green;
    }

    void Graphics::setVertexPosition(entity_t entity, int vertex, GLfloat x, GLfloat y) {
        auto& mesh = world.getComponent<Mesh>(entity);
        mesh.vertices[vertex].position.x = x;
        mesh.vertices[vertex].position.y = y;
    }

    void Graphics::move(entity_t entity, ape::Vec2<GLfloat> displacement) {
        auto& mesh = world.getComponent<Mesh>(entity);

        for(auto& vertex : mesh.vertices) {
            vertex.position += displacement;
        }
    }

    GLFWwindow* Graphics::getWindow() {
        return window;
    }
}
