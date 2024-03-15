#include "Dungeon_Master.h"
#include "Logger.h"
#include "IExceptie.h"
#include <Windows.h>

void play_game()
{
	try
	{
		Dungeon_Master& master{ Dungeon_Master::get_instance() };
		master.creare_scenariu();
		master.incepe_aventura();
	}
	catch (IExceptie& EXC)
	{
		Logger::get_instance().log_data("logfile.txt",EXC.what());
	}
	Logger::destroy_instance();
	Dungeon_Master::destroy_instance();
}