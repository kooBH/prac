#! /bin/sh

#docker commit $1 $2
#docker save -o $2.tar $(docker images -q $2)
docker export $1 > $1.tar


