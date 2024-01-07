#pragma once
#include <bitset>
#include <string>
#include <vector>


class ram
{
    std::vector<std::string> instr_memory_;
    std::vector<std::bitset<32>> stack_;


public:
    int last_instr() const;
    std::string read(int address) const;
    void push(int const& value);
    int pop();
    explicit ram(int const size);
    void load_program();
    void stack_to_file() const;
    
};


