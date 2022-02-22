#pragma once

#include <nlohmann/json.hpp>

namespace evdu {
    const auto DISCOHOOK_MERGE_PATCH_ROOT = R"(
        {
            "attachments": null,
            "author": null,
            "channel_id": null,
            "components": null,
            "content": null,
            "edited_timestamp": null,
            "flags": null,
            "id": null,
            "mention_everyone": null,
            "mention_roles": null,
            "mentions": null,
            "pinned": null,
            "timestamp": null,
            "tts": null,
            "type": null,
            "webhook_id": null
        }
    )"_json;

    const auto DISCOHOOK_MERGE_PATCH_EMBED = R"(
        {
            "type": null,
            "author": {
                "proxy_icon_url": null
            }
        }
    )"_json;
}