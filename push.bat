@echo off

echo git add *
git add *

set /P message="commit message : "
echo git commit -m "%message%"
git commit -m "%message%"

git push