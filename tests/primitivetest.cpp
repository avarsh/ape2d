#include <iostream>
#include <ape/graphics/graphics.h>

int main() {
   
    ape::Graphics graphics;
    graphics.createWindow(800, 600, "Primitive test");

    ape::Shader polygonShader;
    polygonShader.loadShaders("./data/shaders/polygon.vert", "./data/shaders/polygon.frag");

    GLfloat vertices[] = {
        // The triangle
        0.1f, -0.5f,    1.0f, 0.0f, 0.0f,
        -0.8f, -0.5f,   0.0f, 1.0f, 0.0f,
        -0.3f, 0.0f,    0.0f, 0.0f, 1.0f,
        // The square
        0.3f, 0.3f,     0.1f, 0.1f, 0.6f,
        0.6f, 0.3f,     0.2f, 0.0f, 0.3f,
        0.6f, 0.6f,     0.0f, 1.0f, 0.5f,
        0.3f, 0.6f,     0.0f, 0.0f, 1.0f
    };

    GLushort indices[] = {
        0, 1, 2, // Triangle 
        3, 4, 5,
        3, 5, 6 // Square
    };

    int size = sizeof(indices) / sizeof(GLushort);

    GLuint vbo, vao, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
   
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while(graphics.windowIsOpen()) {
        glfwPollEvents();

        graphics.clearWindow(0.3, 0.3, 0.4);
        polygonShader.useProgram();
        glBindVertexArray(vao);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, (GLvoid*)0);
        glBindVertexArray(0);
        graphics.displayWindow();
    }
    
    return 0;
}
