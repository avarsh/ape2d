#include <ape/graphics/graphics.h>

namespace ape {
    Graphics::Graphics(World& world) :
        mWorld(world) {
        // Initialise glfw
        if(!glfwInit()) {
            std::cout << "GLFW failed to initalise.\n";
        }

        glfwSetErrorCallback(_errorCallback);
    }

    Graphics::~Graphics() {
        mPolygonBuffer.deleteBuffers();

        glfwDestroyWindow(mWindow);
        glfwTerminate();
    }

    void Graphics::createWindow(unsigned int width, unsigned int height, const std::string& title) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(mWindow);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(0);

        int w, h;
        glfwGetFramebufferSize(mWindow, &w, &h);
        glViewport(0, 0, w, h);

        // Load polygon vertex and fragment shaders
        mPolygonShader.loadShaders("./data/shaders/polygon.vert", "./data/shaders/polygon.frag");

        glGenVertexArrays(1, &mPolygonVertexArray);
        mPolygonBuffer.initBuffers(mPolygonVertexArray);
    }

    void Graphics::clearWindow(float red, float green, float blue, float alpha) {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Graphics::displayWindow(World& world) {

        mPolygonShader.useProgram();

        // Draw polygons
        mPolygonBuffer.updateBuffer(world);

        glBindVertexArray(mPolygonVertexArray);
        glDrawElements(GL_TRIANGLES, mPolygonBuffer.mElementCount, GL_UNSIGNED_SHORT, (GLvoid*)0);
        glBindVertexArray(0);

        // Unbind buffer objects
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // Swap buffers
        glfwSwapBuffers(mWindow);
    }

    bool Graphics::windowIsOpen() {
        return !glfwWindowShouldClose(mWindow);
    }

    void Graphics::addVertex(entity_t entity, GLfloat x, GLfloat y, GLfloat red, GLfloat green, GLfloat blue) {
        auto& mesh = mWorld.getComponent<Mesh>(entity);

        if(mesh.mBufferIndex == -1) {
            mesh.mBufferIndex = 0; // TODO: change this later
        }

        mesh.mVertices.push_back(x);
        mesh.mVertices.push_back(y);
        mesh.mVertices.push_back(red);
        mesh.mVertices.push_back(green);
        mesh.mVertices.push_back(blue);

        mesh.mVertexCount++;
        mPolygonBuffer.mVertexCount++;

        // Append to indices, but only if we have enough vertices to
        // form a triangle or above
        if(mesh.mVertexCount >= 3) {
            mesh.mIndices.push_back(0);
            mesh.mIndices.push_back(mesh.mVertexCount - 2);
            mesh.mIndices.push_back(mesh.mVertexCount - 1);

            mesh.mIndexCount += 3;
            mPolygonBuffer.mElementCount += 3;
        }
    }

    void Graphics::setVertexColour(entity_t entity, int vertex, GLfloat red, GLfloat blue, GLfloat green) {
        auto& mesh = mWorld.getComponent<Mesh>(entity);

        mesh.mVertices[(vertex * mesh.mDataSize) + 2] = red;
        mesh.mVertices[(vertex * mesh.mDataSize) + 3] = blue;
        mesh.mVertices[(vertex * mesh.mDataSize) + 4] = green;
    }

    void Graphics::setVertexPosition(entity_t entity, int vertex, GLfloat x, GLfloat y) {
        auto& mesh = mWorld.getComponent<Mesh>(entity);

        mesh.mVertices[(vertex * mesh.mDataSize)] = x;
        mesh.mVertices[(vertex * mesh.mDataSize) + 1] = y;
    }
}
