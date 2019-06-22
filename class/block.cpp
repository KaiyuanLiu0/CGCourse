//
// Created by KaiyuanLiu on 2019-06-14.
//

#include "../src/stb_image.h"
#include "block.h"

Block::Block()
{
    SetType(WALL);
}

Block::Block(TYPE type)
{
    SetType(type);
}

Block::Block(Block& block)
{
    SetType(block.GetType());
}

void Block::SetType(TYPE type)
{
    m_type_ = type;
    SetUpBlock();
}

TYPE Block::GetType()
{
    return m_type_;
}

void Block::SetUpBlock()
{
    texture_id_ = LoadTexture(m_type_);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(block_vertices), block_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
}

unsigned int Block::LoadTexture(TYPE type)
{
    unsigned int tmp_texture_id;
    glGenTextures(1, &tmp_texture_id);

    int width, height, channel;
    unsigned char* image;
    glBindTexture(GL_TEXTURE_CUBE_MAP, tmp_texture_id);

    for (int i = 0; i != 6; ++i)
    {
        image = stbi_load(path[type][i].c_str(), &width, &height, &channel, 0);
        if (!image) {
            throw "BLOCK::LOADTEXTURE::TEXTURE_FILE_MISSING";
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        stbi_image_free(image);
    }

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return tmp_texture_id;
}

void Block::Draw(Shader shader)
{
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id_);
    shader.setInt("blockTex", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

}
