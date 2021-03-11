# Use docker images with all the stuff and spack installed
FROM scicellxx-spack0.16.0-base-all:0.1 as builder

# Bare OS image to run the installed executables
FROM ubuntu:18.04

RUN apt-get -yqq update && apt-get -yqq upgrade \
 && apt-get -yqq install build-essential less nano \
 && apt-get autoremove --purge \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

COPY --from=builder /opt/spack-environment /opt/spack-environment
COPY --from=builder /opt/software /opt/software
COPY --from=builder /opt/view /opt/view
COPY --from=builder /etc/profile.d/z10_spack_environment.sh /etc/profile.d/z10_spack_environment.sh

ENTRYPOINT ["/bin/bash", "--rcfile", "/etc/profile", "-l"]