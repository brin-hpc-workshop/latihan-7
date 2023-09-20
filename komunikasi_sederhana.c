// Komunikasi sederhana
// BRIN HPC Workshop 2023

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int rank, size;
  int kirim, terima;

  MPI_Init(&argc, &argv);                // Inisialisasi MPI
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Rank dari proses
  MPI_Comm_size(MPI_COMM_WORLD, &size);  // Total proses

  kirim = rank;
  terima = -1;

  // Inisialisasi array
  int n = 3;
  int* kirim_arr = malloc(n * sizeof(int));
  int* terima_arr = malloc(n * sizeof(int));

  for (int i = 0; i < n; i++) {
    kirim_arr[i] = rank;
    terima_arr[i] = -1;
  }

  if (rank == 0) {
    printf("==== Total process %d\n", size);
  }

  // Kirim data dari rank 0 ke rank 1
  if (rank == 0) {
    MPI_Send(&kirim, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(kirim_arr, n, MPI_INT, 1, 0, MPI_COMM_WORLD);
  } else if (rank == 1) {
    MPI_Recv(&terima, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(terima_arr, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Rank %d menerima data %d dari rank %d\n", rank, terima, 0);
  }
  MPI_Finalize();  // Finalisasi MPI

  return 0;
}