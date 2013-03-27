#!/bin/bash
#sudo apt-get -y install git
#exit
#sudo apt-get install openssh-server
#default-jre
pwd
cd ~
touch test_in_home_of_root
export user=$(whoami)
echo $user
if [ -d "/vagrant" ]; then
    echo 'This script is running in vagrant'
export user=$(whoami)
echo $user
su -c "/vagrant/setup_emscripten_with_shedskin.sh" -s /bin/sh vagrant
fi
exit

