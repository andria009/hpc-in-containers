# Use AlmaLinux as the base image
FROM almalinux:latest

# Install necessary packages including OpenMPI, SSH, and development tools
RUN yum -y update && \
    yum -y install openssh-server openssh-clients sudo wget && \
    yum -y install openmpi openmpi-devel && \
    yum -y install java-17-openjdk-devel && \
    yum -y install python3 python3-pip wget gcc gcc-c++ make cmake git && \
    yum clean all

# Install Miniconda
RUN wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O /tmp/miniconda.sh && \
    bash /tmp/miniconda.sh -b -p /opt/conda && \
    rm /tmp/miniconda.sh

# Add conda to PATH
ENV PATH="/opt/conda/bin:${PATH}"

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
RUN mkdir -p /home/grid/.ssh && \
    chmod 600 /home/grid/.ssh/authorized_keys && \
    chmod 600 /home/grid/.ssh/id_rsa && \
    chmod 700 /home/grid/.ssh && \
    chown grid:grid -R /home/grid/.ssh

# Configure OpenMPI environment
RUN echo "export PATH=/usr/lib64/openmpi/bin:\$PATH" >> /home/grid/.bashrc && \
    echo "export LD_LIBRARY_PATH=/usr/lib64/openmpi/lib:\$LD_LIBRARY_PATH" >> /home/grid/.bashrc && \
    echo "export OMPI_MCA_pml=ob1" >> /home/grid/.bashrc && \
    echo "export OMPI_MCA_btl=tcp,self,vader" >> /home/grid/.bashrc && \
    echo "export OMPI_MCA_btl_base_exclude=openib,uct,psm,psm2,ofi" >> /home/grid/.bashrc && \
    echo "export MANPATH=/usr/share/man/openmpi-x86_64:\$MANPATH" >> /home/grid/.bashrc && \
    echo "export JAVA_HOME=/usr/bin/java" >> /home/grid/.bashrc && \
    echo "export CLASSPATH=.:/home/grid/data/CLASSPATH"

# Install Jupyter Lab and xeus-cling
RUN conda install -y -c conda-forge jupyterlab xeus-cling

# Create a directory for Jupyter notebooks
RUN mkdir /home/grid/data && \
    chown grid:grid /home/grid/data

# Switch to the grid user
USER grid

# Expose SSH and Jupyter Lab ports
EXPOSE 22 8888

# Start SSH service and Jupyter Lab
CMD sudo /usr/sbin/sshd && \
    jupyter lab --ip=0.0.0.0 --no-browser --allow-root --ServerApp.token='' --ServerApp.password='' \
    --notebook-dir='/home/grid/data' --ServerApp.allow_remote_access=True