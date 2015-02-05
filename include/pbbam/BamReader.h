// Copyright (c) 2014, Pacific Biosciences of California, Inc.
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

#ifndef BAMREADER_H
#define BAMREADER_H

#include "pbbam/BamRecord.h"
#include "pbbam/Config.h"
#include "pbbam/SamHeader.h"
#include <memory>
#include <string>

namespace PacBio {
namespace BAM {

class PBBAM_EXPORT BamReader
{
public:
    BamReader(void);
    ~BamReader(void);

public:

    /// Closes the BAM file reader.
    void Close(void);

    /// Opens a BAM file for reading.
    ///
    /// Prefix \p filename with "http://" or "ftp://" for remote files,
    /// or set to "-" for stdin.
    ///
    /// \param[in] filename path to input BAM file
    ///
    /// \returns success/failure
    bool Open(const std::string& filename);

    /// \returns header as SamHeader object
    SamHeader Header(void) const;

    /// \returns human-readable error message
    std::string ErrorString(void) const;

    /// \returns true if error encountered (error string is not empty)
    bool HasError(void) const;

    /// Fetches the next record in a BAM file.
    ///
    /// \param[out] record pointer to BamRecord object
    ///
    /// \returns succcess/failure
    bool GetNext(BamRecord* record);

#ifdef PBBAM_TESTING
public:
#else
private:
#endif // PBBAM_TESTING

    bool GetNext(bam1_t* rawRecord);
    bam_hdr_t* RawHeader(void) const;

private:
    void InitialOpen(void);

private:
    std::shared_ptr<samFile>    file_;
    std::shared_ptr<bam_hdr_t>  header_;
    std::shared_ptr<bam1_t>     rawRecord_;
    std::string filename_;
    std::string errorString_;
};

} // namespace BAM
} // namespace PacBio

#endif // BAMREADER_H