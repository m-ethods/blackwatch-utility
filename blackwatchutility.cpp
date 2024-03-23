// blackwatchutility.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <dpp/dpp.h>
#include "roblox_ranking.h"

std::vector<std::string> split(const std::string& s, char seperator)
{
	std::vector<std::string> output;
	std::string::size_type prev_pos = 0, pos = 0;

	while ((pos = s.find(seperator, pos)) != std::string::npos)
	{
		std::string substring(s.substr(prev_pos, pos - prev_pos));
		output.push_back(substring);
		prev_pos = ++pos;
	}

	output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word
	return output;
}


int main()
{
	std::cout << "Token?: ";

	std::string Token;
	std::getline(std::cin, Token);

	std::cin.clear();
	std::cout << std::endl << "Roblox Cookie?: ";

	std::string RobloxCookie;
	std::getline(std::cin, RobloxCookie);

	dpp::cluster bot(Token);
	bot.on_log(dpp::utility::cout_logger());

	bot.on_slashcommand([](const dpp::slashcommand_t& event) {
		if (event.command.get_command_name() == "hello") {
			event.reply("world");
		}
	});

	bot.on_message_reaction_add([&bot, &RobloxCookie](const dpp::message_reaction_add_t& event) {
		/*
		Message reaction
		This handles: deleting messages & applications.
		*/

		const dpp::emoji Emoji = event.reacting_emoji;

		if (Emoji.name == "1984" && (event.channel_id != "965597502868955157")) {
			/*
			Delete message if it's a discord moderator.
			*/
			const std::vector<dpp::snowflake> MemberRoles = event.reacting_member.get_roles();
			for (dpp::snowflake Role : MemberRoles) {
				if (Role == "966106827827867759" || Role == "966106629928017940") {
					dpp::message MessageToDelete = bot.message_get_sync(event.message_id, event.channel_id);
					dpp::message Message;
					dpp::embed LogEmbed;

					LogEmbed.title = "MESSAGE MODERATED";
					LogEmbed.description = std::format("<@{0}>: `{1}`\n **Moderator**: <@{2}> ({3})", event.message_author_id.str(), MessageToDelete.content, event.reacting_member.user_id.str(), event.reacting_member.get_nickname());
					dpp::embed_footer Footer;
					Footer.set_text(std::format("Channel : #{0}", bot.channel_get_sync(event.channel_id).name));
					LogEmbed.set_footer(Footer);

					Message.add_embed(LogEmbed);
					Message.set_channel_id(dpp::snowflake("1220771311455047760"));

					bot.message_create_sync(Message);
					bot.message_delete(event.message_id, event.channel_id, nullptr);
					break;
				}
			}
		}

		if (Emoji.name == "✅") {
			/*
			Handling applications -- Accepting
			*/
			if (event.channel_id.str() == "965597502868955157" && event.message_author_id.str() == "0") {
				dpp::message ApplicationMessage = bot.message_get_sync(event.message_id, event.channel_id);

				std::vector<std::string> Footer = split(ApplicationMessage.embeds[0].footer->text, ':');

				dpp::message ResultMessage;
				ResultMessage.set_content(std::format("<@{0}> has accepted {1}'s application.", event.reacting_member.user_id.str(), Footer[2]));
				ResultMessage.set_channel_id(dpp::snowflake("965597210190417920"));

				RankUser(Footer[0], "12530867", "72549629", RobloxCookie, "");

				bot.message_create(ResultMessage);
				bot.message_delete(event.message_id, event.channel_id);
			}
		}

		if (Emoji.name == "❎") {
			/*
			Handling applications -- Denying
			*/
			if (event.channel_id.str() == "965597502868955157" && event.message_author_id.str() == "0") {
				dpp::message ApplicationMessage = bot.message_get_sync(event.message_id, event.channel_id);
				
				std::vector<std::string> Footer = split(ApplicationMessage.embeds[0].footer->text, ':');
				
				dpp::message ResultMessage;
				ResultMessage.set_content(std::format("<@{0}> has declined {1}'s application.", event.reacting_member.user_id.str(), Footer[2]));
				ResultMessage.set_channel_id(dpp::snowflake("965597210190417920"));

				bot.message_create(ResultMessage);
				bot.message_delete(event.message_id, event.channel_id);
			}
		}
	});

	/*/
	bot.on_ready([&bot](const dpp::ready_t& event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			bot.global_command_create(dpp::slashcommand("hello", "hello world", bot.me.id));
		}
	});
	/*/

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
