set -e
RC_PATH=~/.$(echo $SHELL | sed 's#/bin/##')rc
PWD=$(cd $(dirname $0);pwd)
cd ${PWD}
LIB=${PWD}/library

cp -r template/bits /usr/local/include/
pushd $PWD
if [ -d ./ac-library ]; then
    echo "'ac-library' already exists"
else
    git clone https://github.com/atcoder/ac-library.git
fi
ACL=${PWD}/ac-library
popd

if !(type oj-bundle > /dev/null 2>&1); then
    pip3 install online-judge-verify-helper
fi

cat << EOF >> $RC_PATH

function ojcopy() {
    oj-bundle -I "${LIB}" \$1 | sed 's*${LIB}*lib*' | pbcopy
}

EOF
cat << EOF >> $RC_PATH
function ojrun() {
    oj-bundle -I "${LIB}" \$1 | sed 's*${LIB}*lib*' > __tmp.cpp &&\
    g++ -std=c++20 -I "${ACL}" __tmp.cpp -o a &&\
    ./a
}

EOF

cat << EOF >> $RC_PATH
function ojtest() {
    PROBLEM_URL=""
    SRC_PATH=""
    if [ \$# -eq 2 ];then
        PROBLEM_URL=\$1
        SRC_PATH=\$2
    else
        CURRENT=\$(pwd)
        DIR_NAME=\`echo "\$CURRENT" | sed -e 's/.*\/\([^\/]*\)$/\1/'\`
        SRC_PATH=\$1
        PROBLEM_URL="https://atcoder.jp/contests/\${DIR_NAME}/tasks/\${DIR_NAME}_\${SRC_PATH:0:1}"
    fi

    rm -rf test && oj d \$PROBLEM_URL &&\
    oj-bundle -I "${LIB}" \$SRC_PATH | sed 's*${LIB}*lib*' > __tmp.cpp &&    g++ -std=c++20 -I "${ACL}" __tmp.cpp -o a &&    oj t -c "./a" && cat __tmp.cpp | pbcopy
}

EOF

cat << EOF >> $RC_PATH
function ojsub() {
    PROBLEM_URL=""
    SRC_PATH=""
    if [ \$# -eq 2 ];then
        PROBLEM_URL=\$1
        SRC_PATH=\$2
    else
        CURRENT=\$(pwd)
        DIR_NAME=\`echo "\$CURRENT" | sed -e 's/.*\/\([^\/]*\)$/\1/'\`
        SRC_PATH=\$1
        PROBLEM_URL="https://atcoder.jp/contests/\${DIR_NAME}/tasks/\${DIR_NAME}_\${SRC_PATH:0:1}"
    fi

    rm -rf test && oj d \$PROBLEM_URL &&\
    oj-bundle -I "${LIB}" \$SRC_PATH | sed 's*${LIB}*lib*' > __tmp.cpp &&    g++ -std=c++20 -I "${ACL}" __tmp.cpp -o a &&    oj t -c "./a" && oj s \${PROBLEM_URL} __tmp.cpp
}

EOF

cat << EOF >> $RC_PATH
function ojd() {
    rm -rf test &&\
    oj d \$1
}

EOF

cat << EOF >> $RC_PATH
function atc() {
    DIR=${PWD}/src/\$1
    mkdir \${DIR}
    cd \${DIR}

    for i in {a..g}
    do
        cp ${PWD}/template/a.cpp \$i.cpp
    done
}

EOF
echo "source $RC_PATH" | pbcopy
echo 'cmd + v, enter'
