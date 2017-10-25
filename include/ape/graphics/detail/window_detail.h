#ifndef WINDOW_DETAIL_H
#define WINDOW_DETAIL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ape/core/vec2.h>

namespace ape {
    namespace window {
        namespace detail {
            extern GLFWwindow* window; // The actual window instance
            extern Vec2i dimensions; // Window dimensions
        }
    }
}

#endif // WINDOW_DETAIL_H
