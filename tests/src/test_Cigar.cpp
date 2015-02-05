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

#include <gtest/gtest.h>
#include <pbbam/Cigar.h>
#include <string>
using namespace PacBio;
using namespace PacBio::BAM;
using namespace std;

TEST(CigarTest, OperationToType)
{
    EXPECT_EQ('M', CigarOperation::TypeToChar(CigarOperationType::ALIGNMENT_MATCH) );
    EXPECT_EQ('I', CigarOperation::TypeToChar(CigarOperationType::INSERTION) );
    EXPECT_EQ('D', CigarOperation::TypeToChar(CigarOperationType::DELETION) );
    EXPECT_EQ('N', CigarOperation::TypeToChar(CigarOperationType::REFERENCE_SKIP) );
    EXPECT_EQ('S', CigarOperation::TypeToChar(CigarOperationType::SOFT_CLIP) );
    EXPECT_EQ('H', CigarOperation::TypeToChar(CigarOperationType::HARD_CLIP) );
    EXPECT_EQ('P', CigarOperation::TypeToChar(CigarOperationType::PADDING) );
    EXPECT_EQ('=', CigarOperation::TypeToChar(CigarOperationType::SEQUENCE_MATCH) );
    EXPECT_EQ('X', CigarOperation::TypeToChar(CigarOperationType::SEQUENCE_MISMATCH) );
}

TEST(CigarTest, TypeToOperation)
{
    EXPECT_EQ(CigarOperationType::ALIGNMENT_MATCH,   CigarOperation::CharToType('M'));
    EXPECT_EQ(CigarOperationType::INSERTION,         CigarOperation::CharToType('I'));
    EXPECT_EQ(CigarOperationType::DELETION,          CigarOperation::CharToType('D'));
    EXPECT_EQ(CigarOperationType::REFERENCE_SKIP,    CigarOperation::CharToType('N'));
    EXPECT_EQ(CigarOperationType::SOFT_CLIP,         CigarOperation::CharToType('S'));
    EXPECT_EQ(CigarOperationType::HARD_CLIP,         CigarOperation::CharToType('H'));
    EXPECT_EQ(CigarOperationType::PADDING,           CigarOperation::CharToType('P'));
    EXPECT_EQ(CigarOperationType::SEQUENCE_MATCH,    CigarOperation::CharToType('='));
    EXPECT_EQ(CigarOperationType::SEQUENCE_MISMATCH, CigarOperation::CharToType('X'));
}

TEST(CigarTest, SetOperationYieldsCorrectType)
{
    CigarOperation c1; c1.Operation(CigarOperationType::ALIGNMENT_MATCH);
    CigarOperation c2; c2.Operation(CigarOperationType::INSERTION);
    CigarOperation c3; c3.Operation(CigarOperationType::DELETION);
    CigarOperation c4; c4.Operation(CigarOperationType::REFERENCE_SKIP);
    CigarOperation c5; c5.Operation(CigarOperationType::SOFT_CLIP);
    CigarOperation c6; c6.Operation(CigarOperationType::HARD_CLIP);
    CigarOperation c7; c7.Operation(CigarOperationType::PADDING);
    CigarOperation c8; c8.Operation(CigarOperationType::SEQUENCE_MATCH);
    CigarOperation c9; c9.Operation(CigarOperationType::SEQUENCE_MISMATCH);

    EXPECT_EQ('M', c1.Type() );
    EXPECT_EQ('I', c2.Type() );
    EXPECT_EQ('D', c3.Type() );
    EXPECT_EQ('N', c4.Type() );
    EXPECT_EQ('S', c5.Type() );
    EXPECT_EQ('H', c6.Type() );
    EXPECT_EQ('P', c7.Type() );
    EXPECT_EQ('=', c8.Type() );
    EXPECT_EQ('X', c9.Type() );
}

