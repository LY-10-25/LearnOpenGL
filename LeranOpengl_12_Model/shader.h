#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // ����glad����ȡ���еı���OpenGLͷ�ļ�
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // ����ID
    unsigned int ID;

    // ��������ȡ��������ɫ��
    Shader(const char* vertexPath, const char* fragmentPath);
    // ʹ��/�������
    void use();
    // uniform���ߺ���
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 model) const;
    void setVec3(const std::string& name, glm::vec3 model) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
};

#endif