#pragma once

#include <memory>
#include <Kafka\Applications\IConsole.h>
#include "Data\City.h"
#include "Data\Sailor.h"
#include "Data\Item.h"

namespace Kafka
{
    class InputFileStream;
} // namespace Kafka

namespace Dk4
{
    class Console : public Kafka::IConsole
    {
    public:
        int Run();

    private:
        bool OpenFile();
        bool ValidateFile();

        void LoadLeader();
        void LoadSailors();
        void LoadCities();
        void LoadItems();

        std::shared_ptr< Kafka::InputFileStream > m_stream;
        char m_teamId;
        SailorData m_sailorData[ SAILOR_NUMBER ];
        CityData m_cityData[ CITY_NUMBER ];
        ItemData m_itemData[ ITEM_NUMBER ];
    };
} // namespace Dk4
