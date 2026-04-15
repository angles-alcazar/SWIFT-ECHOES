#!/bin/bash
set -e

function usage() {
    cat <<EOF
Usage:
  -d, --debug   build SWIFT with debug information
  -o, --opt     build SWIFT with optimizations on
  -h, --help    show this message
EOF
}

PARMETIS=/mnt/home/ssutherland/codes/libs/parmetis/
ONETBB=/mnt/home/ssutherland/codes/libs/oneTBB/
FLAGS="--enable-fof --with-black-holes=ECHOES --enable-optimization=no --with-hydro=sphenix --with-tbbmalloc=${ONETBB} --enable-mpi=no --with-metis=${PARMETIS}"

for a in "$@"; do
    case $a in
        -d|--debug)
            FLAGS="$FLAGS --enable-debug=yes --enable-debugging-checks"
            ;;
        -o|--opt)
            FLAGS="$FLAGS --enable-optimization=yes --with-gcc-arch=native"
            ;;
        --mpi)
            FLAGS="$FLAGS --enable-mpi=yes --with-parmetis=${PARMETIS}"
            MPI=y
            ;;
        -h|--help)
            usage
            exit 2
            ;;
        *)
            FLAGS="$FLAGS $a"
            ;;
    esac
done

if [ $MPI ]; then
    module load modules/2.3-20240529
    module load gcc/11.4.0
    module load openmpi/4.0.7
    module load hdf5/mpi-1.12.3
    module load gsl/2.7.1
    module load fftw/mpi-3.3.10
    export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/mnt/home/ssutherland/codes/libs/parmetis/"
else
    module load modules/2.3-20240529
    module load gcc/11.4.0
    module load hdf5/1.12.3
    module load gsl/2.7.1
    module load fftw/3.3.10
    export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/mnt/home/ssutherland/codes/libs/parmetis/"
fi

./autogen.sh
./configure $FLAGS
make clean
make "-j$(nproc)"
