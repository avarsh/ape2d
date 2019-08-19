# Conventions

This document outlines the coding style when hacking the engine.

## Namespaces
Namespaces may contain public facing functions; where a function is intended
for internal use, a separate detail namespace should be created nested inside
the main namespace, in a detail folder and separate header file.

## Headers

Header guards for a file named filename.h are respectively APE_FILENAME_H.