FROM         ubuntu:16.04 
MAINTAINER   Arnau Prat <arnau.prat@gmail.com>
CMD          bash

RUN mkdir -p /home/user
WORKDIR /home/user 

ADD src ./src 
ADD CMakeLists.txt ./
ADD libs ./libs 

RUN mkdir build 

# Required system packages
RUN apt-get update  
RUN apt-get -y install g++-5 gcc-5 build-essential cmake numactl make libboost1.58-all-dev  
