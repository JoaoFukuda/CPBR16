FROM ubuntu AS builder

FROM pwn.red/jail
COPY --from=builder / /srv/
RUN mkdir -p /srv/app/
COPY flag /srv/app/flag
COPY desafio /srv/app/run
