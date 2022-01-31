// SPDX-License-Identifier: GPL-2.0-only
// PROJECT NAME:  MP3Edit
// COPYRIGHT:     Copyright © 2021 Sean Cassell <sean.cassell@outlook.com>
// FILENAME:      GetControlsVector.cpp
// FILE PURPOSE:  [To be added]
//                


/* **************************** INCLUDED HEADERS **************************** */
#include "GetControlsVector.hpp"


/* ************************** FUNCTION DEFINITIONS ************************** */
auto Utils::GetControlsVector() noexcept->std::vector<SControl> {
	constexpr static const size_t kCONTROL_VEC_SIZE = 23ui64;
	std::vector<SControl> controls_(kCONTROL_VEC_SIZE);
	return controls_;
}
