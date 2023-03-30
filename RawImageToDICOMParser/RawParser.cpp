#include "RawParser.h"

#include <iostream>

RawParser::RawParser(const std::string& fname)
{
    libErr = (LibRaw_errors)rawParser.open_file(fname.c_str());
    if (libErr != LIBRAW_SUCCESS)
        std::cerr << "Failed to load the raw image file and instantiate the rawParser";

    libErr = (LibRaw_errors)rawParser.unpack();

    //Unpacks the RAW files of the image
    if (libErr != LIBRAW_SUCCESS)
        std::cerr << "Failed to unpack raw data";
}

ushort RawParser::getRawWidth() const
{
    return rawParser.imgdata.rawdata.sizes.raw_width;
}

ushort RawParser::getRawHeight() const
{
    return rawParser.imgdata.rawdata.sizes.raw_height;
}

std::span<ushort> RawParser::getRawImageData() const
{
    return { rawParser.imgdata.rawdata.raw_image, static_cast<ushort>(getRawWidth() * getRawHeight()) };
}

RawParser::~RawParser()
{
    rawParser.recycle();
}


