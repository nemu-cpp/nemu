FROM nemuframework/alpine-nemu-cpp:0.12.0 as build

ADD build/ build/
ADD src/ src/
RUN cd build/gnumake && make

FROM alpine:3.15.4

RUN apk add libgcc
RUN apk add libstdc++

COPY --from=build /bin/NemuHelloWorldServer /usr/local/bin/NemuHelloWorldServer

ENTRYPOINT ["/usr/local/bin/NemuHelloWorldServer"]
