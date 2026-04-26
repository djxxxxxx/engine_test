#pragma once

#include <SDL2/SDL.h>
#include <assert.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

// BASEOBJECT / TRANSFORM / RENDERER / CORE / LOG / UTIL

// --------------------------------- BASE_OBJECT -------------------------------------- //
namespace BaseObject
{

extern float point[3];
extern float quad[18];
extern float plane[36];
extern float cube[108];

std::vector<float> scaleVertices(const float *vertices_, size_t vertexCount_, float scaleX_, float scaleY_, float scaleZ_);

} // namespace BaseObject

// --------------------------------- TRANSFORM -------------------------------------- //
namespace Transform
{

struct Transform
{
    glm::mat4 matrix;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

} // namespace Transform

// --------------------------------- RENDERER -------------------------------------- //
namespace Renderer
{

#define NUM_VBO 4

struct Renderer
{
    GLuint program = 0;
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
    GLuint vbo[NUM_VBO] = {0};
    GLsizei vertCount = 0;
    GLenum drawMode = GL_TRIANGLES;
    GLint mvpLoc = -1;
    glm::mat4 model = glm::mat4(1.0f);
    float rotAngle = 0.0f;

    Renderer(const std::string vertShaderPath_ = "", const std::string fragShaderPath_ = "");
    ~Renderer();
};

void setVertices(Renderer *renderer_, size_t vertSize_, float vertices_[]);

void render(Renderer *renderer_);

} // namespace Renderer

// --------------------------------- CORE -------------------------------------- //
namespace Core
{

extern SDL_Window *_window;
extern SDL_GLContext _glContext;

extern std::vector<Renderer::Renderer *> _rendererList;

bool init();

void loop();

void input();

void update();

void render();

void quit();

} // namespace Core

// --------------------------------- LOG -------------------------------------- //
namespace Log
{

void debug(const char *fmt_, ...);
void info(const char *fmt_, ...);
void warn(const char *fmt_, ...);
void error(const char *fmt_, ...);

} // namespace Log

// --------------------------------- UTIL -------------------------------------- //
namespace Util
{

std::string fileRead(std::string path_);

void fileWrite(std::string path_, std::string content_);

} // namespace Util
