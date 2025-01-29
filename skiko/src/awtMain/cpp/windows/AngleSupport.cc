#ifdef SK_ANGLE

#include <windows.h>
#define GL_GLES_PROTOTYPES 0
#define EGL_EGL_PROTOTYPES 0
#include <GLES/gl.h>
#include <EGL/egl.h>
#include "exceptions_handler.h"

static HINSTANCE AngleEGLLibrary = nullptr;

extern "C" {
    EGLBoolean EGLAPIENTRY eglInitialize (EGLDisplay dpy, EGLint *major, EGLint *minor) {
        static auto eglInitialize = (PFNEGLINITIALIZEPROC) GetProcAddress(AngleEGLLibrary, "eglInitialize");
        return eglInitialize(dpy, major, minor);
    }

    EGLBoolean EGLAPIENTRY eglTerminate (EGLDisplay dpy) {
        static auto eglTerminate = (PFNEGLTERMINATEPROC) GetProcAddress(AngleEGLLibrary, "eglTerminate");
        return eglTerminate(dpy);
    }

    EGLBoolean EGLAPIENTRY eglMakeCurrent (EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx) {
        static auto eglMakeCurrent = (PFNEGLMAKECURRENTPROC) GetProcAddress(AngleEGLLibrary, "eglMakeCurrent");
        return eglMakeCurrent(dpy, draw, read, ctx);
    }

    EGLBoolean EGLAPIENTRY eglChooseConfig (EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config) {
        static auto eglChooseConfig = (PFNEGLCHOOSECONFIGPROC) GetProcAddress(AngleEGLLibrary, "eglChooseConfig");
        return eglChooseConfig(dpy, attrib_list, configs, config_size, num_config);
    }

    EGLContext EGLAPIENTRY eglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list) {
        static auto eglCreateContext = (PFNEGLCREATECONTEXTPROC) GetProcAddress(AngleEGLLibrary, "eglCreateContext");
        return eglCreateContext(dpy, config, share_context, attrib_list);
    }

    EGLBoolean EGLAPIENTRY eglDestroyContext (EGLDisplay dpy, EGLContext ctx) {
        static auto eglDestroyContext = (PFNEGLDESTROYCONTEXTPROC) GetProcAddress(AngleEGLLibrary, "eglDestroyContext");
        return eglDestroyContext(dpy, ctx);
    }

    EGLSurface EGLAPIENTRY eglCreateWindowSurface (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list) {
        static auto eglCreateWindowSurface = (PFNEGLCREATEWINDOWSURFACEPROC) GetProcAddress(AngleEGLLibrary, "eglCreateWindowSurface");
        return eglCreateWindowSurface(dpy, config, win, attrib_list);
    }

    EGLBoolean EGLAPIENTRY eglDestroySurface (EGLDisplay dpy, EGLSurface surface) {
        static auto eglDestroySurface = (PFNEGLDESTROYSURFACEPROC) GetProcAddress(AngleEGLLibrary, "eglDestroySurface");
        return eglDestroySurface(dpy, surface);
    }

    EGLBoolean EGLAPIENTRY eglSwapInterval (EGLDisplay dpy, EGLint interval) {
        static auto eglSwapInterval = (PFNEGLSWAPINTERVALPROC) GetProcAddress(AngleEGLLibrary, "eglSwapInterval");
        return eglSwapInterval(dpy, interval);
    }

    EGLBoolean EGLAPIENTRY eglSwapBuffers (EGLDisplay dpy, EGLSurface surface) {
        static auto eglSwapBuffers = (PFNEGLSWAPBUFFERSPROC) GetProcAddress(AngleEGLLibrary, "eglSwapBuffers");
        return eglSwapBuffers(dpy, surface);
    }

    __eglMustCastToProperFunctionPointerType EGLAPIENTRY eglGetProcAddress (const char *procname) {
        static auto eglGetProcAddress = (PFNEGLGETPROCADDRESSPROC) GetProcAddress(AngleEGLLibrary, "eglGetProcAddress");
        return eglGetProcAddress(procname);
    }

    JNIEXPORT jstring JNICALL Java_org_jetbrains_skiko_AngleApi_glGetString(JNIEnv *env, jobject object, jint value)
    {
        static auto glGetString = (PFNGLGETSTRINGPROC) eglGetProcAddress("glGetString");
        const char *content = reinterpret_cast<const char *>(glGetString(value));
        return env->NewStringUTF(content);
    }

    JNIEXPORT void JNICALL Java_org_jetbrains_skiko_AngleSupport_1jvmKt_loadAngleLibraryWindows(JNIEnv *env, jobject obj) {
        AngleEGLLibrary = LoadLibrary("libEGL.dll");
        if (AngleEGLLibrary == nullptr) {
            auto code = GetLastError();
            throwJavaRenderExceptionByErrorCode(env, __FUNCTION__, code);
        }
    }
}

#endif
