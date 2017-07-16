#ifndef _ERROR_
#define _ERROR_

#include "common.h"

void at_error(void(*func)(const char*));
void at_warning(void(*func)(const char*));
void at_debug(void(*func)(const char*));

void error_(const char*);
void warning_(const char*);
void debug_(const char*);

char error_buf[2048];
char error_str[2048];

char warning_buf[2048];
char warning_str[2048];

char debug_buf[2048];
char debug_str[2048];

#define error(MSG, ...) { \
  sprintf(error_str, "[ERROR] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
  sprintf(error_buf, MSG, ##__VA_ARGS__); strcat(error_str, error_buf); \
  error_(error_str); }

#define warning(MSG, ...) { \
  sprintf(warning_str, "[WARNING] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
  sprintf(warning_buf, MSG, ##__VA_ARGS__); strcat(warning_str, warning_buf); \
  warning_(warning_str); }

#define debug(MSG, ...) { \
  sprintf(debug_str, "[DEBUG] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
  sprintf(debug_buf, MSG, ##__VA_ARGS__); strcat(debug_str, debug_buf); \
  debug_(debug_str); }

#define alloc_check(PTR) { if((PTR) == NULL) { error("Out of Memory!"); } }

#define SDL_GL_CheckError() { GLenum __glerror = glGetError(); if (__glerror) { error("OpenGL Error: %s", SDL_GL_ErrorString(__glerror)); } }

#define SDL_GL_CheckFrameBuffer() { GLenum __glfbstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER); if(__glfbstatus != GL_FRAMEBUFFER_COMPLETE) { error("OpenGL FrameBuffer Error: %s", SDL_GL_FrameBufferErrorString(__glfbstatus)); } }

#endif /* end of include guard: _ERROR_ */
