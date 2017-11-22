#ifndef EGLFIXTURE_HPP
#define EGLFIXTURE_HPP

#include <gtest/gtest.h>
#include <glad/glad.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

class EGLFixture : public ::testing::Test {
public:
protected:
    EGLDisplay display;
    EGLContext context;
    virtual void SetUp() {
        const EGLint sContextAttrib[] = {
            EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,    EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
            EGL_NONE
        };
        const EGLint sConfigAttrib[] = {
            EGL_NONE
        };
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        expectNe(EGL_NO_DISPLAY, display, "eglGetDisplay");
        EGLint minor;
        EGLint major;
        auto ret = eglInitialize(display, &major, &minor);
        expectNe(0u, ret, "eglInitialize");
        EGLint numConfigs = 0;
        EGLConfig config = nullptr;
        EGLint noOfRequestedConfigs = 1;
        eglChooseConfig(display, sConfigAttrib, &config, noOfRequestedConfigs, &numConfigs);
        expectNe(0, numConfigs, "eglChooseConfig");
        eglBindAPI(EGL_OPENGL_API);
        context = eglCreateContext(display, config, nullptr, sContextAttrib);
        expectNe(EGL_NO_CONTEXT, context, "eglCreateContext");
        ret = eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, context);
        expectNe(0u, ret, "eglMakeCurrent");
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(eglGetProcAddress))) {
            throw std::logic_error("Fatal exception, cannot initialize GLAD");
        }
    }

    virtual void TearDown() {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroyContext(display, context);
        eglTerminate(display);
        eglReleaseThread();
    }

    template<typename L, typename R>
    void expectNe(L expected, R result, const std::string& message) {
        if (result == expected) {
            std::ostringstream oss;
            oss << std::hex << eglGetError();
            throw std::logic_error("Error: " + oss.str() + ". " + message);
        }
    }
};

#endif // EGLFIXTURE_HPP
