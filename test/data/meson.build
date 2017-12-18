project('foo', 'cpp', default_options : ['cpp_std=c++17'])

cxx = meson.get_compiler('cpp')
if cxx.get_id() == 'msvc'
	# cpp_std=c++17 doesn't work for VC++, meson bug
	# /permissive- makes it more standards compliant
	add_global_arguments('/std:c++17', '/permissive-',
		language: 'cpp')
endif

assert_level = get_option('assert_level')

if assert_level == 'fast'
	add_global_arguments('-DQCX_ASSERT_LEVEL_FAST',
		language: 'cpp')
elif assert_level == 'normal'
	add_global_arguments('-DQCX_ASSERT_LEVEL_NORMAL',
		language: 'cpp')
elif assert_level == 'debug'
	add_global_arguments('-DQCX_ASSERT_LEVEL_DEBUG',
		language: 'cpp')
endif

add_global_arguments('-DQCX_ASSERT_NO_SOURCE_INFO',
	language: 'cpp')

inc = include_directories('include')

executable('my_executable', ['main.cpp', 'asserter.cpp'], include_directories: inc)
