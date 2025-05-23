#pragma once

#include "../../types.hpp"
#include <pqrs/json.hpp>
#include <vector>

namespace krbn {
namespace manipulator {
namespace manipulators {
namespace basic {
class simultaneous_options final {
public:
  enum class key_order {
    insensitive,
    strict,
    strict_inverse,
  };

  enum class key_up_when {
    any,
    all,
  };

  simultaneous_options(const simultaneous_options&) = delete;

  simultaneous_options(void)
      : detect_key_down_uninterruptedly_(false),
        key_down_order_(key_order::insensitive),
        key_up_order_(key_order::insensitive),
        key_up_when_(key_up_when::any) {
  }

  simultaneous_options(const nlohmann::json& json)
      : simultaneous_options() {
    pqrs::json::requires_object(json, "json");

    for (const auto& [key, value] : json.items()) {
      // key is always std::string.

      if (key == "detect_key_down_uninterruptedly") {
        pqrs::json::requires_boolean(value, "`" + key + "`");

        detect_key_down_uninterruptedly_ = value.get<bool>();

      } else if (key == "key_down_order") {
        try {
          key_down_order_ = value;
        } catch (const pqrs::json::unmarshal_error& e) {
          throw pqrs::json::unmarshal_error(fmt::format("`{0}` error: {1}", key, e.what()));
        }

      } else if (key == "key_up_order") {
        try {
          key_up_order_ = value;
        } catch (const pqrs::json::unmarshal_error& e) {
          throw pqrs::json::unmarshal_error(fmt::format("`{0}` error: {1}", key, e.what()));
        }

      } else if (key == "key_up_when") {
        try {
          key_up_when_ = value;
        } catch (const pqrs::json::unmarshal_error& e) {
          throw pqrs::json::unmarshal_error(fmt::format("`{0}` error: {1}", key, e.what()));
        }

      } else if (key == "to_after_key_up") {
        if (value.is_object()) {
          try {
            to_after_key_up_.push_back(std::make_shared<to_event_definition>(value));
          } catch (const pqrs::json::unmarshal_error& e) {
            throw pqrs::json::unmarshal_error(fmt::format("`{0}` error: {1}", key, e.what()));
          }

        } else if (value.is_array()) {
          try {
            for (const auto& j : value) {
              to_after_key_up_.push_back(std::make_shared<to_event_definition>(j));
            }
          } catch (const pqrs::json::unmarshal_error& e) {
            throw pqrs::json::unmarshal_error(fmt::format("`{0}` entry error: {1}", key, e.what()));
          }

        } else {
          throw pqrs::json::unmarshal_error(fmt::format("`{0}` must be object or array, but is `{1}`", key, pqrs::json::dump_for_error_message(value)));
        }

      } else if (key == "description") {
        // Do nothing

      } else {
        throw pqrs::json::unmarshal_error(fmt::format("unknown key `{0}` in `{1}`", key, pqrs::json::dump_for_error_message(json)));
      }
    }
  }

  bool get_detect_key_down_uninterruptedly(void) const {
    return detect_key_down_uninterruptedly_;
  }

  key_order get_key_down_order(void) const {
    return key_down_order_;
  }

  key_order get_key_up_order(void) const {
    return key_up_order_;
  }

  key_up_when get_key_up_when(void) const {
    return key_up_when_;
  }

  const to_event_definitions& get_to_after_key_up(void) const {
    return to_after_key_up_;
  }

private:
  bool detect_key_down_uninterruptedly_;
  key_order key_down_order_;
  key_order key_up_order_;
  key_up_when key_up_when_;
  to_event_definitions to_after_key_up_;
};

inline void from_json(const nlohmann::json& json, simultaneous_options::key_order& value) {
  pqrs::json::requires_string(json, "json");

  auto s = json.get<std::string>();

  if (s == "insensitive") {
    value = simultaneous_options::key_order::insensitive;
  } else if (s == "strict") {
    value = simultaneous_options::key_order::strict;
  } else if (s == "strict_inverse") {
    value = simultaneous_options::key_order::strict_inverse;
  } else {
    throw pqrs::json::unmarshal_error(fmt::format("unknown value: `{0}`", s));
  }
}

inline void from_json(const nlohmann::json& json, simultaneous_options::key_up_when& value) {
  pqrs::json::requires_string(json, "json");

  auto s = json.get<std::string>();

  if (s == "any") {
    value = simultaneous_options::key_up_when::any;
  } else if (s == "all") {
    value = simultaneous_options::key_up_when::all;
  } else {
    throw pqrs::json::unmarshal_error(fmt::format("unknown value: `{0}`", s));
  }
}
} // namespace basic
} // namespace manipulators
} // namespace manipulator
} // namespace krbn
