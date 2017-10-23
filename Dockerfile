FROM alpine:3.5

ADD . /src

WORKDIR /src

RUN runtime_deps='libstdc++' \
    && apk add --virtual .build-dependencies --no-cache scons build-base \
    && scons install \
    && rm -Rf build \
    && apk del .build-dependencies \
    && apk add --no-cache $runtime_deps
