"""Creats python wrappers from boost macro

ASSUMES: ../../libSpace exists and /usr/local/[include,lib] has boost installed.
"""

from distutils.core import setup, Extension

name = 'space'
version = '1.0'

include_dirs=['../../libSpace',
              '/usr/local/include', # for boost
              ]


library_dirs=['../../libSpace',
              '/usr/local/lib', # for boost
              ]

libraries = ['boost_python', 'space']

sources = ['boost_space_module.cpp']

space_module = Extension(name,
                         include_dirs=include_dirs,
                         libraries=libraries,
                         library_dirs=library_dirs,
                         sources=sources)

setup (name=name,
       version=version,
       description='space package',
       ext_modules=[space_module])
