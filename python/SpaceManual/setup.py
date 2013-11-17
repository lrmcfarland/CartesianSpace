# builds python orbits module
# from http://docs.python.org/extending/building.html

from distutils.core import setup, Extension

space_module = Extension('space',
                          include_dirs=['../../libSpace'], # TODO meh.
                          libraries=['space'],
                          library_dirs=['../../libSpace'], # TODO meh**2.
                          sources=['space.cpp'])

setup (name='space',
       version='1.0',
       description='space package',
       ext_modules=[space_module])


