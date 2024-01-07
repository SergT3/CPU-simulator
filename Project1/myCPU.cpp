#include "myCPU.h"

#include <cassert>
#include <iostream>

#include "utils.h"

//assigning initial values to registers
my_cpu::my_cpu() : pc_(0), mar_(0), acc_(0), alu_(), ram_(0)
{
	ram_.load_program();
}

bool my_cpu::is_alu_instruction(const std::string& mdr) const
{
	return alu_instruction_set_.find(split(mdr)[0]) != alu_instruction_set_.end();
}

bool my_cpu::is_cpu_instruction(const std::string& mdr) const
{
	return cpu_instruction_set_.find(split(mdr)[0]) != cpu_instruction_set_.end();
}

bool my_cpu::is_instruction(const std::string& mdr) const
{
	return is_alu_instruction(split(mdr)[0]) or is_cpu_instruction(split(mdr)[0]);
}


void my_cpu::execute(const std::string& instruction)
{
	std::vector<std::string> const split_instruction = split(instruction);
	if(split_instruction.size() > 1)
	{
		for(int i = 1; i < split_instruction.size(); ++i)
		{
			try
			{
				int argument = std::stoi(split_instruction[i]);
			}
			catch (std::exception& e)
			{
				throw std::runtime_error("Wrong arguments given to instruction\n");
			}
		}
	}
	if(is_alu_instruction(split_instruction[0]))
	{
		alu_.set_operation(instruction, acc_);
		acc_ = alu_.run();
	}
	else
	{
		if(split_instruction[0] == "PUSH")
		{
			assert(split_instruction.size() <= 2 && !split_instruction.empty());
			switch(split_instruction.size())
			{
			case 1:
				ram_.push(acc_);
				break;
			case 2:
				ram_.push(stoi(split_instruction[1]));
			}
		}
		else if(split_instruction[0] == "POP")
		{
			switch (split_instruction.size())
			{
			case 1:
				acc_ = ram_.pop();
				break;
			default:
				assert(split_instruction.size() == 1);
			}
		}
		else if(split_instruction[0] == "JMP")
		{
			switch (split_instruction.size())
			{
			case 2:
				if (std::stoi(split_instruction[1]) < ram_.last_instr() && std::stoi(split_instruction[1]) > 0)
				{
					pc_ = std::stoi(split_instruction[1]) - 1;
					assert(pc_ + 1 < ram_.last_instr());
				}
				break;
			default:
				assert(split_instruction.size() == 2);
			}
		}
		else if(split_instruction[0] == "JZ")
		{
			switch (split_instruction.size())
			{
			case 2:
				if (acc_ == 0)
				{
					if(std::stoi(split_instruction[1]) < ram_.last_instr() && std::stoi(split_instruction[1]) > 0)
					{
						pc_ = std::stoi(split_instruction[1]) - 1;
						assert(pc_ + 1 < ram_.last_instr());
					}
				}
				break;
			default:
				assert(split_instruction.size() == 2);
			}
		}
		else if (split_instruction[0] == "JNZ")
		{
			switch (split_instruction.size())
			{
			case 2:
				if (acc_ != 0)
				{
					if (std::stoi(split_instruction[1]) < ram_.last_instr() && std::stoi(split_instruction[1]) > 0)
					{
						pc_ = std::stoi(split_instruction[1]) - 1;
						assert(pc_ + 1 < ram_.last_instr());
					}
				}
				break;
			default:
				assert(split_instruction.size() == 2);
			}
		}
		else if (split_instruction[0] == "JL")
		{
			switch (split_instruction.size())
			{
			case 3:
				if (acc_ < std::stoi(split_instruction[1]))
				{
					if (std::stoi(split_instruction[1]) < ram_.last_instr() && std::stoi(split_instruction[1]) > 0)
					{
						pc_ = std::stoi(split_instruction[2]) - 1;
						assert(pc_ + 1 < ram_.last_instr());
					}
				}
				break;
			default:
				assert(split_instruction.size() == 3);
			}
		}
	}

}


void my_cpu::start()
{
	while(pc_ < ram_.last_instr())
	{
		mdr_ = ram_.read(pc_);
		if (is_instruction(mdr_))
		{
			ir_ = mdr_;
			mar_ = pc_;
		}
		else
		{
			ir_ = "";
		}

		
		if (not ir_.empty())
		{
			execute(ir_);
			std::cout << acc_ << "\n";
			
		}

		if (pc_ + 1 == ram_.last_instr())
		{
			ram_.stack_to_file();
		}

		++pc_;
	}
}






