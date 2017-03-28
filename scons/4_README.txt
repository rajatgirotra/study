Library Linking into executables
================================

Very trivial. Just use LIBS and LIBPATH with the "Program()" function

Progam('foo', LIBS=['list of', 'library_names'], LIBPATH=['list of paths', 'where libraries are stored'])
