#pragma once

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

enum class DISTRICT_TYPE {
    unified = 0,
    divided = 1
};

enum class ELECTION_ROUND_TYPE {
    regular = 0,
    simple = 1
};
