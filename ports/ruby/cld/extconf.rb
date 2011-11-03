
# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

cpp_command('g++')

$CFLAGS << ' -DCLD_WINDOWS '
$LDFLAGS << ' -lcld '


# Give it a name
extension_name = 'cld'

# The destination
dir_config(extension_name)

## C++ cld entry point?
# have_library('cld')

# Do the work
create_makefile(extension_name)
