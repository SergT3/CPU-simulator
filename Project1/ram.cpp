#include "ram.h"

#include <cassert>
#include <fstream>
#include <iostream>



ram::ram(int const size) :
	instr_memory_(size, "NOP") {} // Memory initialized with NOP (no operation)

void ram::load_program()
{
    std::ifstream file;
    file.open("ram.txt");
    if (file.is_open()) 
    {
        std::string line;
        while (std::getline(file, line)) 
        {
            instr_memory_.emplace_back(line);
        }
        file.close();
    }
    else 
    {
        std::cerr << "Unable to open ram.txt\n";
    }
}
void ram::stack_to_file() const
{
    std::vector<std::string> string_stack;
    for (auto i = stack_.begin(); i != stack_.end(); ++i)
    {
        //std::cout << i->to_string();
        string_stack.emplace_back(i->to_string());
    }

    std::ofstream output_file("./stack.txt");
    std::ostream_iterator<std::string> const output_iterator(output_file, "\n");
    std::copy(string_stack.begin(), string_stack.end(), output_iterator);
}
int ram::last_instr() const
{
    return instr_memory_.size();
}

std::string ram::read(int const address) const
{
    std::cout << "Reading instruction at address " << address << "\n";
    assert(address < last_instr() && address >= 0);
    return instr_memory_[address];
}

void ram::push(int const& value)
{
    std::bitset<32> bit_value = value;
    stack_.emplace_back(bit_value);
}

int ram::pop()
{
	int const value = static_cast<int>(stack_.back().to_ulong());
    stack_.pop_back();
    return value;
}
