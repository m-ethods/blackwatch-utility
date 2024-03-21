// blackwatchutility.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <dpp/dpp.h>

int main()
{
	std::cout << "Token?: ";

	std::string Token;
	std::getline(std::cin, Token);

	dpp::cluster bot(Token);
	bot.on_log(dpp::utility::cout_logger());

	bot.on_slashcommand([](const dpp::slashcommand_t& event) {
		if (event.command.get_command_name() == "hello") {
			event.reply("world");
		}
	});

	bot.on_message_reaction_add([](const dpp::message_reaction_add_t& event) {
		
	});

	bot.on_ready([&bot](const dpp::ready_t& event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			bot.global_command_create(dpp::slashcommand("hello", "hello world", bot.me.id));
		}
	});
	
	bot.start(false);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
