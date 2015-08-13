/* PbiRawData.i */

%module PacBioBam

%{
#include <pbbam/PbiRawData.h>
using namespace PacBio;
using namespace PacBio::BAM;
%}

// move ctors not used
%ignore PacBio::BAM::PbiRawBarcodeData::PbiRawBarcodeData(PbiRawBarcodeData&&);   
%ignore PacBio::BAM::PbiRawMappedData::PbiRawMappedData(PbiRawMappedData&&);
%ignore PacBio::BAM::PbiReferenceEntry::PbiReferenceEntry(PbiReferenceEntry&&);
%ignore PacBio::BAM::PbiRawReferenceData::PbiRawReferenceData(PbiRawReferenceData&&);
%ignore PacBio::BAM::PbiRawSubreadData::PbiRawSubreadData(PbiRawSubreadData&&);
%ignore PacBio::BAM::PbiRawData::PbiRawData(PbiRawData&&); 

// assignment operators not used
%ignore PacBio::BAM::PbiRawBarcodeData::operator=;                   
%ignore PacBio::BAM::PbiRawMappedData::operator=;
%ignore PacBio::BAM::PbiReferenceEntry::operator=;
%ignore PacBio::BAM::PbiRawReferenceData::operator=;
%ignore PacBio::BAM::PbiRawSubreadData::operator=;
%ignore PacBio::BAM::PbiRawData::operator=;

HANDLE_STD_EXCEPTION(PacBio::BAM::PbiRawMappedData::AddRecord);

%include <pbbam/PbiRawData.h>
