#!/bin/sh
rm -rf obj_dir
rm -f counter_challenge.vcd

# run Verilator to translate Verilog into C++, including C++ testbench
verilator -Wall --cc --trace counter_challenge.sv --exe counter_tb_challenge.cpp

# build C++ project via make automatically generated by Verilator
make -j -C obj_dir/ -f Vcounter_challenge.mk Vcounter_challenge

# run executable simulation file
obj_dir/Vcounter_challenge