FROM alpine:3.3

RUN apk add --no-cache scons build-base mesa-dev freeglut-dev

ADD . /src

WORKDIR /src

RUN scons install
