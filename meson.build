project('ape2d', 'cpp',
    version : '0.0.2',
    license: 'MIT',
    default_options : ['cpp_std=c++17'])

add_global_arguments('-DSOME_TOKEN=value', language : 'cpp')

sdl2_dep = dependency('SDL2')
sdl2_img_dep = dependency('SDL2_image')

inc = include_directories('include')

subdir('include')
subdir('src')
subdir('tests')
subdir('examples')

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : libape2d,
                  version : '0.0.2',
                  name : 'libape2d',
                  filebase : 'ape2d',
                  description : 'A library for developing 2d games.')