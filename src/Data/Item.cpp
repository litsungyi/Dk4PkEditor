#include "Pch.h"

#include <Kafka\Stream\IInputStream.h>
#include <Kafka\Stream\IOutputStream.h>
#include "Data\Item.h"

namespace Dk4
{
    ItemData::ItemData()
        : m_itemId( 0 )
    {}

    ItemData::~ItemData()
    {}

    void ItemData::WriteToStream( std::shared_ptr<Kafka::IOutputStream> stream )
    {
        stream->WriteInt8( m_owned );
        stream->Skip( 1 );
    }

    void ItemData::ReadFromStream( std::shared_ptr<Kafka::IInputStream> stream )
    {
        m_owned = stream->ReadInt8();
        stream->Skip( 1 );
    }
} // namespace Dk4
