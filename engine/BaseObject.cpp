#include "Engine.h"

namespace BaseObject
{

float point[3] = {0.0f, 0.0f, 0.0f};

float quad[18] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f};

float plane[36] = {
    // 三角形 1: 顺时针（从上方看，Y轴正方向）
    -1.0f, 0.0f, -1.0f, // 左下
    1.0f, 0.0f, 1.0f,   // 右上
    1.0f, 0.0f, -1.0f,  // 右下
    // 三角形 2: 顺时针
    -1.0f, 0.0f, -1.0f, // 左下
    -1.0f, 0.0f, 1.0f,  // 左上
    1.0f, 0.0f, 1.0f    // 右上
};

float cube[108] = {-1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,
                   -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
                   1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, -1.0f,
                   -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
                   -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f, 1.0f,  1.0f,  1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f};

std::vector<float> scaleVertices(const float *vertices_, size_t vertexCount_, float scaleX_, float scaleY_, float scaleZ_)
{
    std::vector<float> scaledVertices;
    scaledVertices.reserve(vertexCount_);

    // 每个顶点有3个分量 (x, y, z)
    size_t vertexNum = vertexCount_ / 3;

    for (size_t i = 0; i < vertexNum; ++i)
    {
        // 读取原始顶点
        float x = vertices_[i * 3 + 0];
        float y = vertices_[i * 3 + 1];
        float z = vertices_[i * 3 + 2];

        // 相对于原点缩放（因为原点就是 0,0,0，所以直接乘）
        scaledVertices.push_back(x * scaleX_);
        scaledVertices.push_back(y * scaleY_);
        scaledVertices.push_back(z * scaleZ_);
    }

    return scaledVertices;
}

} // namespace BaseObject
