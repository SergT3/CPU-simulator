#pragma once
#include <set>
#include <string>
#include "alu.h"
#include "ram.h"



class my_cpu
{
	std::set<std::string> alu_instruction_set_ = { "ADD", "SUB", "SHL", "SHR" };
	std::set<std::string> cpu_instruction_set_ = {"PUSH", "POP", "JMP", "JZ","JNZ", "JL"};
	//registers
	int pc_;
	int mar_;
	std::string mdr_;
	std::string ir_;
	int acc_;
	//components	
	alu alu_;
	ram ram_;



public:
	my_cpu();
	~my_cpu() = default;
	my_cpu(my_cpu&) = default;
	my_cpu(my_cpu&&) = default;
	my_cpu& operator=(my_cpu const&) = default;
	my_cpu& operator=(my_cpu&&) = default;
	void start();
	void execute(const std::string& instruction);
	bool is_instruction(const std::string& mdr) const;
	bool is_alu_instruction(const std::string& mdr) const;
	bool is_cpu_instruction(const std::string& mdr) const;

};