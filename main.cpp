#include "mpi.h"
#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int myRank{}, worldSize{};
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    char msg[100];
    sprintf(msg, "Hi, I am CPU %d!", myRank);
    MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, (myRank + 1) % worldSize, 0, MPI_COMM_WORLD);

    MPI_Status status;
    MPI_Recv(msg, 100, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    cout << "\nI am CPU " << myRank << ". The CPU " << status.MPI_SOURCE << " told me: " << msg 
         << "\nStatus.MPI_SOURCE = " << status.MPI_SOURCE
         << "\nStatus.MPI_TAG = "<< status.MPI_TAG
         << "\nStatus.MPI_ERROR = "<< status.MPI_ERROR << endl;

    MPI_Finalize();
    return 0;
}