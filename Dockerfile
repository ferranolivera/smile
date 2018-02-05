FROM         ubuntu:16.04 
MAINTAINER   Arnau Prat <arnau.prat@gmail.com>
CMD          bash

RUN mkdir -p /home/user
WORKDIR /home/user 

ADD src ./src 
ADD CMakeLists.txt ./
ADD cmake ./cmake 

RUN mkdir build 

# Required system packages
RUN apt-get install -y gcc cmake numactl make libboost1.58-all-dev  
