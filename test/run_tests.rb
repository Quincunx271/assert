require 'tmpdir'
require 'fileutils'
require 'rbconfig'

IS_WINDOWS = (RbConfig::CONFIG['host_os'] =~ /mswin|mingw|cygwin/)
# Ruby thinks '/' is a good separator even on windows, but when running `` commands, it can mess things up
SEPARATOR = IS_WINDOWS ? '\\' : File::SEPARATOR

ASSERTERS = ['fast.cpp', 'normal.cpp', 'debug.cpp']

TEST_CASES = [
	[
		'default',
		[true, true, false]
	],
	[
		'fast',
		[true, false, false]
	],
	[
		'normal',
		[true, true, false]
	],
	[
		'debug',
		[true, true, true]
	],
]

MAINS = ['main_abort.cpp', 'main_throw.cpp']

passed = true
# main_abort.cpp:

puts 'abort handler:'
Dir.mktmpdir do |dir|
	FileUtils.cp_r("../include", "#{dir}")
	FileUtils.cp("./data/meson.build", "#{dir}")
	FileUtils.cp("./data/meson_options.txt", "#{dir}")

	TEST_CASES.each do |args|
		option = "-Dassert_level=#{args[0]}"
		expected = args[1]
		ASSERTERS.zip(expected).each do |asserter, assert_runs|
			FileUtils.cp("./data/#{asserter}", "#{dir}/asserter.cpp")
			FileUtils.cp("./data/main_abort.cpp", "#{dir}/main.cpp")

			FileUtils.cd("#{dir}") do
				begin
					meson = `meson build --buildtype release #{option}`
					puts "test failed: level=#{args[0]}, test=#{asserter}, failed to configure build system" unless $? == 0
					passed &&= $? == 0
					next unless $? == 0
					
					FileUtils.cd("build") do
						ninja = `ninja`

						puts "test failed: level=#{args[0]}, test=#{asserter}, build failed with message:\n#{ninja}" unless $? == 0
						passed &&= $? == 0
						next unless $? == 0
						
						def unwrap array
							raise "internal error; array.size != 1 (array: #{array})" unless array.size == 1
							array[0]
						end

						run = `.#{SEPARATOR}#{unwrap(Dir.glob('my_executable{,.exe,.out}'))} >out.txt 2>&1`
						puts "test failed: level=#{args[0]}, test=#{asserter}, expected: #{assert_runs ? 'asserts' : 'silent'}. result: #{$? != 0 ? 'asserts' : 'silent'}" unless assert_runs == ($? != 0)
						passed &&= assert_runs == ($? != 0)
						next unless assert_runs == ($? != 0)

						puts "test passed: level=#{args[0]}, test=#{asserter}"
					end

				ensure
					FileUtils.remove_entry_secure('build') if File.exist?('build')
				end
			end
		end
	end
end
puts

# main_throw.cpp:
puts 'throw handler:'

Dir.mktmpdir do |dir|
	FileUtils.cp_r("../include", "#{dir}")
	FileUtils.cp("./data/meson.build", "#{dir}")
	FileUtils.cp("./data/meson_options.txt", "#{dir}")

	TEST_CASES.each do |args|
		option = "-Dassert_level=#{args[0]}"
		expected = args[1]
		ASSERTERS.zip(expected).each do |asserter, assert_runs|
			FileUtils.cp("./data/#{asserter}", "#{dir}/asserter.cpp")
			FileUtils.cp("./data/main_throw.cpp", "#{dir}/main.cpp")

			FileUtils.cd("#{dir}") do
				begin
					meson = `meson build --buildtype release #{option}`
					puts "test failed: level=#{args[0]}, test=#{asserter}, failed to configure build system" unless $? == 0
					passed &&= $? == 0
					next unless $? == 0
					
					FileUtils.cd("build") do
						ninja = `ninja`

						puts "test failed: level=#{args[0]}, test=#{asserter}, build failed with message:\n#{ninja}" unless $? == 0
						passed &&= $? == 0
						next unless $? == 0
						
						def unwrap array
							raise "internal error; array.size != 1 (array: #{array})" unless array.size == 1
							array[0]
						end

						run = `./my_executable`
						assert_ran = run == 'logic_error'
						puts "test failed: level=#{args[0]}, test=#{asserter}, expected: #{assert_runs ? 'asserts' : 'silent'}. result: #{assert_ran ? 'asserts' : 'silent'}" unless assert_runs == assert_ran
						passed &&= assert_runs == assert_ran
						next unless assert_runs == assert_ran

						puts "test passed: level=#{args[0]}, test=#{asserter}"
					end

				ensure
					FileUtils.remove_entry_secure('build') if File.exist?('build')
				end
			end
		end
	end
end

puts
puts 'All tests passed' if passed
exit 1 unless passed
