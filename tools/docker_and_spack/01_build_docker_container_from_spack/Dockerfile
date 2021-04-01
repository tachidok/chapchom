# Build stage with scicellxx-spack-base:0.16.0
FROM scicellxx-spack-base:0.16.0 as builder

# Copy the spack.yaml file with the specs into the container
COPY spack.yaml /opt/spack-environment/spack.yaml

# Install the software, remove unnecessary deps
RUN cd /opt/spack-environment && spack env activate . && spack install --fail-fast

# Modifications to the environment that are necessary to run
RUN cd /opt/spack-environment && \
    spack env activate --sh -d . >> /etc/profile.d/z10_spack_environment.sh

ENTRYPOINT ["/bin/bash", "--rcfile", "/etc/profile", "-l"]