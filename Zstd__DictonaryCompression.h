#pragma once

#include "Zstandard__settings.h"   

#include <iostream>
#include <string>   
#include <vector>   


class Zstd__DictonaryCompression
{

public:


    Zstd__DictonaryCompression()
    {
        cctx = ZSTD_createCCtx();        //Создаем контекст сжатия.
        dctx = ZSTD_createDCtx();        //Создаем контекст разжатия.
    }

    ~Zstd__DictonaryCompression()
    {
        ZSTD_freeCCtx(cctx);             //Освобождаем контекст сжатия. 

        for (size_t i=0; i < vec_Dicts.size(); i++)
        {
            ZSTD_freeCDict(vec_Dicts[i].CDict_p);
            ZSTD_freeDDict(vec_Dicts[i].DDict_p);
        }

    }



public:

    enum class result_flag : int
    {
        OK = 1,
        Zstadart_error = 2,
        bad_alloc = 3,
        non_existent_dict_name = 4,
        DictonaryIncorrect_or_Small = 5, 
    };




public:

    const result_flag run_Compress(const int level_compressed, const char* PointerToData_WhichShouldBe_Compressed, const size_t DataSize_WhichShouldBe_Compressed, std::string& string_CompressedResult)
    {

        //-----------------------------------------------------------------------------------------------------
        size_t garant_MaxSize_for_CompressedResult = ZSTD_compressBound(DataSize_WhichShouldBe_Compressed);   //Вообщем функция принимает исходный размер данных, который нужно сжать и возвращает теоретически Максимальный размер после сжатия, но размер после сжатия может быть в итоге и меньше, как я понял, это некая функция подскзка для более оптимальнйо работы для дальнейших функций.

        const size_t size_BeforeResize = string_CompressedResult.size();

        try { string_CompressedResult.resize(size_BeforeResize + garant_MaxSize_for_CompressedResult); } catch (const std::bad_alloc& e) { ErrorName = e.what(); ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters); ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters); return result_flag::bad_alloc; }  //Выделим в конец место для записи сжатых данных.
        //-----------------------------------------------------------------------------------------------------




        //-----------------------------------------------------------------------------------------------------
        const size_t Finaly_ComressedSize =  ZSTD_compress_usingCDict(cctx, &string_CompressedResult[size_BeforeResize], string_CompressedResult.size(), PointerToData_WhichShouldBe_Compressed, DataSize_WhichShouldBe_Compressed, current_Dict_Compress);
        //-----------------------------------------------------------------------------------------------------



        //-------------------------------------------------------------------------------------------------------------------
        unsigned int status_error = ZSTD_isError(Finaly_ComressedSize);  //Проверяем последний вызов на наличие ошибки.

        if (status_error != 0)
        {
            ErrorName = "ZSTD_compress: " + std::string(ZSTD_getErrorName(Finaly_ComressedSize));

            string_CompressedResult.resize(size_BeforeResize);     //Вовзратим размер, который передал Пользовтаель
            string_CompressedResult.shrink_to_fit();

            ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);
            ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters);

            return result_flag::Zstadart_error;
        }
        else
        {
            //finaly_comressed_size = теперь тут кол-во Сжатых байт. Сжатые данные включают в себя, как сам служебный заголовок, который содержит информаци, как о сжатых данных, так и о не сжатых, так и самые Сжатые Полезные даные, возможно после них, еще какой то завершающий зголовок. Вот тут более подробно: https://github.com/facebook/zstd/blob/dev/doc/zstd_compression_format.md


            string_CompressedResult.resize(size_BeforeResize + Finaly_ComressedSize);              //Сократим размер до актуального значения.
            string_CompressedResult.shrink_to_fit();

            return result_flag::OK;
        }
        //--------------------------------------------------------------------------------------------------------------------

    }

    inline const result_flag set__param_Compress(const ZSTD_cParameter param, const int param_value)
    {

        size_t result = ZSTD_CCtx_setParameter(cctx, param, param_value);


        //---------------------------------------------------
        //Параметры и их описание, которые принимает функция ZSTD_CCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_cParameter.
        //Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_cParameter.

        /*
        ZSTD_cParam_getBounds - данная функция принимает один из параметров "ZSTD_cParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_CCtx_setParameter" третьим "param_value" параметром.
        ZSTD_bounds ZSTD_bounds_1 = ZSTD_cParam_getBounds(ZSTD_c_nbWorkers);
        std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
        std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

        Проверку на ошибку после вызова через  ZSTD_isError.
        */
        //---------------------------------------------------


        //-------------------------------------------------1-ZSTD_c_compressionLevel:начало-------------------------------------------
        unsigned int status_error = ZSTD_isError(result);

        if (status_error != 0)
        {
            ErrorName = "ZSTD_CCtx_setParameter: " + std::string(ZSTD_getErrorName(result));

            ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);
            ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters);

            return result_flag::Zstadart_error;
        }
        //-------------------------------------------------1-ZSTD_c_compressionLevel:конец-------------------------------------------


        return result_flag::OK;

    }

    inline const result_flag ResetContext_Compress(const ZSTD_ResetDirective reset_flag)
    {

        size_t result = ZSTD_CCtx_reset(cctx, reset_flag);


        //-------------------------------------------------------------
        unsigned int status_error = ZSTD_isError(result);

        if (status_error != 0)
        {
            ErrorName = "ZSTD_CCtx_reset: " + std::string(ZSTD_getErrorName(result));

            return result_flag::Zstadart_error;
        }
        //-------------------------------------------------------------


        return result_flag::OK;
    }



    const result_flag run_Uncompress(std::string& string_Result_UcompressedData, const char* Pointer_to_CompressedData, const size_t size_CompressedData)
    {

        //-----------------------------------------------------------------------------------------------------
        //Вообщем:

        //Короче, когда Zstd - Сжимает с помощью функции ZSTD_compress() данные - в начала Сжатых данных она доабвляет свой Zstd`ий заголовок, а потом идут уже сами сжатые данные. Соотвесвенно структура "Заголовок-сжатые данные" - НАЗЫВАЕТСЯ frame`ом.

        //-п.1: Соовтетвенно Заголовок Zstd имеет какой то размер. Размер заголовка можно получить с помощью функции ZSTD_findFrameCompressedSize(), которая принимает на вход указатель на Начало frame`а и возвращает размер этого Фрейма в байтах.
        //-п.2: Я не разбирался какая информация содержится в заголовке Zstd, но там есть точно информация о размере данных до сжатия. Этот размер позволяет получится функция ZSTD_getFrameContentSize() - которая принимает на вход указатель на Начало frame`а или на начало Заголовка и возвращает размер данных До сжатия данного frame`а, который был до сжатия. САМ РАЗМЕР ДАННЫХ ДО сжатия НУЖЕН ФУНКЦИИ ДЭКОМПРЕССИИ "ZSTD_decompress".

        //-п.3: Соответсвенно, если указатель на сжатые данные - указывает на несколко обьеденых frame`ов, то есть несколько обьеденненых сжатых данных по одиночке с помощью функции ZSTD_compress() - обьеденнуную через обычную контакеннацию - std::string total = string_compress_1 + string_compress_2 - то такая строка представляет из себя просто послеотвальеность frame`ов и чтобы определить суммарный размер данных, который были до сжатия, нужно, как понятно - вставать в начало Каждого Фрейма и вызывать функцию ZSTD_getFrameContentSize() - которая будет возвращать размер сжатых даных до сжатия. Вопрос в том, как узнать где начинается каждый frame - ну это можно сделать спомощью уже описанной выше функции  ZSTD_findFrameCompressedSize() - которая возвращает размер всего фрейма, то есть вставем в самый первый фрейм - это будет самый первый байт, узнаем размер этого фрейма и смещаемся на его размер - проверяем не выходим ли мы за размер указателя на сжатые данные и идем дальше.
        //-----------------------------------------------------------------------------------------------------



        //---------------------------------------------------------------------------
        ZSTD_DCtx_reset(dctx, ZSTD_reset_session_only);         //Я не уверен, что нужно сбрасывать сессионый параметр, каждый раз новом расжатия, но пусть на всякий случай будет.
        //---------------------------------------------------------------------------


        //---------------------------------
        unsigned long long total_BeforeComressSize = 0;
        size_t total_FramesSize = 0;
        //---------------------------------


        //------------------------------------------------------------------------------------------------------------------------------------------------------
        for (;;)
        {
            //Карусель, карусель, начинает рассказ, прокатись на нашей карусееели.


                //------------------------------------------------------------------Получаем размер фрейма:Начало-----------------------------------------------------------------------
                const size_t Frame_size = ZSTD_findFrameCompressedSize(Pointer_to_CompressedData + total_FramesSize, size_CompressedData);  //Получим размер очередного Фрейма.

                unsigned int status_error = ZSTD_isError(Frame_size);    //Проверяем вызов ZSTD_findFrameCompressedSize на наличии ошибки.

                if (status_error != 0)
                {
                    ErrorName = "ZSTD_findFrameCompressedSize: " + std::string(ZSTD_getErrorName(Frame_size));

                    ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);
                    ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters);

                    return result_flag::Zstadart_error;
                }


                //------------------------------------------------------------------Получаем размер фрейма:Конец-----------------------------------------------------------------------




                //-------------------------------------------------------------Получаем размер Не сжатых данных:Начало-----------------------------------------------------------------------
                const unsigned long long BeforeComressSize = ZSTD_getFrameContentSize(Pointer_to_CompressedData + total_FramesSize, size_CompressedData);  //Получаем размер несжатых данных каждого фрейма

                total_BeforeComressSize = total_BeforeComressSize + BeforeComressSize;   //Суммируем.


                if (total_BeforeComressSize == ZSTD_CONTENTSIZE_UNKNOWN || total_BeforeComressSize == ZSTD_CONTENTSIZE_ERROR)
                {
                    ErrorName = "ZSTD_getFrameContentSize: ZSTD_CONTENTSIZE_UNKNOWN or ZSTD_CONTENTSIZE_ERROR";

                    ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);
                    ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters);

                    return result_flag::Zstadart_error;
                }
                //-------------------------------------------------------------Получаем размер Не сжатых данных:Конец-----------------------------------------------------------------------




                total_FramesSize = total_FramesSize + Frame_size;  //Получаем смещение указывающее на байт следующий сразу за Данным Фреймом сжатых данных, то есть на следующую порцию сжатыых данных, если они там есть и есть не вышли за пределы.




                //--------------------------------------------------------
                if (total_FramesSize >= size_CompressedData)
                {
                    //Значит уже вышли за пределы переданные Пользователем или отоработали ровно необходимое кол-во фреймов.

                    break;
                }
                //--------------------------------------------------------

        }
        //------------------------------------------------------------------------------------------------------------------------------------------------------





        //------------------------------------------------------------------------------Расжимаем данные:Начало----------------------------------------------------------------------

        const size_t size_BeforeResize = string_Result_UcompressedData.size();


        try { string_Result_UcompressedData.resize(size_BeforeResize + total_BeforeComressSize); } catch (const std::bad_alloc& e) { ErrorName = e.what(); return result_flag::bad_alloc; }   //Выделяем дополнительно память точно под размер данных, которые мы Сжимали, то есть это суммарный размер данных до сжатия.


        const size_t Finaly_UnComressedSize = ZSTD_decompress_usingDDict(dctx, &string_Result_UcompressedData[size_BeforeResize], total_BeforeComressSize, Pointer_to_CompressedData, size_CompressedData, current_Dict_Uncompress);



        //------------------------------------------------------------------------------
        unsigned int status_error = ZSTD_isError(Finaly_UnComressedSize);    //Проверяем последний вызов на наличие ошибки.

        if (status_error != 0)
        {
            ErrorName = "ZSTD_decompress: " + std::string(ZSTD_getErrorName(Finaly_UnComressedSize));

            string_Result_UcompressedData.resize(size_BeforeResize);
            string_Result_UcompressedData.shrink_to_fit();

            ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);
            ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters);

            return result_flag::Zstadart_error;
        }
        else
        {
            //Finaly_UnComressedSize - теперь тут размер в байтах Расжатых данных. Должен совпадать с "size_DataBeforeCompression".

            return result_flag::OK;
        }
        //------------------------------------------------------------------------------

        //------------------------------------------------------------------------------Расжимаем данные:Конец----------------------------------------------------------------------



        return result_flag::OK;

    }

    inline const result_flag set__param_Uncompress(const ZSTD_dParameter param, const int param_value)
    {

        size_t result = ZSTD_DCtx_setParameter(dctx, param, param_value);


        //---------------------------------------------------
        //Параметры и их описание, которые принимает функция ZSTD_CCtx_setParameter можно найти или в документации на странице: https://facebook.github.io/zstd/zstd_manual.html   - смотреть enum ZSTD_dParameter.
        //Или в исxодном файле zstd.h - смотреть тот же enum ZSTD_cParameter.

        /*
        ZSTD_dParam_getBounds - данная функция принимает один из параметров "ZSTD_dParameter" и возвращает его минимальное и максимальное значение, которое предается в функцию "ZSTD_DCtx_setParameter" третьим "param_value" параметром.
        ZSTD_bounds ZSTD_bounds_1 = ZSTD_dParam_getBounds(ZSTD_d_windowLogMax);
        std::cout << "минимальные значение параметра:" << ZSTD_bounds_1.lowerBound << std::endl;
        std::cout << "максимальное значение параметра:" << ZSTD_bounds_1.upperBound << std::endl;

        Проверку на ошибку после вызова через  ZSTD_isError.
        */
        //---------------------------------------------------


        //-------------------------------------------------1-ZSTD_c_compressionLevel:начало-------------------------------------------
        unsigned int status_error = ZSTD_isError(result);

        if (status_error != 0)
        {
            ErrorName = "ZSTD_CCtx_setParameter: " + std::string(ZSTD_getErrorName(result));

            ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);
            ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters);

            return result_flag::Zstadart_error;
        }
        //-------------------------------------------------1-ZSTD_c_compressionLevel:конец-------------------------------------------


        return result_flag::OK;

    }

    inline const result_flag ResetContext_Uncompress(const ZSTD_ResetDirective reset_flag)
    {

        size_t result = ZSTD_DCtx_reset(dctx, reset_flag);


        //-------------------------------------------------------------
        unsigned int status_error = ZSTD_isError(result);

        if (status_error != 0)
        {
            ErrorName = "ZSTD_CCtx_reset: " + std::string(ZSTD_getErrorName(result));

            return result_flag::Zstadart_error;
        }
        //-------------------------------------------------------------


        return result_flag::OK;
    }




    const result_flag set_Dict_Usage(const char* Dict_name)
    {

        for (size_t i = 0; i < vec_Dicts.size(); i++)
        {
            if (vec_Dicts[i].Dict_name.compare(Dict_name) == 0)
            {
                current_Dict_Compress   = vec_Dicts[i].CDict_p;
                current_Dict_Uncompress = vec_Dicts[i].DDict_p;

                ZSTD_CCtx_reset(cctx, ZSTD_reset_session_only);   //При изменении словаря сбрасываем на всякий случай сессионые куки.
                ZSTD_DCtx_reset(dctx, ZSTD_reset_session_only);   //При изменении словаря сбрасываем на всякий случай сессионые куки.

                return result_flag::OK;
            }
        }


        ErrorName = "set_Dict_Usage: non-existent dictionary name";

        return result_flag::non_existent_dict_name;
    }

    const result_flag add__Dictonary(const char* Name_Dict, const std::vector<std::string>vec_Samples, const int Compressed_Level)
    {

        try
        {

            //----------------------------------------------------
            //Так как "ZDICT_trainFromBuffer" принимает примеры для словарая в едином массиве, то перекопируем приверы из "vec_Samples" в строку.

            std::string buffer_Samples; size_t TotalSize = 0;
            std::vector<size_t>vec_NumSamples; vec_NumSamples.resize(vec_Samples.size());


            for (size_t i = 0; i < vec_Samples.size(); i++)
            {
                TotalSize = TotalSize + vec_Samples[i].size();
            }


            buffer_Samples.reserve(TotalSize);

            for (size_t i = 0; i < vec_Samples.size(); i++)
            {
                buffer_Samples.append(vec_Samples[i]);
                vec_NumSamples[i] = vec_Samples.size();
            }
            //----------------------------------------------------



            //************************************************************************1-ПОЛУЧАЕМ ТРЕНИРОВАННЫЙ БУФФЕР:НАЧАЛО************************************************************************************************


            std::string buff_for_TrainedDict; buff_for_TrainedDict.resize(100);      //Сюда функция запишет натренированные данные.


            //ИЛИ Я ЧЕГО-ТО НЕ ПОНЯЛ ИЛИ ЭТО КАКАЯ ТО ХЕРНЯ: ZDICT_trainFromBuffer требует на вход буффер в который она поместит тренированные данные, НО Я КАКИМ ХРЕНОМ ЗНАЮ, какой нужен размер буффера для этого ?? То есть тупо придется в цикле вызывать функцию и подбирать размер.


            for (;;)
            {

                size_t dictSize = ZDICT_trainFromBuffer(&buff_for_TrainedDict[0], buff_for_TrainedDict.size(), buffer_Samples.c_str(), vec_NumSamples.data(), vec_Samples.size());


                //-----------------------------------------------------------------------------------------------------------------
                unsigned int status_error = ZSTD_isError(dictSize);


                if (status_error != 0)
                {

                    if (ZSTD_getErrorName(dictSize) == "Destination buffer is too small")
                    {
                        //Значит размер выделнного буффера все еще мал, увеличим и попробуем заново:

                        buff_for_TrainedDict.resize(buff_for_TrainedDict.size() + 1000);

                        continue;
                    }
                    else
                    {
                        ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);
                        ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters);

                        ErrorName = "ZDICT_trainFromBuffer: " + std::string(ZSTD_getErrorName(dictSize));

                        if (ZSTD_getErrorName(dictSize) == "Src size is incorrect")
                        {
                            ErrorName = "ZDICT_trainFromBuffer: DictonaryIncorrect_or_Small";
                            
                            return result_flag::DictonaryIncorrect_or_Small;
                        }

                        return result_flag::Zstadart_error;
                    }

                }
                else
                {
                    //dictSize - теперь тут актуальный размер тренированных данных. Приведем размер "buff_for_TrainedDict" в актуальное состояние:

                    buff_for_TrainedDict.resize(dictSize);

                    break;  //Значит размер буффера удовлетворил функцию, выходим из цикла подбора.
                }
                //-----------------------------------------------------------------------------------------------------------------
            }

            //************************************************************************1-ПОЛУЧАЕМ ТРЕНИРОВАННЫЙ БУФФЕР:НАЧАЛО************************************************************************************************






            //*******************************************************************2-СОЗДАЕМ СЛОВАРЬ ДЛЯ СЖАТИЯ ИЗ ТРЕНИРОВОЧНОГО БУФФЕРА:НАЧАЛО*******************************************************************************************

            ZSTD_CDict* cdict = ZSTD_createCDict(buff_for_TrainedDict.c_str(), buff_for_TrainedDict.size(), Compressed_Level);

            if (cdict == 0)
            {
                ErrorName = "ZSTD_createCDict: return NULL pointer";

                ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);
                ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters);

                return result_flag::Zstadart_error;
            }

            //*******************************************************************2-СОЗДАЕМ СЛОВАРЬ ДЛЯ СЖАТИЯ ИЗ ТРЕНИРОВОЧНОГО БУФФЕРА:КОНЕЦ*******************************************************************************************




            //*******************************************************************3-СОЗДАЕМ Сразу СЛОВАРЬ ДЛЯ РАЗЖАТИЯ ИЗ ТРЕНИРОВОЧНОГО БУФФЕРА:НАЧАЛО*******************************************************************************************

            ZSTD_DDict* ddict = ZSTD_createDDict(buff_for_TrainedDict.c_str(), buff_for_TrainedDict.size());

            if (cdict == 0)
            {
                ErrorName = "ZSTD_createDDict: return NULL pointer";

                ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);
                ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters);

                return result_flag::Zstadart_error;
            }

            //*******************************************************************3-СОЗДАЕМ Сразу СЛОВАРЬ ДЛЯ РАЗЖАТИЯ ИЗ ТРЕНИРОВОЧНОГО БУФФЕРА:КОНЕЦ*******************************************************************************************



            vec_Dicts.emplace_back(cdict, ddict, Name_Dict);



            return result_flag::OK;

        }
        catch (const std::bad_alloc& e)
        {
            ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);
            ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters);

            ErrorName = e.what(); return  result_flag::bad_alloc;
        }
    }




    const std::string& get__ErrorName() const
    {
        return ErrorName;
    }


private:

    //-------------------------
    ZSTD_CCtx* cctx;
    ZSTD_DCtx* dctx;
    //-------------------------
    
    //-------------------------
    ZSTD_CDict* current_Dict_Compress = 0;
    ZSTD_DDict* current_Dict_Uncompress = 0;
    //-------------------------


    //---------------------------------------
    struct Dict_struct
    {
        ZSTD_CDict* CDict_p = 0;
        ZSTD_DDict* DDict_p = 0;

        std::string Dict_name;


        Dict_struct() = default;
        Dict_struct(ZSTD_CDict* CDict_p_, const std::string& Dict_name_) : CDict_p(CDict_p_), Dict_name(Dict_name_) {}
        Dict_struct(ZSTD_DDict* DDict_p_, const std::string& Dict_name_) : DDict_p(DDict_p_), Dict_name(Dict_name_) {}
        Dict_struct(ZSTD_CDict* CDict_p_, ZSTD_DDict* DDict_p_, const std::string& Dict_name_) : DDict_p(DDict_p_), CDict_p(CDict_p_), Dict_name(Dict_name_) {}
    };
    
    std::vector<Dict_struct>vec_Dicts;
    //---------------------------------------




    std::string ErrorName;

};
