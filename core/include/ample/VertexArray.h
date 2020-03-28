#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <memory>

#include "Vector2d.h"
#include "Vector3d.h"
#include "Noncopyable.h"
#include "Texture.h"

namespace ample::graphics
{
enum class normalsMode
{
    SINGLE,
    VERTEX,
};

class VertexArray : public utils::Noncopyable
{
private:
    class VertexBuffer final : utils::Noncopyable
    {
    public:
        struct Executor final : utils::Noncopyable
        {
            Executor(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer, VertexBuffer &buf);
            ~Executor();

        private:
            GLuint _index;
        };

    public:
        VertexBuffer(GLsizeiptr, void *);
        ~VertexBuffer();

    private:
        GLuint _bufferId;
        GLsizeiptr _size;
        void *_data;
    };

public:
    struct VertexArrayRaw
    {
        std::vector<Vector3d<float>> coords;
        std::vector<Vector2d<float>> uvCoords;
        std::vector<Vector3d<float>> normal;

        VertexArrayRaw(const std::vector<Vector3d<float>> &coords,
                       const std::vector<Vector2d<float>> &uvCoords,
                       const std::vector<Vector3d<float>> &normals);
    };

    VertexArray(const VertexArrayRaw &);
    void execute();

private:
    VertexBuffer _xyzCoordsBuffer;
    VertexBuffer _uvCoordsBuffer;
    VertexBuffer _normalsBuffer;
    GLsizei _totalVerts;
};
} // namespace ample::graphics
