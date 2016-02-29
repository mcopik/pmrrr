#!/usr/bin/env bash

#BSUB -J "MatrixProperties[1-18]"    # job name
#BSUB -o SiSc%J.%I.cout # job output 
#BSUB -W 00:45          # limits in hours:minutes
#BSUB -M 30000           # memory in MB
#BSUB -P aices2          # use lecture queue
#BSUB -n 1
#BSUB -a intelmpi
#BSUB -R model==SandyBridge_EP

### switch to Intel MPI module
module load gcc/4.9
module switch intel intel/16.0
module switch openmpi intelmpi
module load cmake
module load python

### which one array job is this?
echo LSB_JOBINDEX: $LSB_JOBINDEX

cd /home/ts193246/SiScLabPmrrr/pmrrrOutput/EXAMPLES/C/

### run the different matrices
case "$LSB_JOBINDEX" in
    1)
        $MPIEXEC main_all.x matrices/Legendre5001
    ;;
 
    2)
        $MPIEXEC main_all.x matrices/Legendre10001
    ;;
 
    3)
        $MPIEXEC main_all.x matrices/Legendre15001
    ;;
 
    4)
        $MPIEXEC main_all.x matrices/Legendre25001
    ;;
 
    5)
        $MPIEXEC main_all.x matrices/Legendre35001
    ;;
 
    6)
        $MPIEXEC main_all.x matrices/Legendre50001
    ;;
    
    7)
        $MPIEXEC main_all.x matrices/OneTwoOne5001
    ;;
 
    8)
        $MPIEXEC main_all.x matrices/OneTwoOne10001
    ;;
 
    9)
        $MPIEXEC main_all.x matrices/OneTwoOne15001
    ;;
 
    10)
        $MPIEXEC main_all.x matrices/OneTwoOne25001
    ;;
 
    11)
        $MPIEXEC main_all.x matrices/OneTwoOne35001
    ;;

    12)
        $MPIEXEC main_all.x matrices/OneTwoOne50001
    ;;
    
    13)
        $MPIEXEC main_all.x matrices/diamond
    ;;
    
    14)
        $MPIEXEC main_all.x matrices/fann1.ex.new
    ;;
    
    15)
        $MPIEXEC main_all.x matrices/fann2.ex.new 
    ;;
    
    16)
        $MPIEXEC main_all.x matrices/input.ftn50.new
    ;;
    
    17)
        $MPIEXEC main_all.x matrices/input12387.new 
    ;;

    18)
        $MPIEXEC main_all.x matrices/Wilkinson32001
    ;;
esac

exit
