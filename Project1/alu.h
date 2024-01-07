#pragma once
#include <string>

class alu
{
	enum instruction { add, sub, shl, shr };
	int operand1_;
	int operand2_;
	int operation_;
public:
	alu() = default;
	~alu() = default;
	alu(alu const &) = default;
	alu(alu&&) = default;
	alu& operator=(alu const &) = default;
	alu& operator=(alu&&) = default;
	void set_operation(const std::string& instruction, int const& acc);
	int run() const;
};

