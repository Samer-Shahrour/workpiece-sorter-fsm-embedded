#!/bin/bash

git add -A
git commit -m "${*}"
git checkout master
git pull --tags origin master
git merge dev
git add -A
git commit -m "${*} ; (auto-)merged"
git push --tags -u origin master
git checkout dev
git merge master
