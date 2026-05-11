FROM alpine:latest
RUN apk add --no-cache build-base valgrind gdb
WORKDIR /app
CMD ["/bin/sh"]