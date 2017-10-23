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

# compile_shared_source_message = '%sCompiling shared       %s$SOURCE%s' % \
compile_shared_source_message = '%sCompiling shared       %s$SOURCE%s $SHCCCOM $SHCXXCOM' % \
   (colors['blue'], colors['green'], colors['end'])

link_program_message = '%sLinking Program        %s$TARGET%s' % \
   (colors['blue'], colors['cyan'], colors['end'])

# link_library_message = '%sLinking Static Library %s$TARGET%s' % \
link_library_message = '%sLinking Static Library %s$TARGET%s: $LINKCOM' % \
   (colors['blue'], colors['cyan'], colors['end'])

# link_shared_library_message = '%sLinking Shared Library %s$TARGET%s' % \
link_shared_library_message = '%sLinking Shared Library %s$TARGET%s: $SHLINKCOM' % \
   (colors['blue'], colors['cyan'], colors['end'])


env = Environment()

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
    ],
    CFLAGS = [
        '-Wall',
        '-fPIC',
        '-m64',
    ],
    CXXFLAGS = [
        '-Wall',
        '-fPIC',
        '-m64',
        '-std=c++11',
        '-std=c++0x',
        '-DMEDIAIO_VERSION_MAJOR=' + mediaioVersionMajor,
        '-DMEDIAIO_VERSION_MINOR=' + mediaioVersionMinor,
        '-DMEDIAIO_VERSION_MICRO=' + mediaioVersionMicro,
    ],
    LINKFLAGS = [
        '-m64',
    ],
    LIBPATH = [
        '#src',
    ],
    SHLIBVERSION = mediaioVersionStr,
)

Export('env')

VariantDir('build/' + buildMode + '/src', 'src', duplicate = 0)
VariantDir('build/' + buildMode + '/app', 'app', duplicate = 0)

SConscript('src/SConscript', variant_dir = 'build/' + buildMode + '/src')
SConscript('app/SConscript', variant_dir = 'build/' + buildMode + '/app')
