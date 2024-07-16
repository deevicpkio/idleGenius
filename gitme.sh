#!/usr/bin/bash

echo -n "Commit description: "
read -r commit_descr

git add .
git status
git commit -m "$commit_descr"
git push origin main
