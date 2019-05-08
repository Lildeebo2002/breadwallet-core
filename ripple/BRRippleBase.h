//
//  BRRippleBase.h
//  Core
//
//  Created by Carl Cherry on 4/16/19.
//  Copyright © 2019 Breadwinner AG. All rights reserved.
//
//  See the LICENSE file at the project root for license information.
//  See the CONTRIBUTORS file at the project root for a list of contributors.
//
#ifndef BRRipple_base_h
#define BRRipple_base_h
#include <stdbool.h>
#include "BRKey.h"

#define ADDRESS_BYTES   (20)



// A Ripple Address - 20 bytes
typedef struct {
    uint8_t bytes[ADDRESS_BYTES];
} BRRippleAddress;

// Even though we only support the Payment type - plan for
// the future
typedef enum {
    PAYMENT
} BRRippleTransactionType ;

// A Ripple Transaction Hash
typedef struct {
    uint8_t bytes[32];
} BRRippleTransactionHash;

typedef struct {
    int currencyType; // 0 - ripple, 1 - other, -1 unknown/invalid
    uint64_t amount;
    uint8_t currencyCode[20];
    uint8_t issuerId[20];
} BRRippleAmount;

typedef enum {
    AMOUNT,
    FEE,
    SENDMAX,
    DELIVERMIN
} BRRippleAmountType;

// Stucture to hold the calculated signature
typedef struct {
    uint8_t signature[256];
    int sig_length;
} BRRippleSignatureRecord;
typedef BRRippleSignatureRecord *BRRippleSignature;

// Ripple has the concept of fields, which are sorted. This
// field stucture allows us to easily sort the fields when
// creating the serialized format
typedef struct _ripple_field {
    int typeCode;
    int fieldCode;
    union _data {
        uint8_t i8;
        uint16_t i16;
        uint32_t i32;
        uint64_t i64;
        BRRippleAmount amount;
        BRRippleAddress address;
        BRKey publicKey;
        BRRippleSignatureRecord signature;
        uint8_t hash[32]; // There are 3 potential hash fields - longest is 32 bytes
    } data;
} BRRippleField;

#endif