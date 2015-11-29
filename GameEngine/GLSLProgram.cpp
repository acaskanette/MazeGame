#include "GLSLProgram.h"

#include <vector>
#include <fstream>
#include "LogManager.h"

GLSLProgram::GLSLProgram() : programID(0), vertexShaderID(0), fragmentShaderID(0), numAttrs(0)
{
}

// Compiles the shaders into a form that your GPU can understand
void GLSLProgram::CompileShaders(const std::string& _vertexShaderFilePath, const std::string& _fragmentShaderFilepath) {
  // Get a program object.
  programID = glCreateProgram();

  // Create the vertex shader object, and store its ID
  vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  if (vertexShaderID == 0)
		LogManager::getInstance().logFatal("Vertex shader failed to be created!");

  // Create the fragment shader object, and store its ID
  fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  if (fragmentShaderID == 0)
		LogManager::getInstance().logFatal("Fragment shader failed to be created!");

  CompileShader(_vertexShaderFilePath, vertexShaderID);
  CompileShader(_fragmentShaderFilepath, fragmentShaderID);
}

void GLSLProgram::LinkShaders() {
  // Attach shaders to our program
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);

  // Link our program
  glLinkProgram(programID);
  GLint isLinked = 0;
  glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);

  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<char> errorLog(maxLength);
    glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

		// Clear the memory
    glDeleteProgram(programID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

		LogManager::getInstance().logFatal("Shaders failed to link!");
  }

  // Always detach shaders after a successful link.
  glDetachShader(programID, vertexShaderID);
  glDetachShader(programID, fragmentShaderID);
  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
}

void GLSLProgram::AddAttribute(const std::string& _attrName) {
  glBindAttribLocation(programID, numAttrs++, _attrName.c_str());
}

GLint GLSLProgram::GetUniformLocation(const std::string& _uniformName) {
  GLint location = glGetUniformLocation(programID, _uniformName.c_str());

  if (location == GL_INVALID_INDEX)
		LogManager::getInstance().logFatal("Uniform " + _uniformName + " not found in shader!");

  return location;
}

void GLSLProgram::Use() {
  glUseProgram(programID);

  // Enable all the attributes
  for (int i = 0; i < numAttrs; i++)
    glEnableVertexAttribArray(i);
}

void GLSLProgram::Unuse() {
  glUseProgram(0);

  for (int i = 0; i < numAttrs; i++)
    glDisableVertexAttribArray(i);
}

void GLSLProgram::CompileShader(const std::string& _filePath, GLuint _id) {
  // Open the file
  std::ifstream shaderFile(_filePath);
  if (shaderFile.fail())
		LogManager::getInstance().logFatal("Failed to open " + _filePath);

  // File contents stores all the text in the file
  std::string fileContents = "";
  std::string line;

  // Get all the lines in the file and add it to the contents
  while (std::getline(shaderFile, line))
    fileContents += line + "\n";

  shaderFile.close();

  // Get a pointer to our file contents c string;
  const char* contentsPtr = fileContents.c_str();
  // Tell opengl that we want to use fileContents as the contents of the shader file
  glShaderSource(_id, 1, &contentsPtr, nullptr);
  // Compile the shader
  glCompileShader(_id);

  // Check for errors
  GLint success = 0;
  glGetShaderiv(_id, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<char> errorLog(maxLength);
    glGetShaderInfoLog(_id, maxLength, &maxLength, &errorLog[0]);

    glDeleteShader(_id);

		LogManager::getInstance().logFatal("Shader " + _filePath + " failed to compile");
  }
}