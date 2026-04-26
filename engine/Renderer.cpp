#include "Engine.h"

namespace Renderer
{

GLuint compileShader(GLenum type_, const char *shaderPath_)
{
    GLuint shader = glCreateShader(type_);
    glShaderSource(shader, 1, &shaderPath_, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        Log::error("Shader compilation failed: %s\n", infoLog);
    }
    return shader;
}

Renderer::Renderer(const std::string vertShaderPath_, const std::string fragShaderPath_)
{

    if (!vertShaderPath_.empty())
    {
        std::string vertShaderStr = Util::fileRead(vertShaderPath_);
        vertexShader = compileShader(GL_VERTEX_SHADER, vertShaderStr.c_str());
    }
    if (!fragShaderPath_.empty())
    {
        std::string fragShaderStr = Util::fileRead(fragShaderPath_);
        fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragShaderStr.c_str());
    }
    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glBindAttribLocation(program, 0, "aPos");

    glLinkProgram(program);
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        Log::error("Program linking failed: %s\n", infoLog);
    }

    glGenBuffers(NUM_VBO, vbo);

    Log::debug("Renderer created.\n");
}

Renderer::~Renderer()
{
    if (vbo[0] != 0)
    {
        glDeleteBuffers(1, vbo);
    }
    if (vertexShader != 0)
    {
        glDeleteShader(vertexShader);
    }
    if (fragmentShader != 0)
    {
        glDeleteShader(fragmentShader);
    }
}

void setVertices(Renderer *renderer_, size_t vertSize_, float vertices_[])
{
    glBindBuffer(GL_ARRAY_BUFFER, renderer_->vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertSize_, vertices_, GL_STATIC_DRAW);
    renderer_->vertCount = static_cast<GLsizei>(vertSize_ / (3 * sizeof(float)));
}

void render(Renderer *renderer_)
{
    glUseProgram(renderer_->program);
    glBindBuffer(GL_ARRAY_BUFFER, renderer_->vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(0);

    if (renderer_->mvpLoc != -1)
    {
        glm::mat4 view = glm::lookAt(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 mvp = proj * view * renderer_->model;
        glUniformMatrix4fv(renderer_->mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
    }

    glDrawArrays(renderer_->drawMode, 0, renderer_->vertCount);
}

} // namespace Renderer