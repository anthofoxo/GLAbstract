#pragma once

#if !defined(GLABS_OPENGL_LOADER_GLAD)
	#if defined(__has_include)
		#if __has_include(<glad/glad.h>)
			#define GLABS_OPENGL_LOADER_GLAD
		#else
			#error "Cannot detect OpenGL loader!"
		#endif
	#else
		#error "Cannot detect OpenGL loader!"
	#endif
#endif

#if defined(GLABS_OPENGL_LOADER_GLAD)
	#include <glad/glad.h>
#endif