from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.build import check_min_cppstd
from conan.tools.files import export_conandata_patches, apply_conandata_patches, copy, load, get, save, rmdir, replace_in_file
import json
from os.path import join
import re
import textwrap

from tornado.options import options


# Host context: Where the library/application is being run
# Build context: Where the library/application is being built

# tool_requires is just a conan2 substitute for build_requires. Normally, tool_requires context can be different than
# the requires configuration. Example:
# 1. cmake tool is needed in Release mode, but your library/application is built in debug mode.
# 2. you are running cmake on ubuntu linux, but cross building the library/application for raspberry pi.


class CPlusPlusConan(ConanFile):
    name = "CPlusPlus"
    settings = "os", "compiler", "build_type", "arch"
    author = "Rajat Girotra"

    options = {"shared": [True, False],
               "fPIC": [True, False],
               "enable_testing": [True, False],
               "lto": [True, False]
               }

    default_options = {"shared": False, "fPIC": True, "enable_testing": True, "lto": False}

    @property
    def _min_cppstd(self):
        return "20"  # can tailor as needed

    def set_version(self):
        content = load(self, join(self.recipe_folder, 'CMakeLists.txt'))
        version = re.search(r'project\([^\)]+VERSION (\d+\.\d+\.\d+)[^\)]*\)', content).group(1)
        self.version = version.strip()

    # config_options() is used to configure or constrain the available options in a package BEFORE assigning them
    # a value. you can remove options based on the current settings.
    # config_options() is called BEFORE configure(), BEFORE assigning the values to the options; and AFTER the settings
    # are already defined.
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    # configure() is called AFTER config_options() and it is used to define the values of the options.
    # when configure() is called, option values are already defined to the default values or the values set by the user.
    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    # export() is used to copy metadata files to the self.export_folder. These files are uploaded to the servers
    # and become an intrinsic part of the package recipe. They are downloaded by the Conan client when the package
    # is being installed. conanfile.py and conandata.yml are always exported by default. Also, conandata.yml is
    # automatically generated read and available in the self.conan_data attribute. export() is the method form of
    # the exports attribute.
    def export(self):
        copy(self, "LICENSE.md", self.recipe_folder, self.export_folder)

    # export_sources() is the method form of exports_sources attribute. It is used to copy source files
    # from the self.recipe_folder to the self.export_sources_folder. these source files are uploaded to
    # the servers together with the package recipe, but are typically not downloaded unless the package is
    # being built from source.
    def export_sources(self):
        copy(self, "CMakeLists.txt", self.recipe_folder, self.export_sources_folder)
        copy(self, "cmake*", self.recipe_folder, self.export_sources_folder)
        copy(self, "src*", self.recipe_folder, self.export_sources_folder)
        export_conandata_patches(self)

    def validate(self):
        if self.settings.compiler.cppstd:
            check_min_cppstd(self, self._min_cppstd)

    def layout(self):
        cmake_layout(self, generator="Ninja")

    # to put your project dependencies

    def requirements(self):
        # by default, the self.requires() means that you are requiring a library. So obviously, you need the headers
        # and the libraries.

        # For any transitive dependencies of boost, the headers=False by default and libs=True by default.
        # If you want your application to access any headers of the transitive dependencies, you need to set
        # transitive_headers=True below

        # What if you are sure that boost will always be a shared library and a dependency of boost will always be a
        # static library, then you can set transitive_libs=False below.

        # What if you depend on boost and boost provides a binary (like some code generator) that you need to run at
        # build time, then you can define the run=True below. It will put BOOST_ROOT/bin in the path at build time.
        # and this dependency is propagated to the consumers downstream..
        self.requires("boost/1.86.0", headers=True, libs=True)
        self.requires("grpc/1.69.0", headers=True, libs=True,
                       options={})

    # build_requirements is called after "requirements". Technically, all you do in build_requirements() can be done
    # inside the "requirements" function; but it is still good to separate the tool requirements and test requirements
    # inside the build_requirements() function.
    def build_requirements(self):
        self.test_requires("gtest/1.15.0")

    # source() method is used to fetch code from third-party. Like github, bitbucket etc.
    def source(self):
        pass  # executed in the self.source_folder

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables['BITS'] = 64 if self.settings.arch == 'x86_64' else "32"
        tc.variables['ENABLE_LTO'] = bool(self.options.lto)
        tc.variables['CMAKE_VERBOSE_MAKEFILE'] = True
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    @property
    def _cmake_install_base_path(self):
        return join("lib64", "cmake", self.name)

    def package_info(self):
        self.cpp_info.name = 'cplusplus'
        self.cpp_info.includedirs = ['include']
        self.cpp_info.libdirs = ['lib', 'lib64']

    def package_id(self):
        pass
