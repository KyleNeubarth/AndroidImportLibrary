#include <jni.h>
#include <string>
//for string stuff
#include <sstream>

//imported precompiled shared library
#include <gperf.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_cbasiclibrary_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "This is a string that was written in C";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_cbasiclibrary_MainActivity_ticksFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::stringstream ss;
    ss << GetTicks();
    std::string ticks = "This number was created using the GetTicks() functions from the gperf shared library: " + ss.str();
    return env->NewStringUTF(ticks.c_str());
}