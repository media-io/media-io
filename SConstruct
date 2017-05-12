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

env = Environment()

env.Append(
    CPPPATH = [
        '#src',
        '/usr/local/include/',
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
