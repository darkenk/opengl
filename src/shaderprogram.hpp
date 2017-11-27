#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <string>
#include <vector>
#include <glad/glad.h>
#include <memory>
#include <map>
#include <iostream>

template<int ShaderType>
class Shader {
public:
    template<typename T>
    Shader(T content): mContent(content) {}

    static constexpr GLuint type = ShaderType;
    const std::string& getContent() { return mContent; }
private:
    const std::string mContent;
};

using VertexShader = Shader<GL_VERTEX_SHADER>;
using FragmentShader = Shader<GL_FRAGMENT_SHADER>;
using GeometryShader = Shader<GL_GEOMETRY_SHADER>;

class ShaderProgram
{
public:
    ShaderProgram() { mProgramId = 0; }
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram(const std::vector<std::pair<GLuint, const std::string>>& /*shaders*/) {}
    ~ShaderProgram();

    template<typename... Attributes, typename... Shaders>
    void init(Shaders... shaders) {
        glGetError();
        createShaders(shaders...);
        createProgram<Attributes...>();
        activate();
        initUniforms();
    }

    template<typename... Attributes>
    void init(const std::vector<std::pair<GLuint, const std::string>>& shaders) {
        glGetError();
        for (const auto& shader : shaders) {
            mShaderIds.push_back(createShader(shader.second, shader.first));
        }
        createProgram<Attributes...>();
        initUniforms();
    }
    template<typename... Attributes>
    static ShaderProgram&& create() {
        ShaderProgram s;
        return std::move(ShaderProgram());
    }
    void activate();
    void deactivate();

    template<typename Uniform>
    void set(const Uniform& uniform) {
        // in future (make a queue and execute once)
        try {
            auto location = mUniforms.at(uniform.name());
            uniform.setGL(location);
        } catch (std::out_of_range&) {
            std::cerr << "No such uniform " << uniform.name() << std::endl;
            std::cerr << "Available uniforms: " << std::endl;
            for (auto u : mUniforms) {
                std::cerr << "Name: " << u.first << " Location: " << u.second << std::endl;
            }
            std::abort();
        }
    }

    GLuint get() {
        return mProgramId;
    }

private:
    GLuint createShader(const std::string& shader, GLuint shaderType) {
        GLuint shaderId = glCreateShader(shaderType);
        const char* str = shader.c_str();
        glShaderSource(shaderId, 1, &str, nullptr);
        glCompileShader(shaderId);
        checkCompilationError(shaderId);
        return shaderId;
    }
    void checkCompilationError(GLuint shaderId);
    void initUniforms();

    template<typename... Attributes>
    void createProgram() {
        mProgramId = glCreateProgram();
        bindAttributes<Attributes...>(mProgramId);
        for (auto shaderId : mShaderIds) {
            glAttachShader(mProgramId, shaderId);
        }
        glLinkProgram(mProgramId);
    }

    // TODO: how to do this better?
    template<typename T, typename T2, typename... Tp>
    void bindAttributes(GLuint program) {
        bindAttributes<T>(program);
        bindAttributes<T2, Tp...>(program);
    }

    template<typename T>
    void bindAttributes(GLuint program) {
        const char* name = T::name;
        std::cout << "Bind attrib " << name << " to " << T::location << std::endl;
        glBindAttribLocation(program, T::location, name);
    }

    template<typename T, typename T2, typename... Tp>
    void createShaders(T shader, T2 sh, Tp... shaders) {
        mShaderIds.push_back(createShader(shader.getContent(), T::type));
        createShaders(sh, shaders...);
    }

    template<typename T>
    void createShaders(T shader) {
        mShaderIds.push_back(createShader(shader.getContent(), T::type));
    }

    GLuint mProgramId;
    std::vector<GLuint> mShaderIds;
    std::map<std::string, GLuint> mUniforms;
};

#endif // SHADERLOADER_H
