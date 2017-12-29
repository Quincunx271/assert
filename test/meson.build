cxx = meson.get_compiler('cpp')
msvc_args = []
if cxx.get_id() == 'msvc'
	# cpp_std=c++17 doesn't work for VC++, meson bug
	# /permissive- makes it more standards compliant
	msvc_args = ['/std:c++17', '/permissive-']
endif

fast_exe = executable('fast_test',
	['test_main.cpp', 'test_fast.cpp'],
	dependencies: [catch2_dep, qcx_assert_dep],
	cpp_args: ['-DQCX_ASSERT_LEVEL_FAST', msvc_args],
	override_options: ['cpp_std=c++17']
)

normal_exe = executable('normal_test',
	['test_main.cpp', 'test_normal.cpp'],
	dependencies: [catch2_dep, qcx_assert_dep],
	cpp_args: ['-DQCX_ASSERT_LEVEL_NORMAL', msvc_args],
	override_options: ['cpp_std=c++17']
)

safe_exe = executable('safe_test',
	['test_main.cpp', 'test_safe.cpp'],
	dependencies: [catch2_dep, qcx_assert_dep],
	cpp_args: ['-DQCX_ASSERT_LEVEL_SAFE', msvc_args],
	override_options: ['cpp_std=c++17']
)

default_exe = executable('default_test',
	['test_main.cpp', 'test_normal.cpp'],
	dependencies: [catch2_dep, qcx_assert_dep],
	cpp_args: [msvc_args],
	override_options: ['cpp_std=c++17']
)

test('qcx assert test: fast', fast_exe)
test('qcx assert test: normal', normal_exe)
test('qcx assert test: safe', safe_exe)
test('qcx assert test: default', default_exe)
