#include "Mesh.h"
#include <vector>

namespace gpx
{
    Mesh::Mesh(Vertex* vertices, uint32_t numVertice)
    {
        drawCount = numVertice;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        std::vector<glm::vec3> position;
        std::vector<glm::vec2> texCoord;

        position.reserve(numVertice);
        texCoord.reserve(numVertice);

        for(size_t i = 0; i < numVertice; i++)
        {
            position.push_back(*vertices[i].GetPos());
            texCoord.push_back(*vertices[i].GetTexCoord());
        }

        glGenBuffers(NUM_BUFFERS, VAB);
        glBindBuffer(GL_ARRAY_BUFFER, VAB[POSITION_VB]);
        glBufferData(GL_ARRAY_BUFFER, numVertice * sizeof(position[0]), &position[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, VAB[TEXCOORD_VB]);
        glBufferData(GL_ARRAY_BUFFER, numVertice * sizeof(texCoord[0]), &texCoord[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glBindVertexArray(0);
    }
    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &VAO);
    }

    void Mesh::Draw()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, drawCount);
        glBindVertexArray(0);
    }
}