# Use AlmaLinux as the base image
FROM almalinux:latest

# Install necessary packages including OpenMPI, SSH
RUN yum -y update && \
    yum -y install openssh-server openssh-clients sudo openmpi openmpi-devel python3 python3-pip wget && \
    yum clean all

# Create a common user called 'grid'
RUN useradd -m grid && \
    echo "grid ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Set up SSH
RUN mkdir /var/run/sshd && \
    echo "PasswordAuthentication yes" >> /etc/ssh/sshd_config && \
    echo "PermitRootLogin no" >> /etc/ssh/sshd_config && \
    ssh-keygen -A

# Copy SSH keys (Assume you have a public key to copy)
# Set passwordless SSH for 'grid' user
COPY ssh-keys/id_rsa.pub /home/grid/.ssh/authorized_keys
COPY ssh-keys/id_rsa.pub /home/grid/.ssh/id_rsa.pub
COPY ssh-keys/id_rsa /home/grid/.ssh/id_rsa
RUN mkdir -p /home/grid/.ssh
RUN chmod 600 /home/grid/.ssh/authorized_keys && \
    chmod 700 /home/grid/.ssh && \
    chown grid:grid -R /home/grid/.ssh

# Configure OpenMPI environment
RUN echo "export PATH=/usr/lib64/openmpi/bin:\$PATH" >> /home/grid/.bashrc && \
    echo "export LD_LIBRARY_PATH=/usr/lib64/openmpi/lib:\$LD_LIBRARY_PATH" >> /home/grid/.bashrc && \
    echo "export OMPI_MCA_pml=ob1" >> /home/grid/.bashrc && \
    echo "export OMPI_MCA_btl=tcp,self,vader" >> /home/grid/.bashrc && \
    echo "export OMPI_MCA_btl_base_exclude=openib,uct,psm,psm2,ofi" >> /home/grid/.bashrc && \
    echo "export MANPATH=/usr/share/man/openmpi-x86_64:\$MANPATH" >> /home/grid/.bashrc

# Expose SSH port
EXPOSE 22 8888

# # Start SSH service
CMD ["/usr/sbin/sshd", "-D"]
