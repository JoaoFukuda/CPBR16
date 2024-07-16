FROM ubuntu

RUN apt update && apt install -y openssh-server

RUN useradd -m guest
RUN mkdir -p /home/guest/.ssh/
COPY id_rsa.pub /home/guest/.ssh/authorized_keys

COPY desafio /home/guest/desafio
COPY motd /motd
COPY flag /flag
RUN chmod u+s /home/guest/desafio
RUN chmod go-r /flag
RUN chown 1001 /motd

USER guest
RUN ln -s /motd /home/guest/motd

USER root
RUN mkdir -p /run/sshd/
CMD ["/usr/sbin/sshd", "-D"]
