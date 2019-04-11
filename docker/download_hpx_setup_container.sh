#! /bin/sh

FILEID=1aM_vfM13BrkIlIIqc7oHHnb8sN_d3cjG
FILENAME=hpx_setup.tar 

wget --load-cookies /tmp/cookies.txt "https://docs.google.com/uc?export=download&confirm=$(wget --quiet --save-cookies /tmp/cookies.txt --keep-session-cookies --no-check-certificate 'https://docs.google.com/uc?export=download&id='$FILEID -O- | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')&id="$FILEID -O $FILENAME && rm -rf /tmp/cookies.txt
