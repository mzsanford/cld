
# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

cpp_command('g++')

$CFLAGS << ' -DCLD_WINDOWS ' << `pkg-config --cflags cld`.chomp
$LDFLAGS << `pkg-config --libs cld`.chomp

# The destination
dir_config('cld')

## C++ cld entry point?
have_library('cld')

# Do the work
create_makefile('cld_native')
