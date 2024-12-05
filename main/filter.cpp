#include "filter.h"
#include <numeric>

WindowFilter::WindowFilter(uint8_t depth)
  : m_depth(depth) {
  m_buffer.reserve(this->m_depth);
}

void WindowFilter::add(int value) {
  if (m_depth == 0 || value <= 0) {
    return;
  }

  if (m_buffer.size() == m_depth) {
    m_buffer.erase(m_buffer.begin());
  }

  m_buffer.push_back(value);
}

int WindowFilter::getFilteredValue() const {
  if (m_buffer.empty()) {
    return 0;
  }
  return std::accumulate(m_buffer.begin(), m_buffer.end(), 0) / m_buffer.size();
}

uint8_t WindowFilter::getSize() const {
  return m_buffer.size();
}
