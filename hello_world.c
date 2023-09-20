// OpenMPI Hello World
// BRIN HPC Workshop 2023

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int rank, size;

  MPI_Init(&argc, &argv);                // Inisialisasi MPI
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Rank dari proses
  MPI_Comm_size(MPI_COMM_WORLD, &size);  // Total proses

  if (rank == 0) printf("==== Total process %d\n", size);

  // MPI_Barrier(MPI_COMM_WORLD);  // Sinkronisasi proses

  printf("Hello World dari process %d\n", rank);

  MPI_Finalize();  // Finalisasi MPI

  return 0;
}