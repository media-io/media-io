import os
import sys

EnsureSConsVersion(2, 3, 0)

mediaioVersionMajor = "0"
mediaioVersionMinor = "0"
mediaioVersionMicro = "1"

mediaioVersion = [
    mediaioVersionMajor,
    mediaioVersionMinor,
    mediaioVersionMicro
]

mediaioVersionStr = ".".join(mediaioVersion)

buildMode = ARGUMENTS.get('mode', 'release')
if not (buildMode in ['debug', 'release']):
    raise Exception("Can't select build mode ['debug', 'release']")

external_include_paths=[]
external_lib_paths=[]

def add_and_parse_library_option(library_name, include=['include'], lib=['lib']):
    AddOption(
        '--' + library_name,
        dest=library_name,
        type='string',
        nargs=1,
        action='store',
        metavar='DIR',
        help='Path to root of ' + library_name + ' library.'
    )

    library_root = GetOption(library_name)
    if(library_root):
        for sub_dir in include:
            external_include_paths.append(os.path.join(library_root, sub_dir))
        for sub_dir in lib:
            external_lib_paths.append(os.path.join(library_root, sub_dir))

add_and_parse_library_option('SDL2')

colors = {}
colors['cyan']   = '\033[96m'
colors['purple'] = '\033[95m'
colors['blue']   = '\033[94m'
colors['green']  = '\033[92m'
colors['yellow'] = '\033[93m'
colors['red']    = '\033[91m'
colors['end']    = '\033[0m'

# If the output is not a terminal, remove the colors
if not sys.stdout.isatty():
   for key, value in colors.iteritems():
      colors[key] = ''

compile_source_message = '%sCompiling              %s$SOURCE%s' % \
   (colors['blue'], colors['green'], colors['end'])

compile_shared_source_message = '%sCompiling shared       %s$SOURCE%s' % \
   (colors['blue'], colors['green'], colors['end'])

link_program_message = '%sLinking Program        %s$TARGET%s' % \
   (colors['blue'], colors['cyan'], colors['end'])

link_library_message = '%sLinking Static Library %s$TARGET%s' % \
   (colors['blue'], colors['cyan'], colors['end'])

link_shared_library_message = '%sLinking Shared Library %s$TARGET%s' % \
   (colors['blue'], colors['cyan'], colors['end'])

env = Environment()

if 'TERM' in os.environ:
    env['ENV']['TERM'] = os.environ['TERM']

env.Append(
    CXXCOMSTR = compile_source_message,
    CCCOMSTR = compile_source_message,
    SHCCCOMSTR = compile_shared_source_message,
    SHCXXCOMSTR = compile_shared_source_message,
    ARCOMSTR = link_library_message,
    SHLINKCOMSTR = link_shared_library_message,
    LINKCOMSTR = link_program_message,
    CPPPATH = [
        '#src',
        '/usr/local/include/',
        external_include_paths,
    ],
    CXXFLAGS = [
        '-Wall',
        '-fPIC',
        '-std=c++11',
        '-std=c++0x',
        '-DMEDIAIO_VERSION_MAJOR=' + mediaioVersionMajor,
        '-DMEDIAIO_VERSION_MINOR=' + mediaioVersionMinor,
        '-DMEDIAIO_VERSION_MICRO=' + mediaioVersionMicro,
    ],
    LIBPATH = [
        '#src',
        '/usr/local/lib/',
        external_lib_paths,
    ],
    SHLIBVERSION = mediaioVersionStr,
)

conf = Configure(env)

Export('env')
Export('conf')

VariantDir('build/' + buildMode + '/src', 'src', duplicate = 0)
VariantDir('build/' + buildMode + '/app', 'app', duplicate = 0)

SConscript('src/SConscript', variant_dir = 'build/' + buildMode + '/src')
SConscript('app/SConscript', variant_dir = 'build/' + buildMode + '/app')
