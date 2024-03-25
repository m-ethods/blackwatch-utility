// roblox_ranking.cpp
// author: systemabec <@m-ethods>

#include <iostream>
#include "cpr/cpr.h"
#include "roblox_ranking.h"

bool RankUser(std::string UserId, std::string GroupId, std::string RankId, std::string RobloxCookie, std::string XcsrfToken)
{
    try
    {
        cpr::Url GroupURL{
            std::format("https://groups.roblox.com/v1/groups/{0}/users/{1}", GroupId, UserId)
        };

        std::ostringstream BodyString;
        BodyString << "{\"roleId\": " << RankId << "}";

        cpr::Body RequestBody = BodyString.str() ;
        cpr::Header Headers {
            {"Content-Type", "application/json"},
            {"Referer", "https://www.roblox.com"},
            {"X-CSRF-TOKEN", XcsrfToken}
        };
        cpr::Cookies RequestCookies{
            {".ROBLOSECURITY", RobloxCookie}
        };

        cpr::Response RequestResponse = cpr::Patch(GroupURL, Headers, RequestBody, RequestCookies);
        if (XcsrfToken == "") {
            return RankUser(UserId, GroupId, RankId, RobloxCookie, RequestResponse.header.at("X-CSRF-Token"));
        }
        std::cout << std::endl << RequestResponse.text;

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Request failed, error: " << e.what() << '\n';
        return false;
    }

    return false;
}