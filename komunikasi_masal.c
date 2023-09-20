// Komunikasi masal
// BRIN HPC Workshop 2023

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int rank, size;
  int kirim, terima;

  MPI_Init(&argc, &argv);                // Inisialisasi MPI
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Rank dari proses
  MPI_Comm_size(MPI_COMM_WORLD, &size);  // Total proses

  // Inisialisasi array
  int n = size;
  int* kirim_arr = malloc(n * sizeof(int));
  int* terima_arr = malloc(n * sizeof(int));
  int* data_arr = malloc(n * sizeof(int));

  int data = rank;

  for (int i = 0; i < n; i++) {
    kirim_arr[i] = rank;
    terima_arr[i] = -1;
    data_arr[i] = -i;
  }

  if (rank == 0) {
    printf("==== Total process %d\n", size);
  }

  // Broadcast data dari rank 0 ke seluruh proses
  MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
  printf("Bcast: data = %d, rank = %d\n", data, rank);
  MPI_Barrier(MPI_COMM_WORLD);  // Sinkronisasi proses

  // Scatter data dari rank 0 ke seluruh proses
  MPI_Scatter(data_arr, 1, MPI_INT, &data, 1, MPI_INT, 0, MPI_COMM_WORLD);
  printf("Scatter: data = %d, rank = %d\n", data, rank);
  MPI_Barrier(MPI_COMM_WORLD);  // Sinkronisasi proses

  // Gather data dari seluruh proses ke rank 0
  MPI_Gather(&data, 1, MPI_INT, data_arr, 1, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    printf("Gather: data = [");
    for (int i = 0; i < n; i++) {
      printf("%d ", data_arr[i]);
    }
    printf("]\n");
  }
  MPI_Barrier(MPI_COMM_WORLD);  // Sinkronisasi proses

  // Reduce data dari seluruh proses ke rank 0
  MPI_Reduce(&data, &data, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    printf("Reduce: data = %d\n", data);
  }
  MPI_Barrier(MPI_COMM_WORLD);  // Sinkronisasi proses

  MPI_Finalize();  // Finalisasi MPI

  return 0;
}