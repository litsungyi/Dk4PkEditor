#pragma once

#include <Kafka\Stream\ISerializable.h>
#include "DK4_Common.h"

namespace Kafka
{
    struct IOutputStream;
    struct IInputStream;
} // namespace Kafka

namespace Dk4
{
    class ItemData : public Kafka::ISerializable
    {
    public:
        ItemData();
        ~ItemData();

        virtual void WriteToStream( std::shared_ptr<Kafka::IOutputStream> stream );
        virtual void ReadFromStream( std::shared_ptr<Kafka::IInputStream> stream );

        size_t          m_itemId;

        char m_owned; // ¬O§_¾Ö¦³ ¾Ö¦³: 0x0C
    };

} // namespace Dk4
