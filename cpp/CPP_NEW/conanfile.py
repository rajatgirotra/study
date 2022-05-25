from conans import ConanFile, tools
from conans.tools import Version, check_min_cppstd
from conan.tools.cmake import CMakeToolchain, CMake, CMakeDeps
import os, re
from os.path import join

class CPPStudyConan(ConanFile):
    name = 'cpp_study'
    license = 'MIT'
    author = 'Rajat Girotra'
    url = 'git@github.com:rajatgirotra/study.git'
    description = 'my cpp study over the years'

    settings = 'os', 'compiler', 'build_type', 'arch'

    # win_bash = True

    options = { 'shared': [False, True],
                'fPIC': [False, True],
                'lto': [False, True]
               }
    default_options = {'shared': False, 'fPIC': True, 'lto': False }

    requires = (
            'boost/1.76.0',
            'benchmark/1.5.3',
            'sqlite3/3.38.5',
            'protobuf/3.20.0'
             )

    exports_sources = ['CMakeLists.txt', 'cmake*', 'src*']

    def set_version(self):
        content = tools.load(os.path.join(self.recipe_folder, 'CMakeLists.txt'))
        version = re.search(r'project\([^\)]+VERSION (\d+\.\d+\.\d+)[^\)]*\)', content).group(1)
        self.version = version.strip()

    def build_requirements(self):
        pass
        # self.build_requires('gtest/1.10.0', force_host_context=True)

    def validate(self):
        check_min_cppstd(self, "17")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables['BITS'] = 64 if self.settings.arch == 'x86_64' else "32"
        tc.variables['ENABLE_LTO'] = bool(self.options.lto)
        tc.variables['CMAKE_VERBOSE_MAKEFILE'] = True
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        # self.run('ls', win_bash=True)
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        # cmake.test(output_on_failure=True)

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_id(self):
        pass

    @property
    def _cmake_install_base_path(self):
        return os.path.join("lib64", "cmake", self.name)

    def package_info(self):
        self.cpp_info.name = 'cpp_study'
        self.cpp_info.includedirs = ['include']
        self.cpp_info.libdirs = ['lib', 'lib64']

