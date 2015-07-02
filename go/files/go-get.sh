#!/bin/bash
#
# Due to a bug in Go, you can't `go get` a private Bitbucket repository
# (issue #5375, linked below). This means you can't `go get ./...` ANY project
# that might depend on a private Bitbucket repository.
#
# This script works around it by detecting Bitbucket imports and using
# `git` directly to clone into it. This will not work if you use private
# Mercurial repositories on Bitbucket.
#
# To use this, just call it as if it is `go get`. Example: "./get.sh ./..."
#
# Go issue: https://code.google.com/p/go/issues/detail?id=5375
 
# This file will be our "set" data structure.
SETFILE=$(mktemp -t hcXXXXX)
 
# Support both Darwin and Linux so we have to determine what sed flags to use
SEDFLAGS=""
case $OSTYPE in
    darwin*)
        SEDFLAGS="-E"
        ;;
    *)
        SEDFLAGS="-E"
        ;;
esac
 
# This gets a single dependency.
function get {
    case "$1" in
        bitbucket*)
            local repo=$(echo $1 | \
                sed ${SEDFLAGS} \
                -e 's/^bitbucket.org\/([^\/]+)\/([^\/]+).*$/git@bitbucket.org:\1\/\2.git/')
            local dst=$(echo $1 | sed ${SEDFLAGS} -e 's/^(bitbucket.org\/[^\/]+\/[^\/]+).*$/\1/')
            dst="${GOPATH}/src/${dst}"
            echo "+ Bitbucket: $repo"
 
            if [ ! -d "$dst" ]; then
                command="git clone $repo $dst"
                echo $command
                $command
            fi
            ;;
        *)
            echo "+ Getting: $1"
            go get $1
            ;;
    esac
}
 
# This will get all the dependencies for a given package.
function getall {
    local imports=$(go list \
        -f '{{range .Imports}}{{.}} {{end}}' $1/...)
    local testImports=$(go list \
        -f '{{range .TestImports}}{{.}} {{end}}' $1/...)
    imports="${imports} ${testImports}"
 
    for import in $imports; do
        case $import in
            *.biz*|*.com*|*.org*)
                ;;
            *)
                continue
                ;;
        esac
 
        # Verify that we haven't processed this import yet
        cat $SETFILE | grep "^${import}$" >/dev/null 2>&1
        if [ $? -eq 0 ]; then
            continue
        fi
 
        # Add the import to our set file so we don't do it again
        echo $import >>${SETFILE}
 
        # If we're importing "C" then it is cgo, and don't worry about that
        if [ "$import" = "C" ]; then
            continue
        fi
 
        # Get the import and then recurse into it
        get $import
        getall $import
    done
}
 
getall $1