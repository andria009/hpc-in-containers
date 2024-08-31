# HPC-In-Containers

## Prerequisites

Before creating your own HPC in containers, you need to have:
- [Docker](https://www.docker.com)
- [Docker-compose](https://docs.docker.com/compose/)

## Start your HPC in containers

1. Clone [this repository](https://github.com/andria009/hpc-in-containers.git)

2. Build image
    ```[user@host hpc-in-containers]$ docker-compose build```

3. Start containers
    ```[user@host hpc-in-containers]$ docker-compose up -d```

4. Login to one of the containers
    ```[user@host hpc-in-containers]$ ssh -i ssh-keys/id_rsa -p 2222 grid@localhost```

5. Make sure passwordless ssh is working
    ```[grid@grid1 ~]$ ssh-keyscan -t rsa,ecdsa,ed25519 example.com >> ~/.ssh/known_hosts```

6. Run sample programs
    6.1 MPI Programming
        - Compile
        ```[grid@grid1 data]$ mpicc -o mpi_hello_world mpi_hello_world.c```
        - Execute
        ```[grid@grid1 data]$ mpirun -np 4 -hostfile hostfile mpi_hello_world```
    
    6.2 OpenMP Programming
    - Compile
        ```[grid@grid1 data]$ gcc -fopenmp -o openmp_hello_world openmp_hello_world.c```
    - Execute
        ```[grid@grid1 data]$ ./openmp_hello_world```
    
    6.3 Hybrid (OpenMP and MPI) Programming
    - Compile
        ```[grid@grid1 data]$ mpicc -fopenmp -o openmp_mpi_hello_world openmp_mpi_hello_world.c```
    - Execute
        ```[grid@grid1 data]$ mpirun -np 4 -hostfile hostfile openmp_mpi_hello_world```

7. Stop containers
    ```[user@host hpc-in-containers]$ docker-compose down```