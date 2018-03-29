#pragma once

#include <Kafka\Stream\ISerializable.h>

namespace Kafka
{
    struct IOutputStream;
    struct IInputStream;
} // namespace Kafka

namespace Dk4
{
    //////////////////////////////////////////////////////////////////////////
    // 海員 
    enum BaseSkill
    {
        BASE_CON,       // 體力
        BASE_AGI,       // 敏捷
        BASE_CRM,       // 魅力
        BASE_INT,       // 智力
        BASE_SPI,       // 精神
        BASE_LUK,       // 運氣
        BASE_MAX        // 技能數
    };

    enum Exp
    {
        EXP_1,          // 商業
        EXP_2,          // 軍事
        EXP_MAX         // 總數
    };

    enum Equipment
    {
        EQUIP_WEAPON,   // 武器
        EQUIP_ARMOR,    // 防具
        EQUIP_ITEM_1,   // 道具１
        EQUIP_ITEM_2,   // 道具２
        EQUIP_ITEM_3,   // 道具３
        EQUIP_MAX       // 總數
    };

    class SailorData : public Kafka::ISerializable
    {
    public:
        SailorData();
        ~SailorData();

        virtual void WriteToStream( std::shared_ptr<Kafka::IOutputStream> stream );
        virtual void ReadFromStream( std::shared_ptr<Kafka::IInputStream> stream );

        size_t m_SailorId;

        char m_Team;
        char m_Base[ BASE_MAX ];
        int m_Exp[ EXP_MAX ];
        short m_HP;
        char m_Health;
        char m_Mood;
        char m_Equipment[ EQUIP_MAX ];
    };

} // namespace Dk4
