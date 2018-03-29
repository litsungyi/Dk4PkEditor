#include "Pch.h"

#include <Kafka\Stream\IInputStream.h>
#include <Kafka\Stream\IOutputStream.h>
#include "Data\City.h"

namespace Dk4
{
    //////////////////////////////////////////////////////////////////////////
    // ´ä¤f
    CityData::CityData()
        : m_CityId( 0 )
    {}

    CityData::~CityData()
    {
    }

    void CityData::WriteToStream( std::shared_ptr<Kafka::IOutputStream> stream )
    {
        stream->WriteInt8( m_Avalible );
        stream->Skip( 1 );
        stream->WriteInt16( m_Facility );
        stream->Skip( 2 );
        stream->WriteInt16( m_Bussiness );
        stream->Skip( 4 );
        stream->WriteInt16( m_Military );
        stream->Skip( 4 );

        for ( int i = 0; i < MAX_TEAM_IN_CITY; ++i )
        {
            stream->WriteInt8( m_MarketShare[ i ].TeamId );
            stream->WriteInt8( m_MarketShare[ i ].MarketShare );
        }

        for ( int i = 0; i < MAX_SPECIALTY; ++i )
        {
            stream->WriteInt8( m_SpecialProduct[ i ].Tradeable );
            stream->WriteInt16( m_SpecialProduct[ i ].Price );
            stream->WriteInt16( m_SpecialProduct[ i ].Amount );
        }

        for ( int i = 0; i < MAX_PRODUCT; ++i )
        {
            stream->WriteInt16( m_Products[ i ] );
        }

        for ( int i = 0; i < MAX_POPULAR; ++i )
        {
            stream->WriteInt8( m_Popular[ i ].ProductId );
            stream->WriteInt8( m_Popular[ i ].PopularStage );
        }

        stream->WriteInt16( m_Status );
    }

    void CityData::ReadFromStream( std::shared_ptr<Kafka::IInputStream> stream )
    {
        m_Avalible = static_cast<CityAvailable>( stream->ReadInt8() );
        stream->Skip( 1 );
        m_Facility = static_cast<CityFacility>( stream->ReadInt16() );
        stream->Skip( 2 );
        m_Bussiness = stream->ReadInt16();
        stream->Skip( 4 );
        m_Military = stream->ReadInt16();
        stream->Skip( 4 );

        for ( int i = 0; i < MAX_TEAM_IN_CITY; ++i )
        {
            m_MarketShare[ i ].TeamId = stream->ReadInt8();
            m_MarketShare[ i ].MarketShare = stream->ReadInt8();
        }

        for ( int i = 0; i < MAX_SPECIALTY; ++i )
        {
            m_SpecialProduct[ i ].Tradeable = static_cast<Tradeability>( stream->ReadInt8() );
            m_SpecialProduct[ i ].Price = stream->ReadInt16();
            m_SpecialProduct[ i ].Amount = stream->ReadInt16();
        }

        for ( int i = 0; i < MAX_PRODUCT; ++i )
        {
            m_Products[ i ] = stream->ReadInt16();
        }

        for ( int i = 0; i < MAX_POPULAR; ++i )
        {
            m_Popular[ i ].ProductId = stream->ReadInt8();
            m_Popular[ i ].PopularStage = stream->ReadInt8();
        }

        m_Status = stream->ReadInt16();
    }
} // namespace Dk4
