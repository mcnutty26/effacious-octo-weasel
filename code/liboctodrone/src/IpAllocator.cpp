/*
This file is part of octoDrone.

octoDrone is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

octoDrone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with octoDrone.  If not, see <http://www.gnu.org/licenses/>.
*/

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
