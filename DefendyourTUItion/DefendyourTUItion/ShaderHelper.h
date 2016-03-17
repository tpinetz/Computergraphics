#pragma once
#include "MainHeaders.h"

class ShaderHelper
{	

public:
	ShaderHelper();
	bool loadShader(const char* vertexShader, const char* fragmentShader);
	~ShaderHelper();

	GLuint getProgramId();
private:
	GLuint programID;

};

