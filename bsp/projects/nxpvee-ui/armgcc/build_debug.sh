#!/bin/sh
CMD='ninja'

mkdir -p debug && cd debug
cmake --preset debug ..
${CMD}
