#include "alu.h"

#include <cassert>
#include <iostream>
#include <string>
#include "utils.h"


int alu::run() const
{
	//add
	//sub
	//<<
	//>>
	switch (operation_)
	{
	case add:
		return operand1_ + operand2_;
	case sub:
		return operand1_ - operand2_;
	case shl:
		return operand1_ << 1;
	case shr:
		return operand1_ >> 1;
	default:
		return operand1_;
	}
}

void alu::set_operation(const std::string& instruction, int const& acc)
{
	std::vector<std::string> const split_instruction = split(instruction);
	switch(split_instruction.size())
	{
	case 1:
		assert(not split_instruction.empty() && split_instruction.size() <= 3);
		break;
	case 2:
		operand1_ = acc;
		operand2_ = stoi(split_instruction[1], nullptr, 10);
		break;
	case 3:
		operand1_ = stoi(split_instruction[1], nullptr, 10);
		operand2_ = stoi(split_instruction[2], nullptr, 10);
		break;
	}
	if(split_instruction[0] == "ADD")
	{
		operation_ = add;
	}
	else if(split_instruction[0] == "SUB")
	{
		operation_ = sub;
	}
	else if (split_instruction[0] == "SHL")
	{
		operation_ = shl;
	}
	else if (split_instruction[0] == "SHR")
	{
		operation_ = shr;
	}
}



