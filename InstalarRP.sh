#!/bin/bash

echo "INSTALLATION OF ROOT version 6.26/02"
mkdir -p ROOT
chmod 777 ROOT
cd ROOT 

echo "Installation of dependencies"
sudo apt-get install dpkg-dev cmake g++ gcc binutils libx11-dev libxpm-dev libxft-dev python libssl-dev

echo "ROOT package download"
wget https://root.cern/download/root_v6.26.02.Linux-ubuntu20-x86_64-gcc9.4.tar.gz

echo "Unpack the archive"
tar -xzvf root_v6.26.02.Linux-ubuntu20-x86_64-gcc9.4.tar.gz

#Permissions
chmod 777 root
chmod -R 777 root/*

cd ..

echo "INSTALLATION OF PYTHIA 8.307"
mkdir -p PYTHIA
chmod 777 PYTHIA
cd PYTHIA

echo "PYTHIA package download"
wget https://pythia.org/download/pythia83/pythia8307.tgz

echo "Unpack the archive"
tar xvfz pythia8307.tgz

#Permissions
chmod 777 pythia8307
chmod -R 777 pythia8307/*

echo "Installation"
cd pythia8307
./configure
sudo apt install gcc g++ automake
make
sudo make install