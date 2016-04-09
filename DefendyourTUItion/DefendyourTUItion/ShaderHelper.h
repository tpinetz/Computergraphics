#pragma once
#include "MainHeaders.h"

#include <stdio.h>  /* defines FILENAME_MAX */

#include <direct.h>


class ShaderHelper
{	

public:
	ShaderHelper();
	bool loadShader(const char* vertexShader, const char* fragmentShader);
	~ShaderHelper();

	GLuint getProgramId();
private:
	GLuint m_programID;

};

