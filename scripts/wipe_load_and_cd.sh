#!/bin/bash

cd ~;
export BASEDIRECTORY=$(pwd)
rm -rf ~/animation/
rm -rf ~/scripts/
cp -r /vagrant/animation/ ~
cp -r /vagrant/scripts/ ~
cd ~/animation
