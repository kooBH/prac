#! /bin/sh

# ex
# ./import_tar.sh hpx_setup.tar

name=$(echo $1 | cut -d "." -f1)
echo $name
cat $1 | docker import - $name:new
