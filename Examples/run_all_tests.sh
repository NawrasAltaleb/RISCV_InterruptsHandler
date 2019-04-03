#!/bin/bash
export SYSTEMC_DISABLE_COPYRIGHT_MESSAGE=1
export PROJECT_DIR=$HOME/Projects/RISCV_InterruptsHandler

echo -e "\e[30;48;5;82mCreate the elf files\e[0m";
cd ${PROJECT_DIR}/Examples/Instruction_Tests
make
cd ${PROJECT_DIR}/Examples/Mini_Programs
make
cd ${PROJECT_DIR}/Examples/Mini_Programs/BubbleSort_c
make
cd ${PROJECT_DIR}/Examples/Mini_Programs/Fibonacci_c
make
cd ${PROJECT_DIR}/Examples/Mini_Programs/Prime_c
make
echo -e "\e[30;48;5;82mFinished creating the elf files\e[0m";

#Running Instruction_Tests
echo -e "\e[30;48;5;82mRunning tests for each instruction\e[0m";
for f in ${PROJECT_DIR}/Examples/Instruction_Tests/*.elf  ;
do
    "${PROJECT_DIR}/bin/RISCV_test" "$f"
done

#Running Programs Tests
echo -e "\e[30;48;5;82mRunning Programs Tests\e[0m";
for f in ${PROJECT_DIR}/Examples/Mini_Programs/*.elf ;
do
    "${PROJECT_DIR}/bin/RISCV_test" "$f"
done


#Running Special Programs Tests
echo -e "\e[30;48;5;82mRunning Special Programs Tests\e[0m";
for f in ${PROJECT_DIR}/Examples/Mini_Programs/*/*.elf ;
do
    "${PROJECT_DIR}/bin/RISCV_test" "$f"
done


#DELETE generated elf ans asm files
echo -e "\e[30;48;5;82mDeleting generated elf and asm files\e[0m";
cd ${PROJECT_DIR}/Examples/Instruction_Tests
make clean
cd ${PROJECT_DIR}/Examples/Mini_Programs
make clean
cd ${PROJECT_DIR}/Examples/Mini_Programs/BubbleSort_c
make clean
cd ${PROJECT_DIR}/Examples/Mini_Programs/Fibonacci_c
make clean
cd ${PROJECT_DIR}/Examples/Mini_Programs/Prime_c
make clean

echo -e "\e[30;48;5;82mDone!\e[0m";
