#!/bin/sh
CMD='ninja'

mkdir -p release && cd release
cmake --preset release ..
${CMD}
