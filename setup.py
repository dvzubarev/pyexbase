# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

import os
import pathlib

from setuptools.command.build_ext import build_ext as _build_ext
from setuptools import setup, Extension

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        super().__init__(name, [])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(_build_ext):
    def build_extension(self, ext):
        cwd = pathlib.Path().absolute()

        # these dirs will be created in build_py, so if you don't have
        # any python sources to bundle, the dirs will be missing
        build_temp = pathlib.Path(self.build_temp)
        build_temp.mkdir(parents=True, exist_ok=True)
        ext_path = pathlib.Path(self.get_ext_fullpath(ext.name))

        build_type = 'Debug' if self.debug else 'Release'
        cmake_args = [
            '-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + str(ext_path.parent.absolute()),
            '-DCMAKE_BUILD_TYPE=' + build_type
        ]

        # example of build args
        build_args = [
            '--config', build_type,
            '--', '-j4'
        ]

        os.chdir(str(build_temp))
        self.spawn(['cmake', str(cwd)] + cmake_args)
        if not self.dry_run:
            self.spawn(['cmake', '--build', '.'] + build_args)
        # Troubleshooting: if fail on line above then delete all possible
        # temporary CMake files including "CMakeCache.txt" in top level dir.
        os.chdir(str(cwd))



setup(
    name='libpyexbase',
    version='0.1',
    description='Bindings for textapp core functions',
    url='http://ids.isa.ru:8083/git/pyexbase',
    author='dvzubarev',
    author_email='zubarev@isa.ru',
    license='MIT',

    ext_modules=[CMakeExtension('libpyexbase')],
    cmdclass={
        'build_ext': CMakeBuild,
    }

)
