#include "Pch.h"

#include <Kafka\Stream\IInputStream.h>
#include <Kafka\Stream\IOutputStream.h>
#include "Data\Sailor.h"

namespace Dk4
{

    //////////////////////////////////////////////////////////////////////////
    // ®ü­û
    SailorData::SailorData()
        : m_SailorId( 0 )
        , m_Team( 0 )
        , m_HP( 0 )
        , m_Health( 0 )
        , m_Mood( 0 )
    {
        for ( int i = 0; i < BASE_MAX; ++i )
        {
            m_Base[ i ] = 0;
        }

        for ( int i = 0; i < EXP_MAX; ++i )
        {
            m_Exp[ i ] = 0;
        }

        for ( int i = 0; i < EQUIP_MAX; ++i )
        {
            m_Equipment[ i ] = 0;
        }
    }

    SailorData::~SailorData()
    {
    }

    void SailorData::WriteToStream( std::shared_ptr<Kafka::IOutputStream> stream )
    {
        stream->WriteInt8( m_Team );
        stream->Skip( 1 );
        for ( size_t i = 0; i < BASE_MAX; i++ )
        {
            stream->WriteInt8( m_Base[ i ] );
        }

        for ( size_t i = 0; i < EXP_MAX; i++ )
        {
            stream->WriteInt32( m_Exp[ i ] );
        }

        stream->WriteInt16( m_HP );
        stream->WriteInt8( m_Health );
        stream->WriteInt8( m_Mood );

        for ( size_t i = 0; i < EQUIP_MAX; i++ )
        {
            stream->WriteInt8( m_Equipment[ i ] );
        }
    }

    void SailorData::ReadFromStream( std::shared_ptr<Kafka::IInputStream> stream )
    {
        m_Team = stream->ReadInt8();
        stream->Skip( 1 );
        for ( size_t i = 0; i < BASE_MAX; i++ )
        {
            m_Base[ i ] = stream->ReadInt8();
        }

        for ( size_t i = 0; i < EXP_MAX; i++ )
        {
            m_Exp[ i ] = stream->ReadInt32();
        }

        m_HP = stream->ReadInt16();
        m_Health = stream->ReadInt8();
        m_Mood = stream->ReadInt8();

        for ( size_t i = 0; i < EQUIP_MAX; i++ )
        {
            m_Equipment[ i ] = stream->ReadInt8();
        }
    }
} // namespace Dk4
