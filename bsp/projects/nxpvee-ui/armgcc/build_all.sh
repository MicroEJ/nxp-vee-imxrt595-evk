#!/bin/sh
CMD='ninja'

mkdir -p debug && cd debug
cmake --preset debug ..
${CMD}

mkdir -p release && cd release
cmake --preset release ..
${CMD}
