// Copyright (c) 2014-2015, Pacific Biosciences of California, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted (subject to the limitations in the
// disclaimer below) provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//  * Neither the name of Pacific Biosciences nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
// GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY PACIFIC
// BIOSCIENCES AND ITS CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL PACIFIC BIOSCIENCES OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
// USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

// Author: Derek Barnett

#include "MemoryUtils.h"
#include <string>
#include <cstdlib>
#include <cstring>

namespace PacBio {
namespace BAM {
namespace internal {

// -----------------
// BamHeaderMemory
// -----------------

BamHeader BamHeaderMemory::FromRawData(bam_hdr_t* hdr)
{
    // null input - error
    if (hdr == nullptr)
        throw std::runtime_error("invalid BAM header");

    // empty text input - ok
    if (hdr->text == nullptr || hdr->l_text == 0)
        return BamHeader();

    // parse normal SAM text input
    return BamHeader(std::string(hdr->text, hdr->l_text));
}

PBBAM_SHARED_PTR<bam_hdr_t> BamHeaderMemory::MakeRawHeader(const BamHeader& header)
{
    const std::string& text = header.ToSam();
    PBBAM_SHARED_PTR<bam_hdr_t> rawData(sam_hdr_parse(text.size(), text.c_str()), internal::HtslibHeaderDeleter());
    rawData->ignore_sam_err = 0;
    rawData->cigar_tab = NULL;
    rawData->l_text = text.size();
    rawData->text = (char*)calloc(rawData->l_text + 1, 1);
    memcpy(rawData->text, text.c_str(), rawData->l_text);
    return rawData;
}

} // namespace internal
} // namespace BAM
} // namespace PacBio

//PBBAM_SHARED_PTR<bam_hdr_t> BamHeaderMemory::MakeRawHeader(const BamHeader& header)
//{
//    if (!header)
//        return PBBAM_SHARED_PTR<bam_hdr_t>(nullptr);
//    return MakeRawHeader(*header.get());
//}
