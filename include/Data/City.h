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
    //////////////////////////////////////////////////////////////////////////
    // 港口

    enum CityAvailable
    {
        Unknown = 0, // 資訊未知
        Known = 1, // 資訊已知
        New = 3, // 新港開闢
    };

    enum CityFacility
    {
        Inn = 0x0001, // 旅館
        Secret = 0x0002, // 遺跡
        Chuch = 0x0004, // 教堂
        Gate = 0x0008, // 城門
        Place = 0x0100, // 廣場
        Trade = 0x0200, // 交易所
        Ship = 0x0400, // 造船廠
        Port = 0x0800, // 碼頭
        Wine = 0x1000, // 酒館
        Guild = 0x2000, // 同業公會
        Pla = 0x4000, // 王宮
        Gov = 0x8000, // 總督府
    };

    enum Tradeability
    {
        CannotTrade = 0,
        CanTrade = 1,
    };

    enum CityStatus
    {
        War = 0x00, // 戰爭
        Sick = 0x01, // 疾病
        Food = 0x02, // 飢荒
        Good = 0x03, // 好景氣
        Bad = 0x04, // 不景氣
        NotEnough1 = 0x05, // 特定貨品不足
        NotEnough2 = 0x06, // 特定貨品不足
        NotEnough3 = 0x07, // 特定貨品不足
        NotEnough4 = 0x08, // 特定貨品不足
        NotEnough5 = 0x09, // 特定貨品不足
        NotEnough6 = 0x0A, // 特定貨品不足
        Normal = 0x0C, // 正常
    };

    struct Market       // 佔有率
    {
        char   TeamId;          // 勢力代號
        char   MarketShare;     // 佔有率
    };

    struct Specialty // 特產
    {
        Tradeability Tradeable; // 0: 不可交易, 1: 可以交易
        short Price; // 價格
        short Amount; // 數量
    };

    struct Popular      // 流行品
    {
        char   ProductId;       // 流行貨品
        char   PopularStage;    // 流行階段
    };

    class CityData : public Kafka::ISerializable
    {
    public:
        CityData();
        ~CityData();

        virtual void WriteToStream( std::shared_ptr<Kafka::IOutputStream> stream );
        virtual void ReadFromStream( std::shared_ptr<Kafka::IInputStream> stream );

        size_t          m_CityId;

        CityAvailable m_Avalible;
        CityFacility m_Facility; // 設施
        short m_Bussiness; // 發展度
        short m_Military; // 武裝度
        Market m_MarketShare[ MAX_TEAM_IN_CITY ]; // 佔有率
        Specialty m_SpecialProduct[ MAX_SPECIALTY ]; // 特產
        short m_Products[ MAX_PRODUCT ]; // 交易品
        Popular m_Popular[ MAX_POPULAR ]; // 流行品
        short m_Status; // 城市狀態
    };

} // namespace Dk4
