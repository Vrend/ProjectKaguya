FROM itsthenetwork/alpine-ncat:latest
RUN apk update && apk upgrade
RUN apk add bash bash-completion
COPY scripts/* /wrkdr/
WORKDIR /wrkdr
ENTRYPOINT bash
