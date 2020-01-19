ape_sources = run_command('find_sources.sh').stdout().strip().split('\n')
libape2d = shared_library('ape2d', 
                          ape_sources,
                          include_directories : inc,
                          dependencies : [sdl2_dep, sdl2_img_dep],
                          install : true)