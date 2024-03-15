#pragma once

#include "Scenariu.h"
#include "Random.h"
#include "EfectSpecial.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <string_view>
#include <utility>


class Actor;

class FileManager
{
public:

	enum class TipCadru
	{
		Verbe,
		Nume,
		ElementeNaturale,
		MomenteZi,
		StareVreme,
	};

	enum class TipAngajat
	{
		Scenarist,
		Regizor,
		Producator,
		Director
	};

	static	FileManager&		fileManager();
	static	void				distruge();
								
	void						organizareScene(Scenariu&, std::string);
	void						citireActori(Scenariu&, std::string, size_t);
	bool						esteNume(const std::string&);
	bool						esteVerb(const std::string&);
	std::string&				extrageElementNatural();
	std::string&				extrageMomentZi();
	std::string&				extrageStareVreme();
	EfectSpecial*				extrageEfectSpecial(std::pair<std::string, double>);
	void						citireFirNarativ(Scenariu&, std::string);
								
private:						
	static inline				FileManager* s_instance{ nullptr };
	FileManager()					
	{								
	}								
	FileManager(const FileManager&)	
	{								
	}								
	~FileManager()					
	{								
	}								

	std::vector<std::string>	verbePosibile;
	std::vector<std::string>	numePosibile;
	std::vector<std::string>	elementeNaturale;
	std::vector<std::string>	momenteZi;
	std::vector<std::string>	stariVreme;

	std::vector<std::string>	citire(TipCadru);
};