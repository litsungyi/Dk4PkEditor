// Dk4PkEditor.cpp : Defines the entry point for the console application.
//

#include "Pch.h"

#include <Windows.h>
#include <codecvt>
#include <conio.h>
#include <iostream>
#include <locale>
#include <string>
#include "TinyFileDialogs\tinyfiledialogs.h"
#include "Application.h"

int main( int argc, char* argv[] )
{
    Dk4::Console console;
    return console.Run();
    
    /*
    int myTeamId = 0;
    char input = 0;
    Kafka::FileWriter saveFile;

    const size_t BUFFER_SIZE = 64;
    char* buffer = new char[ BUFFER_SIZE ];
    buffer = static_cast< char* >( SecureZeroMemory( buffer, BUFFER_SIZE ) );

    // 開啟紀錄檔
    cout << "選擇開啟的檔案 0-7: ";
    cin >> input;

    saveFile.OpenFile( atoi( &input ) );

    // 檢查紀錄檔是否開啟
    if ( saveFile.IsOpened() )
    {
        cout << "File opened" << endl;

        size_t readBytes;

        readBytes = saveFile.GetByte( 0, VALIDATE_STRING_SIZE, buffer, BUFFER_SIZE );

        // 驗證是否為大航海四紀錄檔
        if ( 0 == readBytes )
        {
            cout << "Read nothing!" << endl;
        }
        else
        {
            if ( 0 == strcmp( buffer, VALIDATE_STRING.c_str() ) )
            {
                // 驗證通過
                cout << "File validate success!" << endl;

                // 取得主角資料
                SailorData sailorLeader;
                sailorLeader.Init( -1, &saveFile, SAILOR_LEADER_OFFSET );

                myTeamId = sailorLeader.m_Team;

                cout << "主角的勢力為：" << TEAM_NAME[ myTeamId ] << endl;

                // 取得海員資料
                SailorData* sailorData = new SailorData[ SAILOR_NUMBER ];

                for ( int i = 0, offset = SAILOR_OFFSET; i < SAILOR_NUMBER; ++i, offset += SAILOR_DATA_SIZE )
                {
                    sailorData[ i ].Init( i, &saveFile, offset );

                    cout << SAILOR_NAME[ i ] << " 目前為 " << TEAM_NAME[ sailorData[ i ].m_Team ] << " 的成員" << endl;

                    if ( i <= NON_NPC_SAILOR_NUMBER )
                    {
                        // 檢查是否為本勢力海員
                        if ( sailorData[ i ].m_Team != myTeamId )
                        {
                            cout << "是否邀請 " << SAILOR_NAME[ i ] << " 加入我軍？ (y/n)";
                            cin >> input;
                            if ( 'y' == input )
                            {
                                // 邀請加入
                                saveFile.SetByte( offset, 1, &myTeamId, sizeof( int ) );
                            }
                        }
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
                            if ( sailorData[ i ].m_Team == TEAM_JOINABLE )
                            {
                                cout << "是否邀請 " << SAILOR_NAME[ i ] << " 加入我軍？ (y/n)";
                                cin >> input;
                                if ( 'y' == input )
                                {
                                    // 邀請加入
                                    saveFile.SetByte( offset, 1, &myTeamId, sizeof( int ) );
                                }
                            }
                        }
                        break;
                        }
                    }
                }

                // 取得港口資料
                CityData* cityData = new CityData[ CITY_NUMBER ];

                for ( int i = 0, offset = CITY_OFFSET; i < CITY_NUMBER; ++i, offset += CITY_DATA_SIZE )
                {
                    cityData[ i ].Init( i, &saveFile, offset );

                    cout << CITY_NAME[ i ] << " [商:" << cityData[ i ].m_Bussiness
                        << "/武:" << cityData[ i ].m_Military << "]" << endl;

                    for ( int j = 0; j<MAX_TEAM_IN_CITY; ++j )
                    {
                        if ( 0 <= cityData[ i ].m_MarketShare[ j ].TeamId &&
                            ( TEAM_NUMBER - 2 ) > cityData[ i ].m_MarketShare[ j ].TeamId )
                        {
                            int marketShare = cityData[ i ].m_MarketShare[ j ].MarketShare;
                            cout << TEAM_NAME[ cityData[ i ].m_MarketShare[ j ].TeamId ] <<
                                marketShare << "% ";
                        }
                    }
                    cout << endl;

                    if ( i > 50 )
                    {
                        cout << endl;
                    }

                    for ( int j = 0; j < MAX_SPECIALTY; ++j )
                    {
                        if ( 0 != cityData[ i ].m_SpecialProduct[ j ].Price )
                        {
                            if ( cityData[ i ].m_SpecialProduct[ j ].Tradeable )
                            {
                                saveFile.SetByte( cityData[ i ].m_Offset + CD_OFFSET_SPECIALTY + ( CD_LENGTH_SPECIALTY * j ) + SPECIALTY_STATUS,
                                    1,
                                    &SPECIALTY_TRADEABLE,
                                    sizeof( SPECIALTY_TRADEABLE ) );
                            }
                            cout << cityData[ i ].m_SpecialProduct[ j ].Price << " x" <<
                                cityData[ i ].m_SpecialProduct[ j ].Amount << endl;
                        }
                    }
                }

                // 開闢新港
                for ( int i = 0; i < NEW_CITY_NUMBER; ++i )
                {
                    char newCityOpend;
                    size_t offset = NEW_CITY_OFFSET[ i ];

                    saveFile.GetByte( NEW_CITY_OFFSET[ i ], 1, &newCityOpend, sizeof( newCityOpend ) );
                    cout << "港口 " << NEW_CITY_NAME[ i ] << " (" << static_cast< int >( newCityOpend ) << ")" << endl;
                    if ( CITY_OPENED != newCityOpend )
                    {
                        // 檢查港口是否已經開港
                        cout << "是否開闢港口 " << NEW_CITY_NAME[ i ] << " ？ (y/n)";
                        cin >> input;
                        if ( 'y' == input )
                        {
                            // 開闢港口
                            saveFile.SetByte( offset, 1, &CITY_OPENED, sizeof( CITY_OPENED ) );
                            saveFile.SetByte( offset + CD_LENGTH_FACILITY, 2, &CITY_HOUSE_ALL, sizeof( CITY_HOUSE_ALL ) );
                        }
                    }
                }

                char myOwnValue = 0x0C;
                char value;
                for ( int i = 0, offset = ITEM_OFFSET; i < ITEM_NUMBER; ++i, offset += sizeof( short ) )
                {
                    saveFile.GetByte( offset + sizeof( char ), sizeof( char ), &value, sizeof( value ) );
                    cout << "是否拿取道具 " << ITEM_NAME[ i ] << " ？ (y/n)";
                    cin >> input;
                    if ( 'y' == input )
                    {
                        saveFile.SetByte( offset + sizeof( char ), sizeof( char ), &myOwnValue, sizeof( myOwnValue ) );
                    }
                }

                delete[] sailorData;
                delete[] cityData;
            }
        }
    }
    else
    {
        cout << "File closed" << endl;
    }

    saveFile.CloseFile();
    _getch();

    delete[] buffer;
    */

    return 0;
}
