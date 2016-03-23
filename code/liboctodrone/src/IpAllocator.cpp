#include "IpAllocator.hpp"

IpAllocator::IpAllocator(int first, int second, int third, int fourth){
	m_first = first;
	m_second = second;
	m_third = third;
	m_fourth = fourth;

	if (m_first < 0 || m_first > 255){
		m_first = 0;
	}
	if (m_second < 0 || m_second > 255){
		m_second = 0;
	}
	if (m_third < 0 || m_third > 255){
		m_third = 0;
	}
	if (m_fourth < 0 || m_fourth > 255){
		m_fourth = 0;
	}
}

std::string IpAllocator::next(){
	std::string output = std::to_string(m_first)
		+ "."
		+ std::to_string(m_second)
		+ "."
		+ std::to_string(m_third)
		+ "."
		+ std::to_string(m_fourth);
	
	m_fourth++;
	if (m_fourth > 255){
		m_third++;
		if (m_third > 255){
			m_second++;
			if (m_second > 255){
				m_first++;
				if (m_first > 255){
					m_first = 0;
					m_second = 0;
					m_third = 0;
					m_fourth = 0;
				}
			}
		}
	}
	return(output);
}
