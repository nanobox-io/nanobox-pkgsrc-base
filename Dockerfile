# -*- mode: Dockerfile; tab-width: 4;indent-tabs-mode: nil;-*-
# vim: ts=4 sw=4 ft=Dockerfile et: 1
FROM ubuntu

# Create directories
RUN mkdir -p /var/log/gonano

# Install basic things
RUN apt-get update -qq && \
    apt-get -y install openssh-server sudo curl ftp build-essential && \
    apt-get clean all && \
    rm -rf /var/lib/apt/lists/*

RUN curl -L -o /var/tmp/nanoinit_0.0.1_amd64.deb https://github.com/nanopack/nanoinit/releases/download/v0.0.1/nanoinit_0.0.1_amd64.deb && \
    dpkg -i /var/tmp/nanoinit_0.0.1_amd64.deb

RUN mkdir -p /etc/nanoinit.d && \
    echo "#!/bin/bash" > /etc/nanoinit.d/sshd && \
    echo "/usr/sbin/sshd" >> /etc/nanoinit.d/sshd && \
    chmod 755 /etc/nanoinit.d/sshd && \
    mkdir -p /var/run/sshd

# Add vagrant user
RUN useradd --create-home -s /bin/bash vagrant

RUN mkdir -p /home/vagrant/.ssh
RUN echo "ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEA6NF8iallvQVp22WDkTkyrtvp9eWW6A8YVr+kz4TjGYe7gHzIw+niNltGEFHzD8+v1I2YJ6oXevct1YeS0o9HZyN1Q9qgCgzUFtdOKLv6IedplqoPkcmF0aYet2PkEDo3MlTBckFXPITAMzF8dJSIFo9D8HfdOV0IAdx4O7PtixWKn5y2hMNG0zQPyUecp4pzC6kivAIhyfHilFR61RGL+GPXQ2MWZWFYbAGjyiYJnAmCP3NOTd0jMZEnDkbUvxhMmBYSdETk1rRgm+R4LOzFUGaHqHDLKLX+FIPKcF96hrucXzcWyLbIbEgE98OHlnVYCzRdK8jlqm8tehUc9c9WhQ== vagrant insecure public key" > /home/vagrant/.ssh/authorized_keys
RUN chown -R vagrant: /home/vagrant/.ssh
RUN echo -n 'vagrant:vagrant' | chpasswd

# Enable passwordless sudo for the "vagrant" user
RUN mkdir -p /etc/sudoers.d
RUN install -b -m 0440 /dev/null /etc/sudoers.d/vagrant
RUN echo 'vagrant ALL=NOPASSWD: ALL' >> /etc/sudoers.d/vagrant

# Run runit automatically
CMD [ "/bin/nanoinit", "/bin/sleep", "365d" ]
