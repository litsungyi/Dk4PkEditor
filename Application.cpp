#include "Pch.h"

#include <cassert>
#include <Kafka\Stream\OutputFileStream.h>
#include <Kafka\Stream\InputFileStream.h>
#include "TinyFileDialogs\tinyfiledialogs.h"
#include "Application.h"
#include "DK4_Common.h"
#include "Data\Sailor.h"

namespace Dk4
{
    int Console::Run()
    {
        if ( !OpenFile() )
        {
            std::string title( "錯誤!" );
            std::string message( "開啟檔案失敗" );

            tinyfd_messageBox( title.c_str(), message.c_str(), "ok", "error", 0 );
            return 0;
        }

        if ( !ValidateFile() )
        {
            std::string title( "錯誤!" );
            std::string message( "檔案驗證失敗" );

            tinyfd_messageBox( title.c_str(), message.c_str(), "ok", "error", 0 );
            return 0;
        }

        LoadLeader();
        LoadSailors();
        LoadCities();
        LoadItems();

        return 0;
    }

    bool Console::OpenFile()
    {
        const char* filters[] =
        {
            "*.dk4"
        };
        std::string fileName = tinyfd_openFileDialog( "選擇記錄檔", "", 1, filters, 0 );
        if ( fileName.length() == 0 )
        {
            return false;
        }

        m_stream = std::shared_ptr< Kafka::InputFileStream >( new Kafka::InputFileStream( fileName, true ) );
        return m_stream && m_stream->CanRead();
    }

    bool Console::ValidateFile()
    {
        const std::string VALIDATE_STRING( "DAIKOUKAI4PKW9 1" );
        std::string readString = m_stream->ReadString( VALIDATE_STRING.length() );
        return readString == VALIDATE_STRING;
    }

    void Console::LoadLeader()
    {
        SailorData sailorLeader;
        m_stream->Seek( SAILOR_LEADER_OFFSET );
        sailorLeader.ReadFromStream( m_stream );

        std::string title( "主角的勢力" );
        m_teamId = sailorLeader.m_Team;
        tinyfd_messageBox( title.c_str(), TEAM_NAME[ m_teamId ].c_str(), "ok", "error", 0 );
    }

    void Console::LoadSailors()
    {
        m_stream->Seek( SAILOR_OFFSET );
        for ( int i = 0; i < SAILOR_NUMBER; ++i )
        {
            m_sailorData[ i ].m_SailorId = i;
            m_sailorData[ i ].ReadFromStream( m_stream );
            if ( i <= NON_NPC_SAILOR_NUMBER )
            {
                // 檢查是否為本勢力海員
                if ( m_sailorData[ i ].m_Team != m_teamId )
                {
                    std::string title2( "是否邀請" );
                    tinyfd_messageBox( title2.c_str(), SAILOR_NAME[ i ].c_str(), "ok", "error", 0 );
                }
                else
                {
                    switch ( i )
                    {
                    case 39: // 詹姆茲．克利福德
                    case 42: // 彼德羅．德．巴魯迪斯
                    case 44: // 赫德姆．阿弗美朵．巴夏
                    case 45: // 巴巴洛沙．法斯爾．海雷丁
                    case 52: // 索靜．來島
                    case 54: // 迪歐歌．德．埃斯康特
                    case 66: // 伊文．尼耶迪
                    case 72: // 芬．布蘭科
                    {
                        // 檢查是否為勢力已經滅亡
                        if ( m_sailorData[ i ].m_Team == TEAM_JOINABLE )
                        {
                            std::string title2( "是否邀請" );
                            tinyfd_messageBox( title2.c_str(), SAILOR_NAME[ i ].c_str(), "ok", "error", 0 );
                        }
                    }
                    break;
                    }
                }
            }
        }
    }

    void Console::LoadCities()
    {
        m_stream->Seek( CITY_OFFSET );
        for ( int i = 0; i < CITY_NUMBER; ++i )
        {
            m_cityData[ i ].m_CityId = i;
            m_cityData[ i ].ReadFromStream( m_stream );
        }
    }

    void Console::LoadItems()
    {
        // char myOwnValue = 0x0C;
        m_stream->Seek( ITEM_OFFSET );
        for ( int i = 0; i < ITEM_NUMBER; ++i )
        {
            m_itemData[ i ].m_itemId = i;
            m_itemData[ i ].ReadFromStream( m_stream );
        }
    }
} // namespace Dk4
