# Install additional dependencies in case of osx environment
if [ ${TRAVIS_OS_NAME} = "osx" ]; then
    brew update
    brew install scons
fi

