# use the ubuntu base image
FROM ubuntu:latest
#FROM kmanna/nat-router
# Router 1
RUN apt-get update

RUN apt-get install iptables -y

WORKDIR /router1

COPY ./script.sh ./

RUN chmod 755 /router1/script.sh

USER root
#ENTRYPOINT
#ENTRYPOINT ["/bin/bash", "/home/script.sh"]


ENTRYPOINT [ "/router1/script.sh" ] 

#CMD [ "tail" , "-f", "/dev/null" ]