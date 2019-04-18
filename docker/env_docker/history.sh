#! /bsh/sh

docker pull rikorose/gcc-cmake:latest

docker run --name="iip_demo_env" -it rikorose/gcc-cmake:latest /bin/bash
apt-get update
apt-get install libasound2-dev
exit

docker login
..
..
docker commit iip_demo_env iip_demo_env
docker tag iip_demo_env koobh/iip_demo_env
docker push koobh/iip_demo_env
