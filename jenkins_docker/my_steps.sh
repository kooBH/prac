#! /bin/sh

# 일단 이거 따라함
# https://hub.docker.com/_/jenkins 

# 도커 이미지 받기
sudo docker pull jenkins

sudo -b docker run -8080:8080 -p 50000:50000 jenkins

# password 이거라 뜸

# 6576a27feb7c46edb1d099c11af0bb2f
# 또는 여기서 찾을 수 있다고함
# /var/jenkins_home/secrets/initialAdminPassword






