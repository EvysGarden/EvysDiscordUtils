#include "tools.hpp"
#include <argh.h>
#include <curl/curl.h>
#include <curl/easy.h>
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
        return 2;
    }

    // prepare url
    std::string   url = fmt::format("{}/messages/{}", webhookUrl, messageId);

    // setup curl for the get request
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, evdu::curlWriteFunction);
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    auto curlResult = curl_easy_perform(curl);
    if (curlResult != CURLE_OK) {
        fmt::print("curl error! (curlcode: {})", curlResult);
        return 3;
    }

    json content = json::parse(response);

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
