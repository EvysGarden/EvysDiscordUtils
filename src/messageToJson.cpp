#include "tools.hpp"
#include <argh.h>
#include <cpr/api.h>
#include <cpr/cpr.h>
#include <cpr/cprtypes.h>
#include <fmt/core.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>

using nlohmann::json;

namespace evdu {

    constexpr std::string_view HELP_MESSAGE = R"(Valid Usage:
    -h, --help                          see this little message
    -w, --webhook <webhook_url>         the webhook url
    -m, --message <message_id>          message id to query for
    -p, --pretty                        pretty print outputed json
    -d, --discohook                     strip content for discohook
    -o, --output <filepath>             file to output to. if ignored, prints to console
)";

    json stripForDiscohook(const json& src)
    {
        json dst = src;
        dst.merge_patch(DISCOHOOK_MERGE_PATCH_ROOT);

        for (auto& embed : dst.at("embeds")) { embed.merge_patch(DISCOHOOK_MERGE_PATCH_EMBED); }

        return dst;
    }
} // namespace evdu

int main(int argc, char* argv[])
{
    argh::parser cmdl(argc, argv);

    if (cmdl[{ "-h", "--help" }]) {
        fmt::print(evdu::HELP_MESSAGE);
        return 0;
    }

    std::string webhookUrl;
    if (!(cmdl({ "-w", "--webhook" }) >> webhookUrl)) {
        fmt::print("{}Missing webhook url!\n", evdu::HELP_MESSAGE);
        return 1;
    }

    std::string messageId;
    if (!(cmdl({ "-m", "--message" }) >> messageId)) {
        fmt::print("{}Missing message id!\n", evdu::HELP_MESSAGE);
        return 1;
    }

    std::string   url = fmt::format("{}/messages/{}", webhookUrl, messageId);
    cpr::Response r   = cpr::Get(cpr::Url { url });

    json content = json::parse(r.text);

    if (cmdl[{ "-d", "--discohook" }]) { content = evdu::stripForDiscohook(content); }

    std::string strContent;

    if (cmdl[{ "-p", "--pretty" }]) {
        strContent = content.dump(4);
    } else {
        strContent = content.dump();
    }

    std::string filepath;
    if (cmdl({ "-o", "--output" }) >> filepath) {
        std::ofstream file(filepath, std::ios::out | std::ios::trunc);
        file << strContent;
    } else {
        fmt::print("{}\n", strContent);
    }

    return 0;
}