#include<iostream>

#include "imebra/imebra.h"
#include "RawParser.h"

int main()
{
    RawParser rp("images/rhino.raw");

    imebra::charsetsList_t charsets;
    charsets.push_back("ISO 2022 IR 6");
    imebra::MutableDataSet dataSet("1.2.840.10008.1.2.1", charsets);

    dataSet.setUnicodePatientName(imebra::TagId(imebra::tagId_t::PatientName_0010_0010), imebra::UnicodePatientName(L"Patient^Name", L"", L""));

    const auto width = rp.getRawWidth();
    const auto height = rp.getRawHeight();
    const auto rawSpan = rp.getRawImageData();

    imebra::MutableImage image(rp.getRawWidth(), rp.getRawHeight(), imebra::bitDepth_t::depthU16, "MONOCHROME2", 15);
    {
        imebra::WritingDataHandlerNumeric dataHandler(image.getWritingDataHandler());
        for (std::uint32_t scanY(0); scanY != height; ++scanY)
        {
            for (std::uint32_t scanX(0); scanX != width; ++scanX)
            {

                const auto index = scanY * width + scanX;
                dataHandler.setUint16(index, rawSpan[index]);
            }
        }
    }

    dataSet.setImage(0, image, imebra::imageQuality_t::veryHigh);
    imebra::CodecFactory::save(dataSet, "dicomFile.dcm", imebra::codecType_t::dicom);

    return 0;
}
