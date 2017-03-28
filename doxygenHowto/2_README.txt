tags that we care about

INPUT = <top directory of your source project>

RECURSIVE = YES <for recursive parsing of source directories >

FILE_PATTERNS = *.cpp *.hpp (Files to parse)

EXCLUDE = 
EXCLIDE_PATTERNS = */test*/ (to ignore all test directories)A

EXTRACT_ALL = YES
This is very helpful. Even your code is not documented according to doxygen rules, this option will force
to produce documentation. Use it to see how the documentation looks. Remember usage of this tag will stop
emitting warnings about missing documentation in files.

SOURCE_BROWSER=yes
INLINE_SOURCES=yes These two tags are used to include the source also in the documentation. Can be useful for
code reviews.

OUTPUT_DIRECTORY=<path where documentation is generated>
HTML_DIRECTORY = <relative path to output_directory above where html output is generated>
