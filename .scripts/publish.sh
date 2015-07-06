#!/bin/bash
# -*- mode: bash; tab-width: 2; -*-
# vim: ts=2 sw=8 ft=bash noet

detect_platform() {
  if [ $(uname | grep 'SunOS') ]; then
    echo "SmartOS"
  elif [ $(uname | grep 'Linux') ]; then
    echo "Linux"
  fi    
}

publish_file() {
  secret=$1
  user=$2
  project=$3
  platform=$4
  file=$5
  echo $file
  curl \
    -X POST \
    -H "Key: ${secret}" \
    --data-binary \@/content/packages/pkgsrc/${project}/${platform}/All/${file} \
    https://pkgsrc.nanobox.io/${user}/${project}/${platform}/${file}
  echo ""
}

update_summary() {
  secret=$1
  user=$2
  project=$3
  platform=$4
  curl \
    -X PUT \
    -H "Key: ${secret}" \
    pkgsrc.nanobox.io/${user}/${project}/${platform}
}

publish_all() {
  secret=$1
  user=$2
  project=$3
  platform=$4
  uploaded=$(curl -s https://pkgsrc.nanobox.io/${user}/${project}/${platform}/ | sed 's/<a href=".*">//g;s,</a>.*$,,g;s/<.*>//g')
  for file in $(ls /content/packages/pkgsrc/${project}/${platform}/All/*)
  do
    file=$(basename ${file})
    if [[ ! ${uploaded} =~ ${file} ]]
    then
      publish_file ${secret} ${user} ${project} ${platform} ${file}
    fi
  done
  update_summary ${secret} ${user} ${project} ${platform}
}

publish_all ${NANOBOX_SECRET} ${NANOBOX_USER} ${NANOBOX_PROJECT} $(detect_platform)
