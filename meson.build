project('qcx assert', 'cpp',
	version: '0.0.1'
)

catch2_sp = subproject('catch2')
catch2_dep = catch2_sp.get_variable('catch2_dep')

inc = include_directories('include')

qcx_assert_dep = declare_dependency(include_directories: inc)

subdir('test')
