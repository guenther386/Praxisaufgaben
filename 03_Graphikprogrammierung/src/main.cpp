//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include <iostream>
#include <vector>
#include <sstream>
#include "application.h"


#ifndef WIN32
// These lines are needed if OpenGL is used under linux using nvidia drivers. The following error appears otherwise:
//   Inconsistency detected by ld.so: dl-version.c: 224: _dl_check_map_versions: Assertion `needed != ((void *)0)' failed!
///http://stackoverflow.com/questions/20007961/error-running-a-compiled-c-file-uses-opengl-error-inconsistency-detected
#include <string.h>
#include <stdint.h>
#include <pthread.h>
void junk() {
  int i;
  i=pthread_getconcurrency();
};
#endif



int main(int argc, char* argv[])
{
	// Instanciate the application...
	application app;

	// ... and let it run!
	return app.run(argc, argv);
}
