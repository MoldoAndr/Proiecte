#pragma once
#include <string>
#include <cctype>
class EfectSpecial
{
public:
	EfectSpecial(std::string_view, std::string_view);
	std::string_view	efectVizual() const { return m_efectVizual; }
	std::string_view	efectSonor() const { return m_efectSonor; }

private:
	std::string			m_efectVizual{};
	std::string			m_efectSonor{};
};

