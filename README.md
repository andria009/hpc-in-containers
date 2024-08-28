# HPC in Containers

## Build images
```[user@host hpc-in-containers]$ docker-compose build```

## Start containers
```[user@host hpc-in-containers]$ docker-compose up -d```

### Login to one of the containers
```[user@host hpc-in-containers]$ ssh -i ssh-keys/id_rsa -p 2222 grid@localhost```

#### make sure passwordless ssh is working
```[grid@grid1 ~]$ ssh-keyscan -t rsa,ecdsa,ed25519 example.com >> ~/.ssh/known_hosts```

## MPI Programming
### Compile
```[grid@grid1 data]$ mpicc -o mpi_hello_world mpi_hello_world.c```

### Execute
```[grid@grid1 data]$ mpirun -np 4 -hostfile hostfile mpi_hello_world```

> 

## OpenMP Programming
### Compile
```[grid@grid1 data]$ gcc -fopenmp -o openmp_hello_world openmp_hello_world.c```

### Execute
```[grid@grid1 data]$ ./openmp_hello_world```

## OpenMP and MPI Programming
### Compile
```[grid@grid1 data]$ mpicc -fopenmp -o openmp_mpi_hello_world openmp_mpi_hello_world.c```

### Execute
```[grid@grid1 data]$ mpirun -np 4 -hostfile hostfile openmp_mpi_hello_world```

## Stop containers
```[user@host hpc-in-containers]$ docker-compose down```