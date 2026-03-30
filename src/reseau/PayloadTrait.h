#pragma once
#include "Payloads.h"

template<typename T>
struct PayloadTraits;

template<>
struct PayloadTraits<PayloadConnect>
{
    static constexpr PayloadType type = PayloadType::CONNECT;
};

template<>
struct PayloadTraits<PayloadACK>
{
    static constexpr PayloadType type = PayloadType::ACK;
};

template<>
struct PayloadTraits<PayloadPing>
{
    static constexpr PayloadType type = PayloadType::PING;
};
