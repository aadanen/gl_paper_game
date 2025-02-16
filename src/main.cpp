// actually i shouldn't start this while im doing research with olivier
// this will be my next project though
// a simple game
// using opengl
// from scratch in C++
//
// Knowledge I've Gained:
// how to write multi-file C/C++ programs
// how openGL works (need practice)
// improved at programming
// data structures and algorithms (lets make this game efficient)
// gdb
// makefiles
// work on 'creativity'
// * aesprite?
// * blender?

// Goals
// it would be awesome to do sound from scratch as well
// maybe get rivdog to cook up some songs
// can i merge my passions for video games and jazz?

// openGL is a specification, and the functions are actually implemented by
// the GPU driver. At runtime, I need to basically ask my gpu driver to give
// me function pointers to the OpenGL functions. Glad handles this task
#include <glad/glad.h>

// opening a window is OS specific and complicated. GLFW handles that
#include <GLFW/glfw3.h>

// open source library for reading images (textures)
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

// gl math library (I will not be able to implement these things faster)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <camera.h>

#include <stdio.h>
#include <stdlib.h>

unsigned int SCR_WIDTH = 960;
unsigned int SCR_HEIGHT = 540;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float* normalizeRGBA(unsigned char r, unsigned char g, unsigned char b, 
        unsigned char a);
int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
            "o.o", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    /////////////////////////////////////////////////////////////////////
    float rect_verticies[] = {
        -0.5f, -0.809f, 0.0f,
        0.5f, -0.809f, 0.0f,
        0.5f, 0.809f, 0.0f,
        -0.5f, 0.809f, 0.0f,
    };
    unsigned int rect_indicies[] = {
        0, 1, 3,
        1, 2, 3,
    };


    unsigned int playerVAO;
    glGenVertexArrays(1, &playerVAO);
    glBindVertexArray(playerVAO);

    unsigned int playerVBO;
    glGenBuffers(1, &playerVBO);
    glBindBuffer(GL_ARRAY_BUFFER, playerVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_verticies), 
            rect_verticies, GL_STATIC_DRAW);
    
    unsigned int playerEBO;
    glGenBuffers(1, &playerEBO);
    glBindBuffer(GL_ARRAY_BUFFER, playerEBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_indicies),
            rect_indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
            3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    // since im only allocating these colors once, its no problem to do this
    // as two malloc() calls. If i am ever doing a bunch of colors though
    // it would be better to get one big chunk of memory and then have new 
    // color just be a four byte offset into the chunk
    float* color_paper = normalizeRGBA(241, 240, 235, 255);
    float* color_ink = normalizeRGBA(46, 33, 27, 255);
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        //241, 240, 235
        glClearColor(color_paper[0], color_paper[1], 
                color_paper[2], color_paper[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


        //glUseProgram(shaderProgram);
        glBindVertexArray(playerVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);



        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
float* 
normalizeRGBA(unsigned char r, unsigned char g, unsigned char b, 
        unsigned char a) {
    float* result = (float*)malloc(4*sizeof(unsigned char));
    result[0] = r/255.0;
    result[1] = g/255.0;
    result[2] = b/255.0;
    result[3] = a/255.0;
    return result;
}
