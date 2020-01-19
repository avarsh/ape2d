entity_delete = executable('entity_deletion', 'ecs/entity_deletion.cpp',
                         include_directories: inc,
                         link_with: libape2d)
test('entity deletion test', entity_delete)

entity_tag = executable('entity_tagging', 'ecs/entity_tagging.cpp',
                         include_directories: inc,
                         link_with: libape2d)
test('entity tagging test', entity_tag)