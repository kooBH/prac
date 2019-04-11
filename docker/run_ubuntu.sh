#! /bin/sh
# 단순 실행
# ubuntu 이미지가 없으면 pull
# 컨테이너가 생성이 안도었으면 create 후
# start
# docker run ubuntu:16.04

# --rm 종료후 컨테이너 자동 삭제
# -it ... /bin/bash 배쉬로 실행
docker run -it ubuntu:16.04 /bin/bash
