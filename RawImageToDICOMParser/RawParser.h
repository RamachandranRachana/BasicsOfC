#pragma once

#include "libraw/libraw.h"

#include <span>
#include <string>

class RawParser
{
public:
    RawParser(const std::string& fname);
    ushort getRawWidth() const;
    ushort getRawHeight() const;
    std::span<ushort> getRawImageData() const;

    ~RawParser();

private:
    LibRaw rawParser;
    LibRaw_errors libErr;
};
