#!/bin/sh
set -Eeuxo pipefail # https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/

pushd .
trap "popd" EXIT HUP INT QUIT TERM

CUR_GIT_ROOT=$(git rev-parse --show-toplevel)

find $CUR_GIT_ROOT/res/images -name '*.png' -exec mogrify -verbose {} \;

popd >& /dev/null
