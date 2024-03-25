# Blackwatch-Utility
### How to use
- Use Visual Studio 2022
- Open the .sln file
- Make sure all NuGet packages are correctly installed (CPR is a NuGet package and necessary).
- Change the settings at the top of `blackwatchutility.cpp` accordingly.
- Run the bot!
### Notes
- When you start up the bot, it requires a ROBLOX Cookie. This cookie can be found in cached data in the ROBLOX website, in the .ROBLOSECURITY field. **Do not share this with anyone else**. This cookie should belong to a ROBLOX account with full permissions in your group. This account will rank players accordingly.
- For applications, your application center must send a webhook with the player's answers to `APPLICATIONS_CHANNEL_ID`. This webhook must be an embed. The first embed must have a footer with the following format: `{UserId}:{Rank}:{Anything-Else-Here}`. The "Rank" field is the one configurated in the map `GROUP_RANKS`. In `GROUP_RANKS`, make sure you're filling in a Rank ID and not a Rank Number (Rank numbers go from 1 to 255).
### Credits
[D++](https://dpp.dev/9.0.8/index.html) ;
[CPR](https://github.com/libcpr/cpr)
