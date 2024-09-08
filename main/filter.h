#pragma once

#include <vector>
#include <cstdint>

class WindowFilter {
public:
    WindowFilter(uint8_t depth); 
    void add(int value);
    int getFilteredValue(void) const;
    uint8_t getSize() const;

private:
    uint8_t m_depth;
    std::vector<int> m_buffer;
};