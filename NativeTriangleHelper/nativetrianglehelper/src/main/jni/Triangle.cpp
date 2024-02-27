#include <GLES3/gl3.h>
#include <jni.h>
#include <cmath>

extern "C" JNIEXPORT void JNICALL
Java_com_example_nativetrianglehelper_NativeTriangleHelper_drawTriangle(JNIEnv *env, jobject thiz, jfloat rotationAngle) {
    // Define the vertices of the triangle
    const float sideLength = 1.0f; // Length of each side of the triangle

    GLfloat vertices[] = {
            -0.5f * sideLength, -0.5f * sideLength, 0.0f,  // Bottom-left vertex
            0.5f * sideLength, -0.5f * sideLength, 0.0f,   // Bottom-right vertex
            0.0f, 0.5f * sideLength, 0.0f   // Top vertex
    };

    // Create and bind a vertex buffer object (VBO)
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile vertex shader
    const char* vertexShaderSource = "#version 300 es\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "uniform mat4 rotationMatrix;\n" // Uniform for rotation matrix
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = rotationMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile fragment shader
    const char* fragmentShaderSource = "#version 300 es\n"
                                       "precision mediump float;\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(186.0f/255.0f, 36.0f/255.0f, 37.0f/255.0f, 1.0f);\n" // Set color to rgba(186, 36, 37, 255)
                                       "}\0";
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create and link shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Calculate rotation matrix
    float radians = rotationAngle * M_PI / 180.0f;
    float cosR = cos(radians);
    float sinR = sin(radians);
    GLfloat rotationMatrix[] = {
            cosR, -sinR, 0.0f, 0.0f,
            sinR, cosR, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };

    // Get the location of the rotationMatrix uniform and set its value
    GLuint rotationMatrixLocation = glGetUniformLocation(shaderProgram, "rotationMatrix");
    glUniformMatrix4fv(rotationMatrixLocation, 1, GL_FALSE, rotationMatrix);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}