TEST(CigarTest, SetTypeYieldsCorrectOperation)
{
    CigarOperation c1; c1.Type('M');
    CigarOperation c2; c2.Type('I');
    CigarOperation c3; c3.Type('D');
    CigarOperation c4; c4.Type('N');
    CigarOperation c5; c5.Type('S');
    CigarOperation c6; c6.Type('H');
    CigarOperation c7; c7.Type('P');
    CigarOperation c8; c8.Type('=');
    CigarOperation c9; c9.Type('X');

    EXPECT_EQ(CigarOperationType::ALIGNMENT_MATCH,   c1.Operation());
    EXPECT_EQ(CigarOperationType::INSERTION,         c2.Operation());
    EXPECT_EQ(CigarOperationType::DELETION,          c3.Operation());
    EXPECT_EQ(CigarOperationType::REFERENCE_SKIP,    c4.Operation());
    EXPECT_EQ(CigarOperationType::SOFT_CLIP,         c5.Operation());
    EXPECT_EQ(CigarOperationType::HARD_CLIP,         c6.Operation());
    EXPECT_EQ(CigarOperationType::PADDING,           c7.Operation());
    EXPECT_EQ(CigarOperationType::SEQUENCE_MATCH,    c8.Operation());
    EXPECT_EQ(CigarOperationType::SEQUENCE_MISMATCH, c9.Operation());
}

TEST(CigarStringTest, FromStdString_Empty)
{
    const string emptyCigar = "";
    Cigar cigar = Cigar::FromStdString(emptyCigar);
    EXPECT_TRUE(cigar.empty());
}

TEST(CigarStringTest, FromStdString_SingleOp)
{
    const string singleCigar = "100M";

    Cigar cigar = Cigar::FromStdString(singleCigar);
    ASSERT_TRUE(cigar.size() == 1);

    const CigarOperation& op = cigar.front();
    EXPECT_TRUE(op.Type()   == 'M');
    EXPECT_TRUE(op.Length() == 100);
}

TEST(CigarStringTest, FromStdString_MultipleOps)
{
    const string multiCigar = "100M2D34I6M";

    Cigar cigar = Cigar::FromStdString(multiCigar);
    ASSERT_TRUE(cigar.size() == 4);

    CigarOperation op0 = cigar.at(0);
    CigarOperation op1 = cigar.at(1);
    CigarOperation op2 = cigar.at(2);
    CigarOperation op3 = cigar.at(3);

    EXPECT_TRUE(op0.Type()   == 'M');
    EXPECT_TRUE(op0.Length() == 100);
    EXPECT_TRUE(op1.Type()   == 'D');
    EXPECT_TRUE(op1.Length() == 2);
    EXPECT_TRUE(op2.Type()   == 'I');
    EXPECT_TRUE(op2.Length() == 34);
    EXPECT_TRUE(op3.Type()   == 'M');
    EXPECT_TRUE(op3.Length() == 6);
}

TEST(CigarStringTest, ToStdString_Empty)
{
    const string empty;
    Cigar cigar;
    EXPECT_EQ(empty, cigar.ToStdString());
}

TEST(CigarStringTest, ToStdString_SingleOp)
{
    const string singleCigar = "100M";

    Cigar cigar;
    cigar.push_back( CigarOperation(CigarOperationType::ALIGNMENT_MATCH, 100) );

    EXPECT_EQ(singleCigar, cigar.ToStdString());
}

TEST(CigarStringTest, ToStdString_MultipleOps)
{
    const string multiCigar = "100M2D34I6M";

    Cigar cigar;
    cigar.push_back( CigarOperation(CigarOperationType::ALIGNMENT_MATCH, 100) );
    cigar.push_back( CigarOperation(CigarOperationType::DELETION, 2) );
    cigar.push_back( CigarOperation(CigarOperationType::INSERTION, 34) );
    cigar.push_back( CigarOperation(CigarOperationType::ALIGNMENT_MATCH, 6) );

    EXPECT_EQ(multiCigar, cigar.ToStdString());
}