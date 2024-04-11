#!/bin/bash

git add -A
git commit -m "${*}"
git checkout main
git pull --tags origin main
git merge dev
git add -A
git commit -m "${*} ; (auto-)merged"
git push --tags -u origin main
git checkout dev
git merge main